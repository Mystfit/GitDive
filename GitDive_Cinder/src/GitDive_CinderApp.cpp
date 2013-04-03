#include "GitDive_CinderApp.h"

void GitDive_CinderApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1024, 1024 );
	settings->setFrameRate( 60 );
}

void GitDive_CinderApp::setup()
{
    string repoPath = "/Users/mystfit/Code/Python/Gitdive_Prototypes";
    string gitCmd = "git log -p --reverse --pretty=format:\"GD_commit&%H^GD_commitAuthor&%cn^GD_date&%cd^GD_message&%B\"";
    string combinedCmd = "cd " + repoPath + " && " + gitCmd;
    
    //Get the output of the git command from stdout as a giant string
    string cmdOutput = Utils::getCmdOutput(combinedCmd.c_str());
    
    //Send lines through the log parser to make commit objects
    vector<Commit> commitList = GitLogParser::parseLog(cmdOutput);
    
    fManager.setCommitSource(commitList);
    
    GitLogParser::dumpDiffOutput(fManager.getCommitSource(), "/Users/mystfit/desktop/cinderDiffOut.log");
    fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
}









void GitDive_CinderApp::mouseDown( MouseEvent event )
{
}

void GitDive_CinderApp::keyDown(KeyEvent event){
    console() << event.getChar() << endl;
    
}

void GitDive_CinderApp::update()
{
}

void GitDive_CinderApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( GitDive_CinderApp, RendererGl )
