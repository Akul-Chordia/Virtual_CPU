#pragma once

void test_logic_gates(){
    std::cout << "\nA|B|AND" << std::endl;
    for (int i = 0; i<2; i++){
        for (int j = 0; j<2; j++){
            std::cout << i << "|" << j << "|" << AND(i,j) << std::endl;
        }
    }
    std::cout << "\nA|B|OR" << std::endl;
    for (int i = 0; i<2; i++){
        for (int j = 0; j<2; j++){
            std::cout << i << "|" << j << "|" << OR(i,j) << std::endl;
        }
    }
    std::cout << "\nA|B|XOR" << std::endl;
    for (int i = 0; i<2; i++){
        for (int j = 0; j<2; j++){
            std::cout << i << "|" << j << "|" << XOR(i,j) << std::endl;
        }
    }
    std::cout << "\nA|B|NAND" << std::endl;
    for (int i = 0; i<2; i++){
        for (int j = 0; j<2; j++){
            std::cout << i << "|" << j << "|" << NAND(i,j) << std::endl;
        }
    }
    std::cout << "\nA|B|NOR" << std::endl;
    for (int i = 0; i<2; i++){
        for (int j = 0; j<2; j++){
            std::cout << i << "|" << j << "|" << NOR(i,j) << std::endl;
        }
    }
}


void test_adder(){
    bool a;
    bool b;
    
    for (int i = 0; i<2; i++){
        for (int j = 0; j<2; j++){
            for (int k = 0; k<2; k++){
                std::cout << i << "+" << j << "+" << k << "= ";
                full_adder(i, j, k, a, b);
                std::cout << b << a << std::endl;
            }
        }
    }
}


void test_d_latch(){
    bool a = 0;
    
    d_latch(1, 0, a);
    std::cout << a << std::endl;
    d_latch(1, 1, a);
    std::cout << a << std::endl;
    d_latch(0, 0, a);
    std::cout << a << std::endl;
    d_latch(0, 1, a);
    std::cout << a << std::endl;
}

void test_d_flipflop(){
    bool a = 0;
    bool b = 0;
    
    d_flopflop(0, 0, a, b);
    std::cout << a << std::endl;
    d_flopflop(1, 0, a, b);
    std::cout << a << std::endl;
    d_flopflop(1, 1, a, b);
    std::cout << a << std::endl;
    d_flopflop(0, 1, a, b);
    std::cout << a << std::endl;
    d_flopflop(1, 1, a, b);
    std::cout << a << std::endl;
    d_flopflop(0, 0, a, b);
    std::cout << a << std::endl;
    d_flopflop(0, 1, a, b);
    std::cout << a << std::endl;
}

void test_one_bit_register(){
    bool a = 0;
    bool b = 0;
    
    one_bit_register(0, 0, 0, a, b);
    std::cout << a << std::endl;
    one_bit_register(1, 0, 1, a, b);
    std::cout << a << std::endl;
    one_bit_register(1, 1, 0, a, b);
    std::cout << a << std::endl;
    one_bit_register(1, 1, 1, a, b);
    std::cout << a << std::endl;
    one_bit_register(0, 1, 1, a, b);
    std::cout << a << std::endl;
    one_bit_register(0, 1, 0, a, b);
    std::cout << a << std::endl;
    one_bit_register(0, 1, 1, a, b);
    std::cout << a << std::endl;
}

void print_register(bool value[8]){
    for (int i = 0; i < 8; i++) std::cout << value[i];
    std::cout << std::endl;
}

void test_eight_bit_register() {
    bool data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    bool value[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    bool temp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    std::cout << "Initial state of 8-bit register: ";
    for (int i = 0; i < 8; i++) std::cout << value[i];
    std::cout << std::endl;


    data[0] = 1; data[1] = 0; data[2] = 1; data[3] = 0;
    data[4] = 1; data[5] = 0; data[6] = 1; data[7] = 0;
    
    eight_bit_register(data, 0, 0, value, temp);
    print_register(value); //00000000
    eight_bit_register(data, 1, 0, value, temp);
    print_register(value); //00000000
    eight_bit_register(data, 1, 1, value, temp);
    print_register(value); //10101010
    
    data[0] = 1; data[1] = 1; data[2] = 1; data[3] = 1;
    data[4] = 1; data[5] = 1; data[6] = 1; data[7] = 1;
    
    eight_bit_register(data, 1, 1, value, temp);
    print_register(value); //10101010
    eight_bit_register(data, 0, 1, value, temp);
    print_register(value); //10101010
    eight_bit_register(data, 1, 1, value, temp);
    print_register(value); //10101010
    eight_bit_register(data, 1, 0, value, temp);
    print_register(value); //10101010
    eight_bit_register(data, 0, 0, value, temp);
    print_register(value); //10101010
    eight_bit_register(data, 1, 0, value, temp);
    print_register(value); //10101010
    eight_bit_register(data, 1, 1, value, temp);
    print_register(value); //11111111
}

