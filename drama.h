#ifndef DRAMA_H
#define DRAMA_H

#include "movie.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Drama class
 */
class Drama : public Movie {
private:
  friend class MovieStore;
  friend class HashTable;

public:
  // Return movie's details as a string
  string movieDetails() const override;

  // Create a new Drama Movie
  Movie *create() override;

  // Read the classic movie from the scanner with
  // Drama: F, Stock, Director, Title, Year it released
  bool read(istream &is) override;

  // Print out the movie with all informations
  ostream &printer(ostream &os) const override;

  // Help to check if two Drama movie is equal to each others
  bool operator==(const Movie &other) const override;

  // Help to check if this Drama movie is smaller than the other one
  bool operator<(const Movie &other) const override;
};

#endif // DRAMA_H