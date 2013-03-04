#pragma once

#include "ofMain.h"
#define GRID_WIDTH  16
#define GRID_HEIGHT 16
#define LENGTH		36
class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	ofVbo vbo;
	ofVec3f pos[GRID_WIDTH*GRID_HEIGHT*LENGTH];
	ofVec3f _pos[GRID_WIDTH*GRID_HEIGHT*LENGTH];
	ofFloatColor color[GRID_WIDTH*GRID_HEIGHT*LENGTH];
	
	ofVec3f center;
//	ofEasyCam cam;
	
	float restLength;
	int total;
	int space;
	
	bool doShader;
#ifndef TARGET_LINUX_ARM
#ifdef USE_SHADER
	ofxPostProcessing post;
#endif
#else
	ofShader shader;
#endif
	bool bSqueezy;
	enum MODE
	{
		NONE,
		SQUEEZY,
		ROTATE,
	};
	MODE mode;
};