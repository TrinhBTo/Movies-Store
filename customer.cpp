#include "customer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// default constructor
Customer::Customer() {
  ID = 0;
  firstName = "";
  lastName = "";
}

// constructor with the given input
Customer::Customer(int id, const string &first, const string &last) {
  ID = id;
  firstName = first;
  lastName = last;
}

// Update customer history after every transaction
void Customer::updateHistory(Movie *mov, const string &transactionT) {

  // get the movie's details
  string m = mov->movieDetails();

  // Add the transaction to the history record of the customer
  history.push_back(transactionT + " " + m);
}

// Print out the customer history
void Customer::printHistory() const {

  cout << "Transaction History for " << firstName << " " << lastName << ": "
       << ID << endl;

  // print history line by line chronological order
  for (const auto &transc : history) {

    cout << "   " << transc << endl;
  }
}

// Help to check if two Customer is equal to each others
bool Customer::operator==(const Customer &other) const {

  bool e = false;
  // check if the 2 customers has the same details
  if (this->ID == other.ID && this->firstName == other.firstName &&
      this->lastName == other.lastName) {
    e = true;
  }

  return e;
}
