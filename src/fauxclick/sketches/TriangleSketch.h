#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class TriangleSketch : public SketchBase {

  protected:
    const char* name;
    ofApp* app;
  
  public:
    TriangleSketch(ofApp* app, const char* name);
    ~TriangleSketch();
  
    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);

    const char* getName();
    void logName();
};