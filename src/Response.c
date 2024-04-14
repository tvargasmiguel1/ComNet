#include "Response.h" 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

char * render_static_file(char * fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");  // Provide more detailed error output
        return NULL;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    if (fsize == -1) {
        perror("Error determining file size"); // Handle errors in ftell
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the entire content plus a null terminator
    char *content = malloc(fsize + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Read the entire file into the allocated buffer
    size_t read_size = fread(content, 1, fsize, file);
    if (read_size != fsize) {
        perror("Error reading file");
        free(content);
        fclose(file);
        return NULL;
    }
    
    content[fsize] = '\0';  // Null-terminate the string
    fclose(file);
    return content;
}

