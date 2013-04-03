//
//  GitLogParser.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitLogParser.h"

vector<Commit> GitLogParser::parseLog(string logString)
{
    vector<Commit> commitList(new vector<Commit>);
    vector <string> diffBlock;
    
    //Split string into lines
    vector<string> diffLog;
    boost::split(diffLog, logString, boost::is_any_of("\n"));
    
    for(int i = 0; i < diffLog.size(); i++)
    {
        string line = diffLog[i];
        
        if(starts_with(line, "GD_commit")){
            
            //Parse last commit first with the lines between the last GD_commit line
            if(commitList->size() > 0){
                commitList->back().addDiffList( parseCommit(diffBlock) );
            }
            
            diffBlock.clear();
    
            //Split commit line into key/pair values
            Utils::strip(line, "\n");
                        
            vector<string> logVars;
            vector<string> strVars;

            split(logVars, line, is_any_of("^"));
            
            //Split git log message into component variables
            for(int j = 0; j < logVars.size(); j++){
                vector<string> logVarsSplit;
                split(logVarsSplit, logVars[j], is_any_of("&"));
                strVars.push_back( Utils::checkStrIndexInRange(logVarsSplit, 1) );
            }
            
            commitList->push_back( Commit(strVars[0], strVars[1], strVars[2], strVars[3]) );
        } else {
            diffBlock.push_back(line);
        }
        
        //Remember to add the block to the last commit since we won't be looping around again
        if(i == diffLog.size()-1) commitList->back().addDiffList( parseCommit(diffBlock) );
    }
    
    
    return commitList;
}


vector< boost::shared_ptr<Diff> > GitLogParser::parseCommit(vector<string> diffBlock)
{
    bool inDiffHeader = false;
    vector< boost::shared_ptr<Diff> > diffList;
    boost::shared_ptr<Diff> diff(new Diff());
    boost::shared_ptr<DiffHunk> diffHunk(new DiffHunk());
    
    for(int i = 0; i < diffBlock.size(); i++){
        
        string line = diffBlock[i];
        
        //Start a new diff object when a diff command is found
        if(starts_with(line, "diff --git")){
            inDiffHeader = true;
            
            //Create new diff container
            boost::shared_ptr<Diff> diffPtr(new Diff());
            diff = diffPtr;
            diffList.push_back(diff);
        }
        
        //Move through the header and set up the diff object from the parsed diff vars
        if(inDiffHeader){
            if(starts_with(line, "index"))
            {
            }
            
            else if(starts_with(line, "new file mode"))
            {
                diff->fileMode = Diff::FILEMODE_ADDED;
            }
            
            else if(starts_with(line, "deleted file mode"))
            {
                diff->fileMode = Diff::FILEMODE_DELETED;
            }
            
            else if(starts_with(line, "Binary files"))
            {
                diff->fileType = Diff::FILETYPE_BINARY;
            }
            
            else if(starts_with(line, "--- a/"))
            {
                diff->setFileNameA( line.erase(0, 6) );
            }
            
            else if(starts_with(line, "+++ b/"))
            {
                diff->setFileNameB( line.erase(0, 6) );
            }            
        }
        
        
        //Start a new hunk in the current diff
        if(starts_with(line, "@@ "))
        {            
            //Creates a new diffHunk to store changed lines
            boost::shared_ptr<DiffHunk> diffHunkPtr(new DiffHunk());
            diffHunk = diffHunkPtr;
            diff->addDiffHunk(diffHunk);
            
            //Splits hunk header into startPos/numLines and endPos/numLines
            vector<string> splitLine;
            split(splitLine, line, is_any_of(" ,"));
            
            string preLines = Utils::checkStrIndexInRange(splitLine, 1, true ).erase(0,1);
            string numPreLines = Utils::checkStrIndexInRange(splitLine, 2, true );
            string postLines = Utils::checkStrIndexInRange(splitLine, 3, true ).erase(0,1);
            string numPostLines = Utils::checkStrIndexInRange(splitLine, 4, true );
            
            diffHunk->setPreChangedLines(atoi( preLines.c_str() ), atoi( numPreLines.c_str() ));
            diffHunk->setPostChangedLines(atoi( postLines.c_str() ), atoi( numPostLines.c_str() ));
            diffHunk->setLinePos( atoi( postLines.c_str() ) );
            diffHunk->setOldLinePos( atoi( preLines.c_str() ) );
            
            inDiffHeader = false;
        }
        
        //Already in an existing hunk, add current line
        else {
            if(!inDiffHeader){
                
                Line cLine(line);
                    
                //If the line is to be removed, stick with the old line position
                if(cLine.getLineState() == Line::LINE_ADDED || cLine.getLineState() == Line::LINE_NORMAL ) cLine.setLinePos(diffHunk->getLinepos());
                if(cLine.getLineState() == Line::LINE_DELETED) cLine.setLinePos(diffHunk->getOldLinePos());

                diffHunk->addLine(cLine);
                
                //If the line is an addition or unchanged, then we can move the hunk line position forwards
                if(cLine.getLineState() == Line::LINE_ADDED || cLine.getLineState() == Line::LINE_NORMAL) diffHunk->incrementLinePos();
                if(cLine.getLineState() == Line::LINE_DELETED || cLine.getLineState() == Line::LINE_NORMAL) diffHunk->incrementOldLinePos();
            }
        }
    }
    
    //Sort deltas into add/remove categories
    for(int j = 0; j < diffList.size(); j++) diffList[j]->updateDeltaLists();
    
    return diffList;
}


void GitLogParser::dumpDiffOutput(vector<Commit> commitList, string path){
    //Test of the commit serializer
    ofstream diffOutput;
    diffOutput.open(path.c_str());
    
    for(int i = 0; i < commitList.size(); i++) {
        diffOutput << GitLogParser::serializeCommit(commitList[i]);
    }
    
    //Close the file
    diffOutput.close();
}


string GitLogParser::serializeCommit(Commit commit)
{
    stringstream commitText;
    commitText << "/***=== Commit begins" << endl;
    
    commitText << "|== Commit hash: " << commit.commitHash << endl;
    commitText << "|== Author: " << commit.author << endl;
    commitText << "|== Date: " << commit.date << endl;
    commitText << "|== Message: " << commit.message << endl << endl;
    
    for(int i = 0; i < commit.getNumDiffs(); i++){
        boost::shared_ptr<Diff> diff = commit.getDiff(i);
        commitText << "|/=== Diff File: " << diff->getFileName() << endl;
        
        for(int j = 0; j < diff->getNumHunks(); j++){
            boost::shared_ptr<DiffHunk> diffHunk = diff->getDiffHunk(j);
            commitText << "||/--- Code hunk begins at line " << diffHunk->getPostBlockStart() << endl;
            
            for(int k = 0; k < diffHunk->getNumLines(); k++){
                Line strLine = diffHunk->getLine(k);
                if(strLine.getLineState() == Line::LINE_ADDED) commitText << "|| " << diffHunk->getLine(k).getLinePos() << "+ " << diffHunk->getLine(k).getStr() << endl;
                else if(strLine.getLineState() == Line::LINE_DELETED) commitText << "||r" << diffHunk->getLine(k).getLinePos() << "- " << diffHunk->getLine(k).getStr() << endl;
                else if(strLine.getLineState() == Line::LINE_NORMAL) commitText << "|| " << diffHunk->getLine(k).getLinePos() << " " << diffHunk->getLine(k).getStr() << endl;
            }
            
            commitText << "||\\--- Code hunk ends" << endl;
        }
        commitText << "|\\=== Diff Finish" << endl << endl;
    }
    commitText << "\\***=== Commit ends" << endl << endl << endl;
    
    return commitText.str();
}
