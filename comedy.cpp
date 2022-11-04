#include "comedy.h"

string Comedy::movieDetails() const {

  string s = type + " " + title + "  " + to_string(releaseYear);

  return s;
}

// Create a new Comedy Movie
Movie *Comedy::create() { return new Comedy(); }

// Read the classic movie from the scanner with
// Comedy: F, Stock, Director, Title, Year it released
bool Comedy::read(istream &is) {
  // set the type string
  type = "F";

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
ostream &Comedy::printer(ostream &os) const {
  os << "Comedy: " << type << " "
     << "remaining stock: " << stock << " borrowed stock: " << ogStock - stock
     << ", director: " << director << ", title: " << title
     << ", released year: " << releaseYear;
  return os;
}

// Help to check if two Comedy movie is equal to each others
bool Comedy::operator==(const Movie &other) const {

  // cast the movie to the corrected class
  auto m = dynamic_cast<const Comedy &>(other);

  bool equal = true;

  // check if the 2 movies has the same details
  if (this->type != m.type || this->stock != m.stock ||
      this->director != m.director || this->title != m.title ||
      this->releaseYear != m.releaseYear) {
    equal = false;
  }

  return equal;
}

// Help to check if this Comedy movie is smaller than the other one
bool Comedy::operator<(const Movie &other) const {

  // cast the movie to the corrected class
  auto m = dynamic_cast<const Comedy &>(other);

  bool check = false;

  // if the title is different
  if (this->title != m.title) {

    // return if this movie's title is smaller than the other one
    check = this->title < m.title;

  } else {

    // if not, return if this movie's released year is smaller than the other
    // one
    check = this->releaseYear < m.releaseYear;
  }
  return check;
}