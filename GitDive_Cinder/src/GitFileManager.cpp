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
    vector< boost::shared_ptr <Line> > originalLines = file.getLines();
    vector< boost::shared_ptr <Line> > newLines;
    vector<Line> deltaAddLines = diff->getDeltaAddLines();
    vector<Line> deltaRemoveLines = diff->getDeltaRemoveLines();
    
    //If the file is blank/new, only dump in all the new lines
    if(originalLines.size() < 1){
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
            if(pos < originalLines.size()){
                //Erase the line from the file
                
                originalLines[i]->markForRemoval();
                originalLines.erase(originalLines.begin() + pos); // TODO: Needs to be handled in a better way that updates the visuals
                
                //Store the removed lines as a block of lines so we can keep the original structure of the file
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_DELETE;
                    block.blockStart = deltaRemoveLines[i].getLinePos();
                    block.blockEnd = deltaRemoveLines[i].getLinePos();
                    cout << "-|.";
                } else {
                    if(deltaRemoveLines[i].getLinePos() - block.blockEnd > 1){
                        fileChanges.push_back(block);
                        blockOpen = false;
                        cout << "| RemoveBlock Start:" << block.blockStart << " End:" << block.blockEnd << endl;
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
            cout << "| RemoveBlock Start:" << block.blockStart << " End:" << block.blockEnd << endl;
        }
    }
    
    
    //Reset counters
    deltaIndex = 0;
    int lineCounter = 0;
    blockOpen = false;
    
    //Add lines
    if(deltaAddLines.size() == 0){
        newLines = originalLines;
    } else {
        for(int lineNum = 1; lineNum <= originalLines.size() + deltaAddLines.size(); lineNum++ ){
            
            if(deltaIndex < deltaAddLines.size() && deltaAddLines[deltaIndex].getLinePos() == lineNum){
                
                //Create new line pointer
                boost::shared_ptr<Line> newLine( new Line(deltaAddLines[deltaIndex].getStr(), true) );
                newLine->setLinePos(deltaAddLines[deltaIndex].getLinePos());
                newLines.push_back(newLine);
                
                //Save changes of lines added as blocks of line positions for animation
                if(!blockOpen){
                    blockOpen = true;
                    block = FileChangeBlock();
                    block.blockType = FileChangeBlock::FILECHANGE_ADD;
                    block.blockStart = newLines.back()->getLinePos();
                    block.blockEnd = newLines.back()->getLinePos();
                    cout << "+|";
                }
                
                if(newLines.back()->getLinePos() - block.blockEnd > 1){
                    fileChanges.push_back(block);
                    blockOpen = false;
                    cout << "| AddBlock Start:" << block.blockStart << "| End:" << block.blockEnd << endl;
                } else {
                    block.blockEnd = newLines.back()->getLinePos();
                    cout << ".";
                }
            
                deltaIndex++;
            
            } else {
                boost::shared_ptr<Line> oldLine = originalLines[lineCounter];
                oldLine->setLinePos(lineNum);
                newLines.push_back(oldLine);
                lineCounter++;
                
                //Close the file change block
                if(blockOpen){
                    fileChanges.push_back(block);
                    blockOpen = false;
                    cout << "| AddBlock Start:" << block.blockStart << "| End:" << block.blockEnd << endl;
                }
            }
        }
        
        if(blockOpen){
            fileChanges.push_back(block);
            blockOpen = false;
            cout << "| AddBlock Start:" << block.blockStart << "| End:" << block.blockEnd << endl;
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
                    cout << "+|";
                }
                
                cout << ".";
                block.blockEnd = deltaAddLines[deltaIndex].getLinePos();
                
                //Create new line pointer
                boost::shared_ptr<Line> newLine( new Line(deltaAddLines[deltaIndex++].getStr(), true) );
                newLine->setLinePos(deltaAddLines[deltaIndex].getLinePos());
                newLines.push_back(newLine);
            }
        }
        
        //Close the block if the last line is marked for addition
        if(blockOpen){
            fileChanges.push_back(block);
            blockOpen = false;
            cout << "| Final AddBlock Start:" << block.blockStart << "| End:" << block.blockEnd << endl;
        }
    }
    
    //Reset the file with the new lines
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
    fileText << "<p><h3>File: " << file->getFilename() << "</h3></p>" << endl;
    fileText << colourfyFile(*(file)); //file->getStr();
    fileText << "<p />" << endl << endl;

    return fileText.str();
}

void GitFileManager::syntaxParseFile(GitFile &file ){    
    string inputLang = "cpp.lang";
    srchilite::LangMap langMap(DATADIR, "lang.map");
    
    string lang = langMap.getMappedFileNameFromFileName(file.getFilename());
    if (lang != "") {
        inputLang = lang;
    } // otherwise we default to C++

    //-------------------------------------
    srchilite::RegexRuleFactory ruleFactory;
    srchilite::LangDefManager langDefManager(&ruleFactory);
    
    // we highlight C++ code for simplicity
    srchilite::SourceHighlighter highlighter(langDefManager.getHighlightState(DATADIR, inputLang));
    
    boost::shared_ptr<LineFormatter> passthroughLineFormatter(new LineFormatter("", boost::shared_ptr<Line>line));
    boost::shared_ptr<LineFormatterManager> formatterManager(new LineFormatterManager(passthroughLineFormatter));
    highlighter.setFormatterManager(formatterManager.get());
    highlighter.getFormatterManager()->getFormatter("normal");

//    InfoFormatterPtr keywordFormatter(new InfoFormatter("keyword"));
//    formatterManager.addFormatter("keyword", keywordFormatter);
//    formatterManager.addFormatter("string", InfoFormatterPtr(new InfoFormatter("string")));
//    // for "type" we use the same formatter as for "keyword"
//    formatterManager.addFormatter("type", keywordFormatter);
//    formatterManager.addFormatter("comment", InfoFormatterPtr(new InfoFormatter("comment")));
//    formatterManager.addFormatter("symbol", InfoFormatterPtr(new InfoFormatter("symbol")));
//    formatterManager.addFormatter("number", InfoFormatterPtr(new InfoFormatter("number")));
//    formatterManager.addFormatter("preproc", InfoFormatterPtr(new InfoFormatter("preproc")));
    
    boost::shared_ptr< SyntaxColourListener > colourListener(new SyntaxColourListener());
    highlighter.addListener(colourListener.get());

    // make sure it uses additional information
    srchilite::FormatterParams params;
    highlighter.setFormatterParams(&params);
    vector< boost::shared_ptr<Line> > lines = file.getLines();
    for(int i = 0; i < lines.size(); i++){
        params.start = 0;
        formatterManager->setTargetLine(lines[i]);
        colourListener->setTargetLine(lines[i]);
        highlighter.highlightParagraph(lines[i]->getStr());
    }
    //----------------------------------------
}

string GitFileManager::colourfyFile(GitFile & file){
    
    stringstream colourStream;
    stringstream fileStream;
    string fileName = file.getFilename();
    
    fileStream << file.getStr();
    
    m_srcHiglight.setDataDir(DATADIR);

    string inputLang = "cpp.lang";
    srchilite::LangMap langMap(DATADIR, "lang.map");
    
    string lang = langMap.getMappedFileNameFromFileName(fileName);
    if (lang != "") {
        inputLang = lang;
    } // otherwise we default to C++
    
    m_srcHiglight.highlight(fileStream, colourStream, inputLang);

    return colourStream.str();
}