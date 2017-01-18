/*
 * ex.cpp
 *
 *  Created on: 21/gen/2014
 *      Author: rd
 */

class Rectangle {
    int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}


