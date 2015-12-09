#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxMidi.h"
#include "ofxGui.h"
#include "ParameterWindow.h"
#include "AudioManager.h"
#include "SketchManager.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

private:

  void setupGui();
  void setupMidi();
  void setupAudio();
  void setupSyphon();
  void setupSketches();

public:
  bool showDebugGrid = false;
  bool showGui = true;

  AudioManager *audioManager;
  ParameterWindow *parameterWindow;
  SketchManager *sketchManager;

  void setup();
  void update();
  void draw();
  void exit();

  void newMidiMessage(ofxMidiMessage& eventArgs);

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  ofParameter<string> screenSize;
  ofParameter<string> midiStatus;
  ofParameter<string> midiChannel;
  ofParameter<float> midiPitch;
  ofParameter<float> midiVelocity;
  ofParameter<float> midiControl;
  ofParameter<float> midiValue;
  ofParameter<string> midiDelta;
  ofParameterGroup summary;
  ofParameterGroup midi;
  ofParameterGroup debug;
  ofxPanel gui;

  ofImage debugGridImage;

	ofxSyphonServer mainOutputSyphonServer;

  ofxMidiIn midiIn;
  ofxMidiMessage midiMessage;

};
