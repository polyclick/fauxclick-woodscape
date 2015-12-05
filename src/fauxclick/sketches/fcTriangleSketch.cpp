#include "fcTriangleSketch.h"

const char* fcTriangleSketch::name() {
  return "Triangle Sketch";
}

void fcTriangleSketch::setup() {

}

void fcTriangleSketch::update() {

}

void fcTriangleSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(255);

  for (int i = 0; i < 32; ++i) {
    float selectedBand = beat.getBand(i);
    ofDrawRectangle((ofGetWidth() / 32) * i, 0, ofGetWidth() / 32, ofGetHeight() * selectedBand);
  }
}

void fcTriangleSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}