#include <stdio.h>

int main(int argc, char* argv[]) {
    FILE* file = fopen("./src/hydrogen/test.hydro", "r");
    char fileContents[1000];

    if(file != NULL) {
        while(fgets(fileContents, sizeof(fileContents), file) != NULL) {
            printf("%s", fileContents);
        }
    } else {
        printf("File not found!\n");
    }

    fclose(file);
}