#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class SoundwaveSketch : public SketchBase {
  
  protected:
    const char* name;
    ofApp* app;
  
  public:
    SoundwaveSketch(ofApp* app, const char* name);
    ~SoundwaveSketch();
  
    void setup();
    void update();
    void draw(ofxBeat beat, ofxMidiMessage midi);

    const char* getName();
    void logName();
};