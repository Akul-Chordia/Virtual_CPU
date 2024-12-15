#include <iostream>
#include "logic gates.h"
#include "math.h"

int main(int argc, const char * argv[]) {
//    std::cout << "\nA|B|AND" << std::endl;
//    for (int i = 0; i<2; i++){
//        for (int j = 0; j<2; j++){
//            std::cout << i << "|" << j << "|" << AND(i,j) << std::endl;
//        }
//    }
//    std::cout << "\nA|B|OR" << std::endl;
//    for (int i = 0; i<2; i++){
//        for (int j = 0; j<2; j++){
//            std::cout << i << "|" << j << "|" << OR(i,j) << std::endl;
//        }
//    }
//    std::cout << "\nA|B|XOR" << std::endl;
//    for (int i = 0; i<2; i++){
//        for (int j = 0; j<2; j++){
//            std::cout << i << "|" << j << "|" << XOR(i,j) << std::endl;
//        }
//    }
//    std::cout << "\nA|B|NAND" << std::endl;
//    for (int i = 0; i<2; i++){
//        for (int j = 0; j<2; j++){
//            std::cout << i << "|" << j << "|" << NAND(i,j) << std::endl;
//        }
//    }
    
    bool a;
    bool b;
    
    FullAdder(1, 1, 1, a, b);
    
    std::cout << b << a << std::endl;
    
    return 0;
}
