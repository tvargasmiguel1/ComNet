#include "Response.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *render_static_file(char *fileName) {
    if (fileName == NULL) {
        fprintf(stderr, "File name provided is NULL\n");
        return NULL;
    }

    FILE *file = fopen(fileName, "r"); // Open the file in read mode
    if (!file) { // Check if file opening failed
        perror("Error opening file");
        return NULL;
    }

    // Determine the file size by seeking to the end
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking in file");
        fclose(file);
        return NULL;
    }

    long fsize = ftell(file);
    if (fsize == -1) {
        perror("Error determining file size");
        fclose(file);
        return NULL;
    }

    // Allocate memory for the file content
    char *content = malloc(fsize + 1);
    if (!content) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Rewind the file pointer and read the file into memory
    rewind(file);
    size_t read_size = fread(content, 1, fsize, file);
    if (read_size != fsize) {
        perror("Error reading file");
        free(content);
        fclose(file);
        return NULL;
    }

    content[fsize] = '\0'; // Null-terminate the string

    fclose(file); // Close the file
    return content; // Return the content
}
