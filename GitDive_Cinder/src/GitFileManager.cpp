//
//  GitFileManager.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#include "GitFileManager.h"

GitFileManager::GitFileManager(){
    
}

void GitFileManager::addFile(GitFile file){
    
}


boost::shared_ptr<GitFile> GitFileManager::getFileByName(string fileName){
    for(int i = 0; i < m_fileList.size(); i++){
        if(m_fileList[i]->filename == fileName) return m_fileList[i];
    }
    
    return boost::shared_ptr<GitFile>();
}

void GitFileManager::applyDiffToFile(boost::shared_ptr<GitFile> file, boost::shared_ptr<Diff> diff){
    
    //Make a copy of the original lines
    vector<string> originalLines = file->getLines();
    
    
    //Iterate over the original lines, removing or adding lines that match in the diff
    for(int lineNum = 0; lineNum < originalLines.size(); lineNum++){
        
    }
    
    for(int i = 0; i < diff->getNumHunks(); i++){
        shared_ptr<DiffHunk> diffHunk = diff->getDiffHunk(i);
        
        for(int j = 0; j < diffHunk->getNumLines(); j++)
        {
            Line cLine = diffHunk->getLine(j);
        }
    }
    
}
