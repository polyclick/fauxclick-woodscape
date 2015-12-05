#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class FFTBarSketch : public SketchBase {
  
  private:
    ofxBeat beat;
  
  protected:
    const char* name;
    ofApp* app;
  
  public:
    FFTBarSketch(ofApp* app, const char* name);
    ~FFTBarSketch();

    void setup();
    void update(ofxBeat beat);
    void draw();

    void audioReceived(float* input, int bufferSize, int nChannels);  
  
    const char* getName();
    void logName();
};