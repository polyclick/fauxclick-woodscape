#include "BoidSketch.h"

BoidSketch::BoidSketch(ofApp* app, const char* name){
  this->name = name;
  this->app = app;
  this->bandValue = 0;
}

BoidSketch::~BoidSketch(){
  // destructor
}

void BoidSketch::setup() {
  for(int i=0; i<199 ; i++){
    this->particles.push_back( new Particle(ofRandom(1,1.5), ofRandom(10,500)));
    this->particleBands.push_back((int)ofRandom(0,32));
  }
}

void BoidSketch::update() {
  
}
void BoidSketch::draw() {
  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255);
  
  
  
    for(int i=0; i<199 ; i++){
      int bandIndex =this->particleBands[i];
      this->bandValue = this->app->audioManager->bands.energies[bandIndex];

      Particle* particle = this->particles[i];
      
      particle->energy = this->bandValue;
      particle->draw();
      particle->move();
    }
}

const char* BoidSketch::getName() {
  return this->name;
}

void BoidSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}