#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>

#include <Headers/NButton.h>
#include <Headers/OperationsEnum.h>

#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator(){}


private slots:
    void handleNumberButton();
    void handleOperationButton();

private:
    void createButtons();
    void setUpButtons(QGridLayout& grid);
    void connectSignals();
    void setUpLayouts();

    void updateDisplayedString();



    QVBoxLayout* verticalLayout;

    QGridLayout* gridLayout;

    QLineEdit* textField;
    QString displayedText;

    Operations lastOperation, activeOperation;
    long double number1, number2;
    long double* actualNumber;

    bool is1FloatingPoint;
    bool is2FloatingPoint;

    //Buttons

    //Numbers
    std::array<NButton*, 10> NumberButtons;

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
