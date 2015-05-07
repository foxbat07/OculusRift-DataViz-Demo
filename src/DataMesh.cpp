//
//  DataMesh.cpp
//  OculusRiftDataVizDemo
//
//  Created by Mohit Hingorani on 1/25/15.
//
//

#include "DataMesh.h"



    
void DataMesh::getCoutData( int coutMonth, int coutDay,int coutHour, int coutMinute )
    {
        //coutYear = this->coutYear;
        
        this->coutMonth = coutMonth;
        this->coutDay = coutDay;
        this->coutHour = coutHour;
        this->coutMinute = coutMinute;
        cout<< this->coutMonth <<" "<< this->coutDay <<" "<< this->coutHour <<" "<< this->coutMinute<< "\n";
        
    }
    
void DataMesh::getCinData( int cinMonth, int cinDay,int cinHour, int cinMinute )
    {
        //coutYear = this->coutYear;
        
        this->cinMonth = cinMonth;
        this->cinDay = cinDay;
        this->cinHour = cinHour;
        this->cinMinute = cinMinute;
        cout<< this->cinMonth <<" "<< this->cinDay <<" "<< this->cinHour <<" "<< this->cinMinute<< "\n";
        
    }

void DataMesh::getTitle( string title)
    {
        this->title = title;
    }


void DataMesh::getCommonData(int daysCheckedOut, float deweyClass )
    {
        this->daysCheckedOut = daysCheckedOut;
        this->deweyClass = deweyClass;
    }


void DataMesh::createMesh()
{
    this-> createCoutPosition();
    
    ofColor c;
    c.setHsb( ofMap(this->daysCheckedOut, 0, 20 , 0, 255) , 255, 255,50);
    this->Mesh.addColor(c);
    this->Mesh.addVertex(coutPosition);
    
    this-> createCinPosition();
    c.setHsb( ofMap(this->daysCheckedOut, 0, 20 , 0, 255) , 255, 255,50);
    this->Mesh.addColor(c);
    this->Mesh.addVertex(cinPosition);
    
    createPolyline();
    
}

void DataMesh::drawMesh()
{
    glPointSize(1);
    this->Mesh.setMode(OF_PRIMITIVE_LINES);
    this->Mesh.draw();
}


void DataMesh::createCoutPosition()
{
    //this->coutPosition.x = (this-> deweyClass  - this->deweyAdjust)* 10;
    //this->coutPosition.y = (this->coutDay - this->dayAdjust ) *50;
    //this->coutPosition.z = (this ->coutHour + this->coutMinute/100 - this-> timeAdjust) * 10 ;
    
    this->coutPosition.x = (this-> deweyClass- this->deweyAdjust ) /4;
    this->coutPosition.y = (this->coutDay ) * 15 ;
    this->coutPosition.z = (this ->coutHour + this->coutMinute/100 ) *20  ;
    
    
    
}


void DataMesh::createCinPosition()
{
    //this->coutPosition.x = (this-> deweyClass  - this->deweyAdjust)* 10;
    //this->coutPosition.y = (this->coutDay - this->dayAdjust ) *50;
    //this->coutPosition.z = (this ->coutHour + this->coutMinute/100 - this-> timeAdjust) * 10 ;
    
    this->cinPosition.x = (this-> deweyClass- this->deweyAdjust ) /4 ;
    this->cinPosition.y = -(this->cinDay  ) * 15 ;
    this->cinPosition.z = -(this ->cinHour + this->cinMinute/100 ) *20  ;
    
}

void DataMesh::createPolyline()
{
    ofVec3f startPoint = this->Mesh.getVertex(0);
    ofVec3f endPoint = this->Mesh.getVertex(1);
    ofColor startColor = this->Mesh.getColor(0);
    ofColor endColor = this->Mesh.getColor(1);
    
    for ( int i = 0 ; i< this->polyIndexSize ; i++)
    {
        ofVec3f addPoint = startPoint * ( this->polyIndexSize - i )/this->polyIndexSize  + endPoint * i/this->polyIndexSize;
        ofColor addColor = endColor.lerp(startColor, i/this->polyIndexSize );  //color to be added
        this->dataLine.addVertex(addPoint);
    }
}


void DataMesh::animatePolyline()
{
        ofPolyline &line = this->dataLine;
    
        ofSetColor(255);
        ofBeginShape();
        ofNoFill();
    
        this->backPoly += 0.1;
        this->frontPoly = this->backPoly +1.0;
    
        if( this->backPoly > line.size()- this->frontPoly )
        {
            this->backPoly = 0;
            this->frontPoly = this->backPoly +0.5;
    
        }
    
        cout<< this->backPoly<< " "<<this->frontPoly<< "\n";
        for (int j = this->backPoly; j < this->frontPoly ; j++)
            {
             ofVertex( line[j] );
            }
        ofEndShape();
    
    
   
}




    

