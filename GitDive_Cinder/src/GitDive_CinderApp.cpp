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
    fManager.setSyntaxHighlightStatus(true);
    
    mParams = params::InterfaceGl( "App parameters", Vec2i( 200, 400 ) );
    mParams.addParam( "Split lines by syntax", &fManager.getSyntaxHighlightStatus());

    
//    while(fManager.applyNextCommit());
//    
//    fManager.syntaxParseAllFiles();
//    fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
//    fManager.dumpFileOutput("//Users/mystfit/desktop/colourOut.html");
//    //Debug serialization
//    GitLogParser::dumpDiffOutput(fManager.getCommitSource(), "/Users/mystfit/desktop/cinderDiffOut.log");
}

void GitDive_CinderApp::mouseDown( MouseEvent event )
{
}

void GitDive_CinderApp::keyDown(KeyEvent event){    
    if(event.getChar() == KeyEvent::KEY_SPACE){
        bool success = fManager.applyNextCommit();
        if(success) fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
    }
}

void GitDive_CinderApp::update()
{
//    bool success = fManager.applyNextCommit();
//    if(success) fManager.dumpAllFiles("/Users/mystfit/desktop/dumpFiles");
}

void GitDive_CinderApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    //Draw params window
    params::InterfaceGl::draw();

}


CINDER_APP_BASIC( GitDive_CinderApp, RendererGl )
