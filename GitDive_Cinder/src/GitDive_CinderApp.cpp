#include "GitDive_CinderApp.h"

void GitDive_CinderApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1024, 1024 );
	settings->setFrameRate( 10 );
}

void GitDive_CinderApp::setup()
{
    string repoPath = "/Users/mystfit/Code/Python/Gitdive_Prototypes";
    string gitCmd = "git log -p --reverse --pretty=format:\"GD_commit&%H^GD_commitAuthor&%cn^GD_date&%cd^GD_message&%B\"";
    string combinedCmd = "cd " + repoPath + " && " + gitCmd;
    
    //Get the output of the git command from stdout as a giant string
    string cmdOutput = Utils::getCmdOutput(combinedCmd.c_str());
    
    //Parse the diff log text into commit objects for the file manager
    fManager.setCommitSource(GitLogParser::parseLog(cmdOutput));
    
    //Debug serialization
    GitLogParser::dumpDiffOutput(fManager.getCommitSource(), "/Users/mystfit/desktop/cinderDiffOut.log");
    fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
    fManager.dumpFileOutput("/Users/mystfit/desktop/cinderFileOut.log");
}

void GitDive_CinderApp::mouseDown( MouseEvent event )
{
}

void GitDive_CinderApp::keyDown(KeyEvent event){    
    if(event.getChar() == KeyEvent::KEY_SPACE){
        fManager.applyNextCommit();
        fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
    }
}

void GitDive_CinderApp::update()
{
    fManager.applyNextCommit();
    fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
}

void GitDive_CinderApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( GitDive_CinderApp, RendererGl )
