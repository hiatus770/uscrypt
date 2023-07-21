#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <dirent.h> 
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#include "encrypt.h"
#include "decrypt.h"

// This defines the max length of a file read 
#define FILE_SIZE_LIMIT 1000000
#define KEY "KEY!"
#define isDebug 1
#define DEBUG if (isDebug)

extern int errno; 

/**
 * @brief Returns file data as a string including  
 * 
 * @param fileDir 
 * @return char* 
 */
char* getFileData(char* fileDir){ 
    FILE* filePointer = fopen(fileDir, "r");
    printf("Grabbing: %s\n", fileDir); 
    
    if (filePointer == NULL){
        perror("Error: "); 
    }

    // Set the data string to be whatever is the contents of the file
    char *data = malloc(FILE_SIZE_LIMIT * sizeof(char));
    char c;
    DEBUG printf("Reading file data\n");
    int i = 0;
    while ((c = fgetc(filePointer)) != -1){
        data[i] = c;
        i++;
    }
    DEBUG printf("Finished reading file data\n");
    data[i] = '\0';
    DEBUG printf("Data: %s\n", data);

    fclose(filePointer);

    return data;
}

/**
 * @brief  Writes data to a file, called fileDir 
 * 
 * @param fileDir  The directory of the file to be written to
 * @param data  The data to be written to the file as a string 
 */
void writeFileData(char* fileDir, char* data){
    // Open the file in binary write mode
    FILE* file = fopen(fileDir, "w+");

    if (file == NULL) {
        // File doesn't exist, create a new one
        file = fopen(fileDir, "w+");
        if (file == NULL) {
            printf("Error creating the file %s\n", fileDir);
            return;
        }
    }    if (file == NULL) {
        printf("Error opening the file %s\n", fileDir);
        return;
    }

    // Calculate the size of the data
    size_t dataSize = sizeof(char);
    while (data[dataSize] != '\0') {
        dataSize++;
    }

    // Write the data to the file
    size_t bytesWritten = fwrite(data, sizeof(char), dataSize, file);

    if (bytesWritten != dataSize) {
        printf("Error writing data to the file %s\n", fileDir);
    } else {
        printf("Data successfully written to the file %s\n", fileDir);
    }

    // Close the file
    fclose(file);
}

void main (int argc, char *argv[]){ 
    if (argc > 2){ 
        if (strcmp(argv[1], "encrypt") == 0){
            // ENCRYPTION  
            
            // They failed to use the command properly  
            if (argc == 3){
                printf("Second argument missing for <encrypt>, usage is ./main 1<encrypt> 2<fileDir> <fileExport>"); 
            }    

            // 0:executable 1:encrypt 2:folderInput 3:folderOutput
            char* folderInput = argv[2]; // Folder input   
            char* folderOutput = argv[3]; // Folder output 
            
            // Open up the directory 
            struct dirent *de; 
            DIR *dr = opendir(folderInput);
            
            // If there was an error opening the directory then cry 
            if (dr == NULL){
                printf("ERROR: Could not open directory"); 
                return; 
            }

            printf("Encrypting files of %s to %s\n", folderInput, folderOutput);

            // Loop througgh each item in the folder 
            while ((de = readdir(dr)) != NULL){
                printf("Encrypting file: %s\n", de->d_name);
                // Getting file information
                if (strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0){
                    // Ignore these folders bc they dont contain items 
                    continue; 
                }

                // Getting the path 
                char* fileName = de->d_name;
                char fileDirectory[255] = "";

                // add them together
                strcat(fileDirectory, folderInput);
                strcat(fileDirectory, "/"); 
                strcat(fileDirectory, fileName);

                // Getting file data
                char* fileData = getFileData(fileDirectory); 
                DEBUG printf("Successfully Grabbed Data from: %s\n", fileDirectory);
                
                
                // Writing file data 
                char exportDirectory[] = "";
                sprintf(exportDirectory, "%s/%s", folderOutput, fileName);  
                DEBUG printf("Export Dir: %s\n", exportDirectory);

                FILE * testPointer = fopen(exportDirectory, "w");  
                if (!testPointer){
                    mkdir(folderOutput, "777");
                } else {
                    fclose(testPointer);
                }

                // Write all the encrypted data to the file inside of the folderInput directory 
                DEBUG printf("Export Dir: %s\n", exportDirectory); 
                DEBUG printf("Encrypted data: %s\n", encrypt(fileData, KEY));
                writeFileData(exportDirectory, encrypt(fileData, KEY)); 
            }
            closedir(dr); 
        } else if (strcmp(argv[1], "decrypt") == 0){
            // DECRYPT COMMAND
            DEBUG printf("Decrypt function starting!"); 
            
            // They failed to use the command properly  
            if (argc == 2){
                printf("Second argument missing for <decrypt>, usage is ./main 1<encrypt> 2<fileDir> <fileExport>"); 
            }    

            // 0:executable 1:encrypt 2:folderInput 3:folderOutput
            char* folderInput = argv[2]; // Folder input   
            char* folderOutput = argv[3]; // Folder output 
            
            // Open up the directory 
            struct dirent *de; 
            DIR *dr = opendir(folderInput);
            
            // If there was an error opening the directory then cry 
            if (dr == NULL){
                printf("ERROR: Could not open directory"); 
                return; 
            }

            printf("Decrypting files of %s to %s\n", folderInput, folderOutput);

            // Loop througgh each item in the folder 
            while ((de = readdir(dr)) != NULL){
                // Getting file information
                if (strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0){
                    // Ignore these folders bc they dont contain items 
                    continue; 
                }

                // Getting the path 
                char* fileName = de->d_name;
                char fileDirectory[255] = "";

                // add them together
                strcat(fileDirectory, folderInput);
                strcat(fileDirectory, "/"); 
                strcat(fileDirectory, fileName);

                // Getting file data
                char* fileData = getFileData(fileDirectory); 
                DEBUG printf("Successfully Grabbed Data from: %s\n", fileDirectory);
                
                // Writing file data 
                char*  exportDirectory = (char*)malloc(strlen(folderOutput)+strlen(fileName)+2); 
                sprintf(exportDirectory, "%s/%s", folderOutput, fileName);  

                FILE * testPointer = fopen(exportDirectory, "r");  
                DEBUG printf("Testing pointer value %p\n", testPointer); 
                if (!testPointer){
                    DEBUG printf("Making new directory %s\n", exportDirectory); 
                    mkdir(folderOutput, "777");
                } else {
                    fclose(testPointer); 
                }
                DEBUG printf("Closing test pointer"); 


                // Write all the encrypted data to the file inside of the folderInput directory 
                DEBUG printf("Export Dir: %s\n", exportDirectory); 
                writeFileData(exportDirectory, decrypt(fileData, KEY)); 
                free(exportDirectory);  
            }
            closedir(dr); 
        }
    } else if (argc != 0 && strcmp(argv[1], "--help") == 0){
        printf("Available commands:\n"); 
        printf("encrypt <folderInput> <folderOutput>\n"); 
        printf("decrypt <folderInput> <folderOutput>\n"); 
        printf("uscrypt --help\n"); 
    } else {
        printf("Invalid command, use uscrypt --help to list available commands\n"); 
    }
}