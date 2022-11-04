#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "movie.h"
#include <string>
#include <vector>

using namespace std;

class Customer {

  friend ostream &operator<<(ostream &stream,
                             const Customer &other); // prints out history

private:
  int ID;
  string firstName;
  string lastName;
  vector<string> history;

  friend class MovieStore;

public:
  // default constructor
  Customer();
  // constructor with the given input
  Customer(int id, const string &first, const string &last);

  // Update customer history after every transaction
  void updateHistory(Movie *mov, const string &transactionT);

  // Print out the customer history
  void printHistory() const;

  // Help to check if two Customer is equal to each others
  bool operator==(const Customer &other) const;
};
#endif // CUSTOMER_H