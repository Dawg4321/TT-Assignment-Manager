#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <string.h>

// *** Global Variables ***

// ~~~ g_month_arr ~~~
// array containing arrays with the num of days in each month of the year
// Each slot of outer array corresponds to whether num days is for a leap year 
// E.g. g_month_arr[0] = leapless year, g_month_arr[1] = leap year
extern const int g_month_arr[2][12];

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
    char *name;
    char *class;
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