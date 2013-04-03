//
//  GitFileManager.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 1/04/13.
//
//

#include "GitFileManager.h"

GitFileManager::GitFileManager(){
    m_commitIndex = 0;
}

void GitFileManager::updateFilesFromCommit(Commit &commit){
    
    boost::shared_ptr<GitFile> file;
    
    for(int i = 0; i < commit.getNumDiffs(); i++){
                
        boost::shared_ptr<Diff> diff = commit.getDiff(i);
                
        if(diff->fileMode == Diff::FILEMODE_ADDED){
            file = boost::shared_ptr<GitFile>(new GitFile(diff->getFileName()));
            applyDiffToFile(*(file), diff);
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
                    applyDiffToFile(*(file), diff);
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


bool GitFileManager::applyNextCommit(){
    if(m_commitIndex < m_commitList.size()) {
        updateFilesFromCommit(m_commitList[m_commitIndex]);
        m_commitIndex++;
        return true;
    }
    
    cout << "-->Out of commits!" << endl;
    
    return false;
}



void GitFileManager::applyDiffToFile(GitFile &file, boost::shared_ptr<Diff> diff){
    
    //Make a copy of the original lines
    vector<Line> originalLines = file.getLines();
    vector<Line> deltaAddLines = diff->getDeltaAddLines();
    vector<Line> deltaRemoveLines = diff->getDeltaRemoveLines();
    vector<Line> interimLines = originalLines;
    vector<Line> newLines;
    
    //If the file is blank/new, only dump in all the new lines
    if(originalLines.size() < 1){
        cout << endl << "===Creating new file " << diff->getFileName() << endl << endl;
        for(int i = 0; i < deltaAddLines.size(); i++) deltaAddLines[i].setLinePos(i+1);
        
        file.setLines(deltaAddLines);
        return;
    }
    
    int deltaIndex = 0;
    bool blockOpen;
    int removeStart = 0;
    int removeEnd = 0;
    
    
    //Move through existing lines and strip out lines that match the deltaRemove list
    if(deltaRemoveLines.size() > 0){
        for(int i = 0; i < deltaRemoveLines.size(); i++){
            int pos = deltaRemoveLines[i].getLinePos()- deltaIndex - 1;
            if(pos < interimLines.size()){
                interimLines.erase(interimLines.begin() + pos);
                removeStart = 
                
            } else if(blockOpen) {
                blockOpen = false;
            }
            deltaIndex++;
        }
    }

    //Reset counters
    deltaIndex = 0;
    int lineCounter = 0;
    
    //Add lines
    if(deltaAddLines.size() == 0){
        newLines = interimLines;
    } else {
        for(int lineNum = 1; lineNum <= interimLines.size() + deltaAddLines.size(); lineNum++ ){
            
            if(deltaIndex < deltaAddLines.size() && deltaAddLines[deltaIndex].getLinePos() == lineNum){
                newLines.push_back(deltaAddLines[deltaIndex]);
                deltaIndex++;
            } else {
                Line oldLine = interimLines[lineCounter++];
                oldLine.setLinePos(lineNum);
                newLines.push_back(oldLine);
            }
        }
        
        //If we've run out of source lines, add the remaining delta lines to the end
        if(deltaIndex < deltaAddLines.size()){
            for(int leftovers = deltaIndex; leftovers < deltaAddLines.size() - deltaIndex; leftovers++){
                newLines.push_back(deltaAddLines[deltaIndex++]);
            }
        }
    }
    
    //Reset the file with the new lines
    file.setLines(newLines);
}


void GitFileManager::dumpFileOutput(string path){
    ofstream fileOutput;
    fileOutput.open(path.c_str());
    fileOutput << serializeAllFiles();
    fileOutput.close();
}


void GitFileManager::dumpAllFiles(string path){
    for(int i = 0; i < m_fileList.size(); i++){
        saveFileToDisk(m_fileList[i], path);
    }
}


void GitFileManager::saveFileToDisk(boost::shared_ptr<GitFile> file, string path){
    ofstream fileOutput;
    vector<Line> lines = file->getLines();
    
    string fileName = file->getFilename();
    vector<string> splitLine;
    split(splitLine, fileName, boost::is_any_of("/."));
    
    fileName = Utils::checkStrIndexInRange(splitLine, splitLine.size()-2) + "." + Utils::checkStrIndexInRange(splitLine, splitLine.size()-1);
    string finalPath = path + "/" + fileName;
    cout << "-->Saving file as " << finalPath << endl;
    
    fileOutput.open(finalPath.c_str());
    for(int i = 0; i < lines.size(); i++){
        fileOutput << lines[i].getStr() << endl;
    }
    fileOutput.close();
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
    fileText << "/***======== File: " << file->getFilename() << endl;
    vector<Line> lines = file->getLines();
    
    for(int i = 0; i < lines.size(); i++){
        fileText << lines[i].getStr() << endl;
    }
    fileText << "\\***=========================" << file->getFilename() << endl;
    
    return fileText.str();
}
