#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50


void load_alp_to_memory(const char *file_path) {
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH];
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error: Input file not found.\n");
        return;
    }


    int address = 0;
    while (fgets(main_memory[address], MAX_LINE_LENGTH, file) != NULL && address < MAX_INSTRUCTIONS) {
        main_memory[address][strcspn(main_memory[address], "\n")] = '\0'; // Remove newline character
        address++;
    }
    fclose(file);


    printf("ALP Program loaded into main memory:\n");
    for (int i = 0; i < address; i++) {
        printf("Address %d: %s\n", i, main_memory[i]);
    }
}


int main() {
    load_alp_to_memory("alp_program.txt");
    return 0;
}