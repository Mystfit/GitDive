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
    
            //Split line into seperate strings to pull out git info
            Utils::strip(line, "\n");
                        
            vector<string> logVars;
            vector<string> strVars;

            boost::split(logVars, line, boost::is_any_of("^"));
            
            for(int j = 0; j < logVars.size(); j++){
                vector<string> logVarsSplit;
                boost::split(logVarsSplit, logVars[j], boost::is_any_of("&"));
                strVars.push_back( Utils::checkStrIndexInRange(logVarsSplit, 1) );
                cout << strVars[j] << endl;
            }
            
            if(commitList.size() > 0){
                Diff diff;
                commitList[commitList.size()-1].addDiff()
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
    vector<Diff> diffList;
    
    return diffList;
}

string GitLogParser::serializeCommit(Commit commit)
{
    return commit.commitHash;
}
