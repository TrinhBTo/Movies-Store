#ifndef CLASSIC_H
#define CLASSIC_H

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
 * Classic class
 */
class Classic : public Movie {
private:
  friend class MovieStore;
  friend class HashTable;

public:
  // Return movie's details as a string
  string movieDetails() const override;

  // Print out the movie with all informations
  ostream &printer(ostream &os) const override;

  // Read the classic movie from the scanner with
  // Classic are: C, Stock, Director, Title, Major actor ReleaseMonth
  // ReleasedYear
  bool read(istream &is) override;

  // Create a new Classic Movie
  Movie *create() override;

  // Help to check if two Classic movie is equal to each others
  bool operator==(const Movie &other) const override;

  // Help to check if this Classic movie is smaller than the other one
  bool operator<(const Movie &other) const override;
};

#endif // CLASSIC_H