#include "fcBarSketch.h"

#include "ofLog.h"

void fcBarSketch::setup(){

}

void fcBarSketch::update(){

}

void fcBarSketch::draw(){

}

void fcBarSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}

const char* fcBarSketch::name() {
  return "Bar Sketch";
}