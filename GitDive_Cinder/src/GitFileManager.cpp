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
    vector<Line> deltaAddLines = diff->getDeltaAddLines();
    vector<Line> deltaRemoveLines = diff->getDeltaRemoveLines();
    vector<Line> interimLines;
    vector<Line> newLines;
    
    if(originalLines.size() < 1){
        file->setLines(deltaAddLines);
        return;
    }
    
    int linePos = 1;
    int deltaIndex = 0;
    
    cout << "Num Add lines:" << deltaAddLines.size() << " Num remove lines:" << deltaRemoveLines.size() << endl;
    
    //Remove lines first
    if(deltaRemoveLines.size() < 1){
        interimLines = originalLines;
    } else {
        for(int lineNum = 1; lineNum < originalLines.size() - deltaRemoveLines.size(); lineNum++ ){
            Line origLine = originalLines[lineNum];
            
            if(deltaRemoveLines[deltaIndex].getLinePos() != linePos){
                interimLines.push_back(origLine);
                deltaIndex++;
                linePos++;
            }
            
            linePos++;
        }
    }
    
    //Reset counters
    linePos = 1;
    deltaIndex = 0;
    
    cout << "Num lines (minus removed):" << interimLines.size() << " Num lines(with added):" << interimLines.size() + deltaAddLines.size() << endl;
    
    //Add lines second;
    if(deltaAddLines.size() < 1){
        newLines = interimLines;
    } else {
        for(int lineNum = 1; lineNum < interimLines.size() + deltaAddLines.size(); lineNum++ ){
            
            
            
            if(deltaAddLines[deltaIndex].getLinePos() == linePos){
                newLines.push_back(deltaAddLines[deltaIndex]);
                deltaIndex++;
            } else {
                newLines.push_back(interimLines[linePos]);
                linePos++;
            }
        }
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
