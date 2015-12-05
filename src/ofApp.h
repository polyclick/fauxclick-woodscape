#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"
#include "ofxMidi.h"
#include "ofxBeat.h"

#include "fcSketchBase.h"
#include "fcFFTBarSketch.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

  public:
    void setup();
    void update();
    void draw();
    void exit();

    void vSyncChanged(bool & vSync);
    void capFramerateChanged(bool & vSync);
    void smoothChanged(bool & smooth);

    void newMidiMessage(ofxMidiMessage& eventArgs);
    void audioReceived(float*, int, int);

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

    stringstream text;

    bool bHideGui;
    int activeSketchIndex;

    std::vector<fcSketchBase*> sketches;

    ofParameter<string> sketchLabel;
    ofParameter<string> framerate;
    ofParameter<string> screenSize;

    ofParameter<bool> vSync;
    ofParameter<bool> capFramerate;
    ofParameter<bool> smooth;

    ofParameter<string> midiStatus;
    ofParameter<string> midiChannel;
    ofParameter<float> midiPitch;
    ofParameter<float> midiVelocity;
    ofParameter<float> midiControl;
    ofParameter<float> midiValue;
    ofParameter<string> midiDelta;

    ofParameter<float> audioKick;
    ofParameter<float> audioSnare;
    ofParameter<float> audioHat;

    ofParameterGroup summary;
    ofParameterGroup settings;
    ofParameterGroup midi;
    ofParameterGroup audio;
    ofParameterGroup debug;
    ofxPanel gui;

  	ofxSyphonServer mainOutputSyphonServer;

    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;

    ofxBeat beat;
};
