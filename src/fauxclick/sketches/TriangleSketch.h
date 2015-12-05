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
    void update(ofxBeat beat);
    void draw();
  
    void audioReceived(float* input, int bufferSize, int nChannels);

    const char* getName();
    void logName();
};