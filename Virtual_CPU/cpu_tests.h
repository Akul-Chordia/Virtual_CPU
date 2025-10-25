#pragma once

// Helper function to run a single test and print its status
void run_test(const std::string& test_name, bool (*test_func)(CPU&), CPU& cpu) {
    bool pass = test_func(cpu);
    if (pass) {
        std::cout << "  [CHECK] " << test_name << std::endl;
    } else {
        std::cout << "  [ERROR] " << test_name << std::endl;
        cpu.print_status();
    }
}

// --- Individual Test Functions ---

bool test_mov_imm_A(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"200F", "FF00"}); // MOV A, 15
    cpu.run();
    return cpu.get_register_value("A") == 15;
}

bool test_mov_imm_B(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"212A", "FF00"}); // MOV B, 42
    cpu.run();
    return cpu.get_register_value("B") == 42;
}

bool test_mov_imm_C_D(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2211", "2322", "FF00"}); // MOV C, 17; MOV D, 34
    cpu.run();
    return cpu.get_register_value("C") == 17 && cpu.get_register_value("D") == 34;
}

bool test_mov_reg_A_B(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2137", "2600", "FF00"}); // MOV B, 55; MOV A, B
    cpu.run();
    return cpu.get_register_value("A") == 55;
}

bool test_mov_reg_C_A_D_A(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"204E", "2C00", "2D00", "FF00"}); // MOV A, 78; MOV C, A; MOV D, A
    cpu.run();
    return cpu.get_register_value("C") == 78 && cpu.get_register_value("D") == 78;
}

bool test_add(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"200A", "2105", "0100", "FF00"}); // MOV A, 10; MOV B, 5; ADD A, B
    cpu.run();
    return cpu.get_register_value("A") == 15;
}

bool test_sub(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"200A", "2103", "0200", "FF00"}); // MOV A, 10; MOV B, 3; SUB A, B
    cpu.run();
    return cpu.get_register_value("A") == 7;
}

bool test_sub_zero_flag(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2005", "2105", "0200", "FF00"}); // MOV A, 5; MOV B, 5; SUB A, B
    cpu.run();
    return cpu.get_register_value("A") == 0 && cpu.get_flag_value(0) == true;
}

bool test_inc_A(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2010", "0300", "FF00"}); // MOV A, 16; INC A
    cpu.run();
    return cpu.get_register_value("A") == 17;
}

bool test_dec_A(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2010", "0400", "FF00"}); // MOV A, 16; DEC A
    cpu.run();
    return cpu.get_register_value("A") == 15;
}

bool test_neg_A(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2005", "0500", "FF00"}); // MOV A, 5
    cpu.run();
    return cpu.get_register_value("A") == 251; // -5 in 8-bit 2's complement
}

bool test_and(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"200C", "210A", "1000", "FF00"}); // MOV A, 12 (1100); MOV B, 10 (1010); AND
    cpu.run();
    return cpu.get_register_value("A") == 8; // (1000)
}

bool test_or(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"200C", "210A", "1100", "FF00"}); // MOV A, 12 (1100); MOV B, 10 (1010); OR
    cpu.run();
    return cpu.get_register_value("A") == 14; // (1110)
}

bool test_xor(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"200C", "210A", "1200", "FF00"}); // MOV A, 12 (1100); MOV B, 10 (1010); XOR
    cpu.run();
    return cpu.get_register_value("A") == 6; // (0110)
}

bool test_not(CPU& cpu) {
    cpu.reset();
    cpu.load_program({"2055", "1300", "FF00"}); // MOV A, 85 (01010101); NOT
    cpu.run();
    return cpu.get_register_value("A") == 170; // (10101010)
}

bool test_store_load_A(CPU& cpu) {
    cpu.reset();
    // MOV A, 77; STORE A, mem[100]; MOV A, 0; LOAD A, mem[100]
    cpu.load_program({"204D", "3A64", "2000", "3064", "FF00"});
    cpu.run();
    return cpu.get_register_value("A") == 77;
}

bool test_store_load_B_C_D(CPU& cpu) {
    cpu.reset();
    // MOV B, 11; MOV C, 22; MOV D, 33;
    // STORE B, [10]; STORE C, [11]; STORE D, [12]
    // LOAD B, [11]; LOAD C, [12]; LOAD D, [10]
    cpu.load_program({"210B", "2216", "2321", "3B0A", "3C0B", "3D0C", "310B", "320C", "330A", "FF00"});
    cpu.run();
    bool b_ok = cpu.get_register_value("B") == 22;
    bool c_ok = cpu.get_register_value("C") == 33;
    bool d_ok = cpu.get_register_value("D") == 11;
    return b_ok && c_ok && d_ok;
}


bool test_jmp(CPU& cpu) {
    cpu.reset();
    // JMP 0x06; MOV A, 1; HALT; (at 0x06) MOV A, 2; HALT
    // PC=0, PC=2, PC=4, PC=6
    cpu.load_program({"4006", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    return cpu.get_register_value("A") == 2 && cpu.get_pc_value() == 8;
}

bool test_jz_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 5; MOV B, 5; SUB; JZ 0x0C; MOV A, 1; HALT; (at 0x0C) MOV A, 2; HALT
    // PC=0, PC=2, PC=4, PC=6, PC=8, PC=10, PC=12
    cpu.load_program({"2005", "2105", "0200", "410C", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Jumps to PC=12, executes MOV A, 2 (PC=14), executes HALT
    return cpu.get_register_value("A") == 2 && cpu.get_pc_value() == 14;
}

bool test_jz_not_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 6; MOV B, 5; SUB; JZ 0x0C; MOV A, 1; HALT; (at 0x0C) MOV A, 2; HALT
    cpu.load_program({"2006", "2105", "0200", "410C", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Does not jump, executes MOV A, 1 (PC=10), executes HALT
    return cpu.get_register_value("A") == 1 && cpu.get_pc_value() == 10;
}

bool test_jnz_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 6; MOV B, 5; SUB; JNZ 0x0C; MOV A, 1; HALT; (at 0x0C) MOV A, 2; HALT
    cpu.load_program({"2006", "2105", "0200", "420C", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Jumps to PC=12, executes MOV A, 2 (PC=14), executes HALT
    return cpu.get_register_value("A") == 2 && cpu.get_pc_value() == 14;
}

bool test_jnz_not_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 5; MOV B, 5; SUB; JNZ 0x0C; MOV A, 1; HALT; (at 0x0C) MOV A, 2; HALT
    cpu.load_program({"2005", "2105", "0200", "420C", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Does not jump, executes MOV A, 1 (PC=10), executes HALT
    return cpu.get_register_value("A") == 1 && cpu.get_pc_value() == 10;
}

bool test_je_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 10; MOV B, 10; JE 0x0A; MOV A, 1; HALT; (at 0x0A) MOV A, 2; HALT
    // PC=0, PC=2, PC=4, PC=6, PC=8, PC=10
    cpu.load_program({"200A", "210A", "430A", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Jumps to PC=10, executes MOV A, 2 (PC=12), executes HALT
    return cpu.get_register_value("A") == 2 && cpu.get_pc_value() == 12;
}

bool test_je_not_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 10; MOV B, 11; JE 0x0A; MOV A, 1; HALT; (at 0x0A) MOV A, 2; HALT
    cpu.load_program({"200A", "210B", "430A", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Does not jump, executes MOV A, 1 (PC=8), executes HALT
    return cpu.get_register_value("A") == 1 && cpu.get_pc_value() == 8;
}

bool test_jg_taken(CPU& cpu) {
    cpu.reset();
    // MOV A, 10; MOV B, 9; JG 0x0A; MOV A, 1; HALT; (at 0x0A) MOV A, 2; HALT
    cpu.load_program({"200A", "2109", "700A", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Jumps to PC=10, executes MOV A, 2 (PC=12), executes HALT
    return cpu.get_register_value("A") == 2 && cpu.get_pc_value() == 12;
}

bool test_jg_not_taken_A_less(CPU& cpu) {
    cpu.reset();
    // MOV A, 9; MOV B, 10; JG 0x0A; MOV A, 1; HALT; (at 0x0A) MOV A, 2; HALT
    cpu.load_program({"2009", "210A", "700A", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Does not jump, executes MOV A, 1 (PC=8), executes HALT
    return cpu.get_register_value("A") == 1 && cpu.get_pc_value() == 8;
}

bool test_jg_not_taken_A_equal(CPU& cpu) {
    cpu.reset();
    // MOV A, 10; MOV B, 10; JG 0x0A; MOV A, 1; HALT; (at 0x0A) MOV A, 2; HALT
    cpu.load_program({"200A", "210A", "700A", "2001", "FF00", "2002", "FF00"});
    cpu.run();
    // Does not jump, executes MOV A, 1 (PC=8), executes HALT
    return cpu.get_register_value("A") == 1 && cpu.get_pc_value() == 8;
}



void run_tests(CPU& cpu) {
    std::cout << "--- Running CPU Test Suite ---" << std::endl;
    
    std::cout << "\n[Testing Data Movement]\n";
    run_test("MOV A, imm (0x20)", test_mov_imm_A, cpu);
    run_test("MOV B, imm (0x21)", test_mov_imm_B, cpu);
    run_test("MOV C, imm / D, imm (0x22, 0x23)", test_mov_imm_C_D, cpu);
    run_test("MOV A, B (0x26)", test_mov_reg_A_B, cpu);
    run_test("MOV C, A / D, A (0x2C, 0x2D)", test_mov_reg_C_A_D_A, cpu);

    std::cout << "\n[Testing Arithmetic]\n";
    run_test("ADD (0x01)", test_add, cpu);
    run_test("SUB (0x02)", test_sub, cpu);
    run_test("SUB (0x02) -> Zero Flag", test_sub_zero_flag, cpu);
    run_test("INC (0x03)", test_inc_A, cpu);
    run_test("DEC (0x04)", test_dec_A, cpu);
    run_test("NEG (0x05)", test_neg_A, cpu);

    std::cout << "\n[Testing Logic]\n";
    run_test("AND (0x10)", test_and, cpu);
    run_test("OR (0x11)", test_or, cpu);
    run_test("XOR (0x12)", test_xor, cpu);
    run_test("NOT (0x13)", test_not, cpu);

    std::cout << "\n[Testing Memory]\n";
    run_test("STORE A / LOAD A (0x3A, 0x30)", test_store_load_A, cpu);
    run_test("STORE/LOAD B,C,D (0x3B-D, 0x31-3)", test_store_load_B_C_D, cpu);
    
    std::cout << "\n[Testing Jumps]\n";
    run_test("JMP (0x40)", test_jmp, cpu);
    run_test("JZ (0x41) - Taken", test_jz_taken, cpu);
    run_test("JZ (0x41) - Not Taken", test_jz_not_taken, cpu);
    run_test("JNZ (0x42) - Taken", test_jnz_taken, cpu);
    run_test("JNZ (0x42) - Not Taken", test_jnz_not_taken, cpu);
    run_test("JE (0x43) - Taken", test_je_taken, cpu);
    run_test("JE (0x43) - Not Taken", test_je_not_taken, cpu);
    run_test("JG (0x70) - Taken", test_jg_taken, cpu);
    run_test("JG (0x7Other(s) - Not Taken (A < B)", test_jg_not_taken_A_less, cpu);
    run_test("JG (0x70) - Not Taken (A == B)", test_jg_not_taken_A_equal, cpu);

    std::cout << "\n--- Test Suite Complete ---" << std::endl;
}
