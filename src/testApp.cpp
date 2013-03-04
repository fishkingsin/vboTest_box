#include "testApp.h"
//float cube[]={
//	1,1,1,    -1,1,1,    -1,-1,1,    1,-1,1,        // v0-v1-v2-v3
//	1,1,1,     1,-1,1,    1,-1,-1,   1,1,-1,        // v0-v3-v4-v5
//	1,1,1,     1,1,-1,   -1,1,-1,   -1,1,1,         // v0-v5-v6-v1
//	-1,1,1,    -1,1,-1,   -1,-1,-1,  -1,-1,1,		// v1-v6-v7-v2
//	-1,-1,-1,   1,-1,-1,   1,-1,1,   -1,-1,1,        // v7-v4-v3-v2
//	1,-1,-1,  -1,-1,-1,  -1,1,-1,    1,1,-1};
float cube[]={
	0,0,0,	-1,-1,0,	0,-2,0,	1,-1,0,        // v0-v1-v2-v3 // 0,1,2,3
	0,0,0,	1,-1,0,		1,0,0,	0,1,0,        // v0-v3-v4-v5 // 4,5,6,7
	0,0,0,	-1,-1,0,	-1,0,0,	0,1,0};		//v0-v5-v6-v1 // 8,9,10,11

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	bSqueezy = false;
	center.set(0,0);//ofGetWidth()*0.5,ofGetHeight()*0.5);
	float SIZE = (ofGetWidth()/GRID_WIDTH*1.0f)*0.5;
	space      = SIZE*2;
	for (int i=0; i<GRID_WIDTH; i++) {
		for (int j=0; j<GRID_HEIGHT; j++) {
			
			int x	  = space*0.5+((i) * space+((j%2)*0.5)*space) + center.x;
			int y     = space*0.5+(j * space) + center.y;
			int z     = 0;
			int index = (j*GRID_WIDTH+i) * LENGTH;
						
			// now we are at each line
			int cub_index = 0;
			for (int k=0; k<LENGTH; k++) {
				pos[index +k].x = x+cube[cub_index++]*SIZE;
				pos[index +k].y = y+cube[cub_index++]*SIZE;
				pos[index +k].z = z+cube[cub_index++]*SIZE;
				
				_pos[index +k] = pos[index +k];

				color[index + k] = ofFloatColor::fromHsb(1, 0, (k*1.0f/LENGTH));
			}
			
			
		}
	}
	total = GRID_WIDTH*GRID_HEIGHT*LENGTH;
	vbo.setVertexData(pos, total, GL_DYNAMIC_DRAW);
	vbo.setColorData(color, total, GL_DYNAMIC_DRAW);
	
//	cam.enableOrtho();
//	cam.setFarClip(10000);
//	cam.setNearClip(0);
//	cam.setPosition(0, 0, 500);
//	cam.setGlobalPosition(-ofGetWidth()*0.5, -ofGetHeight()*0.5, 0);
	ofSetupScreenOrtho();
	glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void testApp::update(){
	float t = (ofGetElapsedTimef()) * 0.98;
	float div = 250.0;
	for (int i=0; i<GRID_WIDTH; i++) {
		for (int j=0; j<GRID_HEIGHT; j++) {
			int index = (j*GRID_WIDTH+i) * LENGTH;
			
			for(int k = 0; k < LENGTH; k++)
			{
				if(mode==SQUEEZY)
				{
				ofVec3f vec(
							ofSignedNoise(t, _pos[index+k].y/div, _pos[index+k].z/div)*100,
							ofSignedNoise(_pos[index+k].x/div, t, _pos[index+k].z/div)*100,
							0);
				pos[index+k] = _pos[index+k]+vec;
				}
				else if(mode==ROTATE)
				{
					pos[index+k] = _pos[index+k].getRotated(ofGetFrameNum(),_pos[index], ofVec3f(0,0,1));
				}
				else
				{
					pos[index+k] = _pos[index+k];
				}
				
				color[index + k] = ofFloatColor::fromHsb((i*1.0f/GRID_WIDTH)*((GRID_HEIGHT-j)*1.0f/GRID_HEIGHT), sinf(ofGetElapsedTimef())*0.5+0.5, (k*1.0f/LENGTH)*sinf(ofGetElapsedTimef())*0.5+0.5);
			}
			
//			for(int l = 1 ; l < 3 ; l++)
//			{
//				ofVec3f vec(
//                        ofSignedNoise(t, _pos[index+(l*3+1)].y/div, _pos[index+(l*3+1)].z/div)*100,
//                        ofSignedNoise(_pos[index+(l*3+1)].x/div, t, _pos[index+(l*3+1)].z/div)*100,
//                        0);
//				pos[index+(l*3+1)] = _pos[index+(l*3+1)];
//				pos[index+(l*3+2)] = _pos[index+(l*3+2)];
//				pos[index+(l*3+3)] = _pos[index+(l*3+3)];
//
//			}
			
			
		}
	}
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
//	cam.begin();
	ofPushMatrix();
//	ofTranslate(center);
//	ofDrawAxis(100);
	ofPopMatrix();
	
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	glLineWidth( 5.0f );
	vbo.bind();
	vbo.updateVertexData(pos, total);
	vbo.updateColorData(color, total);
	
	for (int i=0; i<GRID_WIDTH; i++) {
		for (int j=0; j<GRID_HEIGHT; j++) {
			int index = (j*GRID_WIDTH+i) * LENGTH;
			for(int k = 0; k < 3 ; k++)
			{
				vbo.draw(GL_POLYGON, index+(4*k),4);
			}
		}
	}
	
	vbo.unbind();
//	cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='1')
	{
		mode = SQUEEZY;
	}
	if(key=='2')
	{
		mode = ROTATE;
	}
	if(key=='0')
	{
		mode = NONE;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}