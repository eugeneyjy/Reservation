#include <iostream>
#include "mergeSort.hpp"

using namespace std;

void merge(struct customer *customer, const int left, const int mid, const int right) {
    struct customer *leftCustomer = new struct customer[mid - left + 2];
    struct customer *rightCustomer = new struct customer[right - mid + 1];
    for (int i = left; i <= mid; i++) {
        leftCustomer[i - left] = customer[i];
    }
    for (int i = mid + 1; i <= right; i++) {
        rightCustomer[i - mid - 1] = customer[i];
    }

    //For compariing to neighbor element
    struct date max_date(9999, 12, 31);
    leftCustomer[mid - left + 1].setDate(max_date);
    rightCustomer[right - mid].setDate(max_date);

    int i = 0, j = 0;
    for (int k = left; k <= right; k++) {
        const int compare = compareDate(leftCustomer[i], rightCustomer[j]);
        if (compare == -1) {
            customer[k] = leftCustomer[i];
            i++;
        } else {
            customer[k] = rightCustomer[j];
            j++;
        } 
    }
    free_customer(&leftCustomer);
    free_customer(&rightCustomer);
}

struct customer* mergeSort (struct customer *customer, const int left, const int right) {
    if (left < right) {
        const int mid = (left + right) / 2;
        mergeSort(customer, left, mid);
        mergeSort(customer, mid + 1, right);
        merge(customer, left, mid, right);
    }
    return customer;
}
/*********************************************************************
** Function: Sort customer information by date accendingly
** Description: Sorting the customers in the array accendingly by puting
** earlier reservation at the front of customer array via merge sort
** Parameters: struct customer*, int
** Pre-Conditions: customers pointer exist and max index match number of
** customers
** Post-Conditions: Customers sorted by date accendingly
*********************************************************************/
struct customer* sort_by_date(struct customer *customer, const int size) {
    return mergeSort(customer, 0, size - 1);
}

int compareDate(const struct customer left_customer, const struct customer right_customer) {
    if(left_customer.getDate().getYear() < right_customer.getDate().getYear()) {
        return -1;
    }
    else if(left_customer.getDate().getYear() == right_customer.getDate().getYear() && left_customer.getDate().getMonth() < right_customer.getDate().getMonth()) {
        return -1;
    }
    else if(left_customer.getDate().getYear() == right_customer.getDate().getYear() && left_customer.getDate().getMonth() == right_customer.getDate().getMonth() && left_customer.getDate().getDay() < right_customer.getDate().getDay()) {
        return -1;
    }
    else if (left_customer.getDate().getYear() == right_customer.getDate().getYear() && left_customer.getDate().getMonth() == right_customer.getDate().getMonth() && left_customer.getDate().getDay() == right_customer.getDate().getDay()) {
        return compareRnum(left_customer, right_customer);
    } else return 1;
}

int compareRnum(const struct customer left_customer, const struct customer right_customer) {
    if(left_customer.getRnum() < right_customer.getRnum()) {
        return -1;
    } else return 1;
}