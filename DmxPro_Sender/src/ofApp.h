#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxGui.h"
#include "ofxOsc.h"


#ifdef TARGET_RASPBERRY_PI
	#include <pigpio.h>
#endif

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void exit();

	ofxDmx dmx;
	int level;
	float curTime, prevTime, rotTime;

///    ofxPanel panel,gpio, gui;
    ofParameter<int> red, green, blue;
    ofParameter<int> maxSpeed;
///    ofParameter<int> blue;
    ofParameter<bool> autoCycle, fullscreen, dmx1, dmx2, sender, reciver;
    ofParameter<float> radius, speed;

    ofParameterGroup parameters, dmxSettings;
    ofParameter<ofColor> color;

    ofParameter<bool> gpio14;

    ofxPanel gui, gui1;

///    ofTrueTypeFont font;
	ofxOscSender oscSender;
};
