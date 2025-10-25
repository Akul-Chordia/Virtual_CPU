#pragma once

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


void eight_bit_adder(bool a[8], bool b[8], bool cin, bool value[8], bool &carry){
    full_adder(a[7], b[7], cin, value[7], carry);
    for (int i = 6; i>=0; i--){
        full_adder(a[i], b[i], carry, value[i], carry);
    }
}


void increment(bool a[8], bool &carry){
    bool one[8] = {0,0,0,0,0,0,0,1};
    eight_bit_adder(a, one, 0, a, carry);
}


void negate(bool a[8]){
    for (int i = 0; i<8; i++){
        a[i] = NOT(a[i]);
    }
}


void two_complement(bool a[8], bool &carry){
    negate(a);
    increment(a, carry);
}


void eight_bit_sub(bool a[8], bool b[8], bool cin, bool value[8], bool &carry){
    bool temp[8];
    for(int i=0; i<8; i++) temp[i] = b[i];
    bool increment_carry;
    two_complement(temp, increment_carry);
    eight_bit_adder(a, temp, cin, value, carry);
}


void decrement(bool a[8], bool &negative){
    bool one[8] = {0,0,0,0,0,0,0,1};
    eight_bit_sub(a, one, 0, a, negative);
}


void eight_bit_AND(bool a[8], bool b[8]){
    for (int i = 0; i<8; i++){
        a[i] = AND(a[i], b[i]);
    }
}


void eight_bit_OR(bool a[8], bool b[8]){
    for (int i = 0; i<8; i++){
        a[i] = OR(a[i], b[i]);
    }
}


void eight_bit_XOR(bool a[8], bool b[8]){
    for (int i = 0; i<8; i++){
        a[i] = XOR(a[i], b[i]);
    }
}

