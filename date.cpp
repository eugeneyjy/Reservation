#include <iostream>
#include <fstream>
#include <cmath>
#include "date.hpp"

using namespace std;

void read_date_data(struct date& curr_date, ifstream& infile) {
    int year, month, day;
    infile >> year >> month >> day;
    struct date date(year, month, day);
    curr_date = date;
}

/*************************************************************************
** Function: To obtain the first and last two digits of the year entered
** Description:
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*************************************************************************/

void seperate_year(const int year, int& first_two, int& last_two) {
    first_two = year/100;
    last_two = year%100;
}

int day_of_the_week(const int param_year, const int param_month, const int param_day) {
    int day, year_first_two, year_last_two;
    int month = param_month - 2;
    if(month <= 0) {
        month += 12;
    }
    seperate_year(param_year, year_first_two, year_last_two);
    //Formula to calculate day of the week based on date
    day = param_day + floor((13 * month - 1) /5) + year_last_two + floor(year_last_two /4) + floor(year_first_two /4) - 2 * year_first_two;
    day = day % 7;
    if(day < 0) {
        day += 7;
    }
    return day;
}

void correct_date(int& year, int& month, int& day) {
    //Fixing day
    const int special_day = MAX_DAY[1] + 1;
    if(month == 2 && (year % 4 == 0)) {
        if(day > special_day) {
            day -= special_day;
            month += 1;
        }
    } else{
        if(day > MAX_DAY[month-1]) {
            day -= MAX_DAY[month-1];
            month += 1;
        }
    }
    //Fixing month
    if(month > 12) {
        month -= 12;
        year += 1;
    }
}