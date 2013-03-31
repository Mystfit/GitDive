//
//  GitLogParser.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitLogParser.h"

vector<Commit> GitLogParser::parseLog(vector<string> diffLog)
{
    vector<Commit> commitList;
    vector <string> diffBlock;
    
    for(int i = 0; i < diffLog.size(); i++)
    {
        string line = diffLog[i];
        
        if(starts_with(line, "GD_commit")){
            
            //Parse last commit first with the lines between the last GD_commit line
            if(commitList.size() > 0){            
                commitList[commitList.size()-1].addDiffList( parseCommit(diffBlock) );
            }
    
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
            
            commitList.push_back( Commit(strVars[0], strVars[1], strVars[2], strVars[3]) );
        } else {
            diffBlock.push_back(line);
        }
        
    }
    
    return commitList;
}


vector< shared_ptr<Diff> > GitLogParser::parseCommit(vector<string> diffBlock)
{
    bool inDiffHeader = false;
    vector< shared_ptr<Diff> > diffList;
    shared_ptr<Diff> diff(new Diff());
    shared_ptr<DiffHunk> diffHunk(new DiffHunk());
    
    for(int i = 0; i < diffBlock.size(); i++){
        
        string line = diffBlock[i];
        
        //Start a new diff object when a diff command is found
        if(starts_with(line, "diff --git")){
            inDiffHeader = true;
            
            //Create new diff container
            shared_ptr<Diff> diffPtr(new Diff());
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
                diff->fileMode = "added";
            }
            
            else if(starts_with(line, "deleted file mode"))
            {
                diff->fileMode = "deleted";
            }
            
            else if(starts_with(line, "Binary files"))
            {
                diff->fileType = "binary";
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
            shared_ptr<DiffHunk> diffHunkPtr(new DiffHunk());
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
            
            inDiffHeader = false;
        }
        
        //Already in an existing hunk, add current line
        else {
            if(!inDiffHeader){
                diffHunk->addLine(line);
            }
        }
                
        diffList.push_back(diff);
    }
    
    return diffList;
}


string GitLogParser::serializeCommit(boost::shared_ptr<Commit> commit)
{
    string commitText = "/***=== Commit begins\n";
    
    commitText += "|== Commit hash: " + commit->commitHash + "\n";
    commitText += "|== Author: " + commit->author + "\n";
    commitText += "|== Date: " + commit->date + "\n";
    commitText += "|== Message: " + commit->message + "\n\n";
    
    for(int i = 0; i < commit->getNumDiffs(); i++){
        shared_ptr<Diff> diff = commit->getDiff(i);
        commitText += "|/=== Diff File: " + diff->getFileName() + "\n";
        
        for(int j = 0; j < diff->getNumHunks(); j++){
            shared_ptr<DiffHunk> diffHunk = diff->getDiffHunk(j);
            commitText += "||/--- Code hunk begins\n";
            
            for(int k = 0; k < diffHunk->getNumLines(); k++){
                commitText += "|| " + diffHunk->getLine(k);
            }
            
            commitText += "||\\--- Code hunk ends\n";
        }
        commitText += "|\\=== Diff Finish\n";
    }
    commitText += "\\***=== Commit ends\n\n\n";
    
    return commitText;
}
