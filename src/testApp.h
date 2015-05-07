#pragma once

#include "ofMain.h"
#include "/Users/mohithingorani/Documents/OpenFrameworks/of_v0.8.4_osx_release/addons/ofxOculusDK2/src/ofxOculusDK2.h"
#include "ofxCsv.h"
#include "DataMesh.h"
#include "ofMesh.h"
#include "ofPolyline.h"

using namespace wng;


typedef struct{
	ofColor color;
	ofVec3f pos;
	ofVec3f floatPos;
	float radius;
    bool bMouseOver;
    bool bGazeOver;
} DemoSphere;




class testApp : public ofBaseApp
{
  public:
	
	void setup();
	void update();
	void draw();
	
	void drawScene();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOculusDK2		oculusRift;
    ofxCsv mycsv;
    
	ofLight				light;
	ofEasyCam			cam;
	bool showOverlay;
	bool predictive;
	vector<DemoSphere> demos;
    
    vector< DataMesh> dataPoints;

    ofVec3f cursor2D;
    ofVec3f cursor3D;
    
    ofVec3f cursorRift;
    ofVec3f demoRift;
    
    ofVec3f cursorGaze;
    int balls = 75;
    int farEdge = 1000;
    
    int xPos = 0 ;
    int yPos = 50 ;
    int zPos = 0 ;
    int spheresVisualized;
    int numRows;
    int numColumns;
    
    int timeTravel = 0;
    
    ofMesh gridMesh;
    

    
    
};

