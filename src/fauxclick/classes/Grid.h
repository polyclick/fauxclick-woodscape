#pragma once
#include "ofMain.h"

class Grid {

protected:
  ofPoint equilateral( ofPoint one, ofPoint two, float rotation );

  // @todo: store all info in one array
  bool hasPulse;
  bool hasTransform;
  float scaleMultiplier;
  float visibleTresh;
  float faceSizes[11][16];
  int faceTimer[11][16];
  int pulseCue[11][16];
  
  // Set unit width
//  const int unitWidth = 101;
  const int unitWidth = 50;
  
  // Set unit height
//  const int unitHeight = 118;
  const int unitHeight = 59;
  
  // Rows and columns are zero-indexed
  const int rows = 10;
  const int cols = 15;
  
  ofImage imgGrid;

public:
  Grid();
  ~Grid();
  
  vector<ofPoint> face( int row, int col , float scaleMultiplier = 1);
  void drawFace(int row, int col, float scaleMultiplier = 1);
  void enablePulse();
  void enableTransform( float scaleMultiplier =1, float visibleTresh=0.25);
  bool faceVisible(int row, int col);
  void pulseFace(int row, int col, int delay = 0);
  void decay();
  

};