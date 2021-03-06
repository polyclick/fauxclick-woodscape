#include "PulseSketch.h"

PulseSketch::PulseSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

PulseSketch::~PulseSketch(){
  // destructor
}

void PulseSketch::setup() {
  grid.enablePulse();
  grid.enableTransform(0.75);
}

void PulseSketch::activate() {
  midiValue = -1.0;
  this->app->midiManager->midiIn.addListener(this);
}

void PulseSketch::update() {

}
void PulseSketch::draw() {

  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255);

  int midicols = midiValue < 0.0 ? 1 : (int)ofMap(midiValue, 0.0, 1.0, 5.0, 1.0);

  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {

      if (j % midicols == 0) {
        if (this->app->audioManager->beatReceived) {
          grid.pulseFace(i,j);
        }

        //             Draw the face
        ofSetColor(255, 255, 255);
        grid.drawFace(i,j);

        // layer
//        ofSetColor(0, 0, 0);
//        grid.drawFace(i,j, 0.66);
//
//        ofSetColor(255, 255, 255);
//        grid.drawFace(i,j, 0.33);

      }

      //        if (i % 3 == 0) {
      //          if (this->app->audioManager->beatReceived) {
      //            grid.pulseFace(i,j);
      //          }
      //
      //            // Draw the face
      //            ofSetColor(255, 255, 255);
      //            grid.drawFace(i,j);
      //
      //            ofSetColor(0, 0, 0);
      //            grid.drawFace(i,j, 0.66);
      //
      //            ofSetColor(255, 255, 255);
      //            grid.drawFace(i,j, 0.33);
      //
      //        }

    }
  }



  grid.decay();
}

void PulseSketch::deactivate() {
  this->app->midiManager->midiIn.removeListener(this);
}

void PulseSketch::newMidiMessage(ofxMidiMessage &msg) {
//  if(msg.control == 29 && msg.value != midiValue) {
//    midiValue = ofMap(msg.value, 0, 127, 0, 1);
//  }
}

const char* PulseSketch::getName() {
  return this->name;
}

void PulseSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}