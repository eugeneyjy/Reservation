
/*********************************************************************
** Program Filename: date.hpp
** Author: Eugene Yong
** Date: 07/08/2019
** Description: date structure header file
*********************************************************************/
#ifndef __DATE_HPP
#define __DATE_HPP

using namespace std;

const int CURR_YEAR = 2019;
const string DAY_IN_WORD[7] ={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int MAX_DAY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date
{
  int year;
  int month;
  int day;
};

void read_date_data(struct date& date_data, ifstream& infile);
void seperate_year(int year, int& first_two, int& last_two);
int day_of_the_week(int param_year, int param_month, int param_day);
void corret_date(int& year, int& month, int& day);

#endif
