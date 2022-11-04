#ifndef MOVIE_FACTORY_H
#define MOVIE_FACTORY_H

#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "movie.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class MovieFactory {
public:
  // constructor
  MovieFactory();

  // destructor
  ~MovieFactory() {
    for (const auto &m : movies) {
      delete m;
    }
  }
  // creates movies by type
  Movie *create(char movieType);

private:
  static const int FACTORY_SIZE = 'Z' - 'A' + 1;
  Movie *movies[FACTORY_SIZE];
  int getBucket(char movieType) const;
};

#endif // MOVIE_FACTORY_H