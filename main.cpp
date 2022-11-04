#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "MovieStore.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "movie.h"

using namespace std;

void testStore1() {
  cout << "Start testStore1" << endl;

  string cfile = "testcommands-1.txt";
  stringstream out;
  ifstream fs(cfile);
  assert(fs.is_open());
  char commandType;
  string discard;
  while (fs >> commandType) {
    out << commandType;
    getline(fs, discard);
  }
  fs.close();
  string result = "IHHBRIBBIH";
  assert(out.str() == result);
  cout << "End testStore1" << endl;
}

int main() {
  MovieStore store;
  store.processMovies("data4movies.txt");
  store.processCustomers("data4customers.txt");
  store.processCommand("data4commands.txt");
  store.processCommand("testcommands-1.txt");

  testStore1();
  return 0;
}
