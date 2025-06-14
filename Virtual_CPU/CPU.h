#pragma once

class CPU {
private:
    RegisterArray registers;
    bool halt_flag;

public:
    CPU() : halt_flag(false) {}

    void reset() {
        registers.clear_registers();
        halt_flag = false;
        clear_memory(0);
    }

    void int_to_bool_array(int value, bool arr[8]) {
        for (int i = 7; i >= 0; i--) {
            arr[i] = (value >> (7-i)) & 1;
        }
    }
    
    int bool_array_to_int(bool arr[8]) {
        int result = 0;
        for (int i = 0; i < 8; i++) {
            result += arr[7-i] * (1 << i);
        }
        return result;
    }
    
    void decode(const std::string& hex_str, bool opcode[8], bool operand[8]) {
        int instr = (int)std::stoul(hex_str, nullptr, 16);

        // Extract upper 8 bits as opcode
        for (int i = 0; i < 8; i++) {
            opcode[7 - i] = (instr >> (8 + i)) & 1;
        }

        // Extract lower 8 bits as operand
        for (int i = 0; i < 8; i++) {
            operand[7 - i] = (instr >> i) & 1;
        }
    }
    

    void execute_instruction(bool opcode[8], bool operand[8]) {
        int op = bool_array_to_int(opcode);
        int reg_addr = bool_array_to_int(operand);
        bool a_val[8], b_val[8];
        bool result[8] = {0};
        bool carry = false;
        bool negative = false;
        //std::cout << "doing instruction: " << op << std::endl;
        
        
        switch (op) {
            case 0: // NOP
                break;
                
            case 255: // HALT
                halt_flag = true;
                std::cout << "CPU HALTED" << std::endl;
                break;
                
            case 254: // Print A
            {
                registers.read_register(a_val, "A");
                std::cout << "Register A: ";
                for (int i = 0; i < 8; i++) std::cout << a_val[i];
                std::cout << " (decimal: " << bool_array_to_int(a_val) << ")" << std::endl;
            }
                break;
                
            case 1: // A ← A + B
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                eight_bit_adder(a_val, b_val, 0, result, carry);
                registers.write_register(result, 1, 0, "A");
                registers.write_register(result, 1, 1, "A");
                registers.update_flags(result, carry, negative, false);
                break;
                
            case 2: // A ← A - B
            {
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                eight_bit_sub(a_val, b_val, 0, result, negative);
                registers.write_register(result, 1, 0, "A");
                registers.write_register(result, 1, 1, "A");
                registers.update_flags(result, carry, negative, false);
            }
                break;
                
            case 3: // A ← A + 1
            {
                registers.read_register(a_val, "A");
                increment(a_val, carry);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
                registers.update_flags(a_val, carry, negative, false);
            }
                break;
                
            case 4: // A ← A - 1
            {
                registers.read_register(a_val, "A");
                decrement(a_val, negative);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
                registers.update_flags(a_val, carry, negative, false);
            }
                break;
                
            case 5: // A ← -A
            {
                registers.read_register(a_val, "A");
                two_complement(a_val, a_val, negative);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
                registers.update_flags(a_val, carry, negative, false);
            }
                break;
                
            case 16: // A ← A & B
            {
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                eight_bit_ADD(a_val, b_val);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
            }
                break;
            case 17: // A ← A | B
            {
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                eight_bit_OR(a_val, b_val);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
            }
                break;
                
            case 18: // A ← A ^ B
            {
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                eight_bit_XOR(a_val, b_val);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
            }
                break;
                
            case 19: // A ← ~A
            {
                registers.read_register(a_val, "A");
                negate(a_val);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
            }
                break;
            case 32: // A ← operand
            {
                registers.write_register(operand, 1, 0, "A");
                registers.write_register(operand, 1, 1, "A");
            }
                break;
                
            case 33: // B ← operand
            {
                registers.write_register(operand, 1, 0, "B");
                registers.write_register(operand, 1, 1, "B");
            }
                break;
                
            case 34: // C ← operand
            {
                registers.write_register(operand, 1, 0, "C");
                registers.write_register(operand, 1, 1, "C");
            }
                break;
                
            case 35: // D ← operand
            {
                registers.write_register(operand, 1, 0, "D");
                registers.write_register(operand, 1, 1, "D");
            }
                break;
            case 38: // A ← B
            {
                registers.read_register(a_val, "B");
                registers.write_register(operand, 1, 0, "A");
                registers.write_register(operand, 1, 1, "A");
            }
                break;
            case 39: // A ← C
            {
                registers.read_register(a_val, "C");
                registers.write_register(operand, 1, 0, "A");
                registers.write_register(operand, 1, 1, "A");
            }
                break;
            case 40: // A ← D
            {
                registers.read_register(a_val, "D");
                registers.write_register(operand, 1, 0, "A");
                registers.write_register(operand, 1, 1, "A");
            }
                break;
            case 43: // B ← A
            {
                registers.read_register(a_val, "A");
                registers.write_register(operand, 1, 0, "B");
                registers.write_register(operand, 1, 1, "B");
            }
                break;
            case 44: // C ← A
            {
                registers.read_register(a_val, "A");
                registers.write_register(operand, 1, 0, "C");
                registers.write_register(operand, 1, 1, "C");
            }
                break;
            case 45: // D ← A
            {
                registers.read_register(a_val, "A");
                registers.write_register(operand, 1, 0, "D");
                registers.write_register(operand, 1, 1, "D");
            }
                break;
            case 48: // A ← Mem[operand]
            {
                read_memory(reg_addr, a_val, 1);
                registers.write_register(a_val, 1, 0, "A");
                registers.write_register(a_val, 1, 1, "A");
            }
                break;
                
            case 49: // B ← Mem[operand]
            {
                read_memory(reg_addr, a_val, 1);
                registers.write_register(a_val, 1, 0, "B");
                registers.write_register(a_val, 1, 1, "B");
            }
                break;
                
            case 50: // C ← Mem[operand]
            {
                read_memory(reg_addr, a_val, 1);
                registers.write_register(a_val, 1, 0, "C");
                registers.write_register(a_val, 1, 1, "C");
            }
                break;
                
            case 51: // D ← Mem[operand]
            {
                read_memory(reg_addr, a_val, 1);
                registers.write_register(a_val, 1, 0, "D");
                registers.write_register(a_val, 1, 1, "D");
            }
                break;
            case 58: // Mem[operand] ← A
            {
                registers.read_register(a_val, "A");
                write_memory(reg_addr ,a_val, 1);
            }
                break;
            case 59: // Mem[operand] ← B
            {
                registers.read_register(a_val, "B");
                write_memory(reg_addr ,a_val, 1);
            }
                break;
            case 60: // Mem[operand] ← C
            {
                registers.read_register(a_val, "C");
                write_memory(reg_addr ,a_val, 1);
            }
                break;
            case 61: // Mem[operand] ← D
            {
                registers.read_register(a_val, "D");
                write_memory(reg_addr ,a_val, 1);
            }
                break;
            case 64: // PC ← operand (JMP)
            {
                registers.set_pc(operand);
            }
                break;
            case 65: // if ZF == 1, PC ← operand (JNZ)
            {
                if (registers.get_flag(0) != 0){
                    registers.set_pc(operand);
                }
            }
                break;
            case 66: // if ZF == 0, PC ← operand (JZ)
            {
                if (registers.get_flag(0) == 0){
                    registers.set_pc(operand);
                }
            }
                break;
            case 67: // if A == B, PC ← operand (JE)
            {
                bool flag = true;
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                for (int i = 0; i<8; i++){
                    if (a_val[i] != b_val[i]){
                        flag = false ;
                        break;
                    }
                }
                if (flag){
                    registers.set_pc(operand);
                }
            }
                break;
            case 112: // if A > B, PC ← operand (JE)
            {
                bool flag = false;
                registers.read_register(a_val, "A");
                registers.read_register(b_val, "B");
                for (int i = 0; i<8; i++){
                    if (a_val[i] > b_val[i]){
                        flag = true ;
                        break;
                    } else if (a_val[i] < b_val[i]){
                        break;
                    }
                }
                if (flag){
                    registers.set_pc(operand);
                }
            }
                break;
            default:
                std::cout << "Unknown instruction: " << op << std::endl;
                break;
            }
        }


    void load_program(const std::vector<std::string>& hex_program) {
        for (int i = 0; i < hex_program.size() && (i * 2 + 1) < 512; i++) {
            bool opcode[8], operand[8];
            decode(hex_program[i], opcode, operand);
            write_memory(i * 2, opcode, 0);
            write_memory(i * 2 + 1, operand, 0);
        }
    }

    
    void run() {
        std::cout << "Starting CPU execution..." << std::endl;
        
        while (!halt_flag) {
            // Fetch
            bool opcode[8], operand[8];
            bool pc_val[8];
            registers.read_register(pc_val, "PC");
            int pc_int = bool_array_to_int(pc_val);
            
            if (pc_int >= 511) {
                std::cout << "Program Counter out of bounds. Halting." << std::endl;
                break;
            }
            
            read_memory(pc_int, opcode, 0);
            read_memory(pc_int+1, operand, 0);
            
            // Execute
            execute_instruction(opcode, operand);
            
            // Increment PC (unless it's a halt instruction)
            if (!halt_flag) {
                registers.increment_pc();
            }
            
            // Prevent infinite loops
            if (pc_int > 200) {
                std::cout << "Program ran too long. Halting to prevent infinite loop." << std::endl;
                break;
            }
        }
        
        std::cout << std::endl << "Final state: " << std::endl;
        registers.print_registers();
    }

    void debug_step() {
        if (halt_flag) {
            std::cout << "CPU is halted." << std::endl;
            return;
        }

        // Fetch
        bool opcode[8], operand[8];
        bool pc_val[8];
        registers.read_register(pc_val, "PC");
        int pc_int = bool_array_to_int(pc_val);
        
        read_memory(pc_int, opcode, 0);
        read_memory(pc_int+1, operand, 0);
        
        // Display current instruction
        std::cout << "PC: " << pc_int << ", Instruction: ";
        for (int i = 0; i < 8; i++) std::cout << opcode[i];
        for (int i = 0; i < 8; i++) std::cout << operand[i];
        std::cout << std::endl;
        

        std::cout << "Opcode: " << bool_array_to_int(opcode)
                  << ", Operand: " << bool_array_to_int(operand) << std::endl;
        
        // Execute
        execute_instruction(opcode, operand);
        
        // Increment PC
        if (!halt_flag) {
            registers.increment_pc();
        }
        
        registers.print_registers();
    }

    bool is_halted() { return halt_flag; }
    void print_status() { registers.print_registers(); }
};
