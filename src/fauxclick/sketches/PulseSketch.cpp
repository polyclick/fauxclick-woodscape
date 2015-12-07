#include "PulseSketch.h"

PulseSketch::PulseSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

PulseSketch::~PulseSketch(){
  // destructor
}

void PulseSketch::setup() {
  imgGrid.load("images/grid.png");
  
  // Set inital scale values
  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {
      this->faceSizes[i][j] = 0.1;
    }
  }
}

void PulseSketch::update() {

}
void PulseSketch::draw() {
  
//  imgGrid.draw(0,0);
  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255);
  
//  one face
//  vector<ofPoint> face = grid.face(3,3);
  
  // @todo: move to grid class?
//  one face
//  drawFace( face );
  
  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {
      
      float intensity;
      
      if (i % 2 == 0) {
        if (this->app->audioManager->beat.isKick()) {
          this->faceSizes[i][j] = 1;
        }
        
        // Draw the face
        ofSetColor(255, 255, 255);
        drawFace( grid.face(i,j, this->faceSizes[i][j]));
        ofSetColor(0, 0, 0);
        drawFace( grid.face(i,j, this->faceSizes[i][j] * 0.5));
        ofSetColor(255, 255, 255);
        drawFace( grid.face(i,j, this->faceSizes[i][j] * 0.25));
      }
      
      if (!(i % 2 == 0)) {
        if (this->app->audioManager->beat.isHat()) {
          this->faceSizes[i][j] = 1;
        }
        
        ofSetColor(255, 255, 255);
        drawFace( grid.face(i,j, this->faceSizes[i][j] * 0.85));
        ofSetColor(0, 0, 0);
        drawFace( grid.face(i,j, this->faceSizes[i][j] * 0.5));
      }
    }
  }
  
  
  // reduce the size each frame
  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {
      if (this->faceSizes[i][j] > 0.3) { //minimum size
        this->faceSizes[i][j] *= 0.94;
      }
    }
  }
  
}

void PulseSketch::drawFace( vector<ofPoint> vertices) {
  // @todo: if this'd draw a face with x amount of points, that'd be great
  ofDrawTriangle( vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y );
}

const char* PulseSketch::getName() {
  return this->name;
}

void PulseSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}