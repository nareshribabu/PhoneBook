#include "headerfile.h"

int main (){

    /*Variable Declarations*/
    long length = 0;
    long lengthFN = 0;
    long lengthLN = 0;
    long lengthComp = 0;
    long lengthEmail = 0;

    char bufferFN[500];
    char bufferLN[500];
    char bufferComp[500];
    char bufferEmail[500];

    struct contact *contact;
    Info *storeInfo;
    int size = 500;
    char buffer3[4];
    int memoryCount = 0;
    int i = 0;
    int j = 0;
    long counter = 0;
    long temp = 0;
    int found = 0;
    Read record;
    long fnSize;
    long lnSize;
    long compSize;
    long emailSize;
    long returnValue;

    /*ASSIGNMENT4 VARIABLES*/
    char action[2];
    int actionN = 0;
    char actionEdit[2];
    char actionAdd[2];
    int numContacts = 0;
    int flagToEnd = 0;
    int status;
    int k;
    int index = 0;
    char bufferEdit[500];
    long tempEdit = 0;
    long lengthEdit = 0;
    char bufferEmailEdit[500];
    long lengthEmailEdit = 0;
    int m;
    int emailValue = 0;
    int flagMain = 0;

    /*Open File*/
    FILE * file = fopen("myContactList.db", "ab+");

    /*check if the file opened properly*/
    if (file == NULL) {
        printf("Error: Unable to open the file\n");
        exit(1);
    }

    storeInfo = calloc(size, sizeof(Info));
    contact = calloc(size, sizeof(struct contact));

    /*******************************Reading file  into a structure*******************************/
    fseek(file, 0, SEEK_SET);
    found = 0;

    while (found == 0) {
        returnValue = fread(&record, sizeof(Read), 1, file);

        if (returnValue == 0) {
            found = 1;
            break;
        }
        else {

            CalcSizes (record, &fnSize, &lnSize, &compSize, &emailSize);

            contact[i].first_name_posn = record.first_name_posn;
            storeInfo[i].first_name_posn = contact[i].first_name_posn;

            contact[i].last_name_posn = record.last_name_posn;
            storeInfo[i].last_name_posn = contact[i].last_name_posn;

            contact[i].company_name_posn = record.company_name_posn;
            storeInfo[i].company_name_posn = contact[i].company_name_posn;

            contact[i].phone_number = record.phone_number;

            contact[i].email_posn = record.email_posn;
            storeInfo[i].email_posn = contact[i].email_posn;

            contact[i].next = record.next;
            storeInfo[i].next = contact[i].next;

            printContact (i, storeInfo, record, fnSize, lnSize, compSize, emailSize, file);
            storeInfo[i].phone_number = record.phone_number;

            setToNullRecord (record);

            i++;
        }
    }

    /*******************************Remove and open a new file*******************************/
    fclose(file);
    status = remove("myContactList.db");

    if (status != 0) {
        printf("Unable to delete the file\n");
    }

    file = fopen("myContactList.db", "ab+");

    /*check if the file opened properly*/
    if (file == NULL) {
        printf("Error: Unable to write to the file\n");
        exit(1);
    }

    displayContact(storeInfo, i);

    numContacts = i - 1;
    if (i == 0) {
        counter = 0;
    }
    else {
        counter = counter + contact[numContacts].next;
    }

    /*******************************Options Menu*******************************/
    do {

        do {
            printf("Action1: ");
            fscanf(stdin, "%s", action);

            flagMain = 1;

            if(isdigit(action[0]) != 0) {
                actionN = strtoul(action, NULL, 10);
                NumberFunction (storeInfo, actionN);
            }

        } while ((strncmp(action, "A", 1) != 0) && (strncmp(action, "X", 1) != 0) && (actionN <= 0));

        getchar();

        if (strncmp (action, "R", 1) == 0) {
            flagMain = 0;
            printf("\n");
            displayContact(storeInfo, (numContacts + 1));
            actionN = -1;
        }

        /*Realloc*/
        if(memoryCount >= size - 1) {
            size+= 50;
            contact = realloc(contact, sizeof(struct contact) * size);
            storeInfo = realloc(storeInfo, sizeof(Info) * size);
        }

        /*******************************A for Add*******************************/
        if ((strncmp (action, "A", 1) == 0) && (flagMain == 1)) {

            /*Set structure storeInfo to NULL*/
            strcpy(bufferFN,"\0");
            strcpy(bufferLN, "\0");
            strcpy(bufferComp,"\0");
            strcpy(bufferEmail,"\0");

            printf("\n");
            printf("New Contact\n");
            /*******************************FIRST NAME*******************************/
            printf("First Name: ");
            fgets(bufferFN, 500, stdin);

            lengthFN = strlen(bufferFN);
            bufferFN[lengthFN - 1] = '\0';

            /*******************************LAST NAME*******************************/
            printf("Last Name: ");
            fgets(bufferLN, 500, stdin);

            lengthLN = strlen(bufferLN);
            bufferLN[lengthLN - 1] = '\0';

            /*******************************COMPANY NAME*******************************/
            printf("Company Name: ");
            fgets(bufferComp, 500, stdin);

            lengthComp = strlen(bufferComp);
            bufferComp[lengthComp - 1] = '\0';

            if (strncmp(bufferLN, "\0", 1) == 0) {
                while ((strncmp(bufferComp, "\n", 1) == 0) || (strncmp(bufferComp, "\0", 1) == 0)) {

                    printf("Company Name: ");
                    fgets(bufferComp, 500, stdin);
                    lengthComp = strlen(bufferComp);
                    bufferComp[lengthComp - 1] = '\0';
                }
            }

            /*******************************PHONE NUMBER*******************************/
	    do {
                printf("Phone Number (enter only numbers): ");
                fgets(buffer3, 500, stdin);

                length = strlen(buffer3);
                buffer3[length - 1] = '\0';

                temp = strtol(buffer3, NULL, 10);

            } while (((strncmp(buffer3, "\n", 1)) == 0) || ((countDigits(temp) != 7) && (countDigits(temp) != 10)));

            /*******************************EMAIL*******************************/
            do {
                printf("Email: ");
                fgets(bufferEmail, 500, stdin);

                lengthEmail = strlen(bufferEmail);
                bufferEmail[lengthEmail - 1] = '\0';

                emailValue = emailCheck(bufferEmail);

            } while (emailValue != 6);

            emailValue = 0;
            /*******************************Save and Return for Add*******************************/
            flagMain = 0;

            do {
                printf("Action2: ");
                fscanf(stdin, "%s", actionAdd);

                getchar();

            } while ((strncmp(actionAdd, "R", 1) != 0) && (strncmp(actionAdd, "S", 1) != 0));

            /*******************************Save for Add*******************************/
            if ((strncmp(action, "A", 1) == 0) && (strncmp(actionAdd, "S", 1) == 0)) {

                flagMain = 0;
                numContacts++;

                /******************************FN Write to structure********************************/
                storeInfo[numContacts].firstName = calloc(lengthFN, sizeof(char));

                strcpy(storeInfo[numContacts].firstName, bufferFN);

                /*****FIRST NAME POSITION CALCULATIONS*****/
                if (lengthFN <= 1) {
                    storeInfo[numContacts].first_name_posn = 0;
                    counter = counter + (sizeof(struct contact)) - 1;
                }
                else {
                    counter = counter + (sizeof(struct contact));
                    storeInfo[numContacts].first_name_posn = counter;
                }

                /******************************LN Write to structure**********************************/
                storeInfo[numContacts].lastName = calloc(lengthLN, sizeof(char));
                strncpy(storeInfo[numContacts].lastName, bufferLN, lengthLN);

                /*****LAST NAME POSITION CALCULATIONS*****/
                if (lengthLN <= 1) {
                    storeInfo[numContacts].last_name_posn = 0;
                    counter = counter + lengthFN - 1;
                }
                else {
                    counter = counter + lengthFN;
                    storeInfo[numContacts].last_name_posn = counter;
                }

                /******************************Comp Write to structure********************************/
                storeInfo[numContacts].compName = calloc(lengthComp, sizeof(char));

                strncpy(storeInfo[numContacts].compName, bufferComp, lengthComp);

                /*****COMPANY NAME POSITION CALCULATIONS*****/
                if (lengthComp <= 1) {
                    storeInfo[numContacts].company_name_posn = 0;
                    counter = counter + lengthLN - 1;
                }
                else {
                    counter = counter + lengthLN;
                    storeInfo[numContacts].company_name_posn = counter;
                }

                /******************************Phone Write to structure********************************/
                storeInfo[numContacts].phone_number = temp;

                /******************************Email Write to structure********************************/
                storeInfo[numContacts].email = calloc(lengthEmail, sizeof(char));

                strncpy(storeInfo[numContacts].email, bufferEmail, lengthEmail);

                /*****EMAIL POSITION CALCULATIONS*****/
                if (lengthEmail <= 1) {
                    storeInfo[numContacts].email_posn = 0;
                    counter = counter + lengthComp - 1;
                }
                else {
                    counter = counter + lengthComp;
                    storeInfo[numContacts].email_posn = counter;
                }

                /*****NEXT POSITION CALCULATIONS*****/
                counter = counter + lengthEmail;
                storeInfo[numContacts].next = counter;

                printf("\n");
                displayContact(storeInfo, (numContacts + 1));
            }

            if ((strncmp(action, "A", 1) == 0) && (strncmp(actionAdd, "R", 1) == 0)) {
                printf("\n");
                displayContact(storeInfo, (numContacts + 1));
                actionN = -1;
            }
        }

        /*******************************D for Delete*******************************/
        if ((strncmp(action, "D", 1) == 0) && (actionN > 0)) {
            flagMain = 0;
            index = actionN - 1;

            free(storeInfo[index].firstName);
            free(storeInfo[index].lastName);
            free(storeInfo[index].compName);
            free(storeInfo[index].email);

            for (m = index; m <= numContacts; m++) {
                storeInfo[m] = storeInfo[m + 1];
            }

            numContacts = numContacts - 1;
            calcPos (storeInfo, numContacts);

            printf("\n");
            displayContact(storeInfo, (numContacts + 1));

            actionN = -1;
        }

        /*******************************E for Edit*******************************/
        if ((actionN > 0) && (strncmp(action, "E", 1) == 0)) {

            flagMain = 0;
            index = actionN - 1;

            strcpy(bufferEdit,"\0");
            strcpy(bufferEmailEdit,"\0");

            printf("\n");
            printf("Contact #%d\n", actionN);
            printf("First Name: %s\n", storeInfo[index].firstName);
            printf("Last Name: %s\n", storeInfo[index].lastName);
            printf("Company Name: %s\n", storeInfo[index].compName);

            do {
                printf("Phone Number (enter only numbers): ");
                fgets(bufferEdit, 500, stdin);

                lengthEdit = strlen(bufferEdit);
                bufferEdit[lengthEdit - 1] = '\0';

                tempEdit = strtol(bufferEdit, NULL, 10);

            } while (((strncmp(bufferEdit, "\n", 1)) == 0) || ((countDigits(tempEdit) != 7) && (countDigits(tempEdit) != 10)));

            do {
                printf("Email: ");
                fgets(bufferEmailEdit, 500, stdin);

                lengthEmailEdit = strlen(bufferEmailEdit);
                bufferEmailEdit[lengthEmailEdit - 1] = '\0';

                emailValue = emailCheck(bufferEmailEdit);

            } while (emailValue != 6);

            emailValue = 0;

            do {
                printf("Action3: ");
                fscanf(stdin, "%s", actionEdit);
            } while ((strncmp(actionEdit, "R", 1) != 0) && (strncmp(actionEdit, "S", 1) != 0) && (strncmp(actionEdit, "D", 1) != 0));

            /*******************************Save for Edit*******************************/
            if ((strncmp(actionEdit, "S", 1) == 0) && (strncmp(action, "E", 1) == 0)){

                flagMain = 0;
                /**************************Phone Write to structure*************************/
                storeInfo[index].phone_number = tempEdit;

                /**************************Email Write to structure*************************/
                free (storeInfo[index].email);

                storeInfo[index].email = calloc(lengthEmailEdit, sizeof(char));

                strncpy(storeInfo[index].email, bufferEmailEdit, lengthEmailEdit);

                /**************************Calculate new positions*************************/
                calcPos (storeInfo, numContacts);

                printf("\n");
                displayContact(storeInfo, (numContacts + 1));
            }

            if (strncmp(actionEdit, "R", 1) == 0) {
                flagMain = 0;
                printf("\n");
                displayContact(storeInfo, (numContacts + 1));
            }

            if ((strncmp(actionEdit, "D", 1) == 0) && (actionN > 0) && (strncmp(action, "E", 1) == 0)) {

                flagMain = 0;
                index = actionN - 1;

                storeInfo[index].firstName = NULL;
                free(storeInfo[index].firstName);
                storeInfo[index].lastName = NULL;
                free(storeInfo[index].lastName);
                storeInfo[index].compName = NULL;
                free(storeInfo[index].compName);
                storeInfo[index].email = NULL;
                free(storeInfo[index].email);

                for (m = index; m <= (numContacts + 1); m++) {
                    storeInfo[m] = storeInfo[m + 1];
                }

                numContacts = numContacts - 1;

                calcPos (storeInfo, numContacts);

                printf("\n");
                displayContact(storeInfo, (numContacts + 1));
            }

            actionN = -1;

        }

        /*******************************X for Exit*******************************/
        if ((strncmp(action, "X", 1) == 0) && (flagMain == 1)) {

            flagMain = 0;
            for (k = 0; k <= numContacts; k++) {

                /*Write locations to the file*/
                writeLocations (file, storeInfo, k);

                /*Write User inputs to file*/
                if ((strlen(storeInfo[k].firstName) + 1) > 1) {
                    fwrite (storeInfo[k].firstName, sizeof(char), (strlen(storeInfo[k].firstName) + 1), file);
                }
                if ((strlen(storeInfo[k].lastName) + 1) > 1) {
                    fwrite (storeInfo[k].lastName, sizeof(char), (strlen(storeInfo[k].lastName) + 1), file);
                }
                if ((strlen(storeInfo[k].compName) + 1) > 1) {
                    fwrite (storeInfo[k].compName, sizeof(char), (strlen(storeInfo[k].compName) + 1),file);
                }
                if ((strlen(storeInfo[k].email) + 1) > 1) {
                    fwrite (storeInfo[k].email, sizeof(char), (strlen(storeInfo[k].email) + 1), file);
                }

            }

            flagToEnd = 1;
        }

        memoryCount++;

    } while (flagToEnd == 0);

    fclose(file);

    free (contact);

    for(j = 0; j <= numContacts; j++) {
        free(storeInfo[j].firstName);
        free(storeInfo[j].lastName);
        free(storeInfo[j].compName);
        free(storeInfo[j].email);
    }

    free (storeInfo);

    return 0;
}





