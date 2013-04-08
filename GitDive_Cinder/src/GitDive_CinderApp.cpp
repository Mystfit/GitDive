#include "GitDive_CinderApp.h"



void GitDive_CinderApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1024, 1024 );
	settings->setFrameRate( 60 );
    
}



void GitDive_CinderApp::setup()
{
    m_repoPath = "/Users/mystfit/Code/Python/Gitdive_Prototypes";
    m_gitCmd = "git log -p --reverse --pretty=format:\"GD_commit&%H^GD_commitAuthor&%cn^GD_date&%cd^GD_message&%B\"";
    
    m_diffLogPath = "/Users/mystfit/desktop/cinderDiffOut.log";
    m_fileDir = "/Users/mystfit/desktop/dumpFiles";
    m_fileOutput = "/Users/mystfit/desktop/colourOut.html";
    m_targetFile = "diffReader.py";
    
    m_timeSpeed = 20;
    bVizActive = false;
    bDumpFiles = true;
    bOutputSyntax = true;
    bOutputDifflog = false;
    bLoadCommits = true;
    
    initUI();
    
    tRender = boost::shared_ptr<TextRenderer>(new TextRenderer());
    tRender->setTimeline(*(cinder::app::timeline().thisRef()));
    fManager.setTextRenderer(tRender);
    fManager.setSyntaxHighlightStatus(false);
}



void GitDive_CinderApp::initUI(){
    //Setup UI
    mParams = params::InterfaceGl( "App parameters", Vec2i( 400, 200 ) );
    mParams.addParam("Repo path", &m_repoPath);
    mParams.addParam("Split lines by syntax", &fManager.getSyntaxHighlightStatus());
    mParams.addParam("Output syntax to file", &bOutputSyntax);
    mParams.addParam("Output Git diff log to file", &bOutputDifflog);
    mParams.addParam( "Dump files", &bDumpFiles);
    mParams.addParam("Reload commits", &bLoadCommits);
    
    stringstream maxSpeed; 
    maxSpeed << "min=1, max=" << ci::app::getFrameRate()/2;
    mParams.addParam("Commits per second", &m_timeSpeed, maxSpeed.str());
    mParams.addButton("Jump to end", std::bind(&GitDive_CinderApp::jumpToEnd, this));
    mParams.addButton("Start", std::bind(&GitDive_CinderApp::startVisualization, this));
    mParams.addButton("Pause", std::bind(&GitDive_CinderApp::pauseVisualization, this));
    mParams.addParam("File to track", &m_targetFile);

}


void GitDive_CinderApp::startVisualization(){
    fManager.reset();
    if(bLoadCommits) loadGitOutput(m_repoPath, m_gitCmd);
    
    bVizActive = true;
};


void GitDive_CinderApp::loadGitOutput(string repo, string gitCmd){
    cout << "Running git command:" << m_gitCmd << endl;
    string combinedCmd = "cd " + repo + " && " + gitCmd;
    
    //Get the output of the git command from stdout as a giant string
    m_cmdOutput = Utils::getCmdOutput(combinedCmd.c_str());
    
    //Parse the diff log text into commit objects for the file manager
    fManager.setCommitSource(GitLogParser::parseLog(m_cmdOutput));
}


void GitDive_CinderApp::jumpToEnd(){
    if(!m_cmdOutput.size()){
        loadGitOutput(m_repoPath, m_gitCmd);
    }
    
    fManager.setSyntaxHighlightStatus(false);
    while(fManager.applyNextCommit());
    
    if(bOutputSyntax){
        fManager.syntaxParseAllFiles();
        fManager.dumpFileOutput(m_fileOutput);
    }
    
    if(bDumpFiles) fManager.dumpAllFiles(m_fileDir);
    if(bOutputDifflog) GitLogParser::dumpDiffOutput(fManager.getCommitSource(), m_diffLogPath);
}



void GitDive_CinderApp::mouseDown( MouseEvent event )
{
}



void GitDive_CinderApp::keyDown(KeyEvent event){    
//    if(event.getChar() == KeyEvent::KEY_SPACE){
//        bool success = fManager.applyNextCommit();
//        if(success && bDumpFiles) fManager.dumpAllFiles(m_fileDir);
//    }
}



void GitDive_CinderApp::update()
{
    if(bVizActive){
        int frameNum = floor(ci::app::getElapsedFrames() % int(ci::app::getFrameRate() / m_timeSpeed));
        if(frameNum == 0 && frameNum != m_lastFrame){
            bFframeReady = true;
        }
        m_lastFrame = frameNum;
        
        if(bFframeReady){
            bool success = fManager.applyNextCommit();
            if(success){
                if(bDumpFiles) fManager.dumpAllFiles(m_fileDir);
            } else {
                bVizActive = false;
            }
            bFframeReady = false;
        }
    }

}



void GitDive_CinderApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    //Draw params window
    params::InterfaceGl::draw();
    
    tRender->draw( fManager.getFileByName(m_targetFile)->getLines() );
}



CINDER_APP_BASIC( GitDive_CinderApp, RendererGl )
