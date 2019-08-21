#include <iostream>
#include <fstream>
#include <cmath>
#include "date.hpp"

using namespace std;

/*********************************************************************
** Function: Get dates from file which is entered by user in file
** Description: Get the exact date from customer
** Parameters: struct date&, ifstream&
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/

void read_date_data(struct date& curr_date, ifstream& infile)
{
  infile >> curr_date.year >> curr_date.month >> curr_date.day;
}

/***************************************************************************
** Function: To obtain the first two and last two digits of the year entered
** Description: Extract first two and last two digits of the year entered
                to calculate day of the week based on date
** Parameters: int, int&
** Pre-Conditions:
** Post-Conditions:
***************************************************************************/

void seperate_year(int year, int& first_two, int& last_two)
{
  first_two = year / 100;
  last_two = year % 100;
}

/*************************************************************************
** Function: To calculate day of the week based on date
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
  day = param_day + floor((13.0 * month - 1.0) /5.0) + year_last_two + floor(year_last_two /4.0) + floor(year_first_two /4.0) - 2.0 * year_first_two;
  day = day % 7;
  if(day < 0)
  {
    day += 7;
  }
  return day;
}

void corret_date(int& year, int& month, int& day)
{
  //Fixing day
  int special_day = MAX_DAY[1] + 1;
  if(month == 2 && (year % 4 == 0))
  {
    if(day > special_day)
    {
      day -= special_day;
      month += 1;
    }
  }
  else
  {
    if(day > MAX_DAY[month-1])
    {
      day -= MAX_DAY[month-1];
      month += 1;
    }
  }
  //Fixing month
  if(month > 12)
  {
    month -= 12;
    year += 1;
  }
}
