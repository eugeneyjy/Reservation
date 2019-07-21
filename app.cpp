#include <iostream>
#include <fstream>
#include "date.hpp"
#include "customer.hpp"

using namespace std;

int main(int argc, char* argv[]){

  struct customer* customers;
  int n_customer = 0, choice = 0;
  ifstream infile;
  ofstream outfile;
  valid_cla(argc, argv);//validation of command line argument
  open_file(infile, argv);//open customer info file
  infile >> n_customer;
  customers = allocate_customer(n_customer);
  read_customer_data(customers, n_customer, infile);//read in customer data
  infile.close();
  cout << "--Session Time Table--" << endl;
  cout << "11:00 A.M. - 12:30 A.M." << endl;
  cout << "12:30 P.M. - 02:00 P.M." << endl;
  cout << "05:00 P.M. - 06:30 P.M." << endl;
  cout << "06:30 P.M. - 08:00 P.M." << endl << endl;
  sort_by_date(customers, n_customer);
  print_info(customers, n_customer);
  ask_choice(choice);
  run_option(&customers, n_customer, choice);
  save_data(customers, n_customer, argv, outfile);
  free_customer(&customers);
  return 0;
}
