#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "Grid.h"

class CubeSketch : public SketchBase {

  protected:

    void drawCube(int colOdd, int colEven, int rowBottom);
    void shiftColor();
    void pulseCube(int colOdd, int colEven, int rowBottom, int delay=0);

    int stepCounter;
    int cooldown;
  
    ofColor cDark;
    ofColor cMid;
    ofColor cBright;
  
    ofColor cLeft;
    ofColor cRight;
    ofColor cTop;
  
    const char* name;
    ofApp* app;
    Grid grid;

    // Set unit width
    const int unitWidth = 101;
 
    // Set unit height
    const int unitHeight = 118;

    // Rows and columns are zero-indexed
    const int rows = 10;
    const int cols = 15;

  public:
   CubeSketch(ofApp* app, const char* name);
    ~CubeSketch();

    void setup();
    void update();
    void draw();

    const char* getName();
    void logName();
};