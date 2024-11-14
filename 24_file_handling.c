#include <stdio.h>
#include <stdlib.h>


void copyFileCharacterByCharacter(const char *sourceFile, const char *destFile) {
    FILE *src = fopen(sourceFile, "r");
    FILE *dest = fopen(destFile, "w");
    if (src == NULL || dest == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }
    printf("File copied character by character successfully.\n");
    fclose(src);
    fclose(dest);
}


void copyFileLineByLine(const char *sourceFile, const char *destFile) {
    FILE *src = fopen(sourceFile, "r");
    FILE *dest = fopen(destFile, "w");
    if (src == NULL || dest == NULL) {
        perror("Error opening file");
        exit(1);
    }
    char line[1024];
    while (fgets(line, sizeof(line), src) != NULL) {
        fputs(line, dest);
    }
    printf("File copied line by line successfully.\n");
    fclose(src);
    fclose(dest);
}


int main() {
    char sourceFile[100];
    char destFileChar[100];
    char destFileLine[100];


    printf("Enter the name of the source file: ");
    scanf("%s", sourceFile);


    printf("Enter the name of the destination file for character-by-character copy: ");
    scanf("%s", destFileChar);


    printf("Enter the name of the destination file for line-by-line copy: ");
    scanf("%s", destFileLine);
    printf("\nCopying file character by character...\n");
    copyFileCharacterByCharacter(sourceFile, destFileChar);
    printf("\nCopying file line by line...\n");
    copyFileLineByLine(sourceFile, destFileLine);
    return 0;
}