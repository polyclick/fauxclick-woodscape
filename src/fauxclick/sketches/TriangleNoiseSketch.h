#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class TriangleNoiseSketch : public SketchBase {

  protected:
    const char* name;
    ofApp* app;
  
  public:
    TriangleNoiseSketch(ofApp* app, const char* name);
    ~TriangleNoiseSketch();
  
    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);

    const char* getName();
    void logName();
};