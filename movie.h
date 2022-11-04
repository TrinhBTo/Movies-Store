#ifndef MOVIE_H
#define MOVIE_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Movie {
  friend ostream &operator<<(ostream &os, const Movie &m) {
    return m.printer(os);
  }

protected:
  friend class HashTable;
  friend class MovieStore;

  // these are the variables that will be used in the comedy, classic, and drama
  // classes
  string type;
  mutable int stock = 0;
  int ogStock = 0;
  string director = "";
  string title = "";
  string majorActor = "";
  int releaseMonth = 0;
  int releaseYear = 0;

  // ************************** HELPER FUNCTION ******************************
  // this is a helper function that will read the next word in a line
  string readNextItem(istream &io, char delimiter = ',') {
    const char space = ' ';
    string str;
    getline(io, str, delimiter);
    if (str.empty()) {
      return str;
    }

    return str.substr(str.find_first_not_of(space),
                      str.find_last_not_of(space) + 1);
  }

  // helper, trims the line
  string trimString(const string &str) {
    return str.substr(str.find_first_not_of(' '),
                      str.find_last_not_of(' ') + 1);
  }

  // helper - split string into multiple based on delimiter
  vector<string> splitString(const string &str, char delimiter = ',') {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(trimString(token));
    }
    return tokens;
  }

  // *************************************************************************

public:
  // all of these functions will be overriden in the child classes

  Movie() = default;
  // this will return all of the movies details depending on the type
  virtual string movieDetails() const = 0;
  // this will create a new movie
  virtual Movie *create() = 0;
  // this will read the movie and capture all of the variables, title, director,
  // etc.
  virtual bool read(istream &is) = 0;
  // this will print out the movie
  virtual ostream &printer(ostream &os) const = 0;
  // this compares if two movies are equal to each other
  virtual bool operator==(const Movie &other) const = 0;
  // this will be used to sort the movies based on type
  virtual bool operator<(const Movie &other) const = 0;

  virtual ~Movie() = default;
};

#endif // MOVIE_H