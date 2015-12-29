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
  this->numParticles = 200;
  this->numLines = 15;
  this->treshold = 50;

  for(int i=0; i<numParticles ; i++){
    this->particles.push_back( new Particle(ofRandom(1,1.5), ofRandom(10,500)));
    this->particleBands.push_back((int)ofRandom(0, 8));
  }



//  for(int j=0 ; j<numLines ; j++){
//    this->lineFrom.push_back((int)ofRandom(1,numParticles));
//    this->lineTo.push_back((int)ofRandom(1,numParticles));
//  }

//  setLines();
}

void BoidSketch::activate() {
  this->faderMidiValue = -1.0;
  this->app->midiManager->midiIn.addListener(this);
}

void BoidSketch::update() {

}

void BoidSketch::draw() {
  ofBackground(0);
  ofFill();
  ofSetColor(255, 255, 255, 255);
  ofSetLineWidth(4);



    // Draw particles
    for(int i=0; i<numParticles ; i++){
      int bandIndex =this->particleBands[i];
      this->bandValue = this->app->audioManager->bands.energies[bandIndex];

      Particle* particle = this->particles[i];

      particle->energy = this->bandValue;
      particle->draw();
      particle->move();
    }


  if(this->app->audioManager->beatReceived){
    this->treshold = 130;
  };

  this->setLines();
  this->treshold *= 0.94;

  // Draw lines
  ofSetColor(255, 255, 255, 255);
  for (int i=0 ; i<lineFrom.size(); i++) {
    int iFrom = this->lineFrom[i];
    int iTo = this->lineTo[i];

    ofPoint pFrom = this->particles[iFrom]->getPosition();
    ofPoint pTo = this->particles[iTo]->getPosition();

    ofDrawLine(pFrom.x, pFrom.y, pTo.x, pTo.y );
  }

  }

void BoidSketch::setLines(){


  this->lineFrom.clear();
  this->lineTo.clear();


  for (int i=0; i<this->particles.size(); i++) {

    ofPoint p = particles[i]->getPosition();

    // Ceck distance to other particle
    for (int j=0; j<this->particles.size(); j++) {

      ofPoint q = particles[j]->getPosition();
      float d = sqrt( pow(q.x - p.x, 2.0) + pow(q.y - p.y, 2.0));


      if (d > 0 && d < treshold ) {
        this->lineFrom.push_back(i);
        this->lineTo.push_back(j);
      }
    }
  }


//  for(int j=0 ; j<numLines ; j++){
//    this->lineFrom[j] = (int)ofRandom(1,numParticles);
//    this->lineTo[j] = (int)ofRandom(1,numParticles);
//  }
}

void BoidSketch::deactivate() {
  this->app->midiManager->midiIn.removeListener(this);
}

void BoidSketch::newMidiMessage(ofxMidiMessage &msg) {
//  if(msg.control == 60 && msg.value != faderMidiValue) {
//    faderMidiValue = ofMap(msg.value, 0, 127, 0, 1);
//  }
}

const char* BoidSketch::getName() {
  return this->name;
}

void BoidSketch::logName() {
  ofLog(OF_LOG_NOTICE, ofToString(this->name));
}
