#include "TriangleSketch.h"

TriangleSketch::TriangleSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

TriangleSketch::~TriangleSketch(){
  // destructor
}

void TriangleSketch::setup() {
  imgGrid.load("images/grid.png");
  
}

void TriangleSketch::update() {

}

void TriangleSketch::draw() {
  
  imgGrid.draw(0,0);
  ofNoFill();
  ofSetColor(255,0,0, 100);
  
  // Draw the whole thing
  for (int i = 0; i < rows + 1; ++i) {
    for (int j = 0; j < cols + 1; ++j) {
      drawSegment(i,j);
    }
  }
  
}

void TriangleSketch::drawSegment( int row, int col ){
  
  ofPoint a = ofPoint();
  ofPoint b = ofPoint();
  ofPoint c;
  float rotation;
  
  a.y = (row * unitHeight) / 2;
  b.y = a.y + unitHeight;
  
  if (col % 2 == 0 ) {
    if (row % 2 == 0) {
      a.x = col * unitWidth;
      b.x = col * unitWidth;
      rotation = -60;
    } else{
      a.x = col * unitWidth + unitWidth;
      b.x = a.x;
      rotation = 60;
    }
  }else{
    if (row % 2 == 0) {
      a.x = col * unitWidth + unitWidth;
      b.x = a.x;
      rotation = 60;
    } else{
      a.x = col * unitWidth;
      b.x = col * unitWidth;
      rotation = -60;
    }
  }
  
  
  // offset
  a.x += 17;
  b.x += 17;
  c.x += 17;
  
  a.y+= 8;
  b.y+= 8;
  c.y+= 8;
  
  rotation = ofDegToRad( rotation );
  
  c = equilateral( a, b, rotation );
  
  ofDrawTriangle(a.x, a.y, b.x, b.y, c.x, c.y);

}

ofPoint TriangleSketch::equilateral( ofPoint one, ofPoint two, float rotation ){
  /**
   * given two points of an equilateral triangle, return the third point.
   */
  
  ofPoint three = ofPoint();
  
  // find offset from point 1 to 2
  float dX = two.x - one.x;
  float dY = two.y - one.y;
  
  // rotate and add to point 1 to find point 3
  three.x = (cos(rotation) * dX - sin(rotation) * dY) + one.x;
  three.y = (sin(rotation) * dX + cos(rotation) * dY) + one.y;
  
  return three;

}

const char* TriangleSketch::getName() {
  return this->name;
}

void TriangleSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}