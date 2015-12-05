#include "fcBarSketch.h"

const char* fcBarSketch::name() {
  return "Bar Sketch";
}

void fcBarSketch::setup(){

}

void fcBarSketch::update(){

}

void fcBarSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
  ofSetColor(0,255,255);
  float radius = 100;
  ofFill();		// draw "filled shapes"
  ofDrawCircle(100,400,radius);
}

void fcBarSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}