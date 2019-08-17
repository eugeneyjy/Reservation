#include <iostream>
#include <fstream>
#include "date.hpp"
#include "customer.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	char c;
	int n_customer = 0, choice = 0, result_count = 0, r_num = 0;
	struct customer* customers;
	struct customer* result;//The result u pass in to the advance search
	ifstream infile;
	ofstream outfile;
	open_file(infile, argv);//open customer info file
	infile >> n_customer;
	infile >> r_num;
	infile.get(c);
	customers = allocate_customer(n_customer);
	read_customer_data(customers, n_customer, infile);//read in customer data
	infile.close();
	print_session();
	if (n_customer > 0)
	{
		sort_by_date(customers, n_customer);
		print_info(customers, n_customer);
	}
	do
	{
		ask_choice(choice);
		system("cls");
		run_option(&customers, &result, n_customer, result_count, r_num, choice);
	} 
	while (choice != 5);
	save_data(customers, n_customer, r_num, argv, outfile);
	free_customer(&customers);
	if (result_count > 0)
	{
		free_customer(&result);
	}
	return 0;
}