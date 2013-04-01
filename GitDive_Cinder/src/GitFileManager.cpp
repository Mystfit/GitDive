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

void GitFileManager::applyDiffToFile(boost::shared_ptr<GitFile>, boost::shared_ptr<Diff> diff){
    
    for(int i = 0; i < diff->getNumHunks(); i++){
        shared_ptr<DiffHunk> diffHunk = diff->getDiffHunk(i);
        
        for(int j = 0; j < diffHunk->getNumLines(); j++)
        {
            Line cLine = diffHunk->getLine(j);
        }
    }
    
}
