#include "VolumeHistorySketch.h"

#include "ofApp.h"

VolumeHistorySketch::VolumeHistorySketch(ofApp* app, const char* name) {
  this->app = app;
  this->name = name;
}

VolumeHistorySketch::~VolumeHistorySketch(){
  // destructor
}

void VolumeHistorySketch::setup(){
  
  // vector to keep the volume changes
  volumeHistory.assign(volumeHistorySize, 0.0);
}

void VolumeHistorySketch::update(){
  
  float average =
    this->app->audioManager->beat.getBand(0) +
    this->app->audioManager->beat.getBand(1) +
    this->app->audioManager->beat.getBand(2) +
    this->app->audioManager->beat.getBand(3) +
    this->app->audioManager->beat.getBand(4);
  
  average /= 5.0;
  
  // lets record the volume into an array
  volumeHistory.push_back(average);
  cout << this->app->audioManager->beat.getMagnitude() << endl;
  // if we are bigger the the size we want to record - lets drop the oldest value
  if(volumeHistory.size() >= volumeHistorySize){
    volumeHistory.erase(volumeHistory.begin(), volumeHistory.begin() + 1);
  }
}

void VolumeHistorySketch::draw() {
  // draw the average volume:
  ofPushStyle();
  ofPushMatrix();

  int height = ofGetHeight();
  
  // scaling in width of screen
  float widthRatio = (float)ofGetWidth() / (float)volumeHistory.size();
  
  ofTranslate(0.0, 0, 0);
		
		//lets draw the volume history as a graph
		ofBeginShape();
		for (unsigned int i = 0; i < volumeHistory.size(); i++){
      if( i == 0 ) ofVertex(0, height);
      
      float volume = volumeHistory[i] * ofGetHeight() / 2.0;
      ofVertex(i * widthRatio, height - volume);
      
      if(i == volumeHistory.size() - 1) ofVertex(i * widthRatio, height);
    }
		ofEndShape(false);
  
		ofPopMatrix();
  ofPopStyle();
}

const char* VolumeHistorySketch::getName() {
  return this->name;
}

void VolumeHistorySketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}