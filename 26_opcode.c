#include <stdio.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


const char *valid_opcodes[] = {"LOAD", "STORE", "ADD", "SUB", "JMP", "HALT"};
#define NUM_OPCODES (sizeof(valid_opcodes) / sizeof(valid_opcodes[0]))


int is_valid_opcode(const char *opcode) {
    for (int i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcode, valid_opcodes[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void check_opcode_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    for (int i = 0; i < instruction_count; i++) {
        char opcode[MAX_LINE_LENGTH];
        sscanf(main_memory[i], "%s", opcode);  // Extract the first word as opcode
        if (!is_valid_opcode(opcode)) {
            printf("Opcode error at address %d: Invalid opcode '%s'\n", i, opcode);
        }
    }
}


int main() {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",
        "STOREE R2, 200", // Invalid opcode for testing
        "ADD R1, R2",
        "INVALID_OP R3, 300" // Invalid opcode for testing
    };
    int instruction_count = 4;
    check_opcode_errors(main_memory, instruction_count);
    return 0;
}