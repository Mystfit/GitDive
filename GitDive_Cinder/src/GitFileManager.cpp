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

void GitFileManager::updateFilesFromCommit(Commit &commit){
    
    boost::shared_ptr<GitFile> file;
    
    for(int i = 0; i < commit.getNumDiffs(); i++){
                
        boost::shared_ptr<Diff> diff = commit.getDiff(i);
                
        if(diff->fileMode == Diff::FILEMODE_ADDED){
            file = boost::shared_ptr<GitFile>(new GitFile(diff->getFileName()));
            m_fileList.push_back(file);
        }
        
        else if(diff->fileMode == Diff::FILEMODE_DELETED){
            file = getFileByName(diff->getFileName());
            file->setInactive();
        }
        
        else if(diff->fileMode == Diff::FILEMODE_UPDATED){
            file = getFileByName(diff->getFileName());
            if(file){
                if(file->active()){
                    applyDiffToFile(file, diff);
                }
            }
        }
        
    }
}


boost::shared_ptr<GitFile> GitFileManager::getFileByName(string fileName){
    for(int i = 0; i < m_fileList.size(); i++){
        if(m_fileList[i]->getFilename() == fileName) return m_fileList[i];
    }
    
    return boost::shared_ptr<GitFile>();
}


void GitFileManager::applyDiffToFile(boost::shared_ptr<GitFile> file, boost::shared_ptr<Diff> diff){
    
    //Make a copy of the original lines
    vector<Line> originalLines = file->getLines();
    vector<Line> deltaLines = diff->getAllDeltaLines();
    vector<Line> newLines;
    
    int linePos = 1;
    int deltaIndex = 0;
    
    //If there are no original lines we dump all the new lines straight into the file
    if(originalLines.size() == 0){
        cout << "-- Dumping lines traight into new file" << endl;
        file->setLines(deltaLines);
        return;
    }
        
    //Iterate over the original lines, removing or adding lines that match in the diff
    for(int lineNum = 1; lineNum <= originalLines.size() + diff->getNumDeltaLines(); lineNum++){
        
        if(originalLines[linePos-1]) cout << "-line no:" << linePos << " " << originalLines[linePos-1].getStr() << endl;
        Line oldLine = originalLines[linePos-1];
              
        //Skip over lines if line is marked for removal
        if(oldLine.getLinePos() == deltaLines[deltaIndex].getLinePos() && deltaLines[deltaIndex].getLineState() == Line::LINE_DELETED){
            linePos++;
            deltaIndex++;
        }
        
        //Add new lines to list
        else if(deltaLines[deltaIndex].getLinePos() == lineNum && deltaLines[deltaIndex].getLineState() == Line::LINE_ADDED){
            newLines.push_back(deltaLines[lineNum]);
            deltaIndex++;
        }
        
        //Add unmodified lines
        else {
            oldLine.setLinePos(lineNum);
            newLines.push_back(oldLine);
        }
        
        //Always increment the old line position so we get the correct original line number
        linePos++;        
    }
    
    file->setLines(newLines);
}


string GitFileManager::serializeAllFiles(){
    stringstream fileText;
    
    for(int i = 0; i < m_fileList.size(); i++){
        fileText << serializeFile(m_fileList[i]) << endl;
    }
    
    return fileText.str();
}

string GitFileManager::serializeFile(boost::shared_ptr<GitFile> file){
    stringstream fileText;
    vector<Line> lines = file->getLines();
    
    for(int i = 0; i < lines.size(); i++){
        fileText << lines[i].getStr() << endl;
    }
    
    return fileText.str();
}
