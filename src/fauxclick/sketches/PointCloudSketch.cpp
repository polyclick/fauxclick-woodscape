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
  float width = ofGetWidth() / 3.0;
  float height = ofGetHeight();
  
  ofFill();
  ofSetColor(255, 255, 255);
  
  if(this->app->audioManager->beat.isKick()) {
    ofDrawRectangle(0, 0, width, height);
    ofDrawRectangle(width * 2.0, 0, width, height);
  }
  
  if(this->app->audioManager->beat.isHat()) {
    ofDrawRectangle(width, 0, width, height);
  }
}

const char* PointCloudSketch::getName() {
  return this->name;
}

void PointCloudSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}