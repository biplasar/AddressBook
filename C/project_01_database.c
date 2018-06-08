/********************
 * <copyright information>
 * AUTHOR: Michael (Micky) Mangrobang
 * COURSE: ICS 212 Program Structure
 * INSTRUCTOR: Ravi Narayan
 * DATE CREATED: 17 October 2015
 * LAST EDITED 07 June 2018
 * FILE: address_book_linked_list_functions.c
 * DESC: Source file that contains majority of the user interface functions for the application
 ********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

/**********
 * FUNC: addRecord
 * DESC: Adds a new record node to the end of the list
 * PARAM001: start (struct record **start) - Address of start pointer, the start of the list
 * PARAM002: inname (char []) - Name of person to store in the record
 * PARAM003: inaddress (char []) - Address of person to store in the record
 * PARAM004: inbirthyear (int) - Birth year of person to store in the record
 * PARAM005: intelno (char []) - Telephone number of the person to store in the record
 * RETURN: 1 - Record has been added to the database
 **********/
int addRecord(struct record **start,char inname[],char inaddress[], int inbirthyear, char intelno[]);

/**********
 * FUNC: printRecord
 * DESC: Prints all records with the same name that is passed through the parameters
 * PARAM001: start (struct record *) - Start pointer, the start of the list
 * PARAM002: inname (char []) - The person's name to find and print
 * RETURN: 1 - All records of the name given have been printed
 **********/
int printRecord(struct record *start, char inname[]);

/**********
 * FUNC: modifyRecord
 * DESC: Modifies all records with the same name that is passed through the parameters, with the new address and telephone number that has been passed
 * PARAM001: start (struct record *) - Start pointer, the start of the list
 * PARAM002: inname (char []) - The person's name to find and modify
 * PARAM003: inaddress (char []) - New address of person(s) to store in the record
 * PARAM004: intelno (char []) - New telephone number of the person(s) to store in the record
 * RETURN: 1 - All records of the name given have been printed
 **********/
int modifyRecord(struct record *start, char inname[], char inaddress[], char intelno[]);

/**********
 * FUNC: printAllRecords
 * DESC: Prints all records within the database
 * PARAM001: start (struct record *) - Start pointer, the start of the list
 **********/
void printAllRecords(struct record *start);

/**********
 * FUNC: deleteRecord
 * DESC: Deletes all records of the same name that is passed through the parameters
 * PARAM001: start (struct record **) - Address of start, the start of the list
 * PARAM002: inname (char []) - The person's name to find and delete
 * RETURN: 1 - All records of the name given have been deleted
 **********/
int deleteRecord(struct record **start, char inname[]);

/**********
 * FUNC: cleanUp
 * DESC: Deletes all records within the database
 * PARAM001: start (struct record **) - Addres of start, the start of the list
 **********/
void cleanUp(struct record**start);

/**********
 * FUNC: printDebug
 * DESC: Prints debug messages of all the functions
 * PARAM001: n (int) - Determines which function has been called
 * PARAM002: inname (char []) - Name of person passed through the parameter
 * PARAM003: inaddress (char []) - Address of person passed through the parameter
 * PARAM004: inbirthyear (int) - Birth year of person passed through the parameter
 * PARAM005: intelno (char []): Telephone number of the person passed through the parameter
 **********/
void printDebug(int n, char inname[], char inaddress[], int inbirthyear, char intelno[]);

extern int debug_on;

int addRecord(struct record **start, char inname[], char inaddress[], int inbirthyear, char intelno[]) {

    struct record *temp;
    struct record *index;
    struct record *previous;

    if (debug_on) {
        printDebug(1, inname, inaddress, inbirthyear, intelno);
    }

    temp = (struct record *)malloc(sizeof(struct record));

    strcpy(temp->name, inname);
    strcpy(temp->address, inaddress);
    temp->birth_year = inbirthyear;
    strcpy(temp->phone_number, intelno);

    index = *start;
    previous = NULL;

    while(index != NULL) {
        previous = index;
        index = index->next;
    }

    if(previous == NULL) {
        /*Makes sure START is still pointing to the start of the list*/
        temp->next = *start;
        *start = temp;
    } else {
        /*Makes sure the nodes are connected*/
        previous->next = temp;
        temp->next = index;
    }

    printf("Record has been added. \n");

    return 1;
}

int printRecord(struct record *start, char inname[]) {
    struct record *index;
    int printed;
    int namecmp;

    index = start;
    printed = 0;

    if (debug_on) {
        printDebug(2, inname, " ", 0, " ");
    }

    while(index != NULL) {
        namecmp = strcmp(index->name, inname);

        if(namecmp == 0) {
            printed++;

            printf("~~~~~~~~~~~~~~~ \n");
            printf("Record #%d of: \n", printed);
            printf("Name: %s \n", index->name);
            printf("Address: %s \n", index->address);
            printf("Year of Birth: %d \n", index->birth_year);
            printf("Telephone Number: %s \n", index->phone_number);

            index = index->next;
        } else {
            index = index->next;
        }
    }

    if(printed == 0) {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("No records of %s found. \n", inname);
        printf("~~~~~~~~~~~~~~~ \n");
    } else {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("%d records of %s printed. \n", printed, inname);
        printf("~~~~~~~~~~~~~~~ \n");
    }

    return 1;
}

int modifyRecord(struct record *start, char inname[],char inaddress[], char intelno[]) {
    struct record *index;
    int modified;
    int namecmp;

    if (debug_on) {
        printDebug(3, inname, inaddress, 0, intelno);
    }

    index = start;
    modified = 0;

    while(index != NULL) {

        namecmp = strcmp(index->name, inname);

        if(namecmp == 0) {

            strcpy(index->address, inaddress);
            strcpy(index->phone_number, intelno);
            index = index->next;

            modified++;
        } else {
            index = index->next;
        }
    }

    if(modified == 0) {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("No records of %s found. \n", inname);
        printf("~~~~~~~~~~~~~~~ \n");
    } else {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("%d records of %s modified. \n", modified, inname);
        printf("~~~~~~~~~~~~~~~ \n");
    }

    return 1;
}

void printAllRecords(struct record *start) {
    struct record *index;
    int count;

    index = start;
    count = 0;

    if (debug_on) {
        printDebug(4, " ", " ", 0, " ");
    }

    if(index == NULL) {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("The database is empty. \n");
        printf("~~~~~~~~~~~~~~~ \n");
    } else {

        while(index != NULL) {
            count++;

            printf("~~~~~~~~~~~~~~~ \n");
            printf("Record #%d \n", count);
            printf("Name: %s \n", index->name);
            printf("Address: %s \n", index->address);
            printf("Year of Birth: %d \n", index->birth_year);
            printf("Telephone Number: %s \n", index->phone_number);

            index = index->next;
        }

        printf("~~~~~~~~~~~~~~~ \n");
        printf("%d records printed. \n", count);
        printf("~~~~~~~~~~~~~~~ \n");
    }
}

int deleteRecord(struct record **start, char inname[]) {
    struct record *temp;
    struct record *index;
    struct record *previous;
    int deleted;
    int namecmp;

    index = *start;
    deleted = 0;

    if (debug_on) {
        printDebug(5, inname, " ", 0, " ");
    }

    while(index != NULL) {
        namecmp = strcmp(index->name, inname);

        if(namecmp == 0) {

            if(index == *start) {
                temp = index;
                index = index->next;
                *start = index;

                free(temp);
                deleted++;
            } else {

                temp = index;
                index = index->next;
                previous->next = index;

                free(temp);
                deleted++;
            }
        } else {
            previous = index;
            index = index->next;
        }
    }

    if(deleted == 0) {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("No records of %s found. \n", inname);
        printf("~~~~~~~~~~~~~~~ \n");
    } else {
        printf("~~~~~~~~~~~~~~~ \n");
        printf("%d records of %s deleted. \n", deleted, inname);
        printf("~~~~~~~~~~~~~~~ \n");
    }

    return 1;
}

void cleanUp(struct record **start) {
    struct record *temp;
    struct record *index;
    int deleted;

    if(debug_on) {
        printDebug(6, " ", " ", 0, " ");
    }

    index = *start;
    deleted = 0;

    while(index != NULL) {
        temp = index;
        index = index->next;
        *start = index;

        free(temp);
        deleted++;
    }

    printf("~~~~~~~~~~~~~~~ \n");
    printf("%d records deleted. \n", deleted);
    printf("~~~~~~~~~~~~~~~ \n");

    return;

}

void printDebug(int n, char inname[], char inaddress[], int inbirthyear, char intelno[]) {
    printf("\n*************** \n");

    if(n == 1) {
        printf("Function called with parameters: \n");
        printf("addRecord(&start, %s, %s, %d, %s); \n", inname, inaddress, inbirthyear, intelno);
    } else if(n == 2) {
        printf("Function called with parameters: \n");
        printf("printRecord(start, %s); \n", inname);
    } else if(n == 3) {
        printf("Function called with parameters: \n");
        printf("modifyRecord(start, %s, %s, %s); \n", inname, inaddress, intelno);
    } else if(n == 4) {
        printf("Function called with parameters: \n");
        printf("printAllRecords(start); \n");
    } else if(n == 5) {
        printf("Function called with parameters: \n");
        printf("deleteRecord(&start, %s); \n", inname);
    } else if(n == 6) {
        printf("Function called with parameters: \n");
        printf("cleanUp(&start); \n");
    }

    printf("*************** \n");
}
