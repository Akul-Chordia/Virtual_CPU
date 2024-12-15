#pragma once

//Basic math blocks
void HalfAdder(bool a, bool b, bool &sum, bool &carry) {
    sum = XOR(a, b);
    carry = AND(a, b);
}

void FullAdder(bool a, bool b, bool cin, bool &sum, bool &carry) {
    bool sum1, carry1, carry2;
    HalfAdder(a, b, sum1, carry1);
    HalfAdder(sum1, cin, sum, carry2);
    carry = OR(carry1, carry2);
}

