//
//  GitDataTypes.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 29/03/13.
//
//

#include "GitDataTypes.h"


LineElement::LineElement(string element, string elemStr, int pos){
    elem = element;
    str = elemStr;
    
    position = pos;
    setPosition(cinder::Vec2f((float)position * 10.0f, 0.0f));
}

void LineElement::applyCss(boost::shared_ptr<CssParser> cssParser){
    TextAnimateable::applyCss(cssParser, elem);
}

/*
 * Line
 */
Line::Line(string lineStr, bool justUpdated){
    m_lineStr = lineStr;
    
    if(lineStr.compare(0, 1, "+") == 0){
        m_lineState = LINE_ADDED;
    }
    else if(lineStr.compare(0, 1, "-") == 0){
        m_lineState = LINE_DELETED;
    }
    else{
        m_lineState = LINE_NORMAL;
    }
    
    if(!justUpdated) m_lineStr.erase(0,1);
}


void Line::applyCss(boost::shared_ptr<CssParser> cssParser){
    for(vector<LineElement>::iterator it = m_lineElements.begin(); it != m_lineElements.end(); ++it){
        it->TextAnimateable::applyCss(cssParser, it->elem);
    }
}



string Line::getStr(){
    stringstream lineStr;

    if(!m_lineElements.size()){
        lineStr << m_lineStr;
    } else {
        //cout << m_lineElements.size() << "|";
        for(vector<LineElement>::iterator it = m_lineElements.begin(); it != m_lineElements.end(); ++it){
            //cout << it->str << "|";
            //if(it->str != "\n")
            lineStr << it->str;
        }
    }
        
    return lineStr.str();
}


void Line::update(){
    for(std::vector<LineElement>::iterator it = m_lineElements.begin(); it != m_lineElements.end(); ++it){
        if(!it->bIsFloating) it->setPosition( cinder::Vec2f((float)it->position * 8.5f, getPosition().y) );
    }
    m_life++;
}


void Line::draw(cinder::gl::TextureFontRef & texFont){
    if(m_lineElements.size())
    {
        for(std::vector<LineElement>::iterator it = m_lineElements.begin(); it != m_lineElements.end(); ++it){
            it->draw(texFont);
        }
    } else {
        TextAnimateable::draw(texFont);
        //texFont->drawString( getStr(), m_position);
    }
}


void Line::addLineElement( boost::shared_ptr<LineElement> element){
    m_lineElements.push_back(element);
}




void Line::markForRemoval(){
    m_lineState = Line::LINE_DELETED;
    //Update visuals here. Break apart line into component parts
}



/*
 * Commit
 */
Commit::Commit(string _commit, string _date, string _author, string _message){
    commitHash = _commit;
    date = _date;
    author = _author;
    message = _message;
}



/*
 * Diff
 */
Diff::Diff(){
    fileType = Diff::FILETYPE_TEXT;
    fileMode = Diff::FILEMODE_UPDATED;
}


int Diff::getNumDeltaLines(){
    int addLines = 0;
    int removeLines = 0;
    
    for(int i = 0; i < m_hunkList.size(); i++){
        for(int j = 0; j < m_hunkList[i]->getNumLines(); j++){
            Line cLine = m_hunkList[i]->getLine(j);
            
            if(cLine.getLineState() == Line::LINE_ADDED) addLines++;
            else if(cLine.getLineState() == Line::LINE_DELETED) removeLines++;
        }
    }
    
    return addLines - removeLines;
}


vector<Line> Diff::getAllDeltaLines(){
    
    vector<Line> deltaLineList;
    
    for(int i = 0; i < m_hunkList.size(); i++){
        boost::shared_ptr<DiffHunk> diffHunk = m_hunkList[i];
        
        for(int j = 0; j < diffHunk->getNumLines(); j++)
        {
            deltaLineList.push_back(diffHunk->getLine(j));

        }
    }
    
    return deltaLineList;
}


void Diff::updateDeltaLists(){
    vector<Line> originalLines = getAllDeltaLines();
    
    m_deltaAddLines.clear();
    m_deltaRemoveLines.clear();
    
    for(int i = 0; i < originalLines.size(); i++){
        if(originalLines[i].getLineState() == Line::LINE_ADDED) {
            m_deltaAddLines.push_back(originalLines[i]);
        }
        else if(originalLines[i].getLineState() == Line::LINE_DELETED){
            m_deltaRemoveLines.push_back(originalLines[i]);
        }
        else if(originalLines[i].getLineState() == Line::LINE_NORMAL){
            //Throw away
        }
    }
}



/*
 * DiffHunk
 */
DiffHunk::DiffHunk(){
    m_linePos = 0;
}



/*
 * Git File
 */
GitFile::GitFile(string filename){
    m_filename = filename;
    bIsActive = true;
}

void GitFile::update(){
    for(vector< boost::shared_ptr<Line> >::iterator it = m_activeLines.begin(); it != m_activeLines.end(); ++it){
        it->get()->update();
    }
}

void GitFile::setLines(vector< boost::shared_ptr<Line> > lines){
    m_activeLines = lines;
};

void GitFile::resetLineOrder(){
    for(int i = 1; i <= m_activeLines.size(); i++){
        m_activeLines[i-1]->setLinePos(i);
    }
}

string GitFile::getStr(){
    
    stringstream stream;
    for(int i = 0; i < m_activeLines.size(); i++) {
        stream << m_activeLines[i]->getStr().c_str() << endl;
    }
    
    return stream.str();
}