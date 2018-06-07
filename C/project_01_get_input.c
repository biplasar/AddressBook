/********************
 * <copyright information>
 * AUTHOR: Michael (Micky) Mangrobang
 * COURSE: ICS 212 Program Structure
 * INSTRUCTOR: Ravi Narayan
 * DATE: 17 October 2015
 * REVISIONS: 07 June 2018
 * FILE: project_01_get_input.c
 * DESC: Source file that contains the user input code to recieve input and returns the input
 ********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********
 * FUNC: *getName
 * DESC: Recieves string input from the user and stores it in a pointer and returns it
 * RETURN: name (char *) - The name of the person to store in the record
 **********/
char *getName();

/**********
 * FUNC: *getAddress
 * DESC: Recieves multiple lines of string input from the user and stores it in a pointer and returns it
 * RETURN: address (char *) - The person's address to store in the record
 *****************************************************************/
char *getAddress();

/**********
 * FUNC: getBirthyear
 * DESC: Recieves integer input from the user and stores it in a int and returns it. Will also deny character input
 * RETURN: birthyear (int) - The person's year of birth to store in the record
 **********/
int getBirthyear();

/**********
 * FUNC: *getTelno
 * DESC: Recieves string input from the user and stores it in a pointer and returns it
 * RETURN: telno (char *) - The person's telephone number to store in the record
 **********/
char *getTelno();

char *getName() {
    char dummy[5];
    char *name = (char *)malloc(25);

    /*Dummy fgets to take in the '\n' character from main menu input*/
    fgets(dummy, 5, stdin);

    printf("Please enter the contact's NAME. \n");
    fgets(name, 25, stdin);
    /*Removes '\n' character in the string*/
    strtok(name, "\n");

    return name;
}

char *getAddress() {
    char c;
    int numberChar;
    char *address = (char *)malloc(80);

    numberChar = 0;

    printf("Please enter the contact's ADDRESS. \n");
    printf("*NOTE: You may input multiple lines, please input '$' when you are done. \n");

    /*After pressing enter, reads input character by character until it reads '$'*/
    c = getchar();
    while (numberChar < 80 && c != '$') {
        /*Assigns each character to the array position including '\n' and exlucding '$'*/
        address[numberChar] = c;
        numberChar++;
        c = getchar();
    }

    return address;
}

int getBirthyear() {
    char ch;
    int birthyear;

    printf("Please enter the contact's BIRTH YEAR. \n");
    /*Checks to see if the input is integers*/
    while (scanf("%d", &birthyear) != 1) {

        while ((ch = getchar()) != '\n') {
            /*Disposes input that is not numbers*/
            putchar(ch);
        }

        printf(" is not an integer. Please enter an integer value. \n");
    }

    return birthyear;
}

char *getTelno() {
    char dummy[5];
    char *telno = (char *)malloc(15);
    /*Dummy fgets to take in the '\n' character from the address input*/
    fgets(dummy, 5, stdin);

    printf("Please enter the contact's TELEPHONE NUMBER. \n");
    fgets(telno, 15, stdin);
    /*Removes '\n' character in the string*/
    strtok(telno, "\n");

    return telno;
}
