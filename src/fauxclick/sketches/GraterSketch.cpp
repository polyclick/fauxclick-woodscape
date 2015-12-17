#include "GraterSketch.h"

GraterSketch::GraterSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
}

GraterSketch::~GraterSketch(){
  // destructor
}

void GraterSketch::setup() {

  multiplier = 1;
  enabled = true; //@todo: map to midi knob
  
  // Set center point
  center.set(ofGetWidth()/2, ofGetHeight()/2, 0);
  
  mesh = grid.pointMesh();
  mesh.setMode( OF_PRIMITIVE_LINES);
//  mesh.setMode( OF_PRIMITIVE_POINTS);

  
  meshCopy = mesh;
  meshCopy.setMode(OF_PRIMITIVE_LINES);
  
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
  
  meshCopy = mesh;
  meshCopy.setMode(OF_PRIMITIVE_LINES);
  
  cout << mesh.getNumVertices() << endl;

}

void GraterSketch::activate() {
}

void GraterSketch::update() {

}
void GraterSketch::draw() {
  
  // Barrel distortion
  if (this->app->audioManager->beatReceived) {
    multiplier = 2;
  }else{
    multiplier*= 0.85; //@todo: Map to midi twist knob
  }
  
  
  if (enabled){
    // Loop through all the vertices in the mesh and move them away from the mouses
    for (int i=0; i<mesh.getNumVertices(); ++i) {
      ofVec3f vertex = meshCopy.getVertex(i);
      float distanceToCenter = center.distance(vertex);
      
      
      // Small distance to mouse should yield a small displacement
      float displacement = ofMap(distanceToCenter, 0, 600, 300.0, 0, true);
      
      displacement *= multiplier;
      
      // Calculate the direction from the mouse to the current vertex
      ofVec3f direction = vertex - center;
      
      // Normalize the direction so that it has a length of one
      // This lets us easily change the length of the vector later
      direction.normalize();
      
      // Push the vertex in the direction away from the mouse and push it
      // a distance equal to the value of the variable displacement
      
      ofVec3f displacedVertex = vertex + displacement*direction;
      mesh.setVertex(i, displacedVertex);
    }
  }
  
  
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