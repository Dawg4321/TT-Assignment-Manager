#include "date.h"

// *** Global Variables ***
// array containing arrays with the num of days in each month of the year
// Each slot of outer array corresponds to whether num days is for a leap year 
// E.g. g_month_arr[0] = leapless year, g_month_arr[1] = leap year
const int g_month_arr[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
                          {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}}; 

// *** Functions ***

// ~~~ CalcDueDays ~~~
// Return variable: due_days
// E.g. year2 = 21/12/2021 & year1 = 22/09/21. due_days = 120
// Other Cases:
// If year1 > year2, due_days = negative value
// If year1 == year2, due_days = 0
// ~~~~~~~~~~~~~~~~~~~
int CalcDueDays(Date year1, Date year2){

    
    int due_days = 0;

    // determining whether year 1 and 2 are leap years
    // LeapYear() returns 1 if leap year
    int leap1 = LeapYear(year1.year);
    int leap2 = LeapYear(year2.year);

    int year_difference = year2.year - year1.year;    // get number of years in between date
    int month_difference = year2.month - year1.month; // get number of months in between dates
    
    if (year_difference == 0){

        if (month_difference == 0) // if year2.month == year1.month
            due_days = year2.day - year1.day;

        else{   

            if (month_difference > 0){  // if month_difference = positive (date is in future)
                due_days = g_month_arr[leap2][year2.month -1] + year2.day - year1.day;
                if (month_difference == 1)
                    due_days--; // subtract additional day as it will be counted twice in while loop
            }
            else // if month_difference = negative (date is in past)
                due_days = year2.day - g_month_arr[leap1][year1.day -1] - year1.day -1;
            
            int i = month_difference;
            
            while (i != 1 && i != -1){ // iterate through remaining months to add/subtract
                if (i > 0){ // if month difference positive, add number of days in next month
                    due_days += g_month_arr[leap2][year2.month - 1 + i]; 
                    i--;
                }
                else{       // if month difference negative, sub number of days in next month
                    due_days -= g_month_arr[leap2][year2.month - 1 + i];
                    i++;
                }
            }
        }
    }
    else{
        // TODO: Implement year1 != year2 case for day calculation
        due_days = -111111; // placeholder value to show if incorrect case is met
    }
    
    return due_days;
}

// ~~~ LeapYear ~~~
// int y = year to test.
// If y = LeapYear, return 1
// If y = !Leapyear, return 0
// E.g. y = 2000, return = 1
// ~~~~~~~~~~~~~~~~
int LeapYear(int y){
    if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
        return 1;
    else
        return 0;
}

// ~~~ DisplayAssignment ~~~
// Pass in assignment to print
// n_width = width for name output
// c_width = width for class output
// function best used in a table of assignments
// for best results, ensure n_width and c_width are the same accross table output
// ~~~~~~~~~~~~~~~~~~~~~~~~~
void DiplayAssignment(Assignment A, int n_width, int c_width){
        printf("|%*s|%*s|%02d/%02d/%-4d|\n", n_width, A.name,
                                         c_width, A.class,
                                         A.AssDate.day, A.AssDate.month, A.AssDate.year);
}