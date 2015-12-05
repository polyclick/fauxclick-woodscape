#include "FFTBarSketch.h"

FFTBarSketch::FFTBarSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

FFTBarSketch::~FFTBarSketch(){
  // destructor
}

void FFTBarSketch::setup(){

}

void FFTBarSketch::update(){

}

void FFTBarSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(255, 255, 255);
  for (int i = 0; i < 32; ++i) {
    float selectedBand = beat.getBand(i);
    ofDrawRectangle((ofGetWidth() / 32) * i, 0, ofGetWidth() / 32, ofGetHeight() * selectedBand);
  }
}

const char* FFTBarSketch::getName() {
  return this->name;
}

void FFTBarSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name);
}