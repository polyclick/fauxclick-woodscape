#include "Particle.h"

Particle::Particle(int v, int f){
  this->size = 3;
  this->scale = 5;
  this->energy = 0;
  this->decaySize = 0;
  this->smoothedSize = 0;
  
  this->v = v;
  this->f = 1 / f;
  this->dx = v * ofRandom(-1,1);
  this->dy = v * ofRandom(-1,1);
  this->ddx = this->f * ofRandom(-1,1);
  this->ddy = this->f * ofRandom(-1,1);
  
  this->reset();
}

Particle::~Particle(){
  // destructor@
}

void Particle::move(){
  this->ddx = (ofRandom(-10 - this->dx, 10 - this->dx) * this->f);
  this->dx += this->ddx;
  
  this->ddy = (ofRandom(-10 - this->dy, 10 - this->dy) * this->f);
  this->dy += this->ddy;
  
  this->position.x = this->position.x + this->v*this->dx;
  this->position.y = this->position.y + this->v*this->dy;
}

void Particle::draw(){
  
    this->power = exp(this->energy*5);
    this->size = this->scale * this->power;
  
  this->decaySize = max(this->decaySize, this->size);
  this->smoothedSize += ( this->decaySize - this->smoothedSize) * 0.3;
  
  this->decaySize*= 0.8;
  
  if(this->position.x > ofGetWidth() || this->position.x < 0 || this->position.y > ofGetHeight() || this->position.y < 0){
    reset();
  }
  
  ofDrawCircle(this->position.x, this->position.y, this->smoothedSize );
}

ofPoint Particle::getPosition(){
  return this->position;
}
void Particle::reset(){
  this->position.x = (int)ofRandom(-1,ofGetWidth());
  this->position.y = (int)ofRandom(-1,ofGetHeight());
}
