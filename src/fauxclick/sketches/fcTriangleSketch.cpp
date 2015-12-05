#include "fcTriangleSketch.h"

const char* fcTriangleSketch::name() {
  return "Triangle Sketch";
}

void fcTriangleSketch::setup() {

}

void fcTriangleSketch::update() {

}

void fcTriangleSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(0,255,255);
  float radius = 100;
  ofFill();   // draw "filled shapes"
  ofDrawCircle(100,400,radius);
}

void fcTriangleSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}