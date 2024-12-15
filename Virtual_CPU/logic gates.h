#pragma once

//AND and NOT as base functions
bool AND(bool a, bool b) {
    return a && b;
}

bool NOT(bool a) {
    return !a;
}

//Deriving other logic gates
bool NAND(bool a, bool b) {
    return NOT(AND(a, b));
}

bool OR(bool a, bool b) {
    return NAND(NOT(a), NOT(b));
}

bool XOR(bool a, bool b) {
    return AND(OR(a, b), NAND(a, b));
}

