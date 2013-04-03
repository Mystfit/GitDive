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
    
    cout << endl << "--File:" << diff->getFileName() << endl;
    cout << "--Num Add lines:" << deltaAddLines.size() << " Num remove lines:" << deltaRemoveLines.size() << endl;
    
    cout << "--Lines to remove" << endl;
    for(int i = 0; i < deltaRemoveLines.size(); i++){
        cout << "Ln no:" << deltaRemoveLines[i].getLinePos() << " " << deltaRemoveLines[i].getLineStateSymbol() << "|" << deltaRemoveLines[i].getStr() << endl;
    }
    
    cout << endl << "--Lines to add" << endl;
    for(int i = 0; i < deltaAddLines.size(); i++){
        cout << "Ln no:" << deltaAddLines[i].getLinePos() << " " << deltaAddLines[i].getLineStateSymbol() << "|" << deltaAddLines[i].getStr() << endl;
    }
    
    cout << endl << "--Before line removal" << endl;
    for(int i = 0; i < interimLines.size(); i++){
        cout << "Ln no:" << interimLines[i].getLinePos() << " " << interimLines[i].getLineStateSymbol() << "|" << interimLines[i].getStr() << endl;
    }

    
    //Move through existing lines and strip out lines that match the deltaRemove list
    if(deltaRemoveLines.size() > 0){
        for(int i = 0; i < deltaRemoveLines.size(); i++){
            int pos = deltaRemoveLines[i].getLinePos()- deltaIndex - 1;
            if(pos < interimLines.size()) interimLines.erase(interimLines.begin() + pos);
            deltaIndex++;
        }
    }
    
    cout << endl << "--After line removal" << endl;
    for(int i = 0; i < interimLines.size(); i++){
        cout << "Ln no:" << interimLines[i].getLinePos() << " " << interimLines[i].getLineStateSymbol() << "|" << interimLines[i].getStr() << endl;
    }
    

    //Reset counters
    deltaIndex = 0;
    
    //Add lines second;
    if(deltaAddLines.size() < 1){
        newLines = interimLines;
    } else {
        for(int lineNum = 1; lineNum <= interimLines.size(); lineNum++ ){
            
            if(deltaIndex < deltaAddLines.size() && deltaAddLines[deltaIndex].getLinePos() + deltaIndex == lineNum){
//              cout << " !!!Matched lines A:" << linePos+1 << " B:" << deltaAddLines[deltaIndex].getLinePos();
                newLines.push_back(deltaAddLines[deltaIndex]);
                deltaIndex++;
            }
            
            newLines.push_back(interimLines[lineNum-1]);
        }
        
        //If we've run out of source lines, add the remaining delta lines to the end
        if(deltaIndex < deltaAddLines.size()){
            for(int leftovers = deltaIndex; leftovers < deltaAddLines.size() - deltaIndex; leftovers++){
                newLines.push_back(deltaAddLines[deltaIndex++]);
            }
        }
    }
    
    cout << endl << "--After line addition" << endl;
    for(int i = 0; i < interimLines.size(); i++){
        cout << "Ln no:" << interimLines[i].getLinePos() << " " << interimLines[i].getLineStateSymbol() << "|" << interimLines[i].getStr() << endl;
    }

    
    file.setLines(newLines);
    file.resetLineOrder();    
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
