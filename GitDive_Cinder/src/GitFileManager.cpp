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
    vector<FileChangeBlock> fileChanges;
    FileChangeBlock block;
    
    //Move through existing lines and strip out lines that match the deltaRemove list
    if(deltaRemoveLines.size() > 0){
        for(int i = 0; i < deltaRemoveLines.size(); i++){
            
            if(file.getFilename() == "gitSave.sh"){
                if(boost::starts_with(deltaRemoveLines[i].getStr(), "git commit --quiet -m")){
                    cout << "gitSave.sh" << endl;
                    vector<Line> unsortedDeltas = diff->getAllDeltaLines();
                    for(vector<Line>::iterator it = unsortedDeltas.begin(); it != unsortedDeltas.end() ++it){
                        
                    }
                }
            }
            
            
            
            int pos = deltaRemoveLines[i].getLinePos()- deltaIndex - 1;
            if(pos < interimLines.size()){
                //Erase the line from the file
                interimLines.erase(interimLines.begin() + pos);
                
           
                //Store the removed lines as a block of lines so we can keep the original structure of the file
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_DELETE;
                    block.blockStart = deltaRemoveLines[i].getLinePos();
                    block.blockEnd = deltaRemoveLines[i].getLinePos();
                    cout << endl << "RemoveBlock Start:" << block.blockStart << " |.";
                } else {
                    if(deltaRemoveLines[i].getLinePos() - block.blockEnd > 1){
                        fileChanges.push_back(block);
                        blockOpen = false;
                        cout << "| End:" << block.blockEnd << endl;
                    } else {
                        cout << ".";
                        block.blockEnd = deltaRemoveLines[i].getLinePos();
                    }
                }
            }
            deltaIndex++;
        }
        
        //Close the block if the last line is marked for removal
        if(blockOpen){
            fileChanges.push_back(block);
            blockOpen = false;
            cout << "| End:" << block.blockEnd << endl;
        }
    }
    
    
    //Reset counters
    deltaIndex = 0;
    int lineCounter = 0;
    blockOpen = false;
    
    //Add lines
    if(deltaAddLines.size() == 0){
        newLines = interimLines;
    } else {
        for(int lineNum = 1; lineNum <= interimLines.size() + deltaAddLines.size(); lineNum++ ){
            
            if(deltaIndex < deltaAddLines.size() && deltaAddLines[deltaIndex].getLinePos() == lineNum){
                newLines.push_back(deltaAddLines[deltaIndex]);
                
                //Save changes of lines added as blocks of line positions for animation
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_ADD;
                    block.blockStart = newLines.back().getLinePos();
                    block.blockEnd = newLines.back().getLinePos();
                    cout << "AddBlock Start:" << block.blockStart << " |.";
                } else {
                    if(newLines.back().getLinePos() - block.blockEnd > 1){
                        cout << "Diff:" << newLines.back().getLinePos() - block.blockEnd << endl;
                        fileChanges.push_back(block);
                        blockOpen = false;
                        cout << "| End:" << block.blockEnd << endl;
                    } else {
                        block.blockEnd = newLines.back().getLinePos();
                        cout << ".";
                    }
                }
                deltaIndex++;
            
            } else {
                Line oldLine = interimLines[lineCounter++];
                oldLine.setLinePos(lineNum);
                newLines.push_back(oldLine);
                
                //Close the file change block
                if(blockOpen){
                    fileChanges.push_back(block);
                    blockOpen = false;
                    cout << "| End:" << block.blockEnd << endl;
                }
            }
        }
        
        blockOpen = false;
        
        //If we've run out of source lines, add the remaining delta lines to the end
        if(deltaIndex < deltaAddLines.size()){
            
            if(file.getFilename() == "gitSave.sh") cout << "BING. " << file.getFilename() << " Leftover index:" << deltaIndex << " Size:" << deltaAddLines.size() << " Line|" << deltaAddLines[deltaIndex].getStr() << "!!!" << endl;
            
            for(int leftovers = deltaIndex; leftovers < deltaAddLines.size(); leftovers++){
                
                //Will definitely need a new filechange block on the end if dumping all the remaining lines
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_ADD;
                    block.blockStart = deltaAddLines[deltaIndex].getLinePos();
                    cout << "Final AddBlock Start:" << block.blockStart << " |";
                }
                
                cout << ".";
                block.blockEnd = deltaAddLines[deltaIndex].getLinePos();
                newLines.push_back(deltaAddLines[deltaIndex++]);
            }
        }
        
        //Close the block if the last line is marked for addition
        if(blockOpen){
            fileChanges.push_back(block);
            blockOpen = false;
            cout << "| End:" << block.blockEnd << endl;
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
    //cout << "-->Saving file as " << finalPath << endl;
    
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
