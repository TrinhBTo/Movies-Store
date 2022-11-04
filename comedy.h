#ifndef COMEDY_H
#define COMEDY_H

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
 * Comedy class
 */
class Comedy : public Movie {
private:
  friend class MovieStore;
  friend class HashTable;

public:
  // Return movie's details as a string
  string movieDetails() const override;

  // Create a new Comedy Movie
  Movie *create() override;

  // Read the Comedy movie from the scanner with
  // Comedy: F, Stock, Director, Title, Year it released
  bool read(istream &is) override;

  // Print out the movie with all informations
  ostream &printer(ostream &os) const override;

  // Help to check if two Comedy movie is equal to each others
  bool operator==(const Movie &other) const override;

  // Help to check if this Comedy movie is smaller than the other one
  bool operator<(const Movie &other) const override;
};

#endif // COMEDY_H