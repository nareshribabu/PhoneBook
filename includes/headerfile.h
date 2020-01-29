#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct contact {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};

typedef struct contactInfo {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
    char *firstName;
    char *lastName;
    char *compName;
    char *email;
} Info;

typedef struct readContact {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
} Read;

int emailCheck (char emailBuffer[500]);
void calcPos (Info * storeInfo, int numContacts);
void NumberFunction (Info *storeInfo, int chooseNum);
void CalcSizes (Read record, long *fnSize, long *lnSize, long *compSize, long *emailSize);
int compare_name_ascending ( const void * a, const void * b);
void displayContact(Info *storeInfo, int numRecords);
void writeLocations (FILE *file, Info *storeInfo, int numRecords);
void setToNullRecord (Read record);
void printContact (int i, Info *storeInfo, Read record, long fnSize, long lnSize, long compSize, long emailSize, FILE *file);
int countDigits (long num);
