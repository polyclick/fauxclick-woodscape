#pragma once

#include "ofApp.h"
#include "SketchBase.h"

class TrippyLinesSketch : public SketchBase {

  protected:
    const char* name;
    ofApp* app;

  public:
    TrippyLinesSketch(ofApp* app, const char* name);
    ~TrippyLinesSketch();

    void setup();
    void update();
    void draw();

    const char* getName();
    void logName();
};