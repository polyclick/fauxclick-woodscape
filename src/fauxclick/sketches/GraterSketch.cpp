#include "GraterSketch.h"

GraterSketch::GraterSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

GraterSketch::~GraterSketch(){
  // destructor
}

void GraterSketch::setup() {

  
  mesh = grid.pointMesh();
  mesh.setMode(OF_PRIMITIVE_LINES);
  
  float connectionDistance = 200;
  int numVerts = mesh.getNumVertices();
  
  for (int a=0; a<numVerts; ++a) {
    ofVec3f verta = mesh.getVertex(a);
    for (int b=a+1; b<numVerts; ++b) {
      ofVec3f vertb = mesh.getVertex(b);
      float distance = verta.distance(vertb);
      if (distance <= connectionDistance) {
        mesh.addIndex(a);
        mesh.addIndex(b);
      }
    }
  }
  
  cout << mesh.getNumVertices() << endl;

}

void GraterSketch::activate() {
}

void GraterSketch::update() {

}
void GraterSketch::draw() {
  
  ofBackground(0,0,0);
  mesh.draw();
}

void GraterSketch::deactivate() {
 
}

void GraterSketch::newMidiMessage(ofxMidiMessage &msg) {
  if(msg.control == 29 && msg.value != midiValue) {
    midiValue = ofMap(msg.value, 0, 127, 0, 1);
  }
}

const char* GraterSketch::getName() {
  return this->name;
}

void GraterSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}