#include "MovieFactory.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// constructor
// initializes movie buckets
MovieFactory::MovieFactory() {

  // initialize the movies
  for (auto &m : movies) {
    m = nullptr;
  }

  movies[getBucket('C')] = new Classic();
  movies[getBucket('D')] = new Drama();
  movies[getBucket('F')] = new Comedy();
}

// makes sure the movies are in their correct buckets when created
Movie *MovieFactory::create(char movieType) {
  if (movies[getBucket(movieType)] != nullptr) {
    return movies[getBucket(movieType)]->create();
  }
  return nullptr;
}

int MovieFactory::getBucket(char movieType) const {
  // cout<<movieType;
  assert(movieType >= 'A' && movieType <= 'Z');
  return movieType - 'A';
}