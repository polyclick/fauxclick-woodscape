#include "Grid.h"

Grid::Grid(){

}

Grid::~Grid(){
  // destructor@
}

vector<ofPoint> Grid::points(){

}

vector<ofPoint> Grid::face(int row, int col){

}

//ofPoint Grid::equilateral( ofPoint one, ofPoint two, float rotation ){
//  /**
//   * given two points of an equilateral triangle, return the third point.
//   */
//  
//  ofPoint three = ofPoint();
//  
//  // find offset from point 1 to 2
//  float dX = two.x - one.x;
//  float dY = two.y - one.y;
//  
//  // rotate and add to point 1 to find point 3
//  three.x = (cos(rotation) * dX - sin(rotation) * dY) + one.x;
//  three.y = (sin(rotation) * dX + cos(rotation) * dY) + one.y;
//  
//  return three;
//
//}