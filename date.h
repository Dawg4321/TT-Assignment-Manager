#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <string.h>
#include <time.h>

// *** Structs ***

// ~~~ Date ~~~
// Struct to store a date
typedef struct Date{ 
    int day,month,year;
}Date;

// ~~~ Assignment ~~~
// Struct to store data relating to each assignment due
typedef struct Assignment{
    struct Date AssDate;
    char name[25];
    char class[25];
}Assignment;

// *** Functions ***

// ~~~ CalcDueDays ~~~
// Returns the number of days inbetween two dates
// Function accounts for leap years
int CalcDueDays(Date year1, Date year2);

// ~~~ LeapYear ~~~
// Determines whether a year is a leap year. 
int LeapYear(int y);

// ~~~ DisplayAssignment ~~~
// Prints Assignment details to terminal
void DiplayAssignment(Assignment A,int n_width, int c_width);


#endif