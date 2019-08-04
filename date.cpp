#include <iostream>
#include <fstream>
#include <cmath>
#include "date.hpp"

using namespace std;

/*********************************************************************
** Function: Get dates from file which is entered by user in file
** Description:
** Parameters: struct date, ifstream
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/

void read_date_data(struct date& curr_date, ifstream& infile)
{
  infile >> curr_date.year >> curr_date.month >> curr_date.day;
}

/*************************************************************************
** Function: To obtain the first and last two digits of the year entered
** Description:
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*************************************************************************/

void seperate_year(int year, int& first_two, int& last_two)
{
  first_two = year/100;
  last_two = year%100;
}

/*************************************************************************
** Function: To calculate day of the week
** Description:
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*************************************************************************/

int day_of_the_week(int param_year, int param_month, int param_day)
{
  int day, year_first_two, year_last_two;
  int month = param_month - 2;
  if(month <= 0)
  {
    month += 12;
  }
  seperate_year(param_year, year_first_two, year_last_two);
  //Formula to calculate day of the week based on date
  day = param_day + floor((13 * month - 1) /5) + year_last_two + floor(year_last_two /4) + floor(year_first_two /4) - 2 * year_first_two;
  day = day % 7;
  if(day < 0)
  {
    day += 7;
  }
  return day;
}