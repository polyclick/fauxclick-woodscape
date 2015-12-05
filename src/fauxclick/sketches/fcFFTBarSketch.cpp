#include "fcFFTBarSketch.h"

const char* fcFFTBarSketch::name() {
  return "Bar Sketch";
}

void fcFFTBarSketch::setup(){

}

void fcFFTBarSketch::update(){

}

void fcFFTBarSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(255, 255, 255);
  for (int i = 0; i < 32; ++i) {
    float selectedBand = beat.getBand(i);
    ofDrawRectangle((ofGetWidth() / 32) * i, 0, ofGetWidth() / 32, ofGetHeight() * selectedBand);
  }
}

void fcFFTBarSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}