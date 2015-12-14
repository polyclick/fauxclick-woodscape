#include "RandomSketch.h"

RandomSketch::RandomSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

RandomSketch::~RandomSketch(){
  // destructor
}

void RandomSketch::setup() {
  grid.enablePulse();
  grid.enableTransform(0.80);
}

void RandomSketch::activate() {
  midiValue = -1.0;
  this->app->midiManager->midiIn.addListener(this);
}

void RandomSketch::update() {

}
void RandomSketch::draw() {

  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255);

  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {

        if (this->app->audioManager->beatReceived) {
          float chance = ofRandom(1);
          if (chance > 0.66) {
            grid.pulseFace(i,j);
          }
        }
      
          // Draw the face
          ofSetColor(255, 255, 255);
          grid.drawFace(i,j);
      
    }
  }



  grid.decay();
}

void RandomSketch::deactivate() {
  this->app->midiManager->midiIn.removeListener(this);
}

void RandomSketch::newMidiMessage(ofxMidiMessage &msg) {
  if(msg.control == 48 && msg.value != midiValue) {
    midiValue = ofMap(msg.value, 0, 127, 0, 1);
  }
}

const char* RandomSketch::getName() {
  return this->name;
}

void RandomSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}