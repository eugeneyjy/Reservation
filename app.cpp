#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "date.hpp"
#include "customer.hpp"
#include "mergeSort.hpp"

using namespace std;

void welcomeMessage();

int main() {
    char c;
    int n_customer = 0, choice = 0 , result_count = 0, r_num = 0;
    struct customer* customers;
    struct customer* result;//The result u pass in to the advance search
    ifstream infile;
    ofstream outfile;
    open_file(infile);//open customer info file
    //check if file is empty
    if (infile.peek() == ifstream::traits_type::eof()) {
        displayFileFormatError();
        exit(0);
    }
    infile >> n_customer;
    infile >> r_num;
    infile.get(c);
    customers = allocate_customer(n_customer);
    read_customer_data(customers, n_customer, infile);//read in customer data
    infile.close();
    if(n_customer > 0) {
        customers = sort_by_date(customers, n_customer);
    }
    do {
        welcomeMessage();
        ask_choice(choice);
        run_option(&customers, &result, n_customer, result_count, r_num, choice);
        cout << "Press enter to continue..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //clear screen
        cout << "\033[2J\033[1;1H";
    } while(choice != 5);

    save_data(customers, n_customer, r_num, outfile);
    free_customer(&customers);

    if(result_count > 0) {
        free_customer(&result);
    }
    return 0;
}

void welcomeMessage() {
    cout <<  setfill(' ') << setw(50) << "\t       __      __        __\n";
    cout << setw(80) << "\t      /  \\    /  \\ ____ |  | ____  ____    _____   _____ \n";
    cout << setw(80) << "\t      \\   \\/\\/   // __ \\|  |/ ___\\/  _ \\  /     \\ /  __ \\\n";
    cout << setw(80) << "\t       \\        /|  ___/|  |  \\__(  <_> )|  | |  ||  ___/\n";
    cout << setw(80) << "\t        \\__/\\__/  \\____\\|__|\\_____>____/ |__|_|__|\\____\\\n" << endl;
}