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
        
        if(boost::starts_with(line, "GD_commit")){
            
            //Parse last commit first with the lines between the last GD_commit line
            if(commitList.size() > 0){            
                commitList[commitList.size()-1].addDiffList( parseCommit(diffBlock) );
            }
    
            //Split commit line into key/pair values
            Utils::strip(line, "\n");
                        
            vector<string> logVars;
            vector<string> strVars;

            boost::split(logVars, line, boost::is_any_of("^"));
            
            //Split git log message into component variables
            for(int j = 0; j < logVars.size(); j++){
                vector<string> logVarsSplit;
                boost::split(logVarsSplit, logVars[j], boost::is_any_of("&"));
                strVars.push_back( Utils::checkStrIndexInRange(logVarsSplit, 1) );
            }
            
            commitList.push_back( Commit(strVars[0], strVars[1], strVars[2], strVars[3]) );
        } else {
            diffBlock.push_back(line);
        }
        
    }
    
    return commitList;
}


vector<Diff> GitLogParser::parseCommit(vector<string> diffBlock)
{
    bool inDiffHeader = false;
    vector<Diff> diffList;
    Diff diff;
    DiffHunk diffHunk;
    
    for(int i = 0; i < diffBlock.size(); i++){
        
        string line = diffBlock[i];
        
        //Start a new diff object when a diff command is found
        if(boost::starts_with(line, "diff --git")){
            inDiffHeader = true;
            
            //Add last diff to the list
            if(i > 0) diffList.push_back(diff);
            diff = Diff();
            
            //Move through the header and set up the diff object from the parsed diff vars
            if(inDiffHeader){
                if(boost::starts_with(line, "index"))
                {
                }
                
                else if(boost::starts_with(line, "new file mode"))
                {
                    diff.fileMode = "added";
                }
                
                else if(boost::starts_with(line, "deleted file mode"))
                {
                    diff.fileMode = "deleted";
                }
                
                else if(boost::starts_with(line, "Binary files"))
                {
                    diff.fileType = "binary";
                }
                
                else if(boost::starts_with(line, "--- a/"))
                {
                    diff.setFileNameA( line.erase(0, 6) );
                }
                
                else if(boost::starts_with(line, "+++ b/"))
                {
                    diff.setFileNameB( line.erase(0, 6) );
                }
            }
            
            //Start a new hunk in the current diff
            if(boost::starts_with(line, "@@ "))
            {
                inDiffHeader = false;
                
                
                
            }
            
            //Already in an existing hunk, add current line
            else {
                if(!inDiffHeader){
                    diffHunk.addLine(line);
                }
            }
        }
        
        
                
        diffList.push_back(diff);
    }
    
    return diffList;
}

string GitLogParser::serializeCommit(Commit commit)
{
    return commit.commitHash;
}
