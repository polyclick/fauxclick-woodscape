#include "fcBarSketch.h"

#include "ofLog.h"

void fcBarSketch::setup(){
  
}

void fcBarSketch::update(){
  
}

void fcBarSketch::draw(){
  ofSetColor(0,255,255);
  float radius = 100;
  ofFill();		// draw "filled shapes"
  ofDrawCircle(100,400,radius);
}

void fcBarSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}

const char* fcBarSketch::name() {
  return "Bar Sketch";
}