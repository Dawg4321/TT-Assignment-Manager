#ifndef DATE_H
#define DATE_H

// *** Global Variables ***

// ~~~ g_month_arr ~~~
// array containing arrays with the num of days in each month of the year
// Each slot corresponds to whether num days is for a leap year 
// E.g. [0] = leapless year, [1] = leap year
int g_month_arr[2][12];

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
    char name[20],class[20];
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

void DiplayAssignment(Assignment A);


#endif