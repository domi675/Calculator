#include <Headers/OperationsEnum.h>

char operationToChar(Operations o){
    switch (o) {
    case Operations::ADD:
        return '+';
    case Operations::SUBSTRACT:
        return '-';
    case Operations::MULTIPLY:
        return '*';
    case Operations::DIVIDE:
        return '/';
    default:
        return '0';
    }
}
