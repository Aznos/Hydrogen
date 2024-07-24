#include <stdio.h>
#include "lexer/lexer.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: ./hydrogen <filename>\n");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    char fileContents[1000];

    if(file != NULL) {
        while(fgets(fileContents, sizeof(fileContents), file) != NULL) {
            printf("%s\n", fileContents);
        }
    } else {
        printf("File not found!\n");
    }

    fclose(file);
}