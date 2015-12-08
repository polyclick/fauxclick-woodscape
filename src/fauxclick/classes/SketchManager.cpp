#include "SketchManager.h"

#include "ofApp.h"
#include "FlashSketch.h"
#include "PulseSketch.h"
#include "SoundwaveSketch.h"
#include "TrippyLinesSketch.h"
#include "TriangleSketch.h"
#include "VolumeHistorySketch.h"
#include "WaveSketch.h"

SketchManager::SketchManager(ofApp* app){
  this->app = app;
}

SketchManager::~SketchManager(){
  // destructor
}

void SketchManager::setup(){
  sketches.push_back(new WaveSketch(this->app, "WaveSketch"));
  sketches.push_back(new PulseSketch(this->app, "PulseSketch"));
  sketches.push_back(new TriangleSketch(this->app, "TriangleSketch"));
  sketches.push_back(new TrippyLinesSketch(this->app, "TrippyLinesSketch"));
  sketches.push_back(new SoundwaveSketch(this->app, "SoundwaveSketch"));
  sketches.push_back(new FlashSketch(this->app, "FlashSketch"));
  sketches.push_back(new VolumeHistorySketch(this->app, "VolumeHistorySketch"));

  // call setup
  for (auto &sketch : sketches) {
    sketch->setup();
  }

  // active sketch
  activeSketchIndex = 0;
}

void SketchManager::update() {
  sketches[activeSketchIndex]->update();
}

void SketchManager::draw() {
  sketches[activeSketchIndex]->draw();
}

void SketchManager::activateSketch(const char* sketchName) {
  for(int i = 0; i < sketches.size(); i++) {
    if(strcmp(sketches[i]->getName(), sketchName) == 0) {
      activeSketchIndex = i;
      return;
    }
  }

  sketches[activeSketchIndex]->logName();
}