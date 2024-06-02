#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/ini.c"
#include "../headers/Person.h"
#include "IO/ComputeBinaryFile.c"
#include "IO/ComputeASCIIFile.c"

typedef struct {
    const char* inputFile;
    const char* outputFile;
} configuration;

static int handler(void* user, const char* section, const char* name, const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(searchedSection, searchedKey) strcmp(section, searchedSection) == 0 && strcmp(name, searchedKey) == 0
    if (MATCH("testc", "in")) {
        pconfig->inputFile = _strdup(value);
    } else if (MATCH("testc", "out")) {
        pconfig->outputFile = _strdup(value);
    } else {
        return 0;  // unknown section/name, error
    }
    return 1;
}

void setFilePaths(char *iniFilePath, char **inputFilePath, char **outputFilePath) {
    configuration config;
    if (ini_parse(iniFilePath, handler, &config) < 0) {
        printf("Can't load 'testc.ini'\n");
        exit(1);
    }

    *inputFilePath = (char *) malloc(strlen(config.inputFile) * sizeof(char));
    if (*inputFilePath == NULL) {
        printf("Failed to allocate memory on input file.\n");
        free((void *) config.inputFile);
        free((void *) config.outputFile);
        exit(1);
    }
    strcpy(*inputFilePath, config.inputFile);

    *outputFilePath = (char *) malloc(strlen(config.outputFile) * sizeof(char));
    if (*outputFilePath == NULL) {
        printf("Failed to allocate memory on output file.\n");
        free(*inputFilePath);
        free((void *) config.inputFile);
        free((void *) config.outputFile);
        exit(1);
    }
    strcpy(*outputFilePath, config.outputFile);

    free((void *) config.inputFile);
    free((void *) config.outputFile);
}

int main(int argc, char* argv[])
{

    // Get file paths
    char *inputFilePath = NULL, *outputFilePath = NULL;
    setFilePaths("../testc.ini", &inputFilePath, &outputFilePath);
    printf("Config loaded from 'testc.ini':\n");
    printf("Input File: %s\n", inputFilePath);
    printf("Output File: %s\n\n", outputFilePath);


    // Load records from binary file
    int recordCount, capacity;
    const char *binaryFileName = inputFilePath;
    struct PersonTmpl *persons = getRecordsFromFile(binaryFileName, &recordCount, &capacity);

    if(persons == NULL) {
        printf("Failed to read records from file.\n");
        return 1;
    }

    printRecordsInConsole(persons, recordCount);

    // Write records in ASCII file
    populateASCIIFile(outputFilePath, persons, &recordCount);

    // Free allocated memory
    free(persons);

    free(inputFilePath);
    free(outputFilePath);

    return 0;
}
