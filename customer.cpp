#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include "customer.hpp"
#include "mergeSort.hpp"

using namespace std;

void open_file(ifstream & infile) {
    infile.open("customer_data.txt");
    if(infile.fail()) {
        cerr << "Failed to open customer_data.txt" << endl;
        exit(0);
    }
}

/*********************************************************************
** Function: Allocate an array for a customer structure
** Description: Create a customer structure array based on number of customer
** read from file I/O
** Parameters: int
** Pre-Conditions: Read correct integer from file I/O
** Post-Conditions: Allocated a structure array
*********************************************************************/
struct customer* allocate_customer(const int n_customer) {
    struct customer* customer_array = new struct customer[n_customer];
    return customer_array;
}

/*********************************************************************
** Function: Free dynamic memory of customer
** Description: Use to free dynamic allocated memory
** Parameters: struct customer**
** Pre-Conditions: Memory exist
** Post-Conditions: dynamic allocated customer will be free
*********************************************************************/
void free_customer(struct customer** customers) {
    delete [] (*customers);
}

void displayFileFormatError() {
    cerr << "*WARNING*" << endl;
    cerr << "There is an error of data in data.txt text file" << endl;
    cerr << "The data in data.txt should be in the following format\n" << endl;
    cerr << "From the beginning of the file\nnumber of customers\nlast reservation number" << endl;
    cerr << "name,session,contact,year,month,day,number of seat(s),reservation number,\n\nand so on...*MAKE SURE number of customers matches*\n\n" << endl;
}

/*********************************************************************
** Function: Read customer data from input file
** Description: Use to get customer data from the input file at the
** beginning of program to form customer structure array
** Parameters: struct customer*, int, ifstream&
** Pre-Conditions: customer pointer exist and have enough or more space
** than number of customer
** Post-Conditions: customers data passed in to customer array
*********************************************************************/
void read_customer_data(struct customer* customers, const int n_customer, ifstream& infile) {
    string line;
    string testing[10];
    int found, j = 0, l = 0;
    try {
        while(j < n_customer) {
            for (int x = 0; x < l; x++) {
                testing[x] = "";
            }
            l = 0;
            getline(infile, line);
            for(int i = 0; i < 8; i++) {
                found = line.find(",");
                for (int k = 0; k < found; k++) {
                    testing[l] += line[k];
                }
                l++;
                line.erase(0, found + 1);
            }
            if(infile.fail()) {
                cerr << "Failed to read customer." << endl;
            }
            const date curr_date = {stoi(testing[3]), stoi(testing[4]), stoi(testing[5])};
            const string name = testing[0];
            const string contact = testing[2];
            const int session = stoi(testing[1]);
            const int n_seat = stoi(testing[6]);
            const int r_num = stoi(testing[7]);
            struct customer tempCustomer(curr_date, name, contact, session, n_seat, r_num);
            customers[j] = tempCustomer;
            j++;
        }
    }
    catch(const exception& e) {
        displayFileFormatError();
        exit(0);
    }
}

/*********************************************************************
** Function: Find the longest name among the customers
** Description: Use to find the longest name to determine the size of
    name column
** Parameters: struct customer*, int
** Pre-Conditions: customer pointer exist and not empty, max index of
** customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
** longest name
*********************************************************************/
int longest_name(struct customer* customers, const int n_customer) {
    int max_length = 0;
    int combine_length = 0;
    for(int i = 0; i < n_customer; i++) {
        combine_length = customers[i].getName().length();
        if(combine_length > max_length) {
            max_length = combine_length;
        }
    }
    return max_length;
}

/*********************************************************************
** Function: Find the longest contact among the customers
** Description: Use to find the longest contact to determine the size of
     contact column
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and not empty, max index of
    customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
    longest contact
*********************************************************************/
int longest_contact(struct customer* customers, const int n_customer) {
    int max_length = 0;
    int combine_length = 0;
    for(int i = 0; i < n_customer; i++) {
        combine_length = customers[i].getContact().length();
        if(combine_length > max_length) {
            max_length = combine_length;
        }
    }
    return max_length;
}

/*********************************************************************
** Function: Find the shortest contact among the customers
** Description: Use to find the shortest contact to determine the
    spacing of contact heading
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and not empty, max index of
    customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
    shortest contact
*********************************************************************/
int shortest_contact(struct customer* customers, const int n_customer) {
    int min_length = 0;
    int combine_length = 0;
    for(int i = 0; i < n_customer; i++) {
        combine_length = customers[i].getContact().length();
        if(combine_length < min_length) {
            min_length = combine_length;
        }
    }
    return min_length;
}
/*********************************************************************
** Function: Print a character for N times
** Description: Use to format the customer list
** Parameters: int, string
** Pre-Conditions:
** Post-Conditions: Print a character for n times
*********************************************************************/
void print_words(const int length, const string word) {
    for(int i = 0; i < length; i++) {
        cout << word;
    }
}

/*********************************************************************
** Function: Print the content of the customer list
** Description: Use to print the content of customer list according
** to information given from customer array
** Parameters: struct customer*, int
** Pre-Conditions: customer pointer exist and max index match with number
** of customer
** Post-Conditions: Print the middle part (content) of the table list
*********************************************************************/
void print_content(struct customer* customers, const int n_customer) {
    const int longest_name_length = longest_name(customers, n_customer) + 1;
    const int longest_contact_length = longest_contact(customers, n_customer) + 1;
    for(int i = 0; i < n_customer; i++) {
        const int contact_length = customers[i].getContact().length();
        const int name_length = customers[i].getName().length();
        const int year = customers[i].getDate().getYear();
        const int month = customers[i].getDate().getMonth();
        const int day = customers[i].getDate().getDay();
        const string day_of_week = DAY_IN_WORD[day_of_the_week (year, month, day)];
        cout << "|R" << setfill('0') << setw(4) << customers[i].getRnum();
        //print date info
        cout << " |" << setfill('0') << setw(2) << day << "/" << setfill('0') << setw(2) << month << "/" << year << "(" << day_of_week << ")" << setfill(' ') << setw(11-day_of_week.length()) << "|";
        //set setfill( back to space)
        cout << setfill(' ');
        //print name
        cout << customers[i].getName() << " " << setw (longest_name_length - name_length) << "|";
        //print contact info
        cout << customers[i].getContact() << setw (longest_contact_length - contact_length) << "|";
        //print session
        cout << customers[i].getSession() << setw(7) << "|";
        //print seat(s)
        cout << customers[i].getNseat() << setw(7) << "|" << endl;
        if(i == n_customer - 1) {
            break;
        }
        else {
            print_seperate(longest_name_length, longest_contact_length);
        }
    }
}

/*********************************************************************
** Function: Print header of the customer list
** Description: Use to print out the header columns of the customer list
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions: Printed the header of the customer list
*********************************************************************/
void print_heading(struct customer* customers, const int n_customer, const int name_length, const int contact_length)
{
    const int longest_contact_length = longest_contact(customers, n_customer) + 10;
    const int shortest_contact_length = shortest_contact(customers, n_customer);
    cout << "+------";
    cout << "+----------------------+";
    if(name_length > 4) {
        print_words(name_length, "-");
    }
    else {
        print_words(3, "-");
    }
    cout << "+";
    if(contact_length > 7) {
        print_words(contact_length-1, "-");
    }
    else {
        print_words(7, "-");
    }
    cout << "+-------+-------+" << endl;
    cout << "|No.   |Date                  |Name";
    print_words(name_length - 4, " ");
    cout << "|Contact" << setw(longest_contact_length - shortest_contact_length) << "|Session|Seat(s)|" << endl;
    print_seperate(name_length, contact_length);
}

/*********************************************************************
** Function: Print symbols that seperate rows in the table
** Description: Use to seperate rows in the table
** Parameters: int
** Pre-Conditions:
** Post-Conditions: Print a seperating row
*********************************************************************/
void print_seperate(const int name_length, const int contact_length) {
    cout << "+------+----------------------+";
    print_words(name_length, "-");
    cout << "+";
    print_words(contact_length-1, "-");
    cout << "+-------+-------¦" << endl;
}

/*********************************************************************
** Function: Print customer info inside a table
** Description: Combine header, content and closing of the print
** functions to form a complete table
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and max index match with number
** of customer
** Post-Conditions: Print complete customer info in a table
*********************************************************************/
void print_info(struct customer* customers, const int n_customer) {
    const int name_length = longest_name(customers, n_customer) + 1;
    const int contact_length = longest_contact(customers, n_customer) + 1;
    print_heading(customers, n_customer, name_length, contact_length);
    print_content(customers, n_customer);
    print_seperate(name_length, contact_length);
}

/*********************************************************************
** Function: Save customer data in to a file
** Description: Sort customer data by date accendingly and write customer
** data in to file provided in the command line argument
** Parameters: struct customer*, int, char*, ofstream&
** Pre-Conditions: File path exist, customers pointer exist and max
** index match with number of customers
** Post-Conditions: Write sorted customers data in to text file
*********************************************************************/
void save_data(struct customer* customers, const int n_customer, const int r_num, ofstream& outfile) {
    outfile.open("customer_data.txt");
    if(outfile.fail()) {
        cerr << "Failed to open customer_data.txt" << endl;
        exit(0);
    }
    sort_by_date(customers, n_customer);
    outfile << n_customer << endl;
    outfile <<    r_num << endl;
    for(int i = 0; i < n_customer; i++) {
        outfile << customers[i].getName() << "," << customers[i].getSession() << ",";
        outfile << customers[i].getContact() << "," << customers[i].getDate().getYear() << ",";
        outfile << customers[i].getDate().getMonth() << "," << customers[i].getDate().getDay() << ",";
        outfile << customers[i].getNseat() << "," << customers[i].getRnum() << ",";
      if (i != n_customer - 1) {
          outfile << endl;
      }
    }
}

/*********************************************************************
** Function: Print customer info inside a table
** Description: Combine header, content and closing of the print
** functions to form a complete table
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and match index with number
** of customer
** Post-Conditions: Print complete customer info in a table
*********************************************************************/
void copy_customer(struct customer* source, struct customer* destination, const int n_customer) {
    for(int i = 0; i < n_customer; i++) {
        const date curr_date = source[i].getDate();
        const string name = source[i].getName();
        const string contact = source[i].getContact();
        const int session = source[i].getSession();
        const int n_seat = source[i].getNseat();
        const int r_num = source[i].getRnum();
        const struct customer tempCustomer(curr_date, name, contact, session, n_seat, r_num);
        destination[i] = tempCustomer;
    }
}

/*********************************************************************
** Function: Add new customer
** Description: Add new customer by getting various related info
** Parameters: struct customer*, struct customer, int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void add_customer(struct customer* customers, const struct customer customer_info, const int n_customer, int& r_num) {
    const string name = customer_info.getName();
    const string contact = customer_info.getContact();
    const int session = customer_info.getSession();
    const date curr_date = customer_info.getDate();
    const int n_seat = customer_info.getNseat();
    const struct customer newCustomer(curr_date, name, contact, session, n_seat, ++r_num);
    customers[n_customer - 1] = newCustomer;
}

void delete_customer(struct customer* customers, const struct customer customer_info, int& n_customer) {
    for(int i = 0; i < n_customer; i++) {
        if(customers[i] == customer_info) {
            for(int j = i; j < n_customer - 1; j++) {
                customers[j] = customers[j+1];
            }
            n_customer--;
            i--;
        }
    }
}

bool is_int(const string num) {
    if(num.length() <= 0) {
        return false;
    }
    for(int i = 0; i < num.length(); i++) {
        if(num[i] < 48 || num[i] > 57) {
            return false;
        }
    }
    return true;
}

void get_int(int& input)
{
    string num;
    do {
        getline(cin, num);
        if(!is_int(num)) {
            cout << "Please enter an integer." << endl;
        }
    } while(!is_int(num));
    input = stoi(num);
}

int get_betwn(const int min, const int max) {
    int input;
    do {
        get_int(input);
        if(input < min || input > max) {
            cout << "Please enter an integer between or equal to " << min << " and " << max << ": ";
        }
    } while(input < min || input > max);
    return input;
}

void ask_choice(int& choice) {
    cout << "Choose an option from above: " << endl;
    cout << "1. Print reservation record" << endl;
    cout << "2. Search for availability" << endl;
    cout << "3. Update reservation record" << endl;
    cout << "4. Filter reservation record" << endl;
    cout << "5. Save and exit" << endl << endl;
    cout << "Option: ";
    choice = get_betwn(1, 5);
}

void ask_date(int& year, int& month, int& day) {
    const time_t now = time(NULL);
    const tm* time = localtime(&now);
    int restrict_year = 1900 + time->tm_year;
    int restrict_month = 1+ time->tm_mon;
    int restrict_day = time->tm_mday +  3;
    correct_date(restrict_year, restrict_month, restrict_day);
    cout << "Enter date in the following: " << endl;
    cout << "Year: ";
    year = get_betwn(restrict_year, 9999);
    cout << "Month: ";
    get_month(year, restrict_year, month, restrict_month);
    cout << "Day: ";
    get_day(year, restrict_year, month, restrict_month, day, restrict_day);
}

void get_month(const int year, const int curr_year, int& month, const int curr_month) {
    if(year == curr_year) {
        month = get_betwn(curr_month, 12);
    } else {
        month = get_betwn(1, 12);
    }
}

void get_day(const int year, const int curr_year, const int month, const int curr_month, int& day, const int curr_day) {
    if(month == 2) {
        if(year % 4 == 0) {
            if(year == curr_year && month == curr_month) {
                day = get_betwn(curr_day, 29);
            } else {
                day = get_betwn(1, 29);
            }
        } else {
            if(year == curr_year && month == curr_month) {
                day = get_betwn(curr_day, 28);
            } else {
                day = get_betwn(1, 28);
            }
        }
    } else if(month == 4 || month == 6 || month == 9 || month == 11) {
        if(year == curr_year && month == curr_month) {
            day = get_betwn(curr_day, 30);
        } else {
            day = get_betwn(1, 30);
        }
    }
    else {
        if(year == curr_year && month == curr_month) {
            day = get_betwn(curr_day, 31);
        }  else {
            day = get_betwn(1, 31);
        }
    }
}

void ask_session(int& session) {
    cout << "1. 11:00 A.M. - 12:30 A.M." << endl;
    cout << "2. 12:30 P.M. - 02:00 P.M." << endl;
    cout << "3. 05:00 P.M. - 06:30 P.M." << endl;
    cout << "4. 06:30 P.M. - 08:00 P.M." << endl;
    cout << "Enter the session for reservation: ";
    session = get_betwn(1, 4);
}

void ask_guest(int& guest_num) {
    cout << "Enter the number of guest for reservation: ";
    guest_num = get_betwn(1, 8);
}

void ask_contact(string& contact) {
    cout << "Enter contact number of the customer: ";
    getline(cin, contact);
}

void ask_name(string& name) {
    cout << "Enter the customer name for the reservation:" << endl;
    cout << "Full name: ";
    getline(cin, name);
}

void ask_info(struct customer& customer_info) {
    int year, month, day;
    int session, n_seat;
    ask_date(year, month, day);
    ask_session(session);
    ask_guest(n_seat);
    date curr_date(year, month, day);
    customer_info.setDate(curr_date);
    customer_info.setSession(session);
    customer_info.setNseat(n_seat);
    cout << endl;
}

void available_msg(const bool available, const int empty_space) {
    if(!available) {
        cout << "Sorry we have only " << empty_space << " seat(s) left for the reservation time." << endl;
    } else {
        cout << "The reservation time is available." << endl;
    }
}

void run_option(struct customer** customers, struct customer** results, int& n_customer, int& matches, int& r_num, int option) {
    int empty_space;
    bool availability;
    struct customer customer_info;
    ofstream outfile;
    if(option == 1) {
        print_session();
        if(n_customer > 0) {
            sort_by_date(*customers, n_customer);
            print_info(*customers, n_customer);
        }
        else {
            cout << "No reservation record are found..." << endl;
        }
    }
    else if(option == 2) {
        cout << "\nSearching for availability..." << endl;
        ask_info(customer_info);
        availability = src_available(*customers, n_customer, empty_space, customer_info);
        available_msg(availability, empty_space);
    }
    else if(option == 3) {
        cout << "\nUpdating reservation record..." << endl;
        ask_choice_update(option);
        if (option == 1) {
            ask_info(customer_info);
            string name, contact;
            ask_name(name);
            customer_info.setName(name);
            ask_contact(contact);
            customer_info.setContact(contact);
            add_reserve(customers, n_customer, customer_info, r_num);
        }
        else if (option == 2) {
            cout << "\nDeleting reservation record..." << endl;
            delete_reservation(*customers, n_customer);
        }
        else if (option == 3) {
            cout << "Changing reservation record..." << endl;
            change_reservation(*customers, n_customer);
        }
        save_data(*customers, n_customer, r_num, outfile);
    }
    else if(option == 4) {
        if(matches > 0) {
            free_customer(results);
            matches = 0;
        }
        cout << "\nFiltering reservation record..." << endl;
        advanced_search(results, *customers, n_customer, matches);
    }
}

void ask_choice_update(int& choice) {
    cout << "Choose an option to update reservation record: " << endl;
    cout << "1. Add reservation record" << endl;
    cout << "2. Delete reservation record" << endl;
    cout << "3. Change reservation record" << endl << endl;
    cout << "Option: ";
    choice = get_betwn(1, 3);
}

/*********************************************************************
** Function: Search for availability
** Description: Check for availability
** Parameters: struct customer*, int, int&, struct customer
*********************************************************************/
bool src_available(struct customer* customers, const int n_customer, int& empty_space, const struct customer customer_info) {
    empty_space = 8;
    for(int i = 0; i < n_customer; i++) {
        if(customers[i].getDate().getYear() == customer_info.getDate().getYear() && customers[i].getDate().getMonth() == customer_info.getDate().getMonth()
        && customers[i].getDate().getDay() == customer_info.getDate().getDay() && customers[i].getSession() == customer_info.getSession()) {
            empty_space -= customers[i].getNseat();
        }
    }
    if(empty_space < 0) {
        cout << "Session overbooked, please check for reservation availability" << endl;
        return false;
    }
    if(customer_info.getNseat() > empty_space) {
        return false;
    } else {
        return true;
    }
}

void advanced_search(struct customer** results, struct customer* customers, const int n_customer, int& matches) {
    string search, name, contact;
    matches = n_customer;
    *results = allocate_customer(n_customer);
    copy_customer(customers, *results, n_customer);
    cout << "Searching key word: ";
    getline(cin, search);
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    for(int i = 0; i < n_customer; i++) {
        name = customers[i].getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        contact = customers[i].getContact();
        if(name.find(search) == string::npos && contact.find(search) == string::npos) {
            delete_customer(*results, customers[i], matches);
        }
    }
    if(matches > 0) {
        print_info(*results, matches);
    } else {
        cout << "Match not found..." << endl;
    }
}

void add_customer_info(struct customer** customers, const int n_customer, const struct customer customer_info, int& r_num) {
    struct customer *temp;
    temp = allocate_customer(n_customer);
    copy_customer(*customers, temp, n_customer);
    free_customer(&(*customers));
    *customers = allocate_customer(n_customer + 1);
    copy_customer(temp, *customers, n_customer);
    add_customer(*customers, customer_info, n_customer + 1, r_num);
    free_customer(&temp);
}

/*********************************************************************
** Function: Add reservation to update reservation record
** Description: Check for available seat(s) to update add reservation
** Parameters: struct customer**, int&, const struct customer, int&
** Pre-Conditions: no new reservation added
** Post-Conditions: new reservation added
*********************************************************************/
void add_reserve(struct customer** customers, int& n_customer, const struct customer customer_info, int& r_num) {
    int empty_space;
    const bool available = src_available(*customers, n_customer, empty_space, customer_info);
    if(!available) {
        cout << endl;
        cout << "Sorry we have only " << empty_space << " seat(s) left for the reservation time." << endl;
        cout << "Please double check the reservation availability." << endl;
    } else {
        add_customer_info(customers, n_customer, customer_info, r_num);
        n_customer++;
        cout << "Update Success!" << endl;
    }
}

void print_session() {
    cout << "--Session Time Table--" << endl;
    cout << "11:00 A.M. - 12:30 A.M." << endl;
    cout << "12:30 P.M. - 02:00 P.M." << endl;
    cout << "05:00 P.M. - 06:30 P.M." << endl;
    cout << "06:30 P.M. - 08:00 P.M." << endl;
}

/*********************************************************************
** Function: Delete Reservation Record
** Description: Delete reservation record based on reservation number 
    of customer
** Parameters: struct customer*, int&
** Pre-Conditions: no reservation record deleted
** Post-Conditions: chosen reservation record deleted
*********************************************************************/
void delete_reservation(struct customer* customers, int& n_customer) {
    struct customer confirm_customer;
    char decision;
    int reserve_num = 0;
    cout << "Reservation No.: ";
    getCustomerIndex(customers, confirm_customer, n_customer, reserve_num);
    print_info(&confirm_customer, 1);
    cout << "Are you sure you want to delete? (Y/y) or (N/n) : ";
    get_char(decision);
    if((decision == 'Y') || (decision == 'y'))
    {
        delete_customer(customers, confirm_customer, n_customer);
        cout << "Successfully deleted " << "R" << setfill('0') << setw(4);
        cout << confirm_customer.getRnum() << " reservation..." << endl;
    }
    else if ((decision == 'N') || (decision == 'n'))
	{
        cout << "Cancelling reservation record..." << endl;
        cout << "Delete reservation record cancelled" << endl;
    }
}

void sry_msg(const int empty_space) {
    cout << endl;
    cout << "Sorry we have only " << empty_space << " seat(s) left for the reservation time." << endl;
    cout << "Please double check the reservation availability." << endl;
}

void ask_choice_change(int& choice) {
    cout << "Choose an option to change reservation record: " << endl;
    cout << "1. Name" << endl;
    cout << "2. Session" << endl;
    cout << "3. Date" << endl;
    cout << "4. Contact" << endl;
    cout << "5. Number of guest" << endl;
    cout << "Option: ";
    choice = get_betwn(1, 5);
}

void ask_update_confirm(int& choice) {
    cout << "Choose an option to perform next action: " << endl;
    cout << "1. Update changes" << endl;
    cout << "2. Discard changes" << endl;
    cout << "3. Continue changing" << endl;
    cout << "Option: ";
    choice = get_betwn(1, 3);
}

int getCustomerIndex(struct customer* customers, struct customer& confirm_customer, const int n_customer, int reserve_num) {
    int customer_index = -1;
    do {
        get_r_num(reserve_num);
        customer_index = find_r_customer(customers, confirm_customer, n_customer, reserve_num);
        if(customer_index == -1) {
            cout << "Reservation number not found..." << endl;
            cout << "Please enter a valid Reservation No.: ";
        }
    } while(customer_index == -1);
    return customer_index;
}

void change_reservation(struct customer* customers, const int n_customer) {
    int decision = 0, next_act = 0, empty_space = 0;
    struct customer confirm_customer;
    struct customer temp_customer, save_customer;
    int reserve_num = 0, customer_index = 0;
    bool available = true;
    cout << "Reservation No.: ";
    customer_index = getCustomerIndex(customers, confirm_customer, n_customer, reserve_num);
    temp_customer = confirm_customer;
    save_customer = confirm_customer;
    print_info(&confirm_customer, 1);
    do {
        ask_choice_change(decision);
        if(decision == 1) {
            string name;
            ask_name(name);
            temp_customer.setName(name);
        }
        else if(decision == 2) {
            int session;
            ask_session(session);
            temp_customer.setSession(session);
            available = src_available(customers, n_customer, empty_space, temp_customer);
        }
        else if(decision == 3) {
            int year, month, day;
            ask_date(year, month, day);
            struct date newDate(year, month, day);
            temp_customer.setDate(newDate);
            available = src_available(customers, n_customer, empty_space, temp_customer);
        }
        else if(decision == 4) {
            string contact;
            ask_contact(contact);
            temp_customer.setContact(contact);
        }
        else if(decision == 5) {
            int n_seat;
            ask_guest(n_seat);
            temp_customer.setNseat(n_seat);
            available = src_available(customers, n_customer, empty_space, temp_customer);
        }
        if(!available) {
            sry_msg(empty_space);
            temp_customer = save_customer;
        } else {
            save_customer = temp_customer;
        }
        cout << "Reservation information" << endl;
        print_info(&save_customer, 1);
        ask_update_confirm(next_act);
    }while(next_act == 3);

    if(next_act == 1) {
        customers[customer_index] = temp_customer;
    }
}

void get_r_num(int& input) {
    string reservation;
    bool flag = true;
    do {
        getline(cin, reservation);
        if(is_int(reservation)) {
            input = stoi(reservation);
            flag = false;
        } else if(reservation[0] == 'R' || reservation[0] == 'r') {
            reservation.erase(0, 1);
            if(is_int(reservation)) {
                input = stoi(reservation);
                flag = false;
            }
        }
        if(flag == true) {
            cout << "Please enter reservation number in right format." << endl;
            cout << "For example: R1234 or 1234" << endl;
            cout << "Reservation No.: ";
        }
    }while(flag == true);
}

void get_char(char& decision) {
    string str;
    bool flag = false;
    do {
        getline(cin, str);
        if(str.length() == 1) {
            if(str[0] == 'Y' || str[0] == 'y' || str[0] == 'N' || str[0] == 'n') {
                flag = true;
            }
        }
        if(flag == false) {
            cout << "Please enter (Y/y) or (N/n) : ";
        }
    }while(flag == false);
    decision = str[0];
}

int find_r_customer(struct customer* customers, struct customer& result, const int n_customer, const int r_num) {
    struct customer* temp;
    int match = n_customer, index = 0;
    temp = allocate_customer(n_customer);
    copy_customer(customers, temp, n_customer);
    for(int i = 0; i < n_customer; i++) {
        if(customers[i].getRnum() != r_num) {
            delete_customer(temp, customers[i], match);
        }
        else {
            index = i;
        }
    }
    if(match > 0) {
        result = temp[0];
        free_customer(&temp);
        return index;
    }
    free_customer(&temp);
    return -1;
}