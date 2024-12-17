#pragma once

void d_latch(bool data, bool store, bool &value){
    bool temp_value = value;
    bool set = AND(data, store);
    bool reset = AND(NOT(data), store);
    
    temp_value = NOR(set, value);
    value = NOR(reset, temp_value);
}

void d_flopflop(bool data, bool clock, bool &value, bool &temp){
    d_latch(data, NOT(clock), temp);
    d_latch(temp, clock, value);
}

void one_bit_register(bool data, bool store, bool clock, bool &value){
    bool temp;
    data = mux_2_to_1(data, value, store);
    d_flopflop(data, clock, value, temp);
}

void four_bit_register(bool data[4], bool store, bool clock, bool value[4]){
    for (int i = 0; i<4; i++){
        one_bit_register(data[i], store, clock, value[i]);
    }
}

