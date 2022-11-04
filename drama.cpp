#include "drama.h"

string Drama::movieDetails() const {

  string s = type + "  " + title + "  " + to_string(releaseYear);

  return s;
}

// Create a new Drama Movie
Movie *Drama::create() { return new Drama(); }

// Read the classic movie from the scanner with
// Drama: F, Stock, Director, Title, Year it released
bool Drama::read(istream &is) {

  // set the type string
  type = "D";

  // discard the ","
  string c;
  is >> c;

  // read the details
  stock = stoi(trimString(readNextItem(is)));
  ogStock = stock;
  director = readNextItem(is);
  title = readNextItem(is);
  is >> releaseYear;
  return true;
}

// Print out the movie with all informations
ostream &Drama::printer(ostream &os) const {
  os << "Drama: " << type << " "
     << "remaining stock: " << stock << " borrowed stock: " << ogStock - stock
     << ", director: " << director << ", title: " << title
     << ", released year: " << releaseYear;
  return os;
}

// Help to check if two Comedy movie is equal to each others
bool Drama::operator==(const Movie &other) const {

  // cast the movie to the corrected class
  auto m = dynamic_cast<const Drama &>(other);

  bool equal = true;

  // check if the 2 movies has the same details
  if (this->type != m.type || this->stock != m.stock ||
      this->director != m.director || this->title != m.title ||
      this->releaseYear != m.releaseYear) {
    equal = false;
  }

  return equal;
}

// Help to check if this Drama movie is smaller than the other one
bool Drama::operator<(const Movie &other) const {

  // cast the movie to the corrected class
  auto m = dynamic_cast<const Drama &>(other);

  bool check = false;

  // if the director is different
  if (this->director != m.director) {

    // return if this movie's director is smaller than the other one
    check = this->director < m.director;

  } else {

    // if not, return if this movie's title is smaller than the other one
    check = this->title < m.title;
  }

  return check;
}