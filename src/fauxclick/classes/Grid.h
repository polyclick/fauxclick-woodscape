#pragma once
#include "ofMain.h"

class Grid {

protected:

//    ofPoint equilateral( ofPoint one, ofPoint two, float rotation );
  
//  vector<ofPoint> points();
  ofPoint equilateral( ofPoint one, ofPoint two, float rotation );

  // Set unit width
  const int unitWidth = 101;
  
  // Set unit height
  const int unitHeight = 118;
  
  // Rows and columns are zero-indexed
  const int rows = 10;
  const int cols = 15;
  
  ofImage imgGrid;

public:
  Grid();
  ~Grid();
  
  vector<ofPoint> face( int row, int col );

};