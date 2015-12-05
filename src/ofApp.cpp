#include "ofApp.h"

#include "TriangleSketch.h"
#include "FFTBarSketch.h"
#include "TriangleNoiseSketch.h"
#include "SoundwaveSketch.h"

//--------------------------------------------------------------
void ofApp::setup(){

  // window
  ofSetWindowTitle("fauxclick-woodscape");
  ofBackground(0, 0, 0);
  ofSetLogLevel(OF_LOG_VERBOSE);
  
  // libraries and stuff
  this->setupGui();
  this->setupMidi();
  this->setupAudio();
  this->setupSyphon();
  
  // our sketches
  this->setupSketches();
}

//--------------------------------------------------------------
void ofApp::setupGui() {
  vSync.addListener(this, &ofApp::vSyncChanged);
  capFramerate.addListener(this, &ofApp::capFramerateChanged);
  smooth.addListener(this, &ofApp::smoothChanged);
  
  summary.setName("summary");
  summary.add(sketchLabel.set("sketch", ""));
  summary.add(framerate.set("fps", ""));
  summary.add(screenSize.set("resolution", ""));
  
  settings.setName("settings");
  settings.add(vSync.set("vSync", false));
  settings.add(capFramerate.set("capFramerate", false));
  settings.add(smooth.set("smooth", false));
  
  midi.setName("midi");
  midi.add(midiStatus.set("status", ""));
  midi.add(midiChannel.set("channel", ""));
  midi.add(midiPitch.set("pitch", 0, 0, 127));
  midi.add(midiVelocity.set("velocity", 0, 0, 127));
  midi.add(midiControl.set("control", 0, 0, 127));
  midi.add(midiValue.set("value (normalized)", 0, 0, 100));
  midi.add(midiDelta.set("delta", ""));
  
  audio.setName("audio");
  audio.add(audioKick.set("kick", 0, 0, 100));
  audio.add(audioSnare.set("snare", 0, 0, 100));
  audio.add(audioHat.set("hat", 0, 0, 100));
  
  debug.add(summary);
  debug.add(settings);
  debug.add(midi);
  debug.add(audio);
  
  gui.setup(debug);
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
  soundStream.printDeviceList();
  
  // first try to get akai device
  vector<ofSoundDevice> matches = soundStream.getMatchingDevices("Akai Professional, LP: EIE pro (Core Audio)");
  
  // else try traktor a10
  if(!matches.size())
    matches = soundStream.getMatchingDevices("Akai Professional, LP: EIE pro (Core Audio)");
  
  // if akai or traktor found, set as main
  // this will automatically fallback to microphone audio if none of both was found
  if(matches.size())
    soundStream.setDevice(matches[0]);
  
  // setup the soundstream
  bufferSize = beat.getBufferSize();
  soundStream.setup(this, 0, 1, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::setupSyphon() {
  mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::setupSketches() {
  sketches.push_back(new TriangleSketch(this, "TriangleSketch"));
  sketches.push_back(new FFTBarSketch(this, "FFTBarSketch"));
  sketches.push_back(new TriangleNoiseSketch(this, "TriangleNoiseSketch"));
  sketches.push_back(new SoundwaveSketch(this, "SoundwaveSketch"));
  
  // call setup
  for (auto &sketch : sketches) {
    sketch->setup();
  }
  
  // active sketch
  activeSketchIndex = 0;
  sketchLabel = sketches[activeSketchIndex]->getName();
}

//--------------------------------------------------------------
void ofApp::vSyncChanged(bool & vSync){
  ofSetVerticalSync(vSync);
  cout << "vSync: " << vSync << endl;
}

//--------------------------------------------------------------
void ofApp::capFramerateChanged(bool & capFramerate){

  // cap framerate to 60fps if requested
  int framerate = capFramerate ? 60 : 0;
  ofSetFrameRate(framerate);

  // log setting switch
  if(framerate) {
    cout << "Frame rate set to: " << framerate << endl;
  } else {
    cout << "Frame rate set to unlimited" << endl;
  }
}

//--------------------------------------------------------------
void ofApp::smoothChanged(bool & smooth) {
  if(smooth) {
    ofEnableSmoothing();
    cout << "Smoothing: enabled" << endl;
  } else {
    ofDisableSmoothing();
    cout << "Smoothing: disabled" << endl;
  }
}

//--------------------------------------------------------------
void ofApp::update() {

  // update beat detector
  beat.update(ofGetElapsedTimeMillis());

  // debug
  audioKick = beat.kick() * 100.0;
  audioSnare = beat.snare() * 100.0;
  audioHat = beat.hihat() * 100.0;

  // set framerate
  framerate = ofToString(ofGetFrameRate());

  // update active sketch
  sketches[activeSketchIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw() {

  // draw current sketch
  sketches[activeSketchIndex]->draw(beat, midiMessage);

  // publish screen to syphon
  mainOutputSyphonServer.publishScreen();

  // everything AFTER this line will not get send over syphon
  // use it to draw the gui, logs, ...

  // draw gui if needed
  if(!bHideGui){
    ofSetColor(255);
    gui.draw();
  }

  //cout << beat.kick() << "," << beat.snare() << "," << beat.hihat() << endl;
}

//--------------------------------------------------------------
void ofApp::exit() {

  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);
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
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
  beat.audioReceived(input, bufferSize, nChannels);
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
