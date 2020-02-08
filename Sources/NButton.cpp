#include <Headers/NButton.h>

//#include <QWidget>
#include <QGridLayout>

NButton::NButton(std::uint8_t num, QWidget *parent)
    :QPushButton{QString{std::to_string(num).c_str()}, parent}, buttonNumber{num}
{}

void NButton::setUp(QGridLayout *grid, uint8_t x, uint8_t y, uint8_t xslots, uint8_t yslots)
{
    if(grid == nullptr){
        throw std::runtime_error{"QGridLayout passed to NButton::setUp is nullptr!"};
    }
    else{
        grid->addWidget(this, x, y, xslots, yslots);
    }
}




