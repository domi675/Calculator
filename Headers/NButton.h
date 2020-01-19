#pragma once

#include <QPushButton>
#include <cstdint>


class QWidget;
class QGridLayout;


class NButton : public QPushButton
{
    Q_OBJECT

public:
    //only for std::array in calculator.h
    NButton() = default;

    NButton(std::uint8_t num, QWidget* parent);

    virtual ~NButton() {}

    void setUp(QGridLayout* grid, std::uint8_t x, std::uint8_t y, std::uint8_t xslots = 1, std::uint8_t yslots = 1);

    std::uint8_t getNumber() const{ return buttonNumber; }

signals:
    std::uint8_t buttonPressed() const;

private:
    std::uint8_t buttonNumber;
};

