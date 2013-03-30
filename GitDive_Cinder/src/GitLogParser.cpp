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
            boost::split(logVars, line, boost::is_any_of("^"));
            
            vector<string> hashStrings;
            boost::split(hashStrings, logVars[0], boost::is_any_of("&"));
            
            vector<string> authorStrings;
            boost::split(authorStrings, logVars[1], boost::is_any_of("&"));
            
            vector<string> dateStrings;
            boost::split(dateStrings, logVars[2], boost::is_any_of("&"));
            
            vector<string> messageStrings;
            boost::split(messageStrings, logVars[3], boost::is_any_of("&"));
            
        
            //Split variable headers from data for git variables
            string commitHash;
            string commitAuthor;
            string commitDate;
            string commitMessage;
            
            if(hashStrings.size()>1) commitHash = hashStrings[1];
            if(authorStrings.size()>1) commitAuthor= authorStrings[1];
            if(dateStrings.size()>1) commitDate = dateStrings[1];
            if(messageStrings.size()>1) commitMessage = messageStrings[1];
            
            Commit commit(commitHash, commitAuthor, commitDate, commitMessage);
        } else {
            
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
