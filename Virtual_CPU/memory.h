#pragma once
#include <bitset>

std::bitset<8> memory[512];
std::bitset<8> ext_memory[256];

void read_memory(int address, std::bitset<8> &data, bool select) {
    if (select == 0) {
        if (address >= 0 && address < 256) {
            data = memory[address];
        }
    } else {
        if (address >= 0 && address < 256) {
            data = ext_memory[address];
        }
    }
}

void write_memory(int address, const std::bitset<8> &data, bool select) {
    if (select == 0) {
        if (address >= 0 && address < 256) {
            memory[address] = data;
        }
    } else {
        if (address >= 0 && address < 256) {
            ext_memory[address] = data;
        }
    }
}

void clear_memory(bool select) {
    if (select == 0) {
        for (int i = 0; i < 256; i++) {
            memory[i].reset();
        }
    } else {
        for (int i = 0; i < 256; i++) {
            ext_memory[i].reset();
        }
    }
}

// Overloads for bool array
void read_memory(int address, bool data[8], bool select) {
    std::bitset<8> temp;
    read_memory(address, temp, select);
    for (int i = 0; i < 8; ++i) data[i] = temp[i];
}

void write_memory(int address, bool data[8], bool select) {
    std::bitset<8> temp;
    for (int i = 0; i < 8; ++i) temp[i] = data[i];
    write_memory(address, temp, select);
}
