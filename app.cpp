#include <iostream>
#include <fstream>
#include "date.hpp"
#include "customer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  char c;
  int n_customer = 0, choice = 0 , result_count = 0;
  struct customer* customers;
  struct customer* result;//The result u pass in to the advance search
  ifstream infile;
  ofstream outfile;
  valid_cla(argc, argv);//validation of command line argument
  open_file(infile, argv);//open customer info file
  infile >> n_customer;
  infile.get(c);
  customers = allocate_customer(n_customer);
  read_customer_data(customers, n_customer, infile);//read in customer data
  infile.close();
  print_session();
  do
  {
    choice = 0;
    sort_by_date(customers, n_customer);
    print_info(customers, n_customer);
    ask_choice(choice);
    run_option(&customers, n_customer, choice);
  } while(choice != 3);
  save_data(customers, n_customer, argv, outfile);
  free_customer(&customers);
  if(result_count > 0)
  {
    free_customer(&result);
  }
  return 0;
}
