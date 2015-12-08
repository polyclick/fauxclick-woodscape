#include "CubeSketch.h"

CubeSketch::CubeSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

CubeSketch::~CubeSketch(){
  // destructor
}

void CubeSketch::setup() {
  grid.enablePulse();
  grid.enableTransform(0.9, 0.9);
}

void CubeSketch::update() {

}
void CubeSketch::draw() {

  ofBackground(0);
  ofFill();
  
  for(int i=-1; i<14; i+=2) {
    for(int j=10; j>0 ; j-=3){
      
      int delay = 1.5*j;

      if (j%2 == 0) {
        if (this->app->audioManager->beatReceived) {
          pulseCube(i, i+1, j, delay);
        }
        drawCube(i, i+1, j);
      }else{
        if (this->app->audioManager->beatReceived) {
          pulseCube(i-1, i, j, delay);
        }
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

void CubeSketch::pulseCube( int colOdd, int colEven, int rowBottom, int delay) {
  
  // Dark shade
  grid.pulseFace(rowBottom, colOdd, delay);
  grid.pulseFace(rowBottom - 1, colOdd, delay);
  
  // Mid shade
  grid.pulseFace(rowBottom, colEven, delay);
  grid.pulseFace(rowBottom - 1, colEven, delay);
  
  // Bright shade
  grid.pulseFace(rowBottom - 2, colOdd, delay);
  grid.pulseFace(rowBottom - 2, colEven, delay);
}


const char* CubeSketch::getName() {
  return this->name;
}

void CubeSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}