#pragma once

void d_latch(bool data, bool store, bool &value){
    bool set = AND(data, store);
    bool reset = AND(NOT(data), store);
    
    value = OR(set, AND(value, NOT(reset)));
}


void d_flopflop(bool data, bool clock, bool &value, bool &temp){
    d_latch(data, NOT(clock), temp);
    d_latch(temp, clock, value);
}


void one_bit_register(bool data, bool store, bool clock, bool &value, bool &temp) {
    data = mux_2_to_1(value, data, store);
    d_flopflop(data, clock, value, temp);
}


void eight_bit_register(bool data[8], bool store, bool clock, bool value[8], bool temp[8]){
    for (int i = 0; i<8; i++){
        one_bit_register(data[i], store, clock, value[i], temp[i]);
    }
}


void read_register(bool value[8]){
    for (int i = 0; i < 8; i++) std::cout << value[i];
    std::cout << std::endl;
}

