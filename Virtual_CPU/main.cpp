#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "logic gates.h"
#include "selectors.h"
#include "registers.h"
#include "ALU.h"
#include "register_array.h"
#include "memory.h"
#include "CPU.h"
#include "tests.h"
#include "instructions.h"


int main() {
    
    //test_adder();
    //test_d_latch();
    //test_d_flipflop();
    //test_one_bit_register();
    //test_eight_bit_register();
    //test_eight_bit_adder();
    //test_eight_bit_sub();
    //test_increment();
    //test_decrement();
    //test_complement();
    //test_AND();
    //test_OR();
    //test_XOR();
    //test_NOT();
    

    CPU cpu;
    std::string command;
    
    std::cout << "Simple CPU Simulator" << std::endl;
    std::cout << "Type 'help' for available commands" << std::endl;
    std::cout << std::endl;
    
    while (true) {
        std::cout << "cpu> ";
        std::getline(std::cin, command);
        
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;
        
        if (cmd == "help") {
            print_help();
        }
        else if (cmd == "reset") {
            cpu.reset();
            std::cout << "CPU reset." << std::endl;
        }
        else if (cmd == "load") {
            std::vector<std::string> hex_program;
            std::string hex_str;
            while (iss >> hex_str) {
                hex_program.push_back(hex_str);
            }
            if (!hex_program.empty()) {
                cpu.load_program(hex_program);
                std::cout << "Program loaded (" << hex_program.size() << " instructions)." << std::endl;
            } else {
                std::cout << "No program data provided." << std::endl;
            }
        }
        else if (cmd == "run") {
            cpu.run();
        }
        else if (cmd == "step") {
            cpu.debug_step();
        }
        else if (cmd == "status") {
            cpu.print_status();
        }
        else if (cmd == "example") {
            // Example program: Load 5 to A, Load 3 to B, Add them, Print A, Halt
            std::vector<std::string> example = {"2003", "2105", "0100", "FE00" ,"FF00"};
            cpu.reset();
            cpu.load_program(example);
            std::cout << "Example program loaded: 5 + 3 = ?" << std::endl;
            std::cout << "Use 'run' to execute or 'step' to debug." << std::endl;
        }
        else if (cmd == "quit" || cmd == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else if (!cmd.empty()) {
            std::cout << "Unknown command: " << cmd << std::endl;
            std::cout << "Type 'help' for available commands." << std::endl;
        }
    }
    
    return 0;
}
