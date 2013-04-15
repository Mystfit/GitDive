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
    m_diffIndex = 0;
}


bool GitFileManager::updateSingleFile( boost::shared_ptr<Diff> diff, string targetFile ){

    boost::shared_ptr<GitFile> file;
    
    //If the target file doesn't match the file in the diff, exit
    if( targetFile.size() ){
        if(diff->getFileName() != targetFile) return false;
    }

    if(diff->fileMode == Diff::FILEMODE_ADDED){
        file = boost::shared_ptr<GitFile>(new GitFile(diff->getFileName()));
        applyDiffToFile(*(file), diff, bUseSyntaxHighlighting);
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
                applyDiffToFile(*(file), diff, bUseSyntaxHighlighting);
            }
        }
    }
    
    return true;
}



boost::shared_ptr<GitFile> GitFileManager::getFileByName(string fileName){
    for(int i = 0; i < m_fileList.size(); i++){
        if(m_fileList[i]->getFilename() == fileName) return m_fileList[i];
    }
    
    return boost::shared_ptr<GitFile>();
}




bool GitFileManager::applyNextDiff(){
    
    boost::shared_ptr<GitFile> file;
    
    cout << m_commitIndex << endl;
    
    if(m_commitIndex >= m_commitList.size()) return false;
    
    Commit & currentCommit = m_commitList[m_commitIndex];
    
    //Get the next diff in the commit
    if(m_diffIndex < currentCommit.getNumDiffs()){
        
        boost::shared_ptr<Diff> diff = currentCommit.getDiff(m_diffIndex);
        
        if(m_trackedFile != ""){
            bool foundFile;
            
            while(!foundFile){
                if(m_commitIndex < m_commitList.size()){
                    if(m_diffIndex < currentCommit.getNumDiffs()){
                        diff = currentCommit.getDiff(m_diffIndex);
                        
                        if(diff->getFileName() == m_trackedFile){
                            updateSingleFile(diff, m_trackedFile);
                            m_diffIndex++;
                            foundFile = true;
                            return true;
                        }
                        
                        m_diffIndex++;
                        
                    } else {
                        m_diffIndex = 0;
                        m_commitIndex++;
                    }
                } else {
                    break;
                }
            }
        } else {
            updateSingleFile(diff);
            m_diffIndex++;
            return true;
        }
        
    } else {
        if(m_commitIndex < m_commitList.size()) {
            cout << "-->Out of diffs for this commit. Moving to next." << endl;

            m_diffIndex = 0;
            m_commitIndex++;
        } else {
            cout << "-->Out of commits!" << endl;
        }
    }
    
    return false;
    
    //ITS NO USE
    //m_tRender->animLinesIn(file->getLines());
    //m_tRender->setLinesAnimatable();
}


bool GitFileManager::applyNextCommit(){
    if(m_commitIndex < m_commitList.size()) {
        for(int i = 0; i < m_commitList[m_commitIndex].getNumDiffs(); i++){
            
            boost::shared_ptr<Diff> diff = m_commitList[m_commitIndex].getDiff(i);
            updateSingleFile(diff);
            
            m_diffIndex++;
            
            //ITS NO USE
            //m_tRender->animLinesIn(file->getLines());
            //m_tRender->setLinesAnimatable();
        }
        m_diffIndex = 0;
        m_commitIndex++;
        
        return true;
    }
    
    cout << "-->Out of commits!" << endl;
    return false;
}


void GitFileManager::reset(){
    m_commitIndex = 0;
    m_fileList.clear();
}


void GitFileManager::applyDiffToFile(GitFile &file, boost::shared_ptr<Diff> diff, bool useSyntaxHighlighting){
    
    //Make a copy of the original lines
    //vector< boost::shared_ptr <Line> > originalLines = file.getLines();
    vector< boost::shared_ptr <Line> > newLines;
    vector<Line> deltaAddLines = diff->getDeltaAddLines();
    vector<Line> deltaRemoveLines = diff->getDeltaRemoveLines();
    
    //If the file is blank/new, only dump in all the new lines
    if(file.getLines().size() < 1){
        cout << endl << "===Creating new file " << diff->getFileName() << endl << endl;
        for(int i = 0; i < deltaAddLines.size(); i++) {
            
            //Create new line pointer
            boost::shared_ptr<Line> newLine( new Line(deltaAddLines[i].getStr(), true) );
            newLine->setLinePos(i+1);
            newLines.push_back(newLine);            
        }
        
        file.setLines(newLines);
        return;
    }
    
    int deltaIndex = 0;
    bool blockOpen = false;
    vector<FileChangeBlock> fileChanges;
    FileChangeBlock block;
    
    //Move through existing lines and strip out lines that match the deltaRemove list
    if(deltaRemoveLines.size() > 0){
        for(int i = 0; i < deltaRemoveLines.size(); i++){
            
            int pos = deltaRemoveLines[i].getLinePos()- deltaIndex - 1;
            if(pos < file.getLines().size()){
                
                //Erase the line from the file
                file.getLines()[i]->markForRemoval();
                
                //Only break lines on the actively drawing file
                if(file.getFilename().size()){
                    if(m_tRender->getTargetFile()){
                        if(file.getFilename() == m_tRender->getTargetFile()->getFilename() ) {
                            m_tRender->breakLine(file.getLines()[i]);
                        }
                    }
                }
                file.getLines().erase(file.getLines().begin() + pos);
                
                //Store the removed lines as a block of lines so we can keep the original structure of the file
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_DELETE;
                    block.blockStart = deltaRemoveLines[i].getLinePos();
                    block.blockEnd = deltaRemoveLines[i].getLinePos();
                } else {
                    if(deltaRemoveLines[i].getLinePos() - block.blockEnd > 1){
                        fileChanges.push_back(block);
                        blockOpen = false;
                    } else {
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
        }
    }
    
    
    //Reset counters
    deltaIndex = 0;
    int lineCounter = 0;
    blockOpen = false;
    
    //Add lines
    if(deltaAddLines.size() == 0){
        newLines = file.getLines();
    } else {
        for(int lineNum = 1; lineNum <= file.getLines().size() + deltaAddLines.size(); lineNum++ ){
            
            if(deltaIndex < deltaAddLines.size() && deltaAddLines[deltaIndex].getLinePos() == lineNum){
                
                //Create new line pointer
                boost::shared_ptr<Line> newLine( new Line(deltaAddLines[deltaIndex].getStr(), true) );
                newLine->setLinePos(deltaAddLines[deltaIndex].getLinePos());
                newLine->setLineState(Line::LINE_ADDED);
                newLines.push_back(newLine);
                
                //Save changes of lines added as blocks of line positions for animation
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_ADD;
                    block.blockStart = newLines.back()->getLinePos();
                    block.blockEnd = newLines.back()->getLinePos();
                }
                
                if(newLines.back()->getLinePos() - block.blockEnd > 1){
                    fileChanges.push_back(block);
                    blockOpen = false;
                } else {
                    block.blockEnd = newLines.back()->getLinePos();
                }
            
                deltaIndex++;
            
            } else {
                boost::shared_ptr<Line> oldLine = file.getLines()[lineCounter];
                oldLine->setLinePos(lineNum);
                oldLine->setLineState(Line::LINE_NORMAL);
                newLines.push_back(oldLine);
                lineCounter++;
                
                //Close the file change block
                if(blockOpen){
                    fileChanges.push_back(block);
                    blockOpen = false;
                }
            }
        }
        
        if(blockOpen){
            fileChanges.push_back(block);
            blockOpen = false;
        }
        
        //If we've run out of source lines, add the remaining delta lines to the end
        if(deltaIndex < deltaAddLines.size()){
            
            for(int leftovers = deltaIndex; leftovers < deltaAddLines.size(); leftovers++){
                
                //Will definitely need a new filechange block on the end if dumping all the remaining lines
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_ADD;
                    block.blockStart = deltaAddLines[deltaIndex].getLinePos();
                }
                
                block.blockEnd = deltaAddLines[deltaIndex].getLinePos();
                
                //Create new line pointer
                boost::shared_ptr<Line> newLine( new Line(deltaAddLines[deltaIndex++].getStr(), true) );
                newLine->setLineState(Line::LINE_ADDED);
                newLine->setLinePos(deltaAddLines[deltaIndex].getLinePos());
                newLines.push_back(newLine);
            }
        }
        
        //Close the block if the last line is marked for addition
        if(blockOpen){
            fileChanges.push_back(block);
            blockOpen = false;
        }
    }
    
    //Reset the file with the new lines
    if(useSyntaxHighlighting) m_formatterManager->syntaxParseLines(newLines, LineFormatter::getFileLangType(file.getFilename()));
    file.setLines(newLines);
    file.resetLineOrder();
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
    vector< boost::shared_ptr<Line> > lines = file->getLines();
    
    string fileName = file->getFilename();
    vector<string> splitLine;
    split(splitLine, fileName, boost::is_any_of("/."));
    
    fileName = Utils::checkStrIndexInRange(splitLine, splitLine.size()-2) + "." + Utils::checkStrIndexInRange(splitLine, splitLine.size()-1);
    string finalPath = path + "/" + fileName;
    
    fileOutput.open(finalPath.c_str());
    for(int i = 0; i < lines.size(); i++){
        fileOutput << lines[i]->getStr() << endl;
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
    //fileText << "<p><h3>File: " << file->getFilename() << "</h3></p>" << endl;
    fileText << colourfyFile(*(file)); //file->getStr(); //
    //fileText << "<p />" << endl << endl;

    return fileText.str();
}

void GitFileManager::syntaxParseAllFiles(){
    
    for(vector< boost::shared_ptr<GitFile> >::iterator it = m_fileList.begin(); it != m_fileList.end(); ++it){
        m_formatterManager->syntaxParseLines(it->get()->getLines(), LineFormatter::getFileLangType(it->get()->getFilename()));
    }
}

string GitFileManager::colourfyFile(GitFile & file){
    
    stringstream colourStream;
    stringstream fileStream;
    string fileName = file.getFilename();
    
    fileStream << file.getStr();
    
    string inputLang = LineFormatter::getFileLangType(file.getFilename());
    m_srcHiglight.highlight(fileStream, colourStream, inputLang);

    return colourStream.str();
}