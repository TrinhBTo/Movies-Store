#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "classic.h"
#include "comedy.h"
#include "customer.h"
#include "drama.h"
#include "movie.h"

using namespace std;

class HashTable {

  friend ostream &operator<<(ostream &stream, const HashTable &other);

private:
  // the container for the hash table
  vector<vector<Movie *>> hashMovie;
  // helper to sort movies
  static bool sortForMovie(Movie *mov1, Movie *mov2);

public:
  // constructor
  HashTable();
  // destructor
  ~HashTable();

  // returns true if successfully inserted into hash table
  bool insert(Movie *m);
  // returns true if movie exists in hashtable
  bool contains(Movie *m);
  // helper for destructor
  void clear();
  // helper, finds the movie in the hashtable
  Movie *findMovie(const string &movieDetails);
};
#endif