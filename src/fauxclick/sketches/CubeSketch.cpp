#include "CubeSketch.h"

CubeSketch::CubeSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

CubeSketch::~CubeSketch(){
  // destructor
}

void CubeSketch::setup() {

  this->stepCounter = 0;
  this->cooldown = 0;

  this->cRight = ofColor(6, 103, 111);
  this->cLeft = ofColor(70, 186, 177);
  this->cTop = ofColor(158, 224, 208);

  this->cDark = ofColor(6, 103, 111);
  this->cMid = ofColor(70, 186, 177);
  this->cBright = ofColor(158, 224, 208);
  
//  this->cDark = ofColor(0, 0, 0);
//  this->cMid = ofColor(180, 180, 180);
//  this->cBright = ofColor(255, 255, 255);
}

void CubeSketch::activate() {

}

void CubeSketch::update() {

}

void CubeSketch::draw() {

  ofBackground(0);
  ofFill();

  for(int i=0; i<17; i+=2) {
    for(int j=10; j>0 ; j-=3){

      int delay = 20 - 1.5*j;

      if (j%2 == 0) {
        if (this->app->audioManager->beatReceived) {
          if(this->cooldown<=0){
            shiftColor();
            this->cooldown = 25;
          }
        }
        drawCube(i, i+1, j);
      }else{
        if (this->app->audioManager->beatReceived) {
          shiftColor();
        }
        drawCube(i-1, i, j);
      }
    }
  }

  this->cooldown-= 1;

}

void CubeSketch::drawCube( int colOdd, int colEven, int rowBottom) {

  // Dark shade
  ofSetColor(this->cRight);
  grid.drawFace(rowBottom, colOdd);
  grid.drawFace(rowBottom - 1, colOdd);

  // Mid shade
  ofSetColor(this->cLeft);
  grid.drawFace(rowBottom, colEven);
  grid.drawFace(rowBottom - 1, colEven);

  // Bright shade
  ofSetColor(this->cTop);
  grid.drawFace(rowBottom - 2, colOdd);
  grid.drawFace(rowBottom - 2, colEven);
}

void CubeSketch::shiftColor(){

  if(this->stepCounter > 1 ){ this->stepCounter = 0; }

  switch (this->stepCounter) {
    case 0:
      this->cTop =this->cBright;
      this->cLeft = this->cMid;
      this->cRight = this->cDark;
      break;

    case 1:
      this->cTop =this->cBright;
      this->cLeft = this->cDark;
      this->cRight = this->cMid;
      break;

//    case 2:
//      this->cTop =this->cBright;
//      this->cLeft = this->cDark;
//      this->cRight = this->cMid;
//      break;
  }

  this->stepCounter++;



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

void CubeSketch::deactivate() {

}

const char* CubeSketch::getName() {
  return this->name;
}

void CubeSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}