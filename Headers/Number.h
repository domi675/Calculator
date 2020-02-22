#pragma once


class Number
{
public:
    Number();

    void setValue(long double newVal);
    void addChar(unsigned char ch);
    void removeLastCharacter();
    void clear();
    void setIsFP(bool state);

    long double getValue() const;
    bool isFP() const;
    unsigned char getNofP() const;

private:
    long double value;
    bool isFloatingPoint;
    unsigned char nOfPlacesAfterDot;
};

