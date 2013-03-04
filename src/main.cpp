#include "ofMain.h"
#include "testApp.h"
#ifndef TARGET_LINUX_ARM
#include "ofAppGlutWindow.h"
#endif
#ifdef TARGET_OPENGLES
#include "ofGLES2Renderer.h"
#endif
//========================================================================
int main( ){
#ifndef TARGET_LINUX_ARM
    ofAppGlutWindow window;
#if defined (TARGET_OSX)
	window.setGlutDisplayString("rgba double samples>=4 depth");
#endif
	ofSetupOpenGL(&window, 1280,720, OF_WINDOW);			// <-------- setup the GL context
#else
#ifdef TARGET_OPENGLES
	ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofGLES2Renderer()));
#endif
	ofSetupOpenGL(1920,1080, OF_WINDOW);
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
	
}
