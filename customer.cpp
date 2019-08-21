#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
#include "customer.hpp"

using namespace std;

/*********************************************************************
** Function: Open file I/O
** Description: Open the file I/O with the pathing provided by customer
** Parameters: ifstream&, char**
** Pre-Conditions: There is a second vector in the command line argument
** Post-Conditions: Success or fail to open the file I/O
*********************************************************************/
void open_file(ifstream& infile, char* argv[])
{
  infile.open("customer_data.txt");
  if(infile.fail())
  {
    cerr << "Failed to open customer_data.txt" << endl;
    exit(0);
  }
}

/*********************************************************************
** Function: Allocate an array for a customer structure
** Description: Create a customer structure array based on number of customer
**              read from file I/O
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
** Post-Conditions: Dynamic allocated customer will be free
*********************************************************************/
void free_customer(struct customer** customers)
{
  delete [] (*customers);
}

/*********************************************************************
** Function: Read customer data from input file
** Description: Use to get customer data from the input file at the
**              beginning of program to form customer structure array
** Parameters: struct customer*, int, ifstream&
** Pre-Conditions: Customer pointer exist and have enough or more space
**                 than number of customer
** Post-Conditions: Customers data passed in to customer array
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
    for(int i = 0; i < 8; i++)
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
    customers[j].r_num = stoi(testing[7]);
    j++;
  }
}

/*********************************************************************
** Function: Find the longest name among the customers
** Description: Use to find the longest name to determine the size of
                name column
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and not empty, max index of
**                 customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
**                  longest name
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
** Function: Find the longest contact among the customers
** Description: Use to find the longest contact to determine the size of
                contact column
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and not empty, max index of
                   customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
                    longest contact
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
** Function: Find the shortest contact among the customers
** Description: Use to find the shortest contact to determine the
                spacing of contact heading
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and not empty, max index of
                   customer array match the number of customer
** Post-Conditions: Calculate and return the number of character of the
                    shortest contact
*********************************************************************/
int shortest_contact(struct customer* customers, int n_customer)
{
  int min_length = 0;
  int combine_length = 0;
  for(int i = 0; i < n_customer; i++)
  {
    combine_length = customers[i].contact.length();
    if(combine_length < min_length)
    {
      min_length = combine_length;
    }
  }
  return min_length;
}
/*********************************************************************
** Function: Print a character for N times
** Description: Use to format the customer list
** Parameters: int, string
** Pre-Conditions: n/a
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
**              to information given from customer array
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and max index match with number
**                 of customer
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
    cout << "|R" << setfill('0') << setw(4) << customers[i].r_num;
    //print date info
    cout << " |" << setfill('0') << setw(2) << customers[i].curr_date.day << "/" << setfill('0') << setw(2) << customers[i].curr_date.month << "/" << customers[i].curr_date.year << "(" << day_of_week << ")" << setfill(' ') << setw(11-day_of_week.length()) << "|";
    //set setfill( back to space)
    cout << setfill(' ');
    //print name
    cout << customers[i].name << " " << setw (longest_name_length - name_length) << "|";
    //print contact info
    cout << customers[i].contact << setw (longest_contact_length + 1 - contact_length) << "|";
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
      print_seperate(longest_name_length, longest_contact_length);
    }
  }
}

/*********************************************************************
** Function: Print header of the customer list
** Description: Use to print out the header columns of the customer list
** Parameters: struct customer*, int
** Pre-Conditions: n/a
** Post-Conditions: Printed the header of the customer list
*********************************************************************/
void print_heading(struct customer* customers, int n_customer, int name_length, int contact_length)
{
  int longest_contact_length = longest_contact(customers, n_customer) + 10;
  int shortest_contact_length = shortest_contact(customers, n_customer);
  cout << "+------";
  cout << "+----------------------+";
  //print_words(name_length, "-");
  if(name_length > 4)
  {
    print_words(name_length, "-");
  }
  else
  {
    print_words(3, "-");
  }
  cout << "+";
  if(contact_length > 7)
  {
    print_words(contact_length - 1, "-");
  }
  else
  {
    print_words(7, "-");
  }
  cout << "+-------+-------+" << endl;
  cout << "|No.   |Date                  |Name";
  print_words(name_length - 4, " ");
  cout << "|Contact" << setw(longest_contact_length + 1 - shortest_contact_length) << "|Session|Seat(s)|" << endl;
  print_seperate(name_length, contact_length - 1);
}

/*********************************************************************
** Function: Print symbols that seperate rows in the table
** Description: Use to seperate rows in the table
** Parameters: int
** Pre-Conditions: n/a
** Post-Conditions: Print a seperating row
*********************************************************************/
void print_seperate(int name_length, int contact_length)
{
  cout << "+------+----------------------+";
  print_words(name_length, "-");
  cout << "+";
  print_words(contact_length, "-");
  cout << "+-------+-------+" << endl;
}

/*********************************************************************
** Function: Print closing row of the table
** Description: Use to print the last row of the table
** Parameters: int
** Pre-Conditions: n/a
** Post-Conditions: Print the last row of the table
*********************************************************************/
void print_close(int name_length, int contact_length)
{
  cout << "+------+-----------------------";
  print_words(name_length, "-");
  print_words(contact_length, "-");
  cout << "----------------+" << endl;
}

/*********************************************************************
** Function: Print customer info inside a table
** Description: Combine header, content and closing of the print
**              functions to form a complete table
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and max index match with number
**                 of customer
** Post-Conditions: Print complete customer info in a table
*********************************************************************/
void print_info(struct customer* customers, int n_customer)
{
  int name_length = longest_name(customers, n_customer) + 1;
  int contact_length = longest_contact(customers, n_customer) + 2;
  print_heading(customers, n_customer, name_length, contact_length);
  print_content(customers, n_customer);
  print_close(name_length, contact_length);
}

/*********************************************************************
** Function: Swap two customer information
** Description: Use to swap two customer information of index i and
**              index j in the array
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist, index i and index j point
**                 to element in the customer pointer (in range)
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
**              earlier reservation at the front of customer array
** Parameters: struct customer*, int
** Pre-Conditions: Customers pointer exist and max index match number of
**                 customers
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
**              data in to file provided in the command line argument
** Parameters: struct customer*, int, char*, ofstream&
** Pre-Conditions: File path exist, customers pointer exist and max
**                 index match with number of customers
** Post-Conditions: Write sorted customers data in to text file
*********************************************************************/
void save_data(struct customer* customers, int n_customer, int r_num, char* argv[], ofstream& outfile)
{
  outfile.open("customer_data.txt");
  if(outfile.fail())
  {
    cerr << "Failed to open customer_data.txt" << endl;
    exit(0);
  }
  sort_by_date(customers, n_customer);
  outfile << n_customer << endl;
  outfile <<  r_num << endl;
  for(int i = 0; i < n_customer; i++)
  {
    outfile << customers[i].name << "," << customers[i].session << ",";
    outfile << customers[i].contact << "," << customers[i].curr_date.year << ",";
    outfile << customers[i].curr_date.month << "," << customers[i].curr_date.day << ",";
    outfile << customers[i].n_seat << "," << customers[i].r_num << "," << endl;
  }
}

/*********************************************************************
** Function: Print customer info inside a table
** Description: Combine header, content and closing of the print
**              functions to form a complete table
** Parameters: struct customer*, int
** Pre-Conditions: Customer pointer exist and match index with number
**                 of customer
** Post-Conditions: Print complete customer info in a table
*********************************************************************/
void copy_customer(struct customer* source, struct customer* destination, int n_customer)
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
    destination[i].r_num = source[i].r_num;
  }
}

/*********************************************************************
** Function: Check if customer input for advanced search is substring
             compared to customer information
** Description: Check if customer input for advanced search is substring
                compared to customer information
** Parameters: struct customer
** Pre-Conditions: Customer enter substring to perform advanced search
** Post-Conditions: Perform delete_customer funciton if substring
                    input is valid
*********************************************************************/
bool equal(struct customer lhs, struct customer rhs)
{
  if(lhs.name == rhs.name && lhs.contact == rhs.contact && lhs.session == rhs.session
    && lhs.curr_date.year == rhs.curr_date.year && lhs.curr_date.month == rhs.curr_date.month
    && lhs.curr_date.day == rhs.curr_date.day && lhs.n_seat == rhs.n_seat)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*********************************************************************
** Function: Add customer
** Description: Add customer for add reservation record
** Parameters: struct customer*, struct customer, int
** Pre-Conditions: Customer want to add reservation record
** Post-Conditions: New reservation record created
*********************************************************************/
void add_customer(struct customer* customers, struct customer customer_info, int n_customer, int& r_num)
{
  customers[n_customer - 1].name = customer_info.name;
  customers[n_customer - 1].contact = customer_info.contact;
  customers[n_customer - 1].session = customer_info.session;
  customers[n_customer - 1].curr_date = customer_info.curr_date;
  customers[n_customer - 1].n_seat = customer_info.n_seat;
  customers[n_customer - 1].r_num = ++r_num;
}

/*********************************************************************
** Function: Delete customer from customer array
** Description: Used when customer want to delete his/her reservation
                record and in advanced search
** Parameters: struct customer*, struct customer, int&
** Pre-Conditions: Customer chose delete reservation record as option
                   or chose advanced search
** Post-Conditions: Reservation record is either deleted or advanced
                    search display the table for customer
*********************************************************************/
void delete_customer(struct customer* customers, struct customer customer_info, int& n_customer)
{
  for(int i = 0; i < n_customer; i++)
  {
    if(equal(customers[i], customer_info))
    {
      for(int j = i; j < n_customer - 1; j++)
      {
        customers[j] = customers[j+1];
      }
      n_customer--;
      i--;
    }
  }
}

/*********************************************************************
** Function: Validate input for integer
** Description: Check if a string input is an integer
** Parameters: string
** Pre-Conditions: Integer input is entered
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
** Parameters: int&
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

/**********************************************************************
** Function: Get string input from customer and change it to character
** Description: Change customer string input to character if condition
                is met
** Parameters: char*
** Pre-Conditions: Input is in variable string
** Post-Conditions: String input changed to character input if condition
                    is met
***********************************************************************/
void get_char(char& decision)
{
  string str;
  bool flag = false;
  do
  {
    getline(cin, str);
    if(str.length() == 1)
    {
      if(str[0] == 'Y' || str[0] == 'y' || str[0] == 'N' || str[0] == 'n')
      {
        flag = true;
      }
    }
    if(flag == false)
    {
      cout << "Please enter (Y/y) or (N/n) : ";
    }
  }while(flag == false);
  decision = str[0];
}

/*********************************************************************
** Function: Validate if input is within range
** Description: Check if input is within range
** Parameters: int
** Pre-Conditions: Customer enter an integer as input
** Post-Conditions: Display and read in input from customer again if
                    input is out of range
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
** Description: Customer choose his/her options
** Parameters: int&
** Pre-Conditions: Display and read option from customer
** Post-Conditions: An option are chosed by customer
*********************************************************************/
void ask_choice(int& choice)
{
  cout << "Choose an option from above: " << endl;
  cout << "1. Print reservation record" << endl;
  cout << "2. Search for availability" << endl;
  cout << "3. Update reservation record" << endl;
  cout << "4. Filter reservation record" << endl;
  cout << "5. Save and exit" << endl << endl;
  cout << "Option: ";
  choice = get_betwn(1, 5);
}

/*********************************************************************
** Function: Prompt and get update reservation options from customer
** Description: Customer choose his/her options in order to update
                reservation record
** Parameters: int&
** Pre-Conditions: Customer choose to update reservation record
** Post-Conditions: Either one out of three options are choose by
                    customer
*********************************************************************/
void ask_choice_update(int& choice)
{
  cout << "Choose an option to update reservation record: " << endl;
  cout << "1. Add reservation record" << endl;
  cout << "2. Delete reservation record" << endl;
  cout << "3. Change reservation record" << endl << endl;
  cout << "Option: ";
  choice = get_betwn(1, 3);
}

/*********************************************************************
** Function: Prompt and get change reservation options from customer
** Description: Customer choose his/her options in order to change
                reservation record
** Parameters: int&
** Pre-Conditions: Customer choose to change reservation record
** Post-Conditions: Either one out of four options are choose by
                    customer
*********************************************************************/
void ask_choice_change(int& choice)
{
  cout << "Choose an option to change reservation record: " << endl;
  cout << "1. Name" << endl;
  cout << "2. Session" << endl;
  cout << "3. Date" << endl;
  cout << "4. Contact" << endl;
  cout << "5. Number of guest" << endl;
  cout << "Option: ";
  choice = get_betwn(1, 5);
}

void ask_update_confrim(int& choice)
{
  cout << "Choose an option to perform next action: " << endl;
  cout << "1. Update changes" << endl;
  cout << "2. Discard changes" << endl;
  cout << "3. Continue changing" << endl;
  cout << "Option: ";
  choice = get_betwn(1, 3);
}
/*********************************************************************
** Function: Input date from customer
** Description: Ask date from customer while asking for reservation
                information
** Parameters: int&
** Pre-Conditions: Customer enter date for reservation
** Post-Conditions: Get date from customer
*********************************************************************/
void ask_date(int& year, int& month, int& day)
{
  time_t now = time(NULL);
  tm* time = localtime(&now);
  int restrict_year = 1900 + time->tm_year;
  int restrict_month = 1 + time->tm_mon;
  int restrict_day = time->tm_mday + 3;
  corret_date(restrict_year, restrict_month, restrict_day);
  cout << "Enter date in the following: " << endl;
  cout << "Year: ";
  year = get_betwn(restrict_year, 9999);
  cout << "Month: ";
  get_month(year, restrict_year, month, restrict_month);
  cout << "Day: ";
  get_day(year, restrict_year, month, restrict_month, day, restrict_day);
}

/************************************************************************
** Function: Get month of the year from customer
** Description: Customer enter month of the year for reservation date
** Parameters: int, int&
** Pre-Conditions: Customer enter month of the year for reservation date
** Post-Conditions: Month for reservation from customer is stored
************************************************************************/
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

/*********************************************************************
** Function: Get day of the week from customer
** Description: Customer enter day of the week for reservation date
** Parameters: int, int&
** Pre-Conditions: Customer enter day of the week for reservation date
** Post-Conditions: Day for reservation from customer is stored
*********************************************************************/
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
** Description: Customers choose a session
** Parameters: int&
** Pre-Conditions: Display and get session from customer
** Post-Conditions: Session from customer is stored
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
** Function: Get number of guest(s) from customers
** Description: Customers enter number of guest(s)
** Parameters: int&
** Pre-Conditions: Prompt and get number of guest(s) from customer
** Post-Conditions: Get number of guest from customer
*********************************************************************/
void ask_guest(int& guest_num)
{
  cout << "Enter the number of guest for reservation: ";
  guest_num = get_betwn(1, 8);
}

/*********************************************************************
** Function: Get contact number from customer
** Description: Customers enter contact number
** Parameters: string&
** Pre-Conditions: Prompt and get customer contact number
** Post-Conditions: Get customer contact number
*********************************************************************/
void ask_contact(string& contact)
{
  cout << "Enter contact number of the customer: ";
  getline(cin, contact);
}

/*********************************************************************
** Function: Get customer input for his/her name
** Description: Customer input his/her name
** Parameters: string&
** Pre-Conditions: Prompt and get name of customer
** Post-Conditions: Get full name of customer
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
** Parameters: struct customer&
** Pre-Conditions: Prompt and get information of customer
** Post-Conditions: Get complete information from customer
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
** Pre-Conditions: Customer enter a sessions and date to check for
                   availability
** Post-Conditions: Display message for availability of a session
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

/*********************************************************************
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void sry_msg(int empty_space)
{
  cout << endl;
  cout << "Sorry we have only " << empty_space << " seat(s) left for the reservation time." << endl;
  cout << "Please double check the reservation availability." << endl;
}

/************************************************************************
** Function: Run the options choose by customer
** Description: Run the options choose by customer in ask_choice function
** Parameters: struct customer*, int, int&
** Pre-Conditions: Program prompt and get option from customer
** Post-Conditions: The program ran based on the option chose by customer
************************************************************************/
void run_option(struct customer** customers, struct customer** results, int& n_customer, int& matches, int& r_num, int option)
{
  int empty_space;
  bool availability;
  struct customer customer_info;
  if(option == 1)
  {
    print_session();
    if(n_customer > 0)
    {
      sort_by_date(*customers, n_customer);
      print_info(*customers, n_customer);
    }
    else
    {
      cout << "No reservation record are found..." << endl;
    }
  }
  else if(option == 2)
  {
    cout << "\nSearching for availability..." << endl;
    ask_info(customer_info);
    availability = src_available(*customers, n_customer, empty_space, customer_info);
    available_msg(availability, empty_space);
  }
  else if(option == 3)
  {
    cout << "\nUpdating reservation record..." << endl;
    ask_choice_update(option);
    if (option == 1)
    {
      ask_info(customer_info);
      ask_name(customer_info.name);
      ask_contact(customer_info.contact);
      add_reserve(customers, n_customer, customer_info, r_num);
    }
    else if (option == 2)
    {
      cout << "\nDeleting reservation record..." << endl;
      delete_reservation(*customers, n_customer);
    }
    else if (option == 3)
    {
      cout << "Changing reservation record..." << endl;
      change_reservation(*customers, n_customer);
    }
  }
  else if(option == 4)
  {
    if(matches > 0)
    {
      free_customer(results);
      matches = 0;
    }
    cout << "\nFiltering reservation record..." << endl;
    advanced_search(results, *customers, n_customer, matches);
  }
}

/*********************************************************************
** Function: Search for availability
** Description: Check for availability
** Parameters: struct customer*, int, int&, struct customer
** Pre-Conditions: Customet enter date and sessions
** Post-Conditions: Display the availability of a sessions
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
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void advanced_search(struct customer** results, struct customer* customers, int n_customer, int& matches)
{
  string search, name, contact;
  matches = n_customer;
  *results = allocate_customer(n_customer);
  copy_customer(customers, *results, n_customer);
  cout << "Searching key word: ";
  getline(cin, search);
  transform(search.begin(), search.end(), search.begin(), ::tolower);
  for(int i = 0; i < n_customer; i++)
  {
    name = customers[i].name;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    contact = customers[i].contact;
    if(name.find(search) == string::npos && contact.find(search) == string::npos)
    {
      delete_customer(*results, customers[i], matches);
    }
  }
  if(matches > 0)
  {
    print_info(*results, matches);
  }
  else
  {
    cout << "Match not found..." << endl;
  }
}


/*********************************************************************
** Function: Add customer information to update reservation record
** Description: Add customer information to update reservation record
** Parameters: struct customer*, int, struct customer
** Pre-Conditions: Reservation is available for the particular session
** Post-Conditions: Customer information is added
*********************************************************************/
void add_customer_info(struct customer** customers, int n_customer, struct customer customer_info, int& r_num)
{
    struct customer *temp;
    temp = allocate_customer(n_customer);
    copy_customer(*customers, temp, n_customer);
    free_customer(&(*customers));
    n_customer++;
    *customers = allocate_customer(n_customer);
    copy_customer(temp, *customers, n_customer-1);
    add_customer(*customers, customer_info, n_customer, r_num);
    free_customer(&temp);
}

/*********************************************************************
** Function: Add reservation to update reservation record
** Description: Check for available seat(s) to update add reservation
** Parameters: struct customer*, int&
** Pre-Conditions: Customer chose add reservation record as option
** Post-Conditions: New reservation record added
*********************************************************************/
void add_reserve(struct customer** customers, int& n_customer, struct customer customer_info, int& r_num)
{
  int empty_space;
  bool available = src_available(*customers, n_customer, empty_space, customer_info);
  if(!available)
  {
    sry_msg(empty_space);
  }
  else
  {
    add_customer_info(customers, n_customer, customer_info, r_num);
    n_customer++;
    cout << "Update Success!" << endl;
  }
}

/*********************************************************************
** Function: Print session table
** Description: Show user the session time table
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Print out session time table
*********************************************************************/
void print_session()
{

  cout <<  setfill(' ') << setw(50) << "\t       __       __        __\n";
	cout << setw(80) << "\t      /  \\    /  \\ ____ |  | ____  ____    _____   ____ \n";
	cout << setw(80) << "\t      \\   \\/\\/   // __ \\|  |/ ___\\/  _ \\  /     \\ / __ \\\n";
	cout << setw(80) << "\t       \\        /|  ___/|  |  \\__(  <_> )|  | |  \|  ___/\n";
	cout << setw(80) << "\t        \\__/\\__/  \\____\\|__|\\_____>____/ |__|_|__|\\____\\\n";
	cout << endl;
  cout << "--Session Time Table--" << endl;
  cout << "11:00 A.M. - 12:30 A.M." << endl;
  cout << "12:30 P.M. - 02:00 P.M." << endl;
  cout << "05:00 P.M. - 06:30 P.M." << endl;
  cout << "06:30 P.M. - 08:00 P.M." << endl;
}

/*********************************************************************
** Function: Delete reservation record
** Description: Delete a customer reservation record if he/she intend
                to do so
** Parameters: struct customer*, int&
** Pre-Conditions: Customer chose delete reservation record as option
** Post-Conditions: Customer reservation is either deleted or cancel
                    deletion
*********************************************************************/
void delete_reservation(struct customer* customers, int& n_customer)
{
  struct customer confirm_customer;
  char decision;
  int reserve_num = 0, customer_index = 0;
  cout << "Reservation No.: ";
  do
  {
    get_r_num(reserve_num);
    customer_index = find_r_customer(customers, confirm_customer, n_customer, reserve_num);
    if(customer_index == -1)
    {
      cout << "Reservation number not found..." << endl;
      cout << "Please enter a valid Reservation No.: ";
    }
  }while(customer_index == -1);
  print_info(&confirm_customer, 1);
  cout << "Are you sure you want to delete? (Y/y) or (N/n) : ";
  get_char(decision);
  if((decision == 'Y') || (decision == 'y'))
  {
    delete_customer(customers, confirm_customer, n_customer);
    cout << "Successfully deleted " << "R" << setfill('0') << setw(4);
    cout << confirm_customer.r_num << " reservation..." << endl;
  }
  else if ((decision == 'N') || (decision == 'n'))
	{
    cout << "Cancelling reservation record..." << endl;
    cout << "Delete reservation record cancelled" << endl;
  }
}

/*********************************************************************
** Function: Assign reservation number to customer
** Description: Customer get a reservation number
** Parameters: int&
** Pre-Conditions: Customer is not given a reservation number
** Post-Conditions: Customer gets a reservation number
*********************************************************************/
void get_r_num(int& input)
{
  string reservation;
  bool flag = true;
  do
  {
    getline(cin, reservation);
    if(is_int(reservation))
    {
      input = stoi(reservation);
      flag = false;
    }
    else if(reservation[0] == 'R' || reservation[0] == 'r')
    {
      reservation.erase(0, 1);
      if(is_int(reservation))
      {
        input = stoi(reservation);
        flag = false;
      }
    }
    if(flag == true)
    {
      cout << "Please enter reservation number in right format." << endl;
      cout << "For example: R1234 or 1234" << endl;
      cout << "Reservation No.: ";
    }
  }while(flag == true);
}

/*********************************************************************
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
void change_reservation(struct customer* customers, int n_customer)
{
  int decision = 0, next_act = 0, empty_space = 0;
  struct customer confirm_customer, temp_customer, save_customer;
  int reserve_num = 0, customer_index = 0;
  bool available;
  cout << "Reservation No.: ";
  do
  {
    get_r_num(reserve_num);
    customer_index = find_r_customer(customers, confirm_customer, n_customer, reserve_num);
    if(customer_index == -1)
    {
      cout << "Reservation number not found..." << endl;
      cout << "Please enter a valid Reservation No.: ";
    }
  }while(customer_index == -1);
  temp_customer = confirm_customer;
  save_customer = confirm_customer;
  print_info(&confirm_customer, 1);
  do
  {
    ask_choice_change(decision);
    if(decision == 1)
    {
      ask_name(temp_customer.name);
    }
    else if(decision == 2)
    {
      ask_session(temp_customer.session);
      available = src_available(customers, n_customer, empty_space, temp_customer);
    }
    else if(decision == 3)
    {
      ask_date(temp_customer.curr_date.year, temp_customer.curr_date.month, temp_customer.curr_date.day);
      available = src_available(customers, n_customer, empty_space, temp_customer);
    }
    else if(decision == 4)
    {
      ask_contact(temp_customer.contact);
    }
    else if(decision == 5)
    {
      ask_guest(temp_customer.n_seat);
      available = src_available(customers, n_customer, empty_space, temp_customer);
    }
    if(!available)
    {
      sry_msg(empty_space);
      temp_customer = save_customer;
    }
    else
    {
      save_customer = temp_customer;
    }
    cout << "Reservation information" << endl;
    print_info(&save_customer, 1);
    ask_update_confrim(next_act);
  }while(next_act == 3);
  if(next_act == 1)
  {
    customers[customer_index] = temp_customer;
  }
}

/*********************************************************************
** Function: Determine if reservation number exist
** Description: Compared reservation number entered with existing
                reservation number
** Parameters: struct customer*, struct customer&, int
** Pre-Conditions: Reservation number exist
** Post-Conditions: The existence of reservation number is determined
*********************************************************************/
int find_r_customer(struct customer* customers, struct customer& result, int n_customer, int r_num)
{
  struct customer* temp;
  int match = n_customer, index = 0;
  temp = allocate_customer(n_customer);
  copy_customer(customers, temp, n_customer);
  for(int i = 0; i < n_customer; i++)
  {
    if(customers[i].r_num != r_num)
    {
      delete_customer(temp, customers[i], match);
    }
    else
    {
      index = i;
    }
  }
  if(match > 0)
  {
    result = temp[0];
    free_customer(&temp);
    return index;
  }
  free_customer(&temp);
  return -1;
}
