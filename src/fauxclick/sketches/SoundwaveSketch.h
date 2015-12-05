#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class SoundwaveSketch : public SketchBase {
  
  private:
    vector <float> audio;
    float yPosition = 0;
  
  protected:
    const char* name;
    ofApp* app;
  
  public:
    SoundwaveSketch(ofApp* app, const char* name);
    ~SoundwaveSketch();
  
    void setup();
    void update(ofxBeat beat);
    void draw();

    void audioReceived(float* input, int bufferSize, int nChannels);  
  
    const char* getName();
    void logName();
};