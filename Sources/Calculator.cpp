#include <Headers/Calculator.h>
#include <ui_widget.h>


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createButtons();
    setMinimumSize(400, 300);

    verticalLayout = new QVBoxLayout;
    //verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridLayout = new QGridLayout;
    gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    setUpButtons(*gridLayout);

    textField = new QLineEdit;
    textField->setText(QString{"example text"});
    textField->setReadOnly(true);
    textField->setMinimumHeight(60);
    textField->setAlignment(Qt::AlignmentFlag::AlignRight);

    verticalLayout->addWidget(textField);
    verticalLayout->addLayout(gridLayout);

    setLayout(verticalLayout);
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

