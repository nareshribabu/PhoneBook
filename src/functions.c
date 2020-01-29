#include "headerfile.h"

/************************************************CALCULATE NEW POSITIONS*****************************************************/
int emailCheck (char emailBuffer[500]) {

    char email2[500] = "\0";
    char email3[500] = "\0";
    int i;
    long length = 0;
    int validCheck = 0;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    char period = '.';
    char *returnPtr;


    length = strlen(emailBuffer);

    for (i = 0; i < length; i++) {

        if (strncmp(&emailBuffer[i], "@", 1) == 0) {
            break;
        }
        email2[i] = emailBuffer[i];
    }

    if (strlen(email2) > 0) {
      flag1 = 1;
    }

    returnPtr = strchr(emailBuffer, '@');
    if (returnPtr != NULL) {
        if (strlen(returnPtr) > 0) {
            strcpy(email3, returnPtr);
            flag2 = 2;
        }
    }

    returnPtr = strchr(email3, period);

    if (returnPtr != NULL) {
        if (strncmp(returnPtr, ".com", 4) == 0) {
            flag3 = 3;
        }
    }

    validCheck = flag1 + flag2 + flag3;

    return validCheck;
}

/************************************************CALCULATE NEW POSITIONS*****************************************************/
void calcPos (Info * storeInfo, int numContacts) {

    int m = 0;
    int fixPos = 0;

    for (m = 0; m <= numContacts; m++) {

        /*****FIRST NAME POSITION CALCULATIONS*****/
        if ((strlen(storeInfo[m].firstName)) <= 1) {
            storeInfo[m].first_name_posn = 0;
            fixPos = fixPos + (sizeof(struct contact)) - 1;
        }
        else {
            fixPos = fixPos + (sizeof(struct contact));
            storeInfo[m].first_name_posn = fixPos;
        }

        /*****LAST NAME POSITION CALCULATIONS*****/
        if ((strlen(storeInfo[m].lastName)) <= 1) {
            storeInfo[m].last_name_posn = 0;
            fixPos = fixPos + ((strlen(storeInfo[m].firstName)) + 1)- 1;
        }
        else {
            fixPos = fixPos + ((strlen(storeInfo[m].firstName)) + 1);
            storeInfo[m].last_name_posn = fixPos;
        }

        /*****COMPANY NAME POSITION CALCULATIONS****/
        if ((strlen(storeInfo[m].compName)) <= 1) {
            storeInfo[m].company_name_posn = 0;
            fixPos = fixPos + ((strlen(storeInfo[m].lastName)) + 1) - 1;
        }
        else {
            fixPos = fixPos + ((strlen(storeInfo[m].lastName)) + 1);
            storeInfo[m].company_name_posn = fixPos;
        }

        if ((strlen(storeInfo[m].email)) <= 1) {
            storeInfo[m].email_posn = 0;
            fixPos = fixPos + ((strlen(storeInfo[m].compName)) + 1) - 1;
        }
        else {
            fixPos = fixPos + ((strlen(storeInfo[m].compName)) + 1);
            storeInfo[m].email_posn = fixPos;
        }

        /*****NEXT POSITION CALCULATIONS*****/
        fixPos = fixPos + ((strlen(storeInfo[m].email)) + 1);
        storeInfo[m].next = fixPos;
    }

    return;
}

/************************************************NUMBER FUNCTION*****************************************************/
void NumberFunction (Info *storeInfo, int chooseNum) {

    chooseNum = chooseNum - 1;
    printf("\n");
    printf("Contact #%d\n", chooseNum + 1);
    printf("First Name: %s\n", storeInfo[chooseNum].firstName);
    printf("Last Name: %s\n", storeInfo[chooseNum].lastName);
    printf("Phone: %lu\n", storeInfo[chooseNum].phone_number);
    printf("Company Name: %s\n", storeInfo[chooseNum].compName);
    printf("Email: %s\n", storeInfo[chooseNum].email);

    return;
}


/************************************************READ SIZES FROM FILE************************************************/
void CalcSizes (Read record, long *fnSize, long *lnSize, long *compSize, long *emailSize) {
/*FIX MEEEEEEEEE!!!!!use fread to read 1 character at a time and keep a counter and loop until it hits a null character*/

     /*FN SIZE*/
    if (record.first_name_posn == 0) {
        *fnSize = 0;
    }
    else if (record.last_name_posn == 0) {
        *fnSize = record.company_name_posn - record.first_name_posn;
    }
    else {
        *fnSize = record.last_name_posn - record.first_name_posn;
    }

    /*LN SIZE*/
    if (record.last_name_posn == 0) {
        *lnSize = 0;
    }
    else if (record.company_name_posn == 0) {
        *lnSize = record.email_posn - record.last_name_posn;
    }
    else {
        *lnSize = record.company_name_posn - record.last_name_posn;
    }

    /*Comp SIZE*/
    if (record.company_name_posn == 0) {
        *compSize = 0;
    }
    else if (record.email_posn == 0) {
        *compSize = record.next - record.company_name_posn;
    }
    else {
        *compSize = record.email_posn - record.company_name_posn;
    }

    /*Email SIZE*/
    if (record.email_posn == 0) {
        *emailSize = 0;
    }
    else {
        *emailSize = record.next - record.email_posn;
    }

    return;
}

/************************************************COMPARE COMP FUNCTION***********************************************/
int compare_name ( const void * a, const void * b) {

    int returnVar;

    const Info * var1 = a;
    const Info * var2 = b;

    char string1[1000] = "\0";
    char string2[1000] = "\0";

    strcpy(string1, var1->lastName);
    strcat(string1, var1->compName);

    strcpy(string2, var2->lastName);
    strcat(string2, var2->compName);

    /*compare the two strings togeather*/
    returnVar = strcmp(string1,string2);

    return returnVar;
}

/************************************************DISPLAY CONTACT (SORTED)********************************************/
void displayContact(Info *storeInfo, int numRecords) {

    int i;
    int (*compare_ptr)(const void *a, const void *b);
    char alpha = '0';

    printf("Number of contacts: %d\n", numRecords);

    compare_ptr = &compare_name;

    qsort (storeInfo, numRecords, sizeof(Info), compare_ptr);

    for (i = 0; i < numRecords; i++) {
        if (strlen(storeInfo[i].lastName) <= 1) {
            if (strncmp(&alpha, storeInfo[i].compName, 1) != 0) {
                alpha = storeInfo[i].compName[0];
                printf("%c\n", alpha);
            }
            printf ("    %d. %s\n", (i+1), storeInfo[i].compName);
        }
        else {
            if (strncmp(&alpha, storeInfo[i].lastName, 1) != 0) {
                alpha = storeInfo[i].lastName[0];
                printf("%c\n", alpha);
            }
            printf ("    %d. %s %s\n", (i+1), storeInfo[i].firstName, storeInfo[i].lastName);
        }
     }

   return;
}

/*****************************************************WRITE LOCATIONS FILE*************************************************/
void writeLocations (FILE *file, Info *storeInfo, int numRecords) {

    fwrite(&storeInfo[numRecords].phone_number, sizeof(unsigned long), 1, file);
    fwrite(&storeInfo[numRecords].first_name_posn, sizeof(unsigned long), 1, file);
    fwrite(&storeInfo[numRecords].last_name_posn, sizeof(unsigned long), 1, file);
    fwrite(&storeInfo[numRecords].company_name_posn, sizeof(unsigned long), 1, file);
    fwrite(&storeInfo[numRecords].email_posn, sizeof(unsigned long), 1, file);
    fwrite(&storeInfo[numRecords].next, sizeof(unsigned long), 1, file);

    return;
}

/*****************************************************SET TO NULL FOR RECORD*************************************************/
void setToNullRecord (Read record) {

    record.phone_number = 0;
    record.first_name_posn = 0;
    record.last_name_posn = 0;
    record.company_name_posn= 0;
    record.email_posn = 0;
    record.next = 0;

    return;
}

/*****************************************************PRINT CONTACT INFORMATION*************************************************/
void printContact (int i, Info *storeInfo, Read record, long fnSize, long lnSize, long compSize, long emailSize, FILE *file) {

    if (record.first_name_posn != 0) {
        storeInfo[i].firstName = calloc((fnSize), sizeof(char));
        fread(storeInfo[i].firstName, sizeof(char), fnSize, file);
    }
    else if (record.first_name_posn == 0) {
        storeInfo[i].firstName = calloc(1, sizeof(char));
        strcpy(storeInfo[i].firstName, "\0");
    }
    if (record.last_name_posn != 0) {
        storeInfo[i].lastName = calloc((lnSize), sizeof(char));
        fread(storeInfo[i].lastName, sizeof(char), lnSize, file);
    }
    else if (record.last_name_posn == 0) {
        storeInfo[i].lastName = calloc(1, sizeof(char));
        strcpy(storeInfo[i].lastName, "\0");
    }
    if (record.company_name_posn != 0) {
        storeInfo[i].compName = calloc((compSize), sizeof(char));
        fread(storeInfo[i].compName, sizeof(char), compSize, file);
    }
    else if (record.company_name_posn == 0) {
        storeInfo[i].compName = calloc(1, sizeof(char));
        strcpy(storeInfo[i].compName, "\0");
    }

    storeInfo[i].phone_number = record.phone_number;

    if (record.email_posn != 0) {
        storeInfo[i].email = calloc((emailSize), sizeof(char));
        fread(storeInfo[i].email, sizeof(char), emailSize, file);
    }
    else if (record.email_posn == 0) {
        storeInfo[i].email = calloc(1, sizeof(char));
        strcpy(storeInfo[i].email,"\0");
    }

    return;
}

/*Function definitions*/
int countDigits (long num) {

    int numDigits = 0;

    while (num != 0) {

        num = num / 10;
        numDigits++;
    }

    return numDigits;
}
