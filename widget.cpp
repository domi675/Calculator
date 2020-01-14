#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
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

void Widget::createButtons(){
    //Numbers
    buttonZero = new QPushButton(QString{"0"}, this);
    buttonOne = new QPushButton(QString{"1"}, this);
    buttonTwo = new QPushButton(QString{"2"}, this);
    buttonThree = new QPushButton(QString{"3"}, this);
    buttonFour = new QPushButton(QString{"4"}, this);
    buttonFive = new QPushButton(QString{"5"}, this);
    buttonSix = new QPushButton(QString{"6"}, this);
    buttonSeven = new QPushButton(QString{"7"}, this);
    buttonEight = new QPushButton(QString{"8"}, this);
    buttonNine = new QPushButton(QString{"9"}, this);

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

    auto font = buttonZero->font();
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
 * 0 0 . =
*/
void Widget::setUpButtons(QGridLayout& grid){
    grid.addWidget(buttonRemoveCharacter, 0, 0);
    grid.addWidget(buttonDivide, 0, 1);
    grid.addWidget(buttonMultiply, 0, 2);
    grid.addWidget(buttonSubstract, 0, 3);

    grid.addWidget(buttonSeven, 1, 0);
    grid.addWidget(buttonEight, 1, 1);
    grid.addWidget(buttonNine, 1, 2);
    grid.addWidget(buttonAdd, 1, 3, 2, 1);

    grid.addWidget(buttonFour, 2, 0);
    grid.addWidget(buttonFive, 2, 1);
    grid.addWidget(buttonSix, 2, 2);
    //grid.addWidget(buttonAdd, 2, 3);

    grid.addWidget(buttonOne, 3, 0);
    grid.addWidget(buttonTwo, 3, 1);
    grid.addWidget(buttonThree, 3, 2);
    grid.addWidget(buttonCalculate, 3, 3, 2, 1);

    grid.addWidget(buttonClear, 4, 0);
    grid.addWidget(buttonZero, 4, 1);
    grid.addWidget(buttonDot, 4, 2);
    //grid.addWidget(buttonCalculate, 4, 3);
}

