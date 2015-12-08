#pragma once
#include "ofMain.h"

class Grid {

protected:
  ofPoint equilateral( ofPoint one, ofPoint two, float rotation );

  // @todo: store all info in one array
  bool hasPulse;
  float faceSizes[11][16];
  int faceTimer[11][16];
  int pulseCue[11][16];
  
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
  
  void enablePulse();
  bool faceVisible(int row, int col);
  void pulseFace(int row, int col, int delay = 0);
  void decay();
  vector<ofPoint> face( int row, int col , float scaleMultiplier = 1);

};