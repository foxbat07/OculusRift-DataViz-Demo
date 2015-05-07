#include "testApp.h"

//--------------------------------------------------------------
ofImage image1;
ofImage image2;
ofImage image3;

void testApp::setup()
{
	ofBackground(0);
	ofSetLogLevel( OF_LOG_VERBOSE );
	ofSetVerticalSync( true );
    ofSetFrameRate(75);
    ofEnableAlphaBlending();
    
    //girdMesh.setMode()
  
    
    image1.loadImage("Flicker8k_Dataset/54501196_a9ac9d66f2.jpg");
    image2.loadImage("Flicker8k_Dataset/54723805_bcf7af3f16.jpg");
    //image3.loadImage("Flicker8k_Dataset/55135290_9bed5c4ca3.jpg");
    image3.loadImage("Majestic.jpg");
    image3.resize(1000, 600);

    cout<< image1.width << image1.height << " " << image2.width << image2.height ;
    
    
    gridMesh.setMode(OF_PRIMITIVE_POINTS);
    int sideNumber =  15   ;//2x the number
    int gridGap = 300;
    
    for ( int i = -sideNumber ; i< sideNumber ; i++ )
    {
        for ( int j = -sideNumber; j < sideNumber ; j++ )
        {
            for ( int k =-sideNumber ; k< sideNumber ; k++ )
            {
                ofVec3f vPoint;
                
                vPoint.x = i * gridGap;
                vPoint.y = j * gridGap;
                vPoint.z = k * gridGap;
                ofColor c;
                c.set( ofMap(i, -10, 10, 0, 255) , ofMap( j, -10, 10, 0, 255), ofMap( k , -10, 10, 0, 255)  , 200 );
                gridMesh.addColor(c);
                gridMesh.addVertex(vPoint);
                
            }
        }
    }
    
    //ofToggleFullscreen();
	showOverlay = false;
	predictive = true;
	
	ofHideCursor();
	
	oculusRift.baseCamera = &cam;
	oculusRift.setup();
    
    
  	//enable mouse;
	cam.begin();
    cam.setPosition(0, 0, 0);
	cam.end();
}


//--------------------------------------------------------------
void testApp::update()
{
    cam.setPosition(xPos, yPos, zPos);
    
    
    /*
    if(oculusRift.isSetup())
    {
        ofRectangle viewport = oculusRift.getOculusViewport();
        
        for(int i = 0; i < demos.size(); i++)
        {
            // mouse selection
			float mouseDist = oculusRift.distanceFromMouse(demos[i].floatPos);
            demos[i].bMouseOver = (mouseDist < 50);
            
            // gaze selection
            ofVec3f screenPos = oculusRift.worldToScreen(demos[i].floatPos, true);
            float gazeDist = ofDist(screenPos.x, screenPos.y,
                                    viewport.getCenter().x, viewport.getCenter().y);
            demos[i].bGazeOver = (gazeDist < 25);
        }
    }
     
    */
    
    
    if(oculusRift.isSetup())
    {
        ofRectangle viewport = oculusRift.getOculusViewport();
        
        
    }
   
    
}


//--------------------------------------------------------------
void testApp::draw()
{
    
	if(oculusRift.isSetup()){
		
		if(showOverlay){
			
			oculusRift.beginOverlay(-230, 320,240);
			ofRectangle overlayRect = oculusRift.getOverlayRectangle();
			
			ofPushStyle();
			ofEnableAlphaBlending();
			ofFill();
			ofSetColor(255, 70, 192, 140);
			
			ofRect(overlayRect);
			
			ofSetColor(0,255,0,255);
			ofFill();
        
			ofDrawBitmapString("ofxOculusRift demo by\nMohit Hingorani \nFPS:"+ofToString(ofGetFrameRate())+"\nNumber of Rows: "+ofToString(mycsv.numRows)+ "\nPosition: "+ofToString(xPos)+" "+ ofToString(yPos)+" " +ofToString(zPos)+ "\nPredictive Tracking " + (oculusRift.getUsePredictiveOrientation() ? "YES" : "NO")  , 40, 40);
            
            ofSetColor(255, 0, 0);
            ofNoFill();
            ofCircle(overlayRect.getCenter(), 20);
			
			ofPopStyle();
			oculusRift.endOverlay();
		}
        
        ofSetColor(0);
		glEnable(GL_DEPTH_TEST);


		oculusRift.beginLeftEye();
		drawScene();
		oculusRift.endLeftEye();
		
		oculusRift.beginRightEye();
		drawScene();
		oculusRift.endRightEye();
		
		oculusRift.draw();
		
		glDisable(GL_DEPTH_TEST);
    }
	else{
		cam.begin();
		drawScene();
		cam.end();
	}
	
}

//--------------------------------------------------------------
void testApp::drawScene()
{
	/*
	ofPushMatrix();
	ofRotate(90, 0, 0, -1);
	ofDrawGridPlane(500.0f, 10.0f, false );
	ofPopMatrix();
    */
    //draw big sphere
    //
    ofPushMatrix();
	//ofRotate(ofGetElapsedTimef(), 0, 1,0);
    ofSetColor(0, 140, 200);
    ofNoFill();
	//ofSphere(5000);
    //ofSpherePrimitive(500, 100);
	ofPopMatrix();
	ofPushStyle();
    
    
    // draw images
    
    ofPushMatrix();
    //ofTranslate(100, 0);
   // ofRotateX(PI/2);
    ofScale(-1,-1,1);
    ofSetColor(255);
    //image1.draw(200 , 0 , 500);
    //image2.draw(-100 , 0, -500 );
    //ofRotateX(PI/4);
   // image3.draw(0 , 0 , image3.width/2 );
    
    ofPopMatrix();
    
    
    //draw grids
    
    ofPushMatrix();
    glPointSize(3);
    gridMesh.draw();
    ofPopMatrix();
    
	
	//billboard and draw the mouse
	if(oculusRift.isSetup()){
		
		ofPushMatrix();
		oculusRift.multBillboardMatrix();
		ofSetColor(255, 0, 0);
		ofCircle(0,0,.5);
		ofPopMatrix();

	}
	
	ofPopStyle();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    int move =40;
	if( key == 'f' )
	{
		//gotta toggle full screen for it to be right
		ofToggleFullscreen();
	}
	
	if(key == 's'){
		oculusRift.reloadShader();
	}
	
	if(key == 'v'){
		oculusRift.lockView = !oculusRift.lockView;
	}
	
	if(key == 'o'){
		showOverlay = !showOverlay;
	}
	if(key == 'r'){
		oculusRift.reset();
		
	}
	if(key == 'h'){
		ofHideCursor();
	}
	if(key == 'H'){
		ofShowCursor();
	}
	
	if(key == 'p'){
		predictive = !predictive;
		oculusRift.setUsePredictedOrientation(predictive);
	}
    
    
    if( key == 'i')
        yPos+=move;
    if( key == 'j')
        xPos-=move;
    if ( key == 'k')
        yPos-=move;
    if(key == 'l')
        xPos+=move;
    
    if(key == 'q')
        zPos+=move;
    if(key == 'a')
        zPos-=move;

  

    
        
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
 //   cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
//    cursor2D.set(x, y, cursor2D.z);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
