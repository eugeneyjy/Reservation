/*********************************************************************
** Program Filename: customer.hpp
** Author: Eugene Yong
** Date: 07/08/2019
** Description: customer structure header file
*********************************************************************/
#ifndef __CUSTOMER_HPP
#define __CUSTOMER_HPP

#include "date.hpp"

using namespace std;

struct customer {

    private :
        string name, contact;
        int session, n_seat, r_num;
        struct date curr_date;

    public :
        customer() {};
        customer(const struct date curr_date, const string name, const string contact, const int session, const int n_seat, const int r_num) {
            this->curr_date = curr_date;
            this->name = name;
            this->contact = contact;
            this->session = session;
            this->n_seat = n_seat;
            this->r_num = r_num;
        }
        void setName(const string name) {
            this->name = name;
        }
        string getName() const{
            return this->name;
        }

        void setContact(const string contact) {
            this->contact = contact;
        }
        string getContact() const{
            return this->contact;
        }

        void setSession(const int session) {
            this->session = session;
        }
        int getSession() const{
            return this->session;
        }

        void setNseat(const int n_seat) {
            this->n_seat = n_seat;
        }
        int getNseat() const{
            return this->n_seat;
        }

        void setRnum(const int r_num) {
            this->r_num = r_num;
        }
        int getRnum() const{
            return this->r_num;
        }
        void setDate(const struct date curr_date) {
            this->curr_date = curr_date;
        }
        struct date getDate() const{
            return this->curr_date;
        }
        bool operator == (const struct customer& customer) {
            return this->curr_date == customer.getDate() && this->name == customer.getName()
            && this->contact == customer.getContact() && this->session == customer.getSession()
            && this->n_seat == customer.getNseat();
        }
};
//added merge sort to sort customer based on date
//made a getCustomerIndex function for change and delete as it has same repeating code
//and handle file format exceptions, save the data each time it has new update, added const keyword to constant variable and added encapsulation
void open_file(ifstream & infile);
struct customer* allocate_customer(const int n_customer);
void free_customer(struct customer* *customers);
void read_customer_data(struct customer* customers, const int n_customer, ifstream &infile);
int longest_name(struct customer* customers, const int n_customer);
int longest_contact(struct customer* customers, const int n_customer);
int shortest_contact(struct customer* customers, const int n_customer);
void print_words(const int length, const string word);
void print_content(struct customer* customers, const int n_customer);
void print_heading(const int name_length);
void print_seperate(const int name_length, const int contact_length);
void print_close(const int name_length, const int contact_length);
void print_info(struct customer* customers, const int n_customer);
void print_session();
void save_data(struct customer* customers, const int n_customer, const int r_num, ofstream &outfile);
void copy_customer(struct customer* source, struct customer* destionation, const int n_customer);
void add_customer(struct customer* customers, const struct customer customer_info, const int n_customer, int& r_num);
void delete_customer(struct customer* customers, const struct customer customer_info, int& n_customer);
bool is_int(const string num);
int get_betwn(const int min, const int max);
void get_choice(int &choice);
void get_month(const int year, const int curr_year, int& month, const int curr_month);
void get_day(const int year, const int curr_year, const int month, const int curr_month, int& day, const int curr_day);
void ask_choice(int &choice);
void ask_date(int &year, int &month, int &day);
void ask_session(int &session);
void ask_guest(int &guest_num);
void ask_name(string &first_name);
void ask_contact(string &contact);
void ask_info(struct customer &customer_info);
void run_option(struct customer** customers, struct customer** results, int &n_customer, int& matches, int& r_num, int option);
void available_msg(const bool result, const int empty_space);
bool src_available(struct customer* customers, const int n_customer, int &empty_space, const struct customer customer_info);
void advanced_search(struct customer** results, struct customer* customers, const int n_customer, int& matches);
void add_customer_info(struct customer** customers, int n_customer, const struct customer customer_info, int& r_num);
void add_reserve(struct customer** customers, int& n_customer, const struct customer customer_info, int& r_num);
void delete_reservation(struct customer* customers, int& n_customer);
void get_r_num(int& input);
int find_r_customer(struct customer* customers, struct customer& result, const int n_customer, const int r_num);
void ask_choice_update(int& choice);
void change_reservation(struct customer* customers, const int n_customer);
void get_char(char& decision);
void sry_msg(const int empty_space);
int getCustomerIndex(struct customer* customers, struct customer& confirm_customer, const int n_customer, int reserve_num);
void displayFileFormatError();

#endif