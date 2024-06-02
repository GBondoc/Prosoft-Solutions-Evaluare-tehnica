#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../headers/Person.h"

// Function that prints records of type PersonTmpl to ASCII file
void populateASCIIFile(char *outputFilePath, const struct PersonTmpl *persons, const int *recordCount) {
    // Buffer used to set message to be printed in the file
    char buffer[400];
    // Variable used to check if the message was formated correctly
    int written;
    // Variable used to check if the message was written successfully in ASCII file
    size_t result;
    FILE *outputFile;

    outputFile = fopen(outputFilePath, "w");

    if(outputFile == NULL) {
        printf("Could not open file for writing.\n");
        exit(1);
    }

    for(int i = 0; i < *recordCount; i++) {
        switch(persons[i].chRecordType) {
            case REC_TYPE_PERSONAL:
            
                char gender;
                if(persons[i].Details.PersonalInfo.theGender == Male)
                    gender = 'M';
                else if(persons[i].Details.PersonalInfo.theGender == Female)
                    gender = 'F';

                written = snprintf(buffer, sizeof(buffer),
                                "%d, %d, %s, %s, %s, %c\r",
                                persons[i].nPersonID,
                                (int) persons[i].chRecordType,
                                persons[i].Details.PersonalInfo.sLastName,
                                persons[i].Details.PersonalInfo.sFirstName,
                                persons[i].Details.PersonalInfo.sBirthdate,
                                gender);

                if (written < 0) {
                    printf("Error formatting string for person with Id %d\n", persons[i].nPersonID);
                    continue;
                }

                // Write the formatted string to the file
                result = fwrite(buffer, sizeof(char), written, outputFile);
                if (result != written) {
                    printf("Error writing to file\n");
                }
                break;
            case REC_TYPE_HOME:
                written = snprintf(buffer, sizeof(buffer),
                                "%d, %d, %s, %s, %s, %s, %s\r",
                                persons[i].nPersonID,
                                (int) persons[i].chRecordType,
                                persons[i].Details.HomeDetails.homeAddress.sStreet,
                                persons[i].Details.HomeDetails.homeAddress.sCity,
                                persons[i].Details.HomeDetails.homeAddress.sCountry,
                                persons[i].Details.HomeDetails.sPhone,
                                persons[i].Details.HomeDetails.sEmail);

                if (written < 0) {
                    printf("Error formatting string for person with Id %d\n", persons[i].nPersonID);
                    continue;
                }

                // Write the formatted string to the file
                result = fwrite(buffer, sizeof(char), written, outputFile);
                if (result != written) {
                    printf("Error writing to file\n");
                }
                break;
            case REC_TYPE_WORK:
                written = snprintf(buffer, sizeof(buffer),
                                "%d, %d, %s, %s, %s, %s, %s, %s, %s\r",
                                persons[i].nPersonID,
                                (int) persons[i].chRecordType,
                                persons[i].Details.WorkDetails.sCompany,
                                persons[i].Details.WorkDetails.workAddress.sStreet,
                                persons[i].Details.WorkDetails.workAddress.sCity,
                                persons[i].Details.WorkDetails.workAddress.sCountry,
                                persons[i].Details.WorkDetails.sPhone,
                                persons[i].Details.WorkDetails.sFax,
                                persons[i].Details.WorkDetails.sEmail);

                if (written < 0) {
                    printf("Error formatting string for person with Id %d\n", persons[i].nPersonID);
                    continue;
                }

                // Write the formatted string to the file
                result = fwrite(buffer, sizeof(char), written, outputFile);
                if (result != written) {
                    printf("Error writing to file\n");
                }
                break;
            default:
                written = snprintf(buffer, sizeof(buffer),
                                "Person with Id (%d) has unknown record type (%d) and could not be loaded\r",
                                persons[i].nPersonID, persons[i].chRecordType);
                
                if (written < 0) {
                    printf("Error formatting string for person with Id %d\n", persons[i].nPersonID);
                    continue;
                }

                // Write the formatted string to the file
                result = fwrite(buffer, sizeof(char), written, outputFile);
                if (result != written) {
                    printf("Error writing to file\n");
                }

                break;
        }
    }

    fclose(outputFile);
}