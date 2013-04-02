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
    vector<Line> originalLines = file->getLines();
    vector<Line> newLines;
    
    int linePos = 0;
    int deltaLinePos = 0;
    int deltaIndex = 0;
    
    //Iterate over the original lines, removing or adding lines that match in the diff
    for(int lineNum = 0; lineNum < originalLines.size() + diff->getNumDeltaLines(); lineNum++){
        
        Line oldLine = originalLines[lineNum];
        vector<Line> deltaLines = diff->getAllDeltaLines();
        
      
        if(oldLine.getLinePos() == deltaLines[deltaIndex].getLinePos() &&  deltaLines[deltaIndex].getLineState() == Line::LINE_DELETED){
            linePos++;
            deltaIndex++;
        }
        
        //Always increment the old line position so we get the correct original line number
        
        linePos++;
        
        
        //IF Line is added -> DON'T increment oldLinePos, DO increment deltaLinePos
        //IF Line is removed -> DO increment oldLinePos, DON'T increment deltaLinePos



//        if(strcmp(cLine.getStr().c_str(), oldLine.c_str()) && cLine.getLineState() == Line::LINE_DELETED){
//            linePos++;
//        } else if() {
//            
//        }
        
        
    }
    
    
    
}
