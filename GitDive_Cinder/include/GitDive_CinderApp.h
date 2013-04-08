//
//  GitDive_CinderApp.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 28/03/13.
//
//

#ifndef GitDive_Cinder_GitDive_CinderApp_h
#define GitDive_Cinder_GitDive_CinderApp_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "Utils.h"
#include "GitLogParser.h"
#include "GitFileManager.h"

#include <fstream.h>
#include <stdio.h>


using namespace ci;
using namespace ci::app;
using namespace std;

class GitDive_CinderApp : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    void startVisualization(){ visActive = true; };
    void pauseVisualization(){ visActive = false; };
    
    //Variables
    string repoPath;
    string gitCmd;
    GitFileManager fManager;
    params::InterfaceGl mParams;
    
    bool vizActive;
    
};

#endif
