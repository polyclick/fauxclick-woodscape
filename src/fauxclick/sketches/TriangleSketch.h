#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class TriangleSketch : public SketchBase {

  protected:
    void drawSegment( int row, int col );
    ofPoint equilateral( ofPoint one, ofPoint two, float rotation );

    const char* name;
    ofApp* app;
  
    // Set unit width
    const int unitWidth = 101;
  
    // Set unit height
    const int unitHeight = 118;
  
    // Rows and columns are zero-indexed
    const int rows = 10;
    const int cols = 15;
  
    ofImage imgGrid;

  public:
    TriangleSketch(ofApp* app, const char* name);
    ~TriangleSketch();
  
    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);
  
    const char* getName();
    void logName();
};