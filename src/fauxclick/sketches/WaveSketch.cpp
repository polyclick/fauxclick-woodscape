#include "WaveSketch.h"

WaveSketch::WaveSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

WaveSketch::~WaveSketch(){
  // destructor
}

void WaveSketch::setup() {
  grid.enablePulse();
  grid.enableTransform(0.91);
}

void WaveSketch::update() {

}
void WaveSketch::draw() {

  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255);


  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {
      
        if (i % 2 == 0) {
          if (this->app->audioManager->beatReceived) {
            grid.pulseFace(i,j,j*1.5);
          }
          
//             Draw the face
            ofSetColor(255, 255, 255);
            grid.drawFace(i,j);

            // layer
            ofSetColor(0, 0, 0);
            grid.drawFace(i,j, 0.66);

            ofSetColor(255, 255, 255);
            grid.drawFace(i,j, 0.33);

        }

        if (i % 3 == 0) {
          if (this->app->audioManager->beatReceived) {
            grid.pulseFace(i,j,25 - (j*1.5));
          }

            // Draw the face
            ofSetColor(255, 255, 255);
            grid.drawFace(i,j);

            ofSetColor(0, 0, 0);
            grid.drawFace(i,j, 0.66);

            ofSetColor(255, 255, 255);
            grid.drawFace(i,j, 0.33);

        }

    }
  }



  grid.decay();
}

const char* WaveSketch::getName() {
  return this->name;
}

void WaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}