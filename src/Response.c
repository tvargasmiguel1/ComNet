#include "Response.h" 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

char * render_static_file(char * fileName) {
    FILE* file = fopen(fileName, "r"); // Open the file in read mode

    if (file == NULL) { // Check if file opening failed
        return NULL; // Return NULL if file doesn't exist or cannot be opened
    } else {
        printf("%s does exist \n", fileName); // Print a message indicating that the file exists
    }

    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
    long fsize = ftell(file); // Get the size of the file
    fseek(file, 0, SEEK_SET); // Move the file pointer back to the beginning of the file

    char* temp = malloc(sizeof(char) * (fsize + 1)); // Allocate memory to store file content as a string
    char ch;
    int i = 0;

    // Read characters from the file and store them in the allocated memory
    while ((ch = fgetc(file)) != EOF) {
        temp[i] = ch;
        i++;
    }
    
    fclose(file); // Close the file
    return temp; // Return the dynamically allocated string containing file content
}
