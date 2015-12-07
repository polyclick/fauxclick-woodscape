#include "Grid.h"

Grid::Grid(){
  // Set inital face values
  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {
      this->faceSizes[i][j] = 0.1;
      this->faceCooldowns[i][j] = 0;
      this->faceTimer[i][j] = 0;
      this->pulseCue[i][j] = 0;
    }
  }
}

Grid::~Grid(){
  // destructor@
}

// @todo: postponed
//vector<ofPoint> Grid::points(){
//  /**
//   * Return the vertices that make up the grid
//   */
//}

void Grid::pulseFace(int row, int col, int delay){
  /**
   * Cue a pulse, don't actually execute it.
   */
  if(this->faceCooldowns[row][col] <= 0){
    this->pulseCue[row][col] = 1;
    this->faceTimer[row][col] = delay;
    
    // Set beat cooldown in frames
    this->faceCooldowns[row][col] = 25;
  }
};

void Grid::decay(){
  for (int i = 0; i < rows+1 ; i++) {
    for (int j = 0; j < cols+1; j++) {
      // decay size
      if (this->faceSizes[i][j] > 0.3) { //minimum size
        this->faceSizes[i][j] *= 0.95;
      }
      
      // decay cooldown
      this->faceCooldowns[i][j] = this->faceCooldowns[i][j] - 1;
      
      // decay pulse timers
      this->faceTimer[i][j] -= 1;
      
      // do the actual pulse
      // @todo: this shouldn't be here...
      if (this->pulseCue[i][j] == 1 && this->faceTimer[i][j] <= 0) {
        this->faceSizes[i][j] = 1;
        this->pulseCue[i][j]= 0;
      }
    }
  }
}

vector<ofPoint> Grid::face(int row, int col ){
  /**
   * Return three vertices that make up the given grid segment
   * defined by row and column
   */
  
  // The value that will be returned
  vector<ofPoint> v;
  v.reserve(3);
  
  // Define three vertices & a center point
  ofPoint a = ofPoint();
  ofPoint b = ofPoint();
  ofPoint c = ofPoint();
  ofPoint p = ofPoint();
  
  
  
  // The rotation in radians, used to determine the third coördinate
  float rotation;
  
  // The Y-coördinates are known by having defined the grid width
  a.y = (row * unitHeight) / 2;
  b.y = a.y + unitHeight;
  
  // Determine the X-coördinates
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
  
  // Offset the grid ( to match the blueprint )
  a.x += 17;
  b.x += 17;
  c.x += 17;
  
  a.y+= 8;
  b.y+= 8;
  c.y+= 8;
  
  // Rotation required to find the third point
  rotation = ofDegToRad( rotation );
  
  c = equilateral( a, b, rotation );
  
  
  // Calculate the center point p using the incircle
  p.x = (a.x + b.x + c.x) / 3;
  p.y = (a.y + b.y + c.y) / 3;
  
  /**
   * To apply a relative scale, translate the triangle so that center point P 
   * equals the origin. Then scale and translate back to the original position
   */
  
  // Translate to origin
  a.x -= p.x;
  b.x -= p.x;
  c.x -= p.x;
  
  a.y -= p.y;
  b.y -= p.y;
  c.y -= p.y;
  
  // Scale
  a *= this->faceSizes[row][col];
  b *= this->faceSizes[row][col];
  c *= this->faceSizes[row][col];
  
  // Translate back to original position
  a.x += p.x;
  b.x += p.x;
  c.x += p.x;
  
  a.y += p.y;
  b.y += p.y;
  c.y += p.y;
  
  // Return vertices
  v.push_back(a);
  v.push_back(b);
  v.push_back(c);
  
  return v;
  
}

ofPoint Grid::equilateral( ofPoint one, ofPoint two, float rotation ){
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


