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
#include "LineElementManager.h"

#include <fstream.h>
#include <stdio.h>


using namespace ci;
using namespace ci::app;
using namespace std;

class GitDive_CinderApp : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
    void initUI();
	void mouseDown( MouseEvent event );
    void mouseUp(MouseEvent event);
    void mouseWheel(MouseEvent event);
    void keyDown( KeyEvent event );
    void keyUp(KeyEvent event);
	void update();
	void draw();
    void resetView();
    void resetAll();
    void repoPathDialog();
    void trackedFileDialog();
    
    void loadGitOutput(string repo, string gitCmd);
    void startVisualization();
    void pauseVisualization(){ bVizActive = !bVizActive; };
    void jumpToEnd();
    void setTrackedFile();
    void setViewedFile();
    
    //Managers
    GitFileManager fManager;
    boost::shared_ptr<TextRenderer> tRender;
    boost::shared_ptr<LineElementManager> lineElementManager;
    params::InterfaceGl mParams;
    
    //Variables
    string m_gitCmd, m_repoPath, m_cmdOutput, m_targetTrackedFile, m_targetViewFile;
    string m_diffLogPath, m_fileDir, m_fileOutput;

    bool bVizActive, bOutputSyntax, bDumpFiles, bOutputDifflog, bFframeReady, bLoadCommits, bFileActive;
    
    //Input variables
    bool bIsMouseDown, bIsSpaceDown;
    
    int m_timeSpeed, m_lastFrame;
};

#endif
