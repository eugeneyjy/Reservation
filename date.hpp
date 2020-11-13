/*********************************************************************
** Program Filename: date.hpp
** Author: Eugene Yong
** Date: 07/08/2019
** Description: date structure header file
*********************************************************************/
#ifndef __DATE_HPP
#define __DATE_HPP

using namespace std;

const string DAY_IN_WORD[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int MAX_DAY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date {

    private:
        int year;
        int month;
        int day;
    public :
        date() {};
        date(const int year, const int month, const int day) {
            this->year = year;
            this->month = month;
            this->day = day;
        }
        void setYear(const int year) {
            this->year = year;
        }
        int getYear() const{
            return this->year;
        }
        void setMonth(const int month) {
            this->month = month;
        }
        int getMonth() const{
            return this->month;
        }
        void setDay(const int day) {
            this->day = day;
        }
        int getDay() const{
            return this->day;
        }
        bool operator == (const struct date& date) {
            return this->day == date.getDay() && this->month == date.getMonth() && this->year == date.getYear();
        }
        const static int CURR_YEAR = 2019;
};

void read_date_data(struct date& date_data, ifstream& infile);
void seperate_year(const int year, int& first_two, int& last_two);
int day_of_the_week(const int param_year, const int param_month, const int param_day);
void correct_date(int& year, int& month, int& day);

#endif