

#include "HashTable.h"
#include "movie.h"
// #include "comedy.h"
// #include "classic.h"
// #include "drama.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Constructor
HashTable::HashTable() {

  vector<vector<Movie *>> mat;

  for (int i = 0; i < 26; i++) {

    // construct a vector of Movies
    vector<Movie *> v;

    // push back above one-dimensional vector
    mat.push_back(v);
  }

  // initialize the hash table
  hashMovie = mat;
}

// Destructor
HashTable::~HashTable() { clear(); }

// Helper sort function for vector of Movie*
bool HashTable::sortForMovie(Movie *mov1, Movie *mov2) { return *mov1 < *mov2; }

// Insert new Movie to the hash table
bool HashTable::insert(Movie *m) {

  // if movie is already inside, don't add again
  if (contains(m)) {

    return false;
  }

  // find the index for the new movie's type
  int index = (m->type.c_str())[0] - 'A';

  // Check for the movie's type

  // If it's "C"
  if (m->type == "C") {

    // cast movie into correct type Classic
    auto movie = dynamic_cast<Classic *>(m);

    // then push movie into the containers at index
    hashMovie[index].push_back(movie);
  }

  // If it's "D"
  if (m->type == "D") {

    // cast movie into correct type Drama
    auto movie = dynamic_cast<Drama *>(m);

    // then push movie into the containers at index
    hashMovie[index].push_back(movie);
  }

  // If it's "F"
  if (m->type == "F") {

    // cast movie into correct type Comedy
    auto movie = dynamic_cast<Comedy *>(m);

    // then push movie into the containers at index
    hashMovie[index].push_back(movie);
  }

  // sort container to make sure they are in correct order
  sort(hashMovie[index].begin(), hashMovie[index].end(), sortForMovie);

  return true;
}

// Check if the movie given is available in hash table
bool HashTable::contains(Movie *m) {

  // find potential index for the given movie
  int index = (m->type.c_str())[0] - 'A';

  // if the container at that index if empty return false
  if (hashMovie.empty() || hashMovie[index].empty()) {
    return false;
  }

  // Check each movies in the container at index
  for (const auto &i : hashMovie[index]) {

    // using operator== overload, if it's equal to the given movie
    if (i == m) {

      // return true
      return true;
    }
  }

  // return false if there's no movie == to the given one
  return false;
}

// Find the  Movie* with the given details
Movie *HashTable::findMovie(const string &movieDetails) {

  // take in all the details from the main details string
  stringstream ss;
  ss << movieDetails;
  string type;
  ss >> type;

  // find the index for the movie type
  int index = (type.c_str())[0] - 'A';

  // return the movie* with the compatable type Classic and details

  if (type == "C") {

    int month;
    int year;
    string actor;

    // Movie * const &i :
    ss >> month >> year;
    getline(ss, actor, '\0');

    for (const auto &i : hashMovie[index]) {

      if (i->releaseMonth == month && i->releaseYear == year &&
          i->majorActor == i->trimString(actor)) {
        return i;
      }
    }
  }

  // return the movie* with the compatable type Drama and details
  if (type == "D") {

    string director;
    string title;

    getline(ss, director, ',');
    getline(ss, title, ',');

    for (const auto &i : hashMovie[index]) {

      // using operator== overload
      if (i->director == i->trimString(director) &&
          i->title == i->trimString(title)) {
        return i;
      }
    }
  }

  // return the movie* with the compatable type Comedy and details
  if (type == "F") {

    string title;
    int year;

    getline(ss, title, ',');
    ss >> year;

    for (const auto &i : hashMovie[index]) {

      // using operator== overload
      if (i->title == i->trimString(title) && i->releaseYear == year) {
        return i;
      }
    }
  }

  return nullptr;
}

// overloads ostream so that it prints all of the movies in the order we want
ostream &operator<<(ostream &stream, const HashTable &other) {
  string c1 = "C";
  string c2 = "D";
  string c3 = "F";

  stream << "Store Inventory" << endl;

  stream << "  Comedy Movies Lists" << endl;

  int index = (c3.c_str())[0] - 'A';

  for (const auto &i : other.hashMovie[index]) {

    stream << *i << endl;
  }

  stream << "  Drama Movies Lists" << endl;

  index = (c2.c_str())[0] - 'A';

  for (const auto &i : other.hashMovie[index]) {

    stream << *i << endl;
  }

  stream << "  Classic Movies Lists" << endl;

  index = (c1.c_str())[0] - 'A';

  for (const auto &i : other.hashMovie[index]) {

    stream << *i << endl;
  }

  return stream;
}

// helper function for the destructor
void HashTable::clear() {

  // trverse and delete every single pointer
  for (const auto &i : hashMovie) {
    for (const auto &d : i) {
      delete d;
    }
    // delete i;
  }
}