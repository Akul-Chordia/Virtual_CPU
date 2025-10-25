#pragma once

class RegisterArray {
private:
    
    bool A[8], B[8], C[8], D[8];
    bool PC[8]; // Program Counter
    bool Temp[8]; // Temporary register
    bool MAR[8]; // Memory Address Register
    bool flags[4]; // Zero, Carry, Negative, Overflow


public:
    
    // Temporary variables for flip-flops
    bool tempA[8], tempB[8], tempC[8], tempD[8], tempPC[8], tempMAR[8], tempTemp[8];
    

    RegisterArray() {
        clear_registers();
    }

    void clear_registers() {
        for (int i = 0; i < 8; i++) {
            A[i] = B[i] = C[i] = D[i] = 0;
            PC[i] = Temp[i] = MAR[i] = 0;
        }
        for (int i = 0; i < 4; i++) flags[i] = 0;
    }

    void write_register(bool data[8], bool store, bool clock, const std::string &reg) {
        if (reg == "A") eight_bit_register(data, store, clock, A, tempA);
        else if (reg == "B") eight_bit_register(data, store, clock, B, tempB);
        else if (reg == "C") eight_bit_register(data, store, clock, C, tempC);
        else if (reg == "D") eight_bit_register(data, store, clock, D, tempD);
        else if (reg == "PC") eight_bit_register(data, store, clock, PC, tempPC);
        else if (reg == "MAR") eight_bit_register(data, store, clock, MAR, tempMAR);
        else if (reg == "Temp") eight_bit_register(data, store, clock, Temp, tempTemp);
    }
    
    void clocked_write_register(bool data[8], const std::string &reg) {
            write_register(data, 1, 0, reg);
            write_register(data, 1, 1, reg);
        }

    void read_register(bool output[8], const std::string &reg) {
        if (reg == "A") for (int i = 0; i < 8; i++) output[i] = A[i];
        else if (reg == "B") for (int i = 0; i < 8; i++) output[i] = B[i];
        else if (reg == "C") for (int i = 0; i < 8; i++) output[i] = C[i];
        else if (reg == "D") for (int i = 0; i < 8; i++) output[i] = D[i];
        else if (reg == "PC") for (int i = 0; i < 8; i++) output[i] = PC[i];
        else if (reg == "MAR") for (int i = 0; i < 8; i++) output[i] = MAR[i];
        else if (reg == "Temp") for (int i = 0; i < 8; i++) output[i] = Temp[i];
    }


    void increment_pc() {
        bool carry;
        increment(PC, carry);
        increment(PC, carry);
    }

    void set_pc(bool value[8]) {
        for (int i = 0; i < 8; i++) PC[i] = value[i];
    }

    void update_flags(bool result[8], bool carry, bool negative, bool overflow) {
        // Zero flag
        flags[0] = 1;
        for (int i = 0; i < 8; i++) {
            if (result[i]) {
                flags[0] = 0;
                break;
            }
        }
        
        // Carry flag
        flags[1] = carry;
        
        // Negative flag (MSB)
        flags[2] = negative;
        
        // Overflow flag
        flags[3] = overflow;
    }
    
    bool get_flag(int a){
        return flags[a];
    }

    void print_registers() {
        std::cout << "Registers:" << std::endl;
        std::cout << "A: "; for (int i = 0; i < 8; i++) std::cout << A[i]; std::cout << std::endl;
        std::cout << "B: "; for (int i = 0; i < 8; i++) std::cout << B[i]; std::cout << std::endl;
        std::cout << "C: "; for (int i = 0; i < 8; i++) std::cout << C[i]; std::cout << std::endl;
        std::cout << "D: "; for (int i = 0; i < 8; i++) std::cout << D[i]; std::cout << std::endl;
        std::cout << "PC: "; for (int i = 0; i < 8; i++) std::cout << PC[i]; std::cout << std::endl;
        std::cout << "Flags (ZCNO): ";
        for (int i = 0; i < 4; i++) std::cout << flags[i];
        std::cout << std::endl << std::endl;
    }

    bool* get_pc() { return PC; }
    bool* get_mar() { return MAR; }
    bool* get_register(const std::string &reg) {
        if (reg == "A") return A;
        else if (reg == "B") return B;
        else if (reg == "C") return C;
        else if (reg == "D") return D;
        return nullptr;
    }
};
