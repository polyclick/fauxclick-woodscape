#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class FFTBarSketch : public SketchBase {
  
  protected:
    const char* name;
    ofApp* app;
  
  public:
    FFTBarSketch(ofApp* app, const char* name);
    ~FFTBarSketch();

    void setup();
    void update();
    void draw();
  
    const char* getName();
    void logName();
};