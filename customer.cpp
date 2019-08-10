#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "customer.hpp"

using namespace std;

/*********************************************************************
** Function: Check if command line argument is valid
** Description: Use to validate if a command line has 2 arguments
** Parameters: int, char**
** Pre-Conditions:
** Post-Conditions: Command line argument only contain 2 vectors if
** program goes on
*********************************************************************/
void valid_cla(int argc, char* argv[])
{
  if(argc != 2)
  {
    cout << "Please enter command line with ./filename text.txt." << endl;
    exit(0);
  }
}

/*********************************************************************
** Function: Open file I/O
** Description: Open the file I/O with the pathing provided by customer
** Parameters: ifstream&, char**
** Pre-Conditions: There is a second vector in the command line argument
** Post-Conditions: Success or fail to open the file I/O
*********************************************************************/
void open_file(ifstream& infile, char* argv[])
{
  infile.open(argv[1]);
  if(infile.fail())
  {
    cerr << "Failed to open " << argv[1] << endl;
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
struct customer* allocate_customer(int n_customer)
{
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
void free_customer(struct customer** customers)
{
  delete [] (*customers);
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
void read_customer_data(struct customer* customers, int n_customer, ifstream& infile)
{
  string line;
  string testing[10];
  int found, i = 0, j = 0, l = 0;
  while(j < n_customer)
  {
    for (int x = 0; x < l; x++)
    {
      testing[x] = "";
    }
    l = 0;
    getline(infile, line);
    for(int i = 0; i < 7; i++)
    {
      found = line.find(",");
      for (int k = 0; k < found; k++)
      {
        testing[l] += line[k];
      }
      l++;
      line.erase(0, found + 1);
    }
    if(infile.fail())
    {
      cerr << "Failed to read customer." << endl;
    }
    customers[j].name = testing[0];
    customers[j].contact = testing[2];
    customers[j].session = stoi(testing[1]);
    customers[j].curr_date.year = stoi(testing[3]);
    customers[j].curr_date.month = stoi(testing[4]);
    customers[j].curr_date.day = stoi(testing[5]);
    customers[j].n_seat = stoi(testing[6]);
    j++;
  }
}

/*********************************************************************
** Function: Find the longest name among the customers
** Description: Use to find the longest name to determine the size of
** name column
** Parameters: struct customer*, int
** Pre-Conditions: customer pointer exist and not empty, max index of
** customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
** longest name
*********************************************************************/
int longest_name(struct customer* customers, int n_customer)
{
  int max_length = 0;
  int combine_length = 0;
  for(int i = 0; i < n_customer; i++)
  {
    combine_length = customers[i].name.length();
    if(combine_length > max_length)
    {
      max_length = combine_length;
    }
  }
  return max_length;
}

/*********************************************************************
** Function: Find the longest name among the customers
** Description: Use to find the longest name to determine the size of
** name column
** Parameters: struct customer*, int
** Pre-Conditions: customer pointer exist and not empty, max index of
** customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
** longest name
*********************************************************************/
int longest_contact(struct customer* customers, int n_customer)
{
  int max_length = 0;
  int combine_length = 0;
  for(int i = 0; i < n_customer; i++)
  {
    combine_length = customers[i].contact.length();
    if(combine_length > max_length)
    {
      max_length = combine_length;
    }
  }
  return max_length;
}

/*********************************************************************
** Function: Print a character for N times
** Description: Use to format the customer list
** Parameters: int, string
** Pre-Conditions:
** Post-Conditions: Print a character for n times
*********************************************************************/
void print_words(int length, string word)
{
  for(int i = 0; i < length; i++)
  {
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
void print_content(struct customer* customers, int n_customer)
{
  int longest_name_length = longest_name(customers, n_customer) + 1;
  int longest_contact_length = longest_contact(customers, n_customer) + 1;
  int name_length, contact_length;
  string day_of_week;
  for(int i = 0; i < n_customer; i++)
  {
    contact_length = customers[i].contact.length();
    name_length = customers[i].name.length();
    day_of_week = DAY_IN_WORD[day_of_the_week (customers[i].curr_date.year, customers[i].curr_date.month, customers[i].curr_date.day) ];
    //print date info
    cout << "|" << setfill('0') << setw(2) << customers[i].curr_date.day << "/" << setfill('0') << setw(2) << customers[i].curr_date.month << "/" << customers[i].curr_date.year << "(" << day_of_week << ")" << setfill(' ') << setw(11-day_of_week.length()) << "|";
    //set setfill( back to space)
    cout << setfill(' ');
    //print name
    cout << customers[i].name << " " << setw (longest_name_length - name_length) << "|";
    //print contact info
    cout << customers[i].contact << setw (longest_contact_length - contact_length) << "|";
    //print session
    cout << customers[i].session << setw(7) << "|";
    //print seat(s)
    cout << customers[i].n_seat << setw(7) << "|" << endl;
    if(i == n_customer - 1)
    {
      break;
    }
    else
    {
      print_seperate(longest_name_length);
    }
  }
}

/*********************************************************************
** Function: Print header of the customer list
** Description: Use to print out the header columns of the customer list
** Parameters: int
** Pre-Conditions:
** Post-Conditions: Printed the header of the customer list
*********************************************************************/
void print_heading(int name_length)
{
  cout << "┌──────────────────────┬";
  print_words(name_length, "─");
  cout << "┬───────────┬───────┬───────┐" << endl;
  cout << "|Date                  |Name";
  print_words(name_length - 4, " ");
  cout << "|Contact    |Session|Seat(s)|" << endl;
  print_seperate(name_length);
}

/*********************************************************************
** Function: Print symbols that seperate rows in the table
** Description: Use to seperate rows in the table
** Parameters: int
** Pre-Conditions:
** Post-Conditions: Print a seperating row
*********************************************************************/
void print_seperate(int name_length)
{
  cout << "├──────────────────────┼";
  print_words(name_length, "─");
  cout << "┼───────────┼───────┼───────┤" << endl;
}

/*********************************************************************
** Function: Print closing row of the table
** Description: Use to print the last row of the table
** Parameters: int
** Pre-Conditions:
** Post-Conditions: Print the last row of the table
*********************************************************************/
void print_close(int name_length)
{
  cout << "└──────────────────────┴";
  print_words(name_length, "─");
  cout << "┴───────────┴───────┴───────┘" << endl;
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
void print_info(struct customer* customers, int n_customer)
{
  int name_length = longest_name(customers, n_customer) + 1;
  print_heading(name_length);
  print_content(customers, n_customer);
  print_close(name_length);
}

/*********************************************************************
** Function: Swap two customer information
** Description: Use to swap two customer information of index i and
** index j in the array
** Parameters: struct customer*, int, int
** Pre-Conditions: customer pointer exist, index i and index j point
** to element in the customer pointer (in range)
** Post-Conditions: Swap information in customers[i] and customers[j]
*********************************************************************/
void swap_customer(struct customer* customers, int i, int j)
{
  struct customer temp;
  temp = customers[i];
  customers[i] = customers[j];
  customers[j] = temp;
}

/*********************************************************************
** Function: Sort customer information by date accendingly
** Description: Sorting the customers in the array accendingly by puting
** earlier reservation at the front of customer array
** Parameters: struct customer*, int
** Pre-Conditions: customers pointer exist and max index match number of
** customers
** Post-Conditions: Customers sorted by date accendingly
*********************************************************************/
void sort_by_date(struct customer* customers, int n_customer)
{
  struct customer temp;
  for(int i = 0; i < n_customer; i++)
  {
    for(int j = i; j < n_customer; j++)
    {
      if(customers[j].curr_date.year < customers[i].curr_date.year)
      {
        swap_customer(customers, i, j);
      }
      else if(customers[j].curr_date.year == customers[i].curr_date.year && customers[j].curr_date.month < customers[i].curr_date.month)
      {
        swap_customer(customers, i, j);
      }
      else if(customers[j].curr_date.year == customers[i].curr_date.year && customers[j].curr_date.month == customers[i].curr_date.month && customers[j].curr_date.day < customers[i].curr_date.day)
      {
        swap_customer(customers, i, j);
      }
    }
  }
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
void save_data(struct customer* customers, int n_customer, char* argv[], ofstream& outfile)
{
  outfile.open(argv[1]);
  if(outfile.fail())
  {
    cerr << "Failed to open " << argv[1] << endl;
    exit(0);
  }
  sort_by_date(customers, n_customer);
  outfile << n_customer << endl;
  for(int i = 0; i < n_customer; i++)
  {
    outfile << customers[i].name << "," << customers[i].session << ",";
    outfile << customers[i].contact << "," << customers[i].curr_date.year << ",";
    outfile << customers[i].curr_date.month << "," << customers[i].curr_date.day << ",";
    outfile << customers[i].n_seat << "," << endl;
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
void copy_customer(struct customer* source, struct customer* destination, int n_customer)         //qwert
{
  for(int i = 0; i < n_customer; i++)
  {
    destination[i].name = source[i].name;
    destination[i].session = source[i].session;
    destination[i].contact = source[i].contact;
    destination[i].curr_date.year = source[i].curr_date.year;
    destination[i].curr_date.month = source[i].curr_date.month;
    destination[i].curr_date.day = source[i].curr_date.day;
    destination[i].n_seat = source[i].n_seat;
  }
}

/*********************************************************************
** Function:
** Description:
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void add_customer(struct customer* customers, struct customer customer_info, int n_customer)
{
  customers[n_customer - 1].name = customer_info.name;
  customers[n_customer - 1].contact = customer_info.contact;
  customers[n_customer - 1].session = customer_info.session;
  customers[n_customer - 1].curr_date = customer_info.curr_date;
  customers[n_customer - 1].n_seat = customer_info.n_seat;
}

/*********************************************************************
** Function: Validate input for integer
** Description: See if a string input is an integer
** Parameters: string
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
bool is_int(string num)
{
  if(num.length() <= 0)
  {
    return false;
  }
  for(int i = 0; i < num.length(); i++)
  {
    if(num[i] < 48 || num[i] > 57)
    {
      return false;
    }
  }
  return true;
}

/*********************************************************************
** Function: Get string input from customer and change it to int
** Description: Change customer string input to int input
** Parameters: int
** Pre-Conditions: Input is in variable string
** Post-Conditions: String input changed to int input
*********************************************************************/
void get_int(int& input)
{
  string num;
  do
  {
    getline(cin, num);
    if(!is_int(num))
    {
      cout << "Please enter an integer." << endl;
    }
  } while(!is_int(num));
  input = stoi(num);
}

/*********************************************************************
** Function: Validate if input is within range
** Description: See if input is within string
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
int get_betwn(int min, int max)
{
  int input;
  do
  {
    get_int(input);
    if(input < min || input > max)
    {
      cout << "Please enter an integer between or equal to " << min << " and " << max << ": ";
    }
  } while(input < min || input > max);
  return input;
}

/*********************************************************************
** Function: Prompt and get options from customer
** Description: customer choose his/her options
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void ask_choice(int& choice)
{
  cout << "Choose an option from above: " << endl;
  cout << "1. Search for availability" << endl;
  cout << "2. Update reservation record" << endl;
  cout << "3. Save and exit" << endl << endl;
  cout << "Option: ";
  choice = get_betwn(1, 3);
}

/*********************************************************************
** Function: Input date from customer
** Description: Ask date from customer while asking for reservation
** information
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void ask_date(int& year, int& month, int& day)
{
  time_t now = time(NULL);
  tm* time = localtime(&now);
  int curr_year = 1900 + time->tm_year;
  int curr_month = 1+ time->tm_mon;
  int curr_day = time->tm_mday;
  cout << curr_year << " " << curr_month << " " << curr_day << endl;
  cout << "Enter date in the following: " << endl;
  cout << "Year: ";
  year = get_betwn(curr_year, 9999);
  cout << "Month: ";
  get_month(year, curr_year, month, curr_month);
  cout << "Day: ";
  get_day(year, curr_year, month, curr_month, day, curr_day);
}

void get_month(int year, int curr_year, int& month, int curr_month)
{
  if(year == curr_year)
  {
    month = get_betwn(curr_month, 12);
  }else
  {
    month = get_betwn(1, 12);
  }
}

void get_day(int year, int curr_year, int month, int curr_month, int& day, int curr_day)
{
  if(month == 2)
  {
    if(year % 4 == 0)
    {
      if(year == curr_year && month == curr_month)
      {
        day = get_betwn(curr_day, 29);
      }
      else
      {
        day = get_betwn(1, 29);
      }
    }
    else
    {
      if(year == curr_year && month == curr_month)
      {
        day = get_betwn(curr_day, 28);
      }
      else
      {
        day = get_betwn(1, 28);
      }
    }
  }
  else if(month == 4 || month == 6 || month == 9 || month == 11)
  {
    if(year == curr_year && month == curr_month)
    {
      day = get_betwn(curr_day, 30);
    }
    else
    {
      day = get_betwn(1, 30);
    }
  }
  else
  {
    if(year == curr_year && month == curr_month)
    {
      day = get_betwn(curr_day, 31);
    }
    else
    {
      day = get_betwn(1, 31);
    }
  }
}

/*********************************************************************
** Function: Get input session from customers
** Description: customers choose a session
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void ask_session(int& session)
{
  cout << "1. 11:00 A.M. - 12:30 A.M." << endl;
  cout << "2. 12:30 P.M. - 02:00 P.M." << endl;
  cout << "3. 05:00 P.M. - 06:30 P.M." << endl;
  cout << "4. 06:30 P.M. - 08:00 P.M." << endl;
  cout << "Enter the session for reservation: ";
  session = get_betwn(1, 4);
}

/*********************************************************************
** Function: Get number of guests from customers
** Description: customers enter number of guests
** Parameters: int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void ask_guest(int& guest_num)
{
  cout << "Enter the number of guest for reservation: ";
  guest_num = get_betwn(1, 8);
}

/*********************************************************************
** Function: Get contact from customer
** Description: customers enter contact
** Parameters: string
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void ask_contact(string& contact)
{
  cout << "Enter contact number of the customer: ";
  getline(cin, contact);
}

/*********************************************************************
** Function: Get customer input for his/her name
** Description: customer input his/her name
** Parameters: string
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void ask_name(string& name)
{
  cout << "Enter the customer name for the reservation:" << endl;
  cout << "Full name: ";
  getline(cin, name);
}

/***************************************************************************
** Function: Get a complete information from customer
** Description: Get data, session and number of guests from customers
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions:
***************************************************************************/
void ask_info(struct customer& customer_info)
{
  ask_date(customer_info.curr_date.year, customer_info.curr_date.month, customer_info.curr_date.day);
  ask_session(customer_info.session);
  ask_guest(customer_info.n_seat);
  cout << endl;
}

/*********************************************************************
** Function: Display message for availability
** Description: To inform customer if a session is available
** Parameters: bool, int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void available_msg(bool available, int empty_space)
{
  if(!available)
  {
    cout << "Sorry we have only " << empty_space << " seat(s) left for the reservation time." << endl;
  }
  else
  {
    cout << "The reservation time is available." << endl;
  }
}

/************************************************************************
** Function: Run the options choose by customer
** Description: Run the options choose by customer in ask_choice function
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions:
************************************************************************/
void run_option(struct customer** customers, int& n_customer, int option)
{
  int empty_space;
  bool availability;
  struct customer customer_info;
  if(option == 1)
  {
    cout << "\nSearching for availability..." << endl;
    ask_info(customer_info);
    availability = src_available(*customers, n_customer, empty_space, customer_info);
    available_msg(availability, empty_space);
  }
  else if(option == 2)
  {
    struct customer* temp;
    cout << "\nUpdating reservation record..." << endl;
    ask_info(customer_info);
    ask_name(customer_info.name);
    ask_contact(customer_info.contact);
    add_reserve(customers, n_customer, customer_info);
  }
}

/*********************************************************************
** Function: Search for availability
** Description: Check for availability
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
bool src_available(struct customer* customers, int n_customer, int& empty_space, struct customer customer_info)
{
  empty_space = 8;
  for(int i = 0; i < n_customer; i++)
  {
    if(customers[i].curr_date.year == customer_info.curr_date.year && customers[i].curr_date.month == customer_info.curr_date.month && customers[i].curr_date.day == customer_info.curr_date.day && customers[i].session == customer_info.session)
    {
      empty_space -= customers[i].n_seat;
    }
  }
  if(empty_space < 0)
  {
    cout << "Session overbooked, please check for reservation availability" << endl;
    return false;
  }
  if(customer_info.n_seat > empty_space)
  {
    return false;
  }
  else
  {
    return true;
  }
}

/*********************************************************************
** Function: Update customer info to update reservation record
** Description: Add customer info
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void add_customer_info(struct customer** customers, int n_customer, struct customer customer_info)
{
    struct customer *temp;
    temp = allocate_customer(n_customer);
    copy_customer(*customers, temp, n_customer);
    free_customer(&(*customers));
    n_customer++;
    *customers = allocate_customer(n_customer);
    copy_customer(temp, *customers, n_customer-1);
    free_customer(&temp);
    add_customer(*customers, customer_info, n_customer);
}

/*********************************************************************
** Function: Add reservation to update reservation record
** Description: Check for available seat(s) to update add reservation
** Parameters: struct customer*, int
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void add_reserve(struct customer** customers, int& n_customer, struct customer customer_info)
{
  int empty_space;
  bool available = src_available(*customers, n_customer, empty_space, customer_info);
  if(!available)
  {
    cout << endl;
    cout << "Sorry we have only " << empty_space << " seat(s) left for the reservation time." << endl;
    cout << "Please double check the reservation availability." << endl;
  }
  else
  {
    add_customer_info(customers, n_customer, customer_info);
    n_customer++;
    cout << "Update Success!" << endl;
  }
}

/*********************************************************************
** Function: Print session table
** Description: Show user the session time table
** Parameters:
** Pre-Conditions:
** Post-Conditions: Print out session time table
*********************************************************************/
void print_session()
{
  cout << "--Session Time Table--" << endl;
  cout << "11:00 A.M. - 12:30 A.M." << endl;
  cout << "12:30 P.M. - 02:00 P.M." << endl;
  cout << "05:00 P.M. - 06:30 P.M." << endl;
  cout << "06:30 P.M. - 08:00 P.M." << endl;
}
