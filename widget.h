#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget(){}

private:
    void createButtons();
    void setUpButtons(QGridLayout& grid);


    QVBoxLayout* verticalLayout;

    QGridLayout* gridLayout;

    QLineEdit* textField;

    //Buttons

    //Numbers
    QPushButton* buttonZero;
    QPushButton* buttonOne;
    QPushButton* buttonTwo;
    QPushButton* buttonThree;
    QPushButton* buttonFour;
    QPushButton* buttonFive;
    QPushButton* buttonSix;
    QPushButton* buttonSeven;
    QPushButton* buttonEight;
    QPushButton* buttonNine;

    //Operations
    QPushButton* buttonAdd;
    QPushButton* buttonSubstract;
    QPushButton* buttonMultiply;
    QPushButton* buttonDivide;

    //Other
    QPushButton* buttonRemoveCharacter;
    QPushButton* buttonClear;
    QPushButton* buttonCalculate;
    QPushButton* buttonDot;
};
