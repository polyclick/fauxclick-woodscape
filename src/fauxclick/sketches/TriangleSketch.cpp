#include "TriangleSketch.h"

const char* TriangleSketch::name() {
  return "Triangle Sketch";
}

void TriangleSketch::setup() {

}

void TriangleSketch::update() {

}

void TriangleSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(0,255,255);
  float radius = 100;
  ofFill();   // draw "filled shapes"
  ofDrawCircle(100,400,radius);
}

void TriangleSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}