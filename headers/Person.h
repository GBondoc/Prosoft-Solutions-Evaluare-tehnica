#pragma once

// Person.h HAD BIGGER SIZES COMPARED TO WHAT WAS ASKED IN BINARY FILES

// I CHANGED THIS FILE FOR EASIER CODE TO READ
// EXAMPLE OF NOT HAVING THIS FILE CHANGED IS ON GENDER
// BECAUSE GENDER HAS A SIZE OF 4 AND BINARY FILE ASKED FOR SIZE 1 ON THAT FIELD
// SO I HAD TO DO IMPLEMENT IT A BIT DIFFERENT
// SPECIFIED CHANGES FOR GENDER ARE ON: GenerateBinaryFile.c in line 73; ComputeBinaryFileToASCII.c;

// I CHECKED THEIR SIZES FOR OTHER POSSIBLE MEMORY OPTIMIZATION AND HERE IS WHAT I FOUND
// I CHANGED GENDER LOCATION IN PERSONAL INFO
// THIS IS NOT A RANDOM CHANGE EVEN THOUGH IT DOES NOT INFLUENCE THE SIZE IN THIS SPECIFIC SCENARIO

struct AddressTmpl
{
    char sStreet[31];
    char sCity[31];
    char sCountry[31];
};

enum Gender
{
    Male = 1,
    Female = 2
};

struct PersonTmpl
{
    int nPersonID;

    char chRecordType;
#define REC_TYPE_PERSONAL  1
#define REC_TYPE_HOME      2
#define REC_TYPE_WORK      3

    union
    {
        struct /* record type 1 */
        {
            enum Gender theGender;
            char sFirstName[31];
            char sLastName[31];
            char sBirthdate[11]; /* YYYY/MM/DD date format */
        }PersonalInfo;

        struct /* record type 2 */
        {
            struct AddressTmpl homeAddress;
            char sPhone[16];
            char sEmail[31];
        }HomeDetails;

        struct /* record type 3 */
        {
            char sCompany[31];
            struct AddressTmpl workAddress;
            char sPhone[16];
            char sFax[16];
            char sEmail[31];
        }WorkDetails;
    }Details;
};