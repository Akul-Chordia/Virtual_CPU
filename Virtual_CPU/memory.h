#pragma once
#include <bitset>

class Memory{
private:
    bool memory[512][8];
    bool ext_memory[256][8];

public:
    void read_memory(int address, bool data[8], bool select) {
        if (select == 0) {
            if (address >= 0 && address < 512) {
                for (int i = 0; i < 8; i++) {
                    data[i] = memory[address][i];
                }
            }
        } else {
            if (address >= 0 && address < 256) {
                for (int i = 0; i < 8; i++) {
                    data[i] = ext_memory[address][i];
                }
            }
        }
    }

    void write_memory(int address, bool data[8], bool select) {
        if (select == 0) {
            if (address >= 0 && address < 512) {
                for (int i = 0; i < 8; i++) {
                    memory[address][i] = data[i];
                }
            }
        } else {
            if (address >= 0 && address < 256) {
                for (int i = 0; i < 8; i++) {
                    ext_memory[address][i] = data[i];
                }
            }
        }
    }

    void clear_memory(bool select) {
        if (select == 0) {
            for (int i = 0; i < 512; i++) {
                for (int j = 0; j < 8; j++) {
                    memory[i][j] = 0;
                }
            }
        } else {
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 8; j++) {
                    ext_memory[i][j] = 0;
                }
            }
        }
    }

};
