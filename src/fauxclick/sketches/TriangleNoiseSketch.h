#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class TriangleNoiseSketch : public SketchBase {
  private:
    ofxBeat beat;

  protected:
    const char* name;
    ofApp* app;
  
  public:
    TriangleNoiseSketch(ofApp* app, const char* name);
    ~TriangleNoiseSketch();
  
    void setup();
    void update(ofxBeat beat);
    void draw();

    void audioReceived(float* input, int bufferSize, int nChannels);
  
    const char* getName();
    void logName();
};