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
    m_targetViewFile = "GitDive_Cinder/src/GitDataTypes.h";
    m_targetTrackedFile = m_targetViewFile;
    
    m_timeSpeed = 20;
    bVizActive = false;
    bDumpFiles = false;
    bOutputSyntax = false;
    bOutputDifflog = false;
    bLoadCommits = true;
    
    initUI();
    gl::enableAlphaBlending();
    
    lineElementManager = boost::shared_ptr<LineElementManager>(new LineElementManager());
    tRender = boost::shared_ptr<TextRenderer>(new TextRenderer());
    tRender->setTimeline(cinder::app::timeline().thisRef());
    tRender->setLineManager(lineElementManager);
    
    boost::shared_ptr<LineFormatterManager> formatterManager(new LineFormatterManager(lineElementManager ));
    fManager.setFormatterManager(formatterManager);
    fManager.setTextRenderer(tRender);
    fManager.setSyntaxHighlightStatus(true);
}



void GitDive_CinderApp::initUI(){
    //Setup UI
    mParams = params::InterfaceGl( "App parameters", Vec2i( 400, 300 ) );
    mParams.addParam("Repo path", &m_repoPath);
    mParams.addParam("Split lines by syntax", &fManager.getSyntaxHighlightStatus());
    mParams.addParam("Output syntax to file", &bOutputSyntax);
    mParams.addParam("Output Git diff log to file", &bOutputDifflog);
    mParams.addParam("Dump files", &bDumpFiles);
    mParams.addParam("Reload commits", &bLoadCommits);
    
    stringstream maxSpeed; 
    maxSpeed << "min=1, max=" << ci::app::getFrameRate()/2;
    mParams.addParam("Commits per second", &m_timeSpeed, maxSpeed.str());
    mParams.addButton("Reset view", std::bind(&GitDive_CinderApp::resetView, this));
    mParams.addButton("Jump to end", std::bind(&GitDive_CinderApp::jumpToEnd, this));
    mParams.addSeparator();
    mParams.addParam("File to view", &m_targetViewFile);
    mParams.addButton("View", std::bind(&GitDive_CinderApp::setViewedFile, this));
    mParams.addParam("File to track", &m_targetTrackedFile);
    mParams.addButton("Track", std::bind(&GitDive_CinderApp::setTrackedFile, this));
    mParams.addSeparator();
    mParams.addButton("Pause", std::bind(&GitDive_CinderApp::pauseVisualization, this));
    mParams.addButton("Start", std::bind(&GitDive_CinderApp::startVisualization, this));
}

void GitDive_CinderApp::setViewedFile(){
    boost::shared_ptr<GitFile> file = fManager.getFileByName(m_targetViewFile);
    if(file) tRender->setTargetFile(file);
}

void GitDive_CinderApp::setTrackedFile(){
    boost::shared_ptr<GitFile> file = fManager.getFileByName(m_targetTrackedFile);
    if(file) tRender->setTargetFile(file);
    fManager.setTrackedFile(m_targetTrackedFile);
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

void GitDive_CinderApp::resetView(){
    tRender->resetView();
}


void GitDive_CinderApp::jumpToEnd(){
    if(!m_cmdOutput.size()){
        loadGitOutput(m_repoPath, m_gitCmd);
    }
    
    //fManager.setSyntaxHighlightStatus(false);
    while(fManager.applyNextCommit());
    
    if(bOutputSyntax){
        fManager.syntaxParseAllFiles();
        fManager.dumpFileOutput(m_fileOutput);
    }
    
    if(bDumpFiles) fManager.dumpAllFiles(m_fileDir);
    if(bOutputDifflog) GitLogParser::dumpDiffOutput(fManager.getCommitSource(), m_diffLogPath);
}


void GitDive_CinderApp::mouseWheel(MouseEvent event){
    if(bIsMouseDown) tRender->setTextZoom(event.getWheelIncrement() * 0.3);
    else tRender->setTextOffset(event.getWheelIncrement() * 5);
}



void GitDive_CinderApp::mouseDown( MouseEvent event )
{
    bIsMouseDown = true;
}

void GitDive_CinderApp::mouseUp(MouseEvent event){
    bIsMouseDown = false;
}



void GitDive_CinderApp::keyDown(KeyEvent event){    
    if(event.getChar() == KeyEvent::KEY_SPACE){
        tRender->setFollowCamera();
    }
}

void GitDive_CinderApp::keyUp(KeyEvent event){
    if(event.getChar() == KeyEvent::KEY_SPACE){
        tRender->setManual();
    }
}



void GitDive_CinderApp::update()
{
    if(fManager.getFileByName(m_targetViewFile) && !bFileActive){
        setTrackedFile();
        bFileActive = true;
    }
    
    if(bVizActive){
        int frameNum = floor(ci::app::getElapsedFrames() % int(ci::app::getFrameRate() / m_timeSpeed));
        if(frameNum == 0 && frameNum != m_lastFrame){
            bFframeReady = true;
            //tRender->setLinesAnimatable();
        }
        m_lastFrame = frameNum;
        
        
        if(bFframeReady){
            bool success = fManager.applyNextDiff();
//            if(success){
//                //if(bDumpFiles) fManager.dumpAllFiles(m_fileDir);
//            } else {
//                bVizActive = false;
//                cout << "--- FINISHED ---" << endl;
//            }
            bFframeReady = false;
        }
        
        lineElementManager->update();
        tRender->update();
    }

}



void GitDive_CinderApp::draw()
{
	// clear out the window with black
	gl::clear( tRender->getBackgroundColour() );
    
    
    
    if(tRender) tRender->draw();
    
    //Draw params window
    params::InterfaceGl::draw();
}



CINDER_APP_BASIC( GitDive_CinderApp, RendererGl )
