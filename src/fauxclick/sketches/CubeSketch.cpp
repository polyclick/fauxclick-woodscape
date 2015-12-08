#include "CubeSketch.h"

CubeSketch::CubeSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

CubeSketch::~CubeSketch(){
  // destructor
}

void CubeSketch::setup() {
//  grid.enablePulse();
}

void CubeSketch::update() {

}
void CubeSketch::draw() {

  ofBackground(0);
  ofFill();
  
  for(int i=-1; i<16; i+=2) {
    for(int j=10; j>0 ; j-=3){
      if (j%2 == 0) {
        drawCube(i, i+1, j);
      }else{
        drawCube(i-1, i, j);
      }
    }
  }


  grid.decay();
}

void CubeSketch::drawCube( int colOdd, int colEven, int rowBottom) {
  
  // Dark shade
  ofSetColor(6, 103, 111);
  grid.drawFace(rowBottom, colOdd);
  grid.drawFace(rowBottom - 1, colOdd);
  
  // Mid shade
  ofSetColor(70, 186, 177);
  grid.drawFace(rowBottom, colEven);
  grid.drawFace(rowBottom - 1, colEven);
  
  // Bright shade
  ofSetColor(158, 224, 208);
  grid.drawFace(rowBottom - 2, colOdd);
  grid.drawFace(rowBottom - 2, colEven);
}


const char* CubeSketch::getName() {
  return this->name;
}

void CubeSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}