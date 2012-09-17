#ifndef PERSON_READING_H
#define PERSON_READING_H

struct PersonReading {
  double x;
  double y;
  double height;
  uint64_t id;
  PersonReading(double x, double y, double height) {
    this->x = x;
    this->y = y;
    this->height = height;
    this->id = 0;
  }
  PersonReading(double x, double y, double height, int id) {
    this->x = x;
    this->y = y;
    this->height = height;
    this->id = id;
  }
  PersonReading() {
  }
  bool hasId() { return this->id; }  
};

#endif
