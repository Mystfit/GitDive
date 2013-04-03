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
        
    if(originalLines.size() < 1){
        cout << endl << "===Creating new file " << diff->getFileName() << endl << endl;
        for(int i = 0; i < deltaAddLines.size(); i++) deltaAddLines[i].setLinePos(i);
        
        file.setLines(deltaAddLines);
        return;
    }
    
    int deltaIndex = 0;
    
    cout << "--File:" << diff->getFileName() << endl;
    cout << "--Num Add lines:" << deltaAddLines.size() << " Num remove lines:" << deltaRemoveLines.size() << endl;
        
    if(deltaRemoveLines.size() > 0){
        for(int i = 0; i < deltaRemoveLines.size(); i++){
            int pos = deltaRemoveLines[i].getLinePos()- deltaIndex - 1;
            cout << "R actual:" << deltaRemoveLines[i].getLinePos() << " Index:"  << pos << " Remaining:" << interimLines.size() << " Line||" << deltaRemoveLines[i].getStr()  << endl;
            if(pos < interimLines.size()) interimLines.erase(interimLines.begin() + pos);
            deltaIndex++;
        }
    }
    

    //Reset counters
    int linePos = 0;
    deltaIndex = 0;
    string line;
    
    cout << "--Removed lines. Orig Size:" << originalLines.size() << " Num lines (minus removed):" << interimLines.size() << " Num lines(with added):" << interimLines.size() + deltaAddLines.size() << endl;
    cout << "--Lines to add:" << deltaAddLines.size() << endl;
    
    //Add lines second;
    if(deltaAddLines.size() < 1){
        newLines = interimLines;
    } else {
        for(int lineNum = 1; lineNum <= interimLines.size(); lineNum++ ){
            
//            cout << endl << "---Delta index:" << deltaIndex << " Line index:" << linePos << " Line num:" << lineNum << " Source size:" << interimLines.size() << " Search size:" << interimLines.size() + deltaAddLines.size();
            
            if(deltaIndex < deltaAddLines.size() && deltaAddLines[deltaIndex].getLinePos() + deltaIndex == linePos+1){
//                cout << " !!!Matched lines A:" << linePos+1 << " B:" << deltaAddLines[deltaIndex].getLinePos();
                newLines.push_back(deltaAddLines[deltaIndex]);
                deltaIndex++;
            }
            
            
            newLines.push_back(interimLines[linePos]);
            linePos++;
            
            //If we've run out of source lines, add the remaining delta lines to the end
            if(lineNum == interimLines.size()){
                cout << "--Adding " << deltaAddLines.size() - deltaIndex << " lines to the end of the file" << endl;
                for(int leftovers = deltaIndex; leftovers < deltaAddLines.size() - deltaIndex; leftovers++){
                    newLines.push_back(deltaAddLines[deltaIndex++]);
                }
            }
        }
    }
    
    cout << endl << "==Final file" << endl;
    for(int i = 0; i < newLines.size(); i++){
        newLines[i].setLinePos(i+1);
        cout << "--i:" << i << " Mode:" << newLines[i].getLineState() << " LineNum:" << newLines[i].getLinePos() <<  " Line ||" << newLines[i].getStr() << endl;
    }
    cout << "=====" << endl << endl;

    
    file.setLines(newLines);
    file.resetLineOrder();    
}


void GitFileManager::saveFileToDisk(boost::shared_ptr<GitFile> file, string path){
    ofstream fileOutput;
    vector<Line> lines = file->getLines();
    
    fileName = file->getFilename();
    
    fileOutput.open(path);
    for(int i = 0; i <   lines.size(); i++){
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
