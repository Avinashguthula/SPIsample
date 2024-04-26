#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a line contains SPI write, read, or wait
int is_spi_operation(const char *line){
    return strstr(line, "SPIWrite") !=NULL||strstr(line, "SPIRead") != NULL||strstr(line, "WAIT") != NULL;
}
// Function to remove comments starting with "//"
void remove_comments(char *line) {
    char *comment_start = strstr(line, "//");
    if (comment_start) {
        *comment_start = '\0'; 
         }
}
int main() {
    // Open the input file for reading and output file for writing
    FILE *inputFile = fopen("Afe79xxPg1.txt", "r");
    FILE *outputFile = fopen("Afe79xxPg1_sample_onlySPI.txt", "w");
    if (inputFile == NULL||outputFile == NULL) {
        perror("Error opening file");
        fclose(inputFile); // Close the input file
        return 1;
    }
 char buffer[1024]; // Buffer to store read data
 // Read data from the input file and write to the output file
  while (fgets(buffer, sizeof(buffer), inputFile) != NULL)  {
        remove_comments(buffer);                        // Remove comments from the line
        if (is_spi_operation(buffer)) { // Remove trailing newline character
            char *newline = strchr(buffer, '\n');
            if (newline) {
                *newline = '\0';
            }    // Write the processed data to the output file
            fputs(buffer, outputFile);
            fputc('\n', outputFile);             // Add LF (Line Feed) to each line
        }
    }
    fclose(inputFile);
    fclose(outputFile);

    printf("SPI operations extracted from Afe79xxPg1.txt and written to Afe79xxPg1_sample_onlySPI.txt.\n");

    return 0;
}
