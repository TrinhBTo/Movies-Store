#include "MovieStore.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

MovieStore::~MovieStore() {

  for (const auto &i : customers) {
    delete i;
  }
}

// read to end of line, returning string for debugging
const string MovieStore::discardLine(istream &is) {
  string discard;
  getline(is, discard);
  return discard;
}

// processes the movie files
void MovieStore::processMovies(const string &filename) {
  ifstream fs(filename);
  if (!fs.is_open()) {
    cerr << "Could not open file: " << filename << endl;
  }
  char movieType;
  while (fs >> movieType) {
    // creates movie and puts in the correct bucket
    Movie *movie = factory.create(movieType);
    if (movie != nullptr) {
      if (movie->read(fs)) {
        // inserts movie into hashtable
        movies.insert(movie);
      } else {
        delete movie;
      }
    } else {
      cerr << "Unrecognized movie type: " << movieType << endl;
      cerr << "Discarding line: " << discardLine(fs) << endl;
    }
  }
  fs.close();
}

// processes customer file
void MovieStore::processCustomers(const string &customerFile) {

  ifstream fs(customerFile);

  if (!fs.is_open()) {

    cerr << "Could not open file: " << customerFile << endl;
  }

  int id;
  string first;
  string last;

  while (fs >> id) {
    // captures first and last name
    fs >> first >> last;

    // check if customer id is valid
    if (id >= 0) {

      // creates new customer with id, first and last name
      auto *cust = new Customer(id, first, last);

      // adds to customer storage
      customers.push_back(cust);
    }
  }

  fs.close();
}

// helper function to find customers
Customer *MovieStore::findCustomer(int id) {
  // if customer id is found in customer storage, return customer
  for (const auto &cust : customers) {

    if (cust->ID == id) {

      return cust;
    }
  }

  return nullptr;
}

// helper function to check if customer exists in customer storage
bool MovieStore::containsCustomer(int id) {
  // return true if id is in customer storage
  for (const auto &cust : customers) {

    if (cust->ID == id) {

      return true;
    }
  }
  return false;
}

// process commands files
void MovieStore::processCommand(const string &commandFile) {
  // Create InputFileStream
  ifstream transactionFile;

  // Open file
  transactionFile.open(commandFile);

  // Check if the filr is open
  if (transactionFile.is_open()) {

    // Innitialize transaction command
    string transc;

    // Read file line by line

    while (getline(transactionFile, transc)) {

      // and push into a queue
      transactions.push(transc);
    }

    // Process the Commands stored in queue
    while (!transactions.empty()) {

      // Check the command and process
      processTransaction(transactions.front());

      // Take the command out of the queue after finish
      transactions.pop();
    }
  }

  // Close file
  transactionFile.close();
}

// processes transactions from the queue
void MovieStore::processTransaction(const string &transc) {

  // A stringstream to break down each command.
  stringstream fs(transc);

  // First evaluate the Command type
  string commandType;
  int custID;
  string mediaType;
  string details;
  Customer *c;
  Movie *m;

  while (fs >> commandType) {
    if (commandType == "B") {
      fs >> custID >> mediaType;
      getline(fs, details);
      // find the customer the id belongs to and the movie if they exist
      c = findCustomer(custID);
      m = movies.findMovie(details);

      if (c != nullptr && m != nullptr) {
        borrow(m, c);
      }
    } else if (commandType == "R") {

      fs >> custID >> mediaType;
      getline(fs, details);

      // find the customer the id belongs to and the movie if they exist
      c = findCustomer(custID);
      m = movies.findMovie(details);

      if (c != nullptr && m != nullptr) {
        returnCommand(m, c);
      }

    } else if (commandType == "H") {
      string s;
      // makes sure that there is a cust ID after command bc invalid otherwise
      if (getline(fs, s)) {

        custID = atoi(s.c_str());

        if (containsCustomer(custID)) {
          c = findCustomer(custID);

          c->printHistory();
        }
      } else {
        cerr << "Print history unsuccessful!" << endl;
      }
    } else if (commandType == "I") {
      // using operator overload to print out all of the movies in the inventory
      cout << movies;

    } else {
      // takes care of errors if no compatible command type, and will discard
      // the line so its not processed further
      cerr << "No compatible command type or invalid customer/movie" << endl;
      cerr << "Discarding line: " << discardLine(fs) << endl;
    }
  }
}

// returns true or false if borrow transaction is successful
bool MovieStore::borrow(Movie *mov, Customer *cust) {
  // if the movie exists in hashtable and the customer exists in customer
  // storage, process transaction
  if (mov != nullptr && containsCustomer(cust->ID) && cust != nullptr) {
    // if the stock is 0, cannot borrow
    if (mov->stock == 0) {
      cerr << "Cannot Borrow" << endl;
      return false;
    }

    // if there stock to borrow
    if (mov->stock >= 1) {
      // add to currently checked out to keep track of it
      currentlyCheckedOut.emplace(cust->ID, mov);
      // updates stock of movie
      mov->stock = mov->stock - 1;
      // updates history of customer to show transaction
      cust->updateHistory(mov, "B");

      return true;
    }
  }
  return false;
}

// returns true if return transaction is successful
bool MovieStore::returnCommand(Movie *mov, Customer *cust) {
  // if movie exists in hashtable and customer exists in customer storage, carry
  // on
  if (mov != nullptr && containsCustomer(cust->ID) && cust != nullptr) {
    // checks if the movie being returned has already been checked out by the
    // same customer trying to return it
    for (const auto &p : currentlyCheckedOut) {
      // check if the customer has checked out the movie
      if (p.first == cust->ID && p.second == mov) {
        // bc its being returned, deleted from map
        currentlyCheckedOut.erase(cust->ID);
        // updates the stock of the movie
        mov->stock = mov->stock + 1;
        // updates history of customer
        cust->updateHistory(mov, "R");
        return true;
      }
    }
  }
  return false;
}
