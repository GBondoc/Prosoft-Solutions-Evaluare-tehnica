#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../headers/Person.h"

struct PersonTmpl persons[8];

void createPersons() {
    persons[0].nPersonID = 11;
    persons[0].chRecordType = REC_TYPE_PERSONAL;
    strcpy(persons[0].Details.PersonalInfo.sLastName, "Ion");
    strcpy(persons[0].Details.PersonalInfo.sFirstName, "Mihai");
    strcpy(persons[0].Details.PersonalInfo.sBirthdate, "11-02-2000");
    persons[0].Details.PersonalInfo.theGender = Male;

    
    persons[1].nPersonID = 12;
    persons[1].chRecordType = REC_TYPE_PERSONAL;
    strcpy(persons[1].Details.PersonalInfo.sLastName, "Vasilica");
    strcpy(persons[1].Details.PersonalInfo.sFirstName, "Andreea");
    strcpy(persons[1].Details.PersonalInfo.sBirthdate, "15-12-2010");
    persons[1].Details.PersonalInfo.theGender = Female;

    
    persons[2].nPersonID = 13;
    persons[2].chRecordType = REC_TYPE_HOME;
    strcpy(persons[2].Details.HomeDetails.homeAddress.sStreet, "Calea Rahovei");
    strcpy(persons[2].Details.HomeDetails.homeAddress.sCity, "Bucuresti");
    strcpy(persons[2].Details.HomeDetails.homeAddress.sCountry, "Romania");
    strcpy(persons[2].Details.HomeDetails.sPhone, "+408162381");
    strcpy(persons[2].Details.HomeDetails.sEmail, "ajshdas@gmail.com");

    
    persons[3].nPersonID = 14;
    persons[3].chRecordType = REC_TYPE_WORK;
    strcpy(persons[3].Details.WorkDetails.sCompany, "PSS Prosoft Solutions");
    strcpy(persons[3].Details.WorkDetails.workAddress.sStreet, "Surprise");
    strcpy(persons[3].Details.WorkDetails.workAddress.sCity, "Bucuresti");
    strcpy(persons[3].Details.WorkDetails.workAddress.sCountry, "Romania");
    strcpy(persons[3].Details.WorkDetails.sPhone, "+401827371");
    strcpy(persons[3].Details.WorkDetails.sFax, "Fax");
    strcpy(persons[3].Details.WorkDetails.sEmail, "PSS@gmail.com");


    persons[4].nPersonID = 15;
    persons[4].chRecordType = 6;
    strcpy(persons[4].Details.PersonalInfo.sLastName, "asjhd");
    strcpy(persons[4].Details.PersonalInfo.sFirstName, "hdfghdfg");
    strcpy(persons[4].Details.PersonalInfo.sBirthdate, "whatever");
    persons[4].Details.PersonalInfo.theGender = Male;
    

    persons[5].nPersonID = 16;
    persons[5].chRecordType = REC_TYPE_WORK;
    strcpy(persons[5].Details.WorkDetails.sCompany, "Gigel SRL");
    strcpy(persons[5].Details.WorkDetails.workAddress.sStreet, "13 Septembrie");
    strcpy(persons[5].Details.WorkDetails.workAddress.sCity, "Bucuresti");
    strcpy(persons[5].Details.WorkDetails.workAddress.sCountry, "Romania");
    strcpy(persons[5].Details.WorkDetails.sPhone, "+4018213261");
    strcpy(persons[5].Details.WorkDetails.sFax, "Fax2");
    strcpy(persons[5].Details.WorkDetails.sEmail, "GSRL@gmail.com");

    persons[6].nPersonID = 17;
    persons[6].chRecordType = REC_TYPE_PERSONAL;
    strcpy(persons[6].Details.PersonalInfo.sLastName, "Ion2");
    strcpy(persons[6].Details.PersonalInfo.sFirstName, "Mihai2");
    strcpy(persons[6].Details.PersonalInfo.sBirthdate, "11-02-2000");
    persons[6].Details.PersonalInfo.theGender = Male;

    
    persons[7].nPersonID = 18;
    persons[7].chRecordType = REC_TYPE_HOME;
    strcpy(persons[7].Details.HomeDetails.homeAddress.sStreet, "Calea Rahovei2");
    strcpy(persons[7].Details.HomeDetails.homeAddress.sCity, "Bucuresti2");
    strcpy(persons[7].Details.HomeDetails.homeAddress.sCountry, "Romania2");
    strcpy(persons[7].Details.HomeDetails.sPhone, "+40816381");
    strcpy(persons[7].Details.HomeDetails.sEmail, "ajshdas2@gmail.com");
}

void generateBinaryFile(char *path) {
    FILE *binaryFile;

    binaryFile = fopen(path, "wb");
    if(binaryFile == NULL) {
        printf("Could not open file for writing.");
        return;
    }

    // Write the number of records to the file
    int person_count = sizeof(persons) / sizeof(persons[0]);
    for (int i = 0; i < person_count; i++) {
        fwrite(&persons[i].nPersonID, sizeof(persons[i].nPersonID), 1, binaryFile);
        fwrite(&persons[i].chRecordType, sizeof(persons[i].chRecordType), 1, binaryFile);
        switch(persons[i].chRecordType) {
            case REC_TYPE_PERSONAL:
                fwrite(&persons[i].Details.PersonalInfo.sLastName, sizeof(persons[i].Details.PersonalInfo.sLastName), 1, binaryFile);
                fwrite(&persons[i].Details.PersonalInfo.sFirstName, sizeof(persons[i].Details.PersonalInfo.sFirstName), 1, binaryFile);
                fwrite(&persons[i].Details.PersonalInfo.sBirthdate, sizeof(persons[i].Details.PersonalInfo.sBirthdate), 1, binaryFile);
                // CHANGE GENDER TO CHAR SO IT INSERTS 1 BYTE INSTEAD OF 4
                char gender = persons[i].Details.PersonalInfo.theGender;
                fwrite(&gender, sizeof(gender), 1, binaryFile);
                break;
            case REC_TYPE_HOME:
                fwrite(&persons[i].Details.HomeDetails.homeAddress.sStreet, sizeof(persons[i].Details.HomeDetails.homeAddress.sStreet), 1, binaryFile);
                fwrite(&persons[i].Details.HomeDetails.homeAddress.sCity, sizeof(persons[i].Details.HomeDetails.homeAddress.sCity), 1, binaryFile);
                fwrite(&persons[i].Details.HomeDetails.homeAddress.sCountry, sizeof(persons[i].Details.HomeDetails.homeAddress.sCountry), 1, binaryFile);
                fwrite(&persons[i].Details.HomeDetails.sPhone, sizeof(persons[i].Details.HomeDetails.sPhone), 1, binaryFile);
                fwrite(&persons[i].Details.HomeDetails.sEmail, sizeof(persons[i].Details.HomeDetails.sEmail), 1, binaryFile);
                break;
            case REC_TYPE_WORK:
                fwrite(&persons[i].Details.WorkDetails.sCompany, sizeof(persons[i].Details.WorkDetails.sCompany), 1, binaryFile);
                fwrite(&persons[i].Details.WorkDetails.workAddress.sStreet, sizeof(persons[i].Details.WorkDetails.workAddress.sStreet), 1, binaryFile);
                fwrite(&persons[i].Details.WorkDetails.workAddress.sCity, sizeof(persons[i].Details.WorkDetails.workAddress.sCity), 1, binaryFile);
                fwrite(&persons[i].Details.WorkDetails.workAddress.sCountry, sizeof(persons[i].Details.WorkDetails.workAddress.sCountry), 1, binaryFile);
                fwrite(&persons[i].Details.WorkDetails.sPhone, sizeof(persons[i].Details.WorkDetails.sPhone), 1, binaryFile);
                fwrite(&persons[i].Details.WorkDetails.sFax, sizeof(persons[i].Details.WorkDetails.sFax), 1, binaryFile);
                fwrite(&persons[i].Details.WorkDetails.sEmail, sizeof(persons[i].Details.WorkDetails.sEmail), 1, binaryFile);
                break;
        }
        fwrite("\r", sizeof(char), 1, binaryFile);
    }

    // Close the file after writing
    fclose(binaryFile);
}

int main() {
    createPersons();
    generateBinaryFile("../../files/Person.dat");
    return 0;
}