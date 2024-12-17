#pragma once

//Basic math blocks
void half_adder(bool a, bool b, bool &sum, bool &carry) {
    sum = XOR(a, b);
    carry = AND(a, b);
}

void full_adder(bool a, bool b, bool cin, bool &sum, bool &carry) {
    bool sum1, carry1, carry2;
    half_adder(a, b, sum1, carry1);
    half_adder(sum1, cin, sum, carry2);
    carry = OR(carry1, carry2);
}

void four_bit_adder(bool a[4], bool b[4], bool cin, bool value[4], bool &carry){
    full_adder(a[0], b[0], cin, value[0], carry);
    full_adder(a[1], b[1], carry, value[1], carry);
    full_adder(a[2], b[2], carry, value[2], carry);
    full_adder(a[3], b[3], carry, value[3], carry);
}


