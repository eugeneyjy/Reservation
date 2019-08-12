#include <iostream>
#include <fstream>
#include "date.hpp"
#include "customer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  char c;
<<<<<<< HEAD
  int n_customer = 0, choice = 0 , result_count = 0, r_num = 0;
=======
  int n_customer = 0, choice = 0;
>>>>>>> 1288442a12d354981c845deb954c179efebde020
  struct customer* customers;
  struct customer* result;
  ifstream infile;
  ofstream outfile;
  valid_cla(argc, argv);//validation of command line argument
  open_file(infile, argv);//open customer info file
  infile >> n_customer;
  infile >> r_num;
  infile.get(c);
  customers = allocate_customer(n_customer);
  read_customer_data(customers, n_customer, infile);//read in customer data
  infile.close();
  print_session();
  if(n_customer > 0)
  {
    sort_by_date(customers, n_customer);
    print_info(customers, n_customer);
  }
  do
  {
    choice = 0;
    ask_choice(choice);
<<<<<<< HEAD
    run_option(&customers, &result, n_customer, result_count, r_num, choice);
  } while(choice != 6);
  save_data(customers, n_customer, r_num, argv, outfile);
=======
    run_option(&customers, n_customer, choice);
  } while(choice != 5);
  save_data(customers, n_customer, argv, outfile);
>>>>>>> 1288442a12d354981c845deb954c179efebde020
  free_customer(&customers);
  return 0;
}
