#include <Headers/Calculator.h>
#include <Headers/OperationsEnum.h>

#include <ui_widget.h>

#include <cmath>


Calculator::Calculator(QWidget *parent)
    : QWidget{parent}, displayedText{"0"}, lastOperation{Operations::UNKNOWN_FIRST}, activeOperation{Operations::UNKNOWN_FIRST}, number1{0}, number2{0}, actualNumber{&number1},
      is1FloatingPoint{false}, is2FloatingPoint{false}
{
    createButtons();
    setUpLayouts();
    setUpButtons(*gridLayout);
    connectSignals();
}

void Calculator::handleNumberButton()
{
    auto str = std::to_string(*actualNumber);
    str.erase(str.find_last_not_of('0'), std::string::npos);
    if(str.length() < 16){
        auto bt = dynamic_cast<NButton*>(sender());
        std::uint8_t num = 0;
        if(bt)
            num = bt->getNumber();

        if(activeOperation == Operations::UNKNOWN_FIRST){
            actualNumber = &number1;
        }
        if((actualNumber == &number1 && is1FloatingPoint) || (actualNumber == &number2 && is2FloatingPoint)){
            str.push_back(num);
            *actualNumber = std::stold(str);
        }
        else{
            *actualNumber *= 10;
            *actualNumber += num;
        }
        lastOperation = Operations::ADD_NUMBER;
        updateDisplayedString();
    }
    else{
        //display information about max allowed number length
    }

}

void Calculator::handleOperationButton()
{
    switch(lastOperation){
    case Operations::CLEAR_ALL:
        number1 = number2 = 0;
        actualNumber = &number1;
        is1FloatingPoint = is2FloatingPoint = false;
        activeOperation = Operations::UNKNOWN_FIRST;
        break;
    case Operations::CLEAR_LAST:
        if((*actualNumber - std::floor(*actualNumber)) == 0){
            *actualNumber /= 10;
            *actualNumber = std::floor(*actualNumber);
        }
        else{

        }
        break;
    case Operations::CALCULATE:
        switch(activeOperation){
        case Operations::ADD:
            number1 = number1 + number2;
            break;
        case Operations::SUBSTRACT:
            number1 = number1 - number2;
            break;
        case Operations::MULTIPLY:
            number1 = number1 * number2;
            break;
        case Operations::DIVIDE:
            number1 = number1 / number2;
            break;
        default:
            //do nothing
            break;
        }
        number2 = 0;
        actualNumber = &number1;
        activeOperation = Operations::UNKNOWN_FIRST;
        break;
    case Operations::INSERT_DOT:
        if(actualNumber == &number1){
            is1FloatingPoint = true;
        }
        else{
            is2FloatingPoint = true;
        }
        break;
    case Operations::ADD:
        activeOperation = lastOperation;
        actualNumber = &number2;
        break;
    case Operations::SUBSTRACT:
        activeOperation = lastOperation;
        actualNumber = &number2;
        break;
    case Operations::MULTIPLY:
        activeOperation = lastOperation;
        actualNumber = &number2;
        break;
    case Operations::DIVIDE:
        activeOperation = lastOperation;
        actualNumber = &number2;
        break;
    }

    updateDisplayedString();
}

void Calculator::createButtons(){
    //Numbers
    for(std::uint8_t i = 0; i <= 9; ++i){
        NumberButtons[i] = new NButton{i, this};
    }

    //Operations
    buttonAdd = new QPushButton{QString{"+"}, this};
    buttonSubstract = new QPushButton{QString{"-"}, this};
    buttonMultiply = new QPushButton{QString{"*"}, this};
    buttonDivide = new QPushButton{QString{"/"}, this};

    //Other
    buttonRemoveCharacter = new QPushButton{QString{"<-"}, this};
    buttonClear = new QPushButton{QString{"C"}, this};
    buttonCalculate = new QPushButton{QString{"="}, this};
    buttonDot = new QPushButton{QString{"."}, this};

    auto font = NumberButtons[0]->font();
    font.setPointSize(16);

    auto lista = children();
    for(auto& child : lista){
        auto button = dynamic_cast<QPushButton*>(child);
        if(button != nullptr){
            button->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
            button->setFont(font);
        }
    }
}


/*
 *<- / * -
 * 7 8 9 +
 * 4 5 6 +
 * 1 2 3 =
 * C 0 . =
*/
void Calculator::setUpButtons(QGridLayout& grid){
    grid.addWidget(buttonRemoveCharacter, 0, 0);
    grid.addWidget(buttonDivide, 0, 1);
    grid.addWidget(buttonMultiply, 0, 2);
    grid.addWidget(buttonSubstract, 0, 3);

    NumberButtons[7]->setUp(&grid, 1, 0);
    NumberButtons[8]->setUp(&grid, 1, 1);
    NumberButtons[9]->setUp(&grid, 1, 2);
    grid.addWidget(buttonAdd, 1, 3, 2, 1);

    NumberButtons[4]->setUp(&grid, 2, 0);
    NumberButtons[5]->setUp(&grid, 2, 1);
    NumberButtons[6]->setUp(&grid, 2, 2);
    //grid.addWidget(buttonAdd, 2, 3);

    NumberButtons[1]->setUp(&grid, 3, 0);
    NumberButtons[2]->setUp(&grid, 3, 1);
    NumberButtons[3]->setUp(&grid, 3, 2);
    grid.addWidget(buttonCalculate, 3, 3, 2, 1);

    grid.addWidget(buttonClear, 4, 0);
    NumberButtons[0]->setUp(&grid, 4, 1);
    grid.addWidget(buttonDot, 4, 2);
    //grid.addWidget(buttonCalculate, 4, 3);
}

void Calculator::connectSignals()
{
    //Number Buttons
    for(const auto& nb : NumberButtons){
        QObject::connect(nb, &QAbstractButton::clicked, this, &Calculator::handleNumberButton);
    }

    //Operations Buttons
    QObject::connect(buttonAdd, &QAbstractButton::clicked, [this](){ lastOperation = Operations::ADD, handleOperationButton();});
    QObject::connect(buttonSubstract, &QAbstractButton::clicked, [this](){ lastOperation = Operations::SUBSTRACT, handleOperationButton();});
    QObject::connect(buttonMultiply, &QAbstractButton::clicked, [this](){ lastOperation = Operations::MULTIPLY, handleOperationButton();});
    QObject::connect(buttonDivide, &QAbstractButton::clicked, [this](){ lastOperation = Operations::DIVIDE, handleOperationButton();});
    QObject::connect(buttonRemoveCharacter, &QAbstractButton::clicked, [this](){ lastOperation = Operations::CLEAR_LAST, handleOperationButton();});
    QObject::connect(buttonClear, &QAbstractButton::clicked, [this](){ lastOperation = Operations::CLEAR_ALL, handleOperationButton();});
    QObject::connect(buttonCalculate, &QAbstractButton::clicked, [this](){ lastOperation = Operations::CALCULATE, handleOperationButton();});
    QObject::connect(buttonDot, &QAbstractButton::clicked, [this](){ lastOperation = Operations::INSERT_DOT, handleOperationButton();});
}

void Calculator::setUpLayouts()
{
    setMinimumSize(400, 300);

    verticalLayout = new QVBoxLayout;
    gridLayout = new QGridLayout;
    gridLayout->setSizeConstraint(QLayout::SetNoConstraint);

    textField = new QLineEdit;
    textField->setText(QString{""});
    textField->setReadOnly(true);
    textField->setMinimumHeight(60);
    textField->setAlignment(Qt::AlignmentFlag::AlignRight);
    auto font = textField->font();
    font.setPixelSize(26);
    textField->setFont(font);

    verticalLayout->addWidget(textField);
    verticalLayout->addLayout(gridLayout);

    setLayout(verticalLayout);
}

void Calculator::updateDisplayedString()
{
    displayedText.clear();
    char * num1, * num2;

    if((number1 - std::floor(number1)) == 0){
        std::string n1 = std::to_string(number1);
        n1.erase(n1.find('.'), std::string::npos);
        num1 = const_cast<char *>(n1.c_str());
    }
    else{
        num1 = const_cast<char *>(std::to_string(number1).c_str());
    }

    displayedText.append(num1);

    if(activeOperation != Operations::UNKNOWN_FIRST){

        displayedText.append(" ");
        displayedText.append(operationToChar(activeOperation));
        displayedText.append(" ");

        if((number2 - std::floor(number2)) == 0){
            std::string n2 = std::to_string(number2);
            n2.erase(n2.find('.'), std::string::npos);
            num2 = const_cast<char *>(n2.c_str());
        }
        else{
            num2 = const_cast<char *>(std::to_string(number2).c_str());
        }

        if(activeOperation != lastOperation)
            displayedText.append(num2);

    }

    textField->setText(displayedText);
}

