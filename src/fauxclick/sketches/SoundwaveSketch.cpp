#include "PointCloudSketch.h"

PointCloudSketch::PointCloudSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

PointCloudSketch::~PointCloudSketch(){
  // destructor
}

void PointCloudSketch::setup(){

}

void PointCloudSketch::update(){
  
}

void PointCloudSketch::draw() {

}

const char* PointCloudSketch::getName() {
  return this->name;
}

void PointCloudSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}