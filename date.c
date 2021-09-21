#include<stdio.h>
#include<time.h>
#include<stdbool.h>

// Global Variables
int g_month_arr[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // arr storing num of days in each month of year
                          {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}}; // [0] = leapless year, [1] = leap year
// Structs
typedef struct Date{ // struct to store a date
    int day,month,year;
}Date;

typedef struct Assignment{ // struct to store data relating to each assignment due
    struct Date AssDate;
    int x,y;
    char z[255];
}Assignment;

// Functions

int LeapYear(int y){
    if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
        return 1;
    return 0;
}

int CalcDueDays(Date year2){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    int due_days = 0;
    int leap1 = LeapYear(tm.tm_year+1900);
    int leap2 = LeapYear(year2.year);

    if (year2.year == tm.tm_year+1900){

        int month_difference = year2.month - tm.tm_mon - 1; 
            
        if (month_difference == 0)
            due_days = year2.day - tm.tm_mday;

        else{
            int remaining_days_in_m = 0;    

            if (month_difference > 0){
                due_days = g_month_arr[leap2][year2.month -1] + year2.day - tm.tm_mday;
                if (month_difference == 1)
                    due_days--; 
            }
            else
                due_days = year2.day - g_month_arr[leap1][tm.tm_mday -1] - tm.tm_mday -1;
            
            int i = month_difference;
            while (i != 1 && i != -1){
                if (i > 0){
                    due_days += g_month_arr[leap2][year2.month - 1 + i];
                    i--;
                }
                
                else{
                    due_days -= g_month_arr[leap2][year2.month - 1 + i];
                    i++;
                }
            }
        }
    }
    else{
        // TODO: Implement year1 != year2 case for day calculation
    }
    
    return due_days;
}