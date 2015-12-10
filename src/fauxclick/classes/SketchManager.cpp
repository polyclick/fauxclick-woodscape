#include "SketchManager.h"

#include "ofApp.h"
#include "FlashSketch.h"
#include "PulseSketch.h"
#include "SoundwaveSketch.h"
#include "TrippyLinesSketch.h"
#include "TriangleSketch.h"
#include "VolumeHistorySketch.h"
#include "WaveSketch.h"
#include "CubeSketch.h"
#include "BoidSketch.h"
#include "EinsteinSketch.h"

SketchManager::SketchManager(ofApp* app){
  this->app = app;
}

SketchManager::~SketchManager(){
  // destructor
}

void SketchManager::setup(){
  
  // all sketches
  sketches.push_back(new BoidSketch(this->app, "BoidSketch"));
  sketches.push_back(new CubeSketch(this->app, "CubeSketch"));
  sketches.push_back(new WaveSketch(this->app, "WaveSketch"));
  sketches.push_back(new PulseSketch(this->app, "PulseSketch"));
  sketches.push_back(new TriangleSketch(this->app, "TriangleSketch"));
  sketches.push_back(new TrippyLinesSketch(this->app, "TrippyLinesSketch"));
  sketches.push_back(new SoundwaveSketch(this->app, "SoundwaveSketch"));
  sketches.push_back(new FlashSketch(this->app, "FlashSketch"));
  sketches.push_back(new VolumeHistorySketch(this->app, "VolumeHistorySketch"));
  sketches.push_back(new EinsteinSketch(this->app, "EinsteinSketch"));

  // call setup of each sketch
  for (auto &sketch : sketches) {
    sketch->setup();
  }

  // activate first sketch
  this->activateSketch(sketches[0]->getName());
}

void SketchManager::update() {
  sketches[activeSketchIndex]->update();
}

void SketchManager::draw() {
  sketches[activeSketchIndex]->draw();
}

// Activate a sketch by name
// If we have a current active sketch, first deactivate it
// then switch the index so the draw method gets called
void SketchManager::activateSketch(const char* sketchName) {
  for(int i = 0; i < sketches.size(); i++) {
    if(strcmp(sketches[i]->getName(), sketchName) == 0) {
      if(activeSketchIndex > -1)
        sketches[activeSketchIndex]->deactivate();
      
      sketches[i]->activate();
      
      // set new index so draw loop calls draw method of that sketch
      activeSketchIndex = i;
      sketches[activeSketchIndex]->logName();
      return;
    }
  }
}