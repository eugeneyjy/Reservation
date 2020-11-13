#include <iostream>
#include "customer.hpp"

#ifndef __MERGESORT_HPP
#define __MERGESORT_HPP

using namespace std;

//implement mergeSort to sort the file if it is not in order
void merge(struct customer *customer, const int left, const int mid, const int right);
struct customer* mergeSort (struct customer *customer, const int left, const int right);
struct customer* sort_by_date(struct customer *customer, const int size);
int compareDate(const struct customer left_customer, const struct customer right_customer);
int compareRnum(const struct customer left_customer, const struct customer right_customer);

#endif
