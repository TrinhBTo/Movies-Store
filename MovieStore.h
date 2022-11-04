#ifndef MOVIE_STORE_H
#define MOVIE_STORE_H

#include "MovieFactory.h"
//#include "MovieFactory.cpp"
#include "HashTable.h"
//#include "HashTable.cpp"
#include "customer.h"
//#include "customer.cpp"

// #include "movie.h"
// #include "comedy.h"
// #include "classic.h"
// #include "drama.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class MovieStore {
public:
  MovieStore() = default;
  ~MovieStore();

  // helper, discard line if there is an error
  const string discardLine(istream &is);
  // processes movies file
  void processMovies(const string &filename);
  // processes customer file
  void processCustomers(const string &customerFile);
  // processes command file
  void processCommand(const string &commandFile);
  // helper, returns customer with id
  Customer *findCustomer(int id);
  // helper, returns true if customer exists in customer storage
  bool containsCustomer(int id);
  // returns true if borrow transaction is succesful
  bool borrow(Movie *mov, Customer *cust);
  // returns true if return transaction is successful
  bool returnCommand(Movie *mov, Customer *cust);
  // processes transactions
  void processTransaction(const string &transc);

private:
  // holds all of the movies, our movie storage
  HashTable movies;
  // holds all of the customers, customer storage
  vector<Customer *> customers;
  //
  MovieFactory factory;
  // will store all of the borrowed movies and the customer who borrowed them
  unordered_map<int, Movie *> currentlyCheckedOut;
  // is used to process transactions
  queue<string> transactions;
};

#endif // MOVIE_STORE_H