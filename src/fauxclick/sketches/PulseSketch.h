#pragma once

#include "ofApp.h"
#include "SketchBase.h"
#include "Grid.h"

class PulseSketch : public SketchBase {

  protected:

    void drawFace( vector<ofPoint> vertices );

    float faceSizes[11][16];
//    float faceSizes[11][16];

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

    ofImage imgGrid;

  public:
   PulseSketch(ofApp* app, const char* name);
    ~PulseSketch();

    void setup();
    void update();
    void draw();

    const char* getName();
    void logName();
};