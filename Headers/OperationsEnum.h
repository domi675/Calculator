#pragma once

enum class Operations{
    UNKNOWN_FIRST,
    CLEAR_ALL,
    CLEAR_LAST,
    CALCULATE,
    INSERT_DOT,
    ADD_NUMBER,

    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,

    RESERVED_ALWAYS_LAST
};

char operationToChar(Operations o);
