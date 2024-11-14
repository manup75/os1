#include <stdio.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


void check_operand_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    for (int i = 0; i < instruction_count; i++) {
        int operand_count = 0;
        char *token = strtok(main_memory[i], " ,");
        // Count tokens after the opcode as operands
        while (token != NULL) {
            operand_count++;
            token = strtok(NULL, " ,");
        }
       
        if (operand_count < 3) { // Opcode + 2 operands
            printf("Operand error at address %d: Missing operand(s) in instruction '%s'\n", i, main_memory[i]);
        }
    }
}


int main() {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",
        "STORE R2", // Missing operand for testing
        "ADD R1, R2",
        "SUB R3" // Missing operand for testing
    };
    int instruction_count = 4;
    check_operand_errors(main_memory, instruction_count);
    return 0;
}