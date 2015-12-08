#include "WaveSketch.h"

WaveSketch::WaveSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

WaveSketch::~WaveSketch(){
  // destructor
}

void WaveSketch::setup() {
}

void WaveSketch::update() {

}
void WaveSketch::draw() {

//  imgGrid.draw(0,0);
  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255);


  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {

        if (i % 2 == 0) {
          if (this->app->audioManager->beatReceived) {
            grid.pulseFace(i,j,j*1.5);
          }

          if(grid.faceVisible(i,j)){
            // Draw the face
            ofSetColor(255, 255, 255);
            drawFace( grid.face(i,j));

            // layer
            ofSetColor(0, 0, 0);
            drawFace( grid.face(i,j, 0.66));

            ofSetColor(255, 255, 255);
            drawFace( grid.face(i,j, 0.33));
          }

        }

        if (i % 3 == 0) {
          if (this->app->audioManager->beatReceived) {
            grid.pulseFace(i,j,25 - (j*1.5));
          }

          if(grid.faceVisible(i,j)){
            // Draw the face
            ofSetColor(255, 255, 255);
            drawFace( grid.face(i,j));

            ofSetColor(0, 0, 0);
            drawFace( grid.face(i,j, 0.66));

            ofSetColor(255, 255, 255);
            drawFace( grid.face(i,j, 0.33));
          }
        }

    }
  }



  grid.decay();
}

void WaveSketch::drawFace( vector<ofPoint> vertices) {
  // @todo: if this'd draw a face with x amount of points, that'd be great
  ofDrawTriangle( vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y );
}

const char* WaveSketch::getName() {
  return this->name;
}

void WaveSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}