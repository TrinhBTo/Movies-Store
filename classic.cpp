#include "classic.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Return movie's details as a string
string Classic::movieDetails() const {

  string s = type + " " + to_string(releaseMonth) + " " +
             to_string(releaseYear) + " " + majorActor;

  return s;
}

// Create a new Classic Movie
Movie *Classic::create() { return new Classic(); }

// Read the classic movie from the scanner with
// Classic: C, Stock, Director, Title, Major actor ReleaseMonth ReleasedYear

bool Classic::read(istream &is) {

  // set the type string
  type = "C";

  // discard the ","
  string c;
  is >> c;

  // read stock director and title
  stock = stoi(trimString(readNextItem(is)));
  ogStock = stock;
  director = readNextItem(is);
  title = readNextItem(is);

  // read major actor, released month and released year as a string
  string str;
  vector<string> vs;

  // split the string into different components
  if (getline(is, str) && !str.empty()) {
    vs = splitString(trimString(str), ' ');
  }

  // then assign it to its variable.
  majorActor = vs[0] + " " + vs[1];
  releaseMonth = stoi(vs[2]);
  releaseYear = stoi(vs[3]);

  return true;
}

// Print out the movie with all informations
ostream &Classic::printer(ostream &os) const {
  os << "Classic: " << type << " "
     << "remaining stock: " << stock << " borrowed stock: " << ogStock - stock
     << ", director: " << director << ", title: " << title
     << ", major actor: " << majorActor << ", released date: " << releaseMonth
     << " " << releaseYear;
  return os;
}

// Help to check if two Classic movie is equal to each others
bool Classic::operator==(const Movie &other) const {

  // cast the movie to the corrected class
  auto m = dynamic_cast<const Classic &>(other);

  bool equal = true;

  // check if the 2 movies has the same details
  if (this->type != m.type || this->stock != m.stock ||
      this->director != m.director || this->title != m.title ||
      this->majorActor != m.majorActor ||
      this->releaseMonth != m.releaseMonth ||
      this->releaseYear != m.releaseYear) {
    equal = false;
  }

  return equal;
}

// Help to check if this Classic movie is smaller than the other one
bool Classic::operator<(const Movie &other) const {

  // cast the movie to the corrected class
  auto m = dynamic_cast<const Classic &>(other);

  // if they are released in the same year then compare the released moth
  if (this->releaseYear == m.releaseYear) {

    // if they are released in the same month, compare the major actor
    if (this->releaseMonth == m.releaseMonth) {

      // if they have the same major actor return false
      if (this->majorActor == m.majorActor) {

        return false;
      }

      // else return if this movie's major actor is smaller than the other one
      return this->majorActor < m.majorActor;
    }

    // else return if this movie's released month is smaller than the other one
    return this->releaseMonth < m.releaseMonth;
  }

  // else return if this movie's released year is smaller than the other one
  return this->releaseYear < m.releaseYear;
}
