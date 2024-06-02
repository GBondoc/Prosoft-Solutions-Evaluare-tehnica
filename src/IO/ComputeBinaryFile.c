#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../headers/Person.h"

// Each record is separated by \r at the end in the binary file
void skipToNextRecord(FILE *binaryFile) {
    char c;
    while ((c = fgetc(binaryFile)) != EOF) {
        if (c == '\r') {
            break;
        }
    }
    // Move back 2 bytes to unread the \r
    fseek(binaryFile, -1, SEEK_CUR);
}

// Function that reads \r to prepare for the next record to be read
void readCRLF(FILE *binaryFile) {
    char endLine[2];
    fread(endLine, sizeof(char), 1, binaryFile);
    endLine[1] = '\0';
}

// Function that reads a record of type PersonTmpl and loads it in person variable
int readSingleRecord(FILE *binaryFile, struct PersonTmpl *person) {

    if(fread(&person->nPersonID, sizeof(person->nPersonID), 1, binaryFile) == 1) {

        fread(&person->chRecordType, sizeof(person->chRecordType), 1, binaryFile);

        switch(person->chRecordType) {
            case REC_TYPE_PERSONAL:
                fread(&person->Details.PersonalInfo.sLastName,
                        sizeof(person->Details.PersonalInfo.sLastName), 1, binaryFile);
                person->Details.PersonalInfo.sLastName[30] = '\0';

                fread(&person->Details.PersonalInfo.sFirstName,
                        sizeof(person->Details.PersonalInfo.sFirstName), 1, binaryFile);
                person->Details.PersonalInfo.sFirstName[30] = '\0';

                fread(&person->Details.PersonalInfo.sBirthdate,
                        sizeof(person->Details.PersonalInfo.sBirthdate), 1, binaryFile);
                person->Details.PersonalInfo.sBirthdate[10] = '\0';



                char gender;
                fread(&gender, sizeof(gender), 1, binaryFile);
                
                int igender = (int) gender;

                if(igender == 1)
                    person->Details.PersonalInfo.theGender = Male;
                else if(igender == 2)
                    person->Details.PersonalInfo.theGender = Female;
                else
                    printf("3");


                break;
            case REC_TYPE_HOME:
                fread(&person->Details.HomeDetails.homeAddress.sStreet,
                        sizeof(person->Details.HomeDetails.homeAddress.sStreet), 1, binaryFile);
                person->Details.HomeDetails.homeAddress.sStreet[30] = '\0';

                fread(&person->Details.HomeDetails.homeAddress.sCity,
                        sizeof(person->Details.HomeDetails.homeAddress.sCity), 1, binaryFile);
                person->Details.HomeDetails.homeAddress.sCity[30] = '\0';
                
                fread(&person->Details.HomeDetails.homeAddress.sCountry,
                        sizeof(person->Details.HomeDetails.homeAddress.sCountry), 1, binaryFile);
                person->Details.HomeDetails.homeAddress.sCountry[30] = '\0';
                
                fread(&person->Details.HomeDetails.sPhone,
                        sizeof(person->Details.HomeDetails.sPhone), 1, binaryFile);
                person->Details.HomeDetails.sPhone[15] = '\0';
                
                fread(&person->Details.HomeDetails.sEmail,
                        sizeof(person->Details.HomeDetails.sEmail), 1, binaryFile);
                person->Details.HomeDetails.sEmail[30] = '\0';
                break;
            case REC_TYPE_WORK:
                fread(&person->Details.WorkDetails.sCompany,
                        sizeof(person->Details.WorkDetails.sCompany), 1, binaryFile);
                person->Details.WorkDetails.sCompany[30] = '\0';
                
                fread(&person->Details.WorkDetails.workAddress.sStreet,
                        sizeof(person->Details.WorkDetails.workAddress.sStreet), 1, binaryFile);
                person->Details.WorkDetails.workAddress.sStreet[30] = '\0';
                
                fread(&person->Details.WorkDetails.workAddress.sCity,
                        sizeof(person->Details.WorkDetails.workAddress.sCity), 1, binaryFile);
                person->Details.WorkDetails.workAddress.sCity[30] = '\0';
                
                fread(&person->Details.WorkDetails.workAddress.sCountry,
                        sizeof(person->Details.WorkDetails.workAddress.sCountry), 1, binaryFile);
                person->Details.WorkDetails.workAddress.sCountry[30] = '\0';
                
                fread(&person->Details.WorkDetails.sPhone,
                        sizeof(person->Details.WorkDetails.sPhone), 1, binaryFile);
                person->Details.WorkDetails.sPhone[15] = '\0';
                
                fread(&person->Details.WorkDetails.sFax,
                        sizeof(person->Details.WorkDetails.sFax), 1, binaryFile);
                person->Details.WorkDetails.sPhone[15] = '\0';
                
                fread(&person->Details.WorkDetails.sEmail,
                        sizeof(person->Details.WorkDetails.sEmail), 1, binaryFile);
                person->Details.WorkDetails.sEmail[30] = '\0';

                break;
            default:
                skipToNextRecord(binaryFile);
                readCRLF(binaryFile);
                return -1;
        }
        readCRLF(binaryFile);
        return 1;
    }
    return 0;
}

// Function that adds newPerson to the end of persons array
void addRecordToDynamicArray(struct PersonTmpl **persons, int *count, int *capacity, const struct PersonTmpl *newPerson) {
    if(*count >= *capacity) {
        *capacity = (*capacity) * 2;
        *persons = realloc(*persons, *capacity * sizeof(struct PersonTmpl));
        if(*persons == NULL) {
            printf("Memory allocation failed. Terminating program.");
            exit(1);
        }
    }
    (*persons)[*count] = (*newPerson);
    (*count)++;
}

// Function that prints in console all persons
void printRecordsInConsole(const struct PersonTmpl *persons, const int recordCount) {
    for(int i = 0; i < recordCount; i++) {
        switch (persons[i].chRecordType)
        {
        case REC_TYPE_PERSONAL:
            printf("PERSONAL: %d, %d, %s, %s, %s, ", persons[i].nPersonID,
                                                        persons[i].chRecordType,
                                                        persons[i].Details.PersonalInfo.sLastName,
                                                        persons[i].Details.PersonalInfo.sFirstName,
                                                        persons[i].Details.PersonalInfo.sBirthdate);
            if(persons[i].Details.PersonalInfo.theGender == Male)
                printf("%c", 'M');
            else if (persons[i].Details.PersonalInfo.theGender == Female)
                printf("%c", 'F');
            printf("\n");
            break;
        case REC_TYPE_HOME:
            printf("HOME: %d, %d, %s, %s, %s, %s, %s\n", persons[i].nPersonID,
                                                        persons[i].chRecordType,
                                                        persons[i].Details.HomeDetails.homeAddress.sStreet,
                                                        persons[i].Details.HomeDetails.homeAddress.sCity,
                                                        persons[i].Details.HomeDetails.homeAddress.sCountry,
                                                        persons[i].Details.HomeDetails.sPhone,
                                                        persons[i].Details.HomeDetails.sEmail);
            break;
        case REC_TYPE_WORK:
            printf("WORK: %d, %d, %s, %s, %s, %s, %s, %s, %s\n", persons[i].nPersonID,
                                                                persons[i].chRecordType,
                                                                persons[i].Details.WorkDetails.sCompany,
                                                                persons[i].Details.WorkDetails.workAddress.sStreet,
                                                                persons[i].Details.WorkDetails.workAddress.sCity,
                                                                persons[i].Details.WorkDetails.workAddress.sCountry,
                                                                persons[i].Details.WorkDetails.sPhone,
                                                                persons[i].Details.WorkDetails.sFax,
                                                                persons[i].Details.WorkDetails.sEmail);
            break;
        default:
            printf("Person with Id (%d) has unknown record type (%d). Omitting.\n", persons[i].nPersonID, (int) persons[i].chRecordType);
            break;
        }
    }
}

// Function that returns array of records of type PersonTmpl
struct PersonTmpl* getRecordsFromFile(const char *inputFilePath, int *recordCount, int *capacity) {
    FILE *binaryFile = fopen(inputFilePath, "rb");

    if(binaryFile == NULL) {
        printf("Could not open file for reading.\n");
        return NULL;
    }

    *capacity = 5; // Initial capacity of dynamic memory allocated array
    *recordCount = 0;

    struct PersonTmpl *persons = malloc(*capacity * sizeof(struct PersonTmpl));
    if(persons == NULL) {
        printf("Memory alocation failed.\n");
        fclose(binaryFile);
        return NULL;
    }

    while(!feof(binaryFile)) {
        struct PersonTmpl person;
        if(!readSingleRecord(binaryFile, &person))
            break;
        else {
            addRecordToDynamicArray(&persons, recordCount, capacity, &person);
            memset(&person, 0, sizeof(struct PersonTmpl));
        }
    }

    fclose(binaryFile);

    return persons;
}
