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

struct customer
{
  string name;
  string contact;
  int session;
  struct date curr_date;
  int n_seat;
  int r_num;
};

void valid_cla(int argc, char *argv[]);
void open_file(ifstream &infile, char *argv[]);
struct customer* allocate_customer(int n_customer);
void free_customer(struct customer* *customers);
void read_customer_data(struct customer* customers, int n_customer, ifstream &infile);
int longest_name(struct customer* customers, int n_customer);
int longest_contact(struct customer* customers, int n_customer);
int shortest_contact(struct customer* customers, int n_customer);
void print_words(int length, string word);
void print_content(struct customer* customers, int n_customer);
void print_heading(int name_length);
void print_seperate(int name_length, int contact_length);
void print_close(int name_length, int contact_length);
void print_info(struct customer* customers, int n_customer);
void print_session();
void sort_by_date(struct customer* customers, int n_customer);
void swap_customer(struct customer* customers, int i, int j);
void save_data(struct customer* customers, int n_customer, int r_num, char *argv[], ofstream &outfile);
void copy_customer(struct customer* source, struct customer* destionation, int n_customer);
bool equal(struct customer lhs, struct customer rhs);
void add_customer(struct customer* customers, struct customer customer_info, int n_customer, int& r_num);
void delete_customer(struct customer* customers, struct customer customer_info, int& n_customer);
bool is_int(string num);
int get_betwn(int min, int max);
void get_choice(int &choice);
void get_month(int year, int curr_year, int& month, int curr_month);
void get_day(int year, int curr_year, int month, int curr_month, int& day, int curr_day);
void ask_choice(int &choice);
void ask_date(int &year, int &month, int &day);
void ask_session(int &session);
void ask_guest(int &guest_num);
void ask_name(string &first_name);
void ask_contact(string &contact);
void ask_info(struct customer &customer_info);
void run_option(struct customer** customers, struct customer** results, int &n_customer, int& matches, int& r_num, int option);
void available_msg(bool result, int empty_space);
bool src_available(struct customer* customers, int n_customer, int &empty_space, struct customer customer_info);
<<<<<<< HEAD
void advanced_search(struct customer** results, struct customer* customers, int n_customer, int& matches);
void add_customer_info(struct customer** customers, int n_customer, struct customer customer_info, int& r_num);
void add_reserve(struct customer** customers, int& n_customer, struct customer customer_info, int& r_num);
void delete_reservation(struct customer* customers, int& n_customer);
void get_r_num(int& input);
=======
void advanced_search(struct customer* *result, struct customer* customers, int n_customer);
void add_customer_info(struct customer* *customers, int n_customer, struct customer customer_info);
void add_reserve(struct customer* *customers, int &n_customer, struct customer customer_info);
void delete_reservation(struct customer* *original, struct customer* *erase, struct customer* *remained, struct customer* customers, int n_customer);

>>>>>>> 1288442a12d354981c845deb954c179efebde020
#endif
