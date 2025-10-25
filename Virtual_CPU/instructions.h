#pragma once

void print_help() {
    std::cout << "Simple CPU Simulator Commands:" << std::endl;
    std::cout << "  help         - Show this help message" << std::endl;
    std::cout << "  reset        - Reset CPU and clear memory" << std::endl;
    std::cout << "  load <prog>  - Load program (space-separated hex values)" << std::endl;
    std::cout << "  run          - Run loaded program" << std::endl;
    std::cout << "  step         - Execute one instruction" << std::endl;
    std::cout << "  status       - Show register status" << std::endl;
    std::cout << "  example      - Load and run example program" << std::endl;
    std::cout << "  test         - Run tests" << std::endl;
    std::cout << "  quit         - Exit simulator" << std::endl;
    std::cout << std::endl;
    std::cout << "Instruction Set:" << std::endl;
    std::cout << "  0x01XX -  (A ← A + B)" << std::endl;
    std::cout << "  0x02XX -  (A ← A - B)" << std::endl;
    std::cout << "  0x03XX -  (A ← A + 1)" << std::endl;
    std::cout << "  0x04XX -  (A ← A - 1)" << std::endl;
    std::cout << "  0x05XX -  (A ← -A)" << std::endl;

    std::cout << "  0x10XX -  (A ← A & B)" << std::endl;
    std::cout << "  0x11XX -  (A ← A | B)" << std::endl;
    std::cout << "  0x12XX -  (A ← A ^ B)" << std::endl;
    std::cout << "  0x13XX -  (A ← ~A)" << std::endl;

    std::cout << "  0x20XX -  (A ← operand)" << std::endl;
    std::cout << "  0x21XX -  (B ← operand)" << std::endl;
    std::cout << "  0x22XX -  (C ← operand)" << std::endl;
    std::cout << "  0x23XX -  (D ← operand)" << std::endl;
    //std::cout << "  0x24XX -  (MAR ← operand)" << std::endl;
    //std::cout << "  0x25XX -  (TEMP ← operand)" << std::endl;
    std::cout << "  0x26XX -  (A ← B)" << std::endl;
    std::cout << "  0x27XX -  (A ← C)" << std::endl;
    std::cout << "  0x28XX -  (A ← D)" << std::endl;
    
    std::cout << "  0x2BXX -  (B ← A)" << std::endl;
    std::cout << "  0x2CXX -  (C ← A)" << std::endl;
    std::cout << "  0x2DXX -  (D ← A)" << std::endl;
    std::cout << "  0x2EXX -  (MAR ← A)" << std::endl;
    std::cout << "  0x2FXX -  (TEMP ← A)" << std::endl;
    
    std::cout << "  0x30XX -  (A ← Mem[operand])" << std::endl;
    std::cout << "  0x31XX -  (B ← Mem[operand])" << std::endl;
    std::cout << "  0x32XX -  (C ← Mem[operand])" << std::endl;
    std::cout << "  0x33XX -  (D ← Mem[operand])" << std::endl;
    std::cout << "  0x34XX -  (MAR ← Mem[operand])" << std::endl;
    std::cout << "  0x35XX -  (TEMP ← Mem[operand])" << std::endl;
    
    std::cout << "  0x3AXX -  (Mem[operand] ← A)" << std::endl;
    std::cout << "  0x3BXX -  (Mem[operand] ← B)" << std::endl;
    std::cout << "  0x3CXX -  (Mem[operand] ← C)" << std::endl;
    std::cout << "  0x3DXX -  (Mem[operand] ← D)" << std::endl;

    std::cout << "  0x40XX -  (PC ← operand)" << std::endl;
    std::cout << "  0x41XX -  (if ZF == 1, PC ← operand)" << std::endl;
    std::cout << "  0x42XX -  (if ZF == 0, PC ← operand)" << std::endl;
    std::cout << "  0x43XX -  (if A == B, PC ← operand)" << std::endl;
    //std::cout << "  0x43XX -  (if CF == 1, PC ← operand)" << std::endl;
    //std::cout << "  0x44XX -  (if CF == 0, PC ← operand)" << std::endl;
    //std::cout << "  0x45XX -  (push PC; PC ← operand)" << std::endl;
    //std::cout << "  0x46XX -  (PC ← pop)" << std::endl;

    //std::cout << "  0x50XX -  (push ACC)" << std::endl;
    //std::cout << "  0x51XX -  (ACC ← pop)" << std::endl;

    //std::cout << "  0x60XX -  (set flags from ACC - operand)" << std::endl;
    
    std::cout << "  0x70XX -  (A > B, PC ← operand)" << std::endl;
    std::cout << "  0x00XX -  (no operation)" << std::endl;
    std::cout << "  0xFDXX -  (Print B)" << std::endl;
    std::cout << "  0xFEXX -  (Print A)" << std::endl;
    std::cout << "  0xFFXX -  (halt execution)" << std::endl;
    std::cout << std::endl;
}
