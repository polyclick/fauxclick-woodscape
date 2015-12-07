#include "ofApp.h"

#include "WaveSketch.h"
#include "PulseSketch.h"
#include "TriangleSketch.h"
#include "FFTBarSketch.h"
#include "TriangleNoiseSketch.h"
#include "SoundwaveSketch.h"
#include "PointCloudSketch.h"
#include "VolumeHistorySketch.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // window
  ofSetWindowTitle("fauxclick-woodscape");
  ofBackground(0, 0, 0);
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofSetFrameRate(0);  // unlimited
  ofSetVerticalSync(true);
  ofDisableSmoothing();
  
  // libraries and stuff
  this->setupGui();
  this->setupMidi();
  this->setupAudio();
  this->setupSyphon();
  
  // our sketches
  this->setupSketches();
}

//--------------------------------------------------------------
void ofApp::setupMidi() {
  midiIn.listPorts();
  midiIn.openPort("Ableton Push User Port");
  midiIn.ignoreTypes(false, false, false);  // sysex, timing, active sense
  midiIn.addListener(this);
  midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void ofApp::setupAudio() {
  audioManager = new AudioManager(this);
  audioManager->setup();
}

//--------------------------------------------------------------
void ofApp::setupSyphon() {
  mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::setupGui() {
  
  summary.setName("summary");
  summary.add(sketchLabel.set("sketch", ""));
  summary.add(screenSize.set("resolution", ""));
  
  midi.setName("midi");
  midi.add(midiStatus.set("status", ""));
  midi.add(midiChannel.set("channel", ""));
  midi.add(midiPitch.set("pitch", 0, 0, 127));
  midi.add(midiVelocity.set("velocity", 0, 0, 127));
  midi.add(midiControl.set("control", 0, 0, 127));
  midi.add(midiValue.set("value (normalized)", 0, 0, 100));
  midi.add(midiDelta.set("delta", ""));
  
  debug.add(summary);
  debug.add(midi);
  
  gui.setup(debug);
  
  parameterWindow = new ParameterWindow(this);
  parameterWindow->setup();
}

//--------------------------------------------------------------
void ofApp::setupSketches() {
  sketches.push_back(new WaveSketch(this, "WaveSketch"));
  sketches.push_back(new PulseSketch(this, "PulseSketch"));
  sketches.push_back(new TriangleSketch(this, "TriangleSketch"));
  sketches.push_back(new FFTBarSketch(this, "FFTBarSketch"));
  sketches.push_back(new TriangleNoiseSketch(this, "TriangleNoiseSketch"));
  sketches.push_back(new SoundwaveSketch(this, "SoundwaveSketch"));
  sketches.push_back(new PointCloudSketch(this, "PointCloudSketch"));
  sketches.push_back(new VolumeHistorySketch(this, "VolumeHistorySketch"));
  
  // call setup
  for (auto &sketch : sketches) {
    sketch->setup();
  }
  
  // active sketch
  activeSketchIndex = 0;
  sketchLabel = sketches[activeSketchIndex]->getName();
}

//--------------------------------------------------------------
void ofApp::update() {
  audioManager->update();
  parameterWindow->update();

  // update active sketch
  sketches[activeSketchIndex]->update();

}

//--------------------------------------------------------------
void ofApp::draw() {

  // draw current sketch
  sketches[activeSketchIndex]->draw();

  // publish screen to syphon
  mainOutputSyphonServer.publishScreen();

  // everything AFTER this line will not get send over syphon
  // use it to draw the gui, logs, ...

  // draw gui if needed
  if(!bHideGui){
    ofSetColor(255);
    gui.draw();
    
    parameterWindow->draw();
  }
}

//--------------------------------------------------------------
void ofApp::exit() {

  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);
  
  // release memory
  delete parameterWindow;
  delete audioManager;
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

  // make a copy of the latest message
  midiMessage = msg;

  // show in debug
  midiStatus = ofxMidiMessage::getStatusString(midiMessage.status);
  midiChannel = ofToString(midiMessage.channel);
  midiPitch = midiMessage.pitch;
  midiVelocity = midiMessage.velocity;
  midiControl = midiMessage.control;

  if(midiMessage.status == MIDI_PITCH_BEND) {
    midiValue = ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, 100);
  } else {
    midiValue = ofMap(midiMessage.value, 0, 127, 0, 100);
  }

  midiDelta = ofToString(midiMessage.deltatime);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  ofLog(OF_LOG_NOTICE, "the number is " + ofToString(key));

  switch(key) {
    case 'h':
      bHideGui = !bHideGui;

    case '1':
      activeSketchIndex = 0;
      break;

    case '2':
      activeSketchIndex = 1;
      break;

    case '3':
      activeSketchIndex = 2;
      break;
      
    case '4':
      activeSketchIndex = 3;
      break;

    case '5':
      activeSketchIndex = 4;
      break;
      
    case '6':
      activeSketchIndex = 5;
      break;
      
    case '7':
      activeSketchIndex = 6;
      break;
  }

  sketches[activeSketchIndex]->logName();
  sketchLabel = sketches[activeSketchIndex]->getName();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
