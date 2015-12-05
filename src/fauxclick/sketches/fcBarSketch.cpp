#include "fcBarSketch.h"

const char* fcBarSketch::name() {
  return "Bar Sketch";
}

void fcBarSketch::setup(){

}

void fcBarSketch::update(){

}

void fcBarSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(255);

  for (int i = 0; i < 32; ++i) {
    float selectedBand = beat.getBand(i);
    ofDrawRectangle((ofGetWidth() / 32) * i, 0, ofGetWidth() / 32, ofGetHeight() * selectedBand);
  }
}

void fcBarSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}