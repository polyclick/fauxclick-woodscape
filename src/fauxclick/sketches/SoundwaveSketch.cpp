#include "SoundwaveSketch.h"

const char* SoundwaveSketch::name() {
  return "Bar Sketch";
}

void SoundwaveSketch::setup(){

}

void SoundwaveSketch::update(){

}

void SoundwaveSketch::draw(ofxBeat beat, ofxMidiMessage midi) {
//  ofPushStyle();
//		ofPushMatrix();
//		ofTranslate(32, 170, 0);
//  
//		ofSetColor(225);
//		ofDrawBitmapString("Left Channel", 4, 18);
//		
//		ofSetLineWidth(1);
//		ofDrawRectangle(0, 0, 512, 200);
//  
//		ofSetColor(245, 58, 135);
//		ofSetLineWidth(3);
//  
//  ofBeginShape();
//  for (unsigned int i = 0; i < left.size(); i++){
//				ofVertex(i*2, 100 -left[i]*180.0f);
//  }
//  ofEndShape(false);
//  
//		ofPopMatrix();
//  ofPopStyle();
}

void SoundwaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, this->name());
}