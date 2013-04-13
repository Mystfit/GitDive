//
//  LineElementFactory.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 13/04/13.
//
//

#include "LineElementManager.h"

LineElementManager::LineElementManager(){
    
}



boost::shared_ptr<LineElement> LineElementManager::getFreeLineElement(string elemType, string search, int index){
    boost::shared_ptr<LineElement> lineElem;
    
    vector< boost::shared_ptr<LineElement> >::iterator elem;
    for(elem = m_freeLineElements.begin(); elem != m_freeLineElements.end(); ++elem){
        if(elem->get()->elem == elemType && elem->get()->getStr() == search){
    
            lineElem = (boost::shared_ptr<LineElement>)elem->get();
            m_freeLineElements.erase(elem);
            break;
        }
    }
    
    if(!lineElem){
        lineElem = boost::shared_ptr<LineElement>(new LineElement(elemType, search, index));
    }
    
    return lineElem;
}



void LineElementManager::breakLine(boost::shared_ptr<Line> line){
    vector< boost::shared_ptr<LineElement> > lineElems = line->getLineElements();
    line->animOut(m_timeline, cinder::Vec2f(0, line->getLinePos() * LINE_HEIGHT), cinder::Color(0.2,0.2,0.2));
    
    //Rescue line elements first
    //    for(int i = 0; i < lineElems.size(); i++){
    //        m_freeLineElements.push_back(lineElems[i]);
    //        m_freeLineElements.back()->setFloating();
    //        m_freeLineElements.back()->animOut(m_timeline, m_freeLineElements.back()->getPosition(), cinder::Color(0,0,0), 10.0f);
    //    }
    
    line.reset();
}

void LineElementManager::update(){
    
    if(m_targetFile) m_targetFile->update();
    
    //Remove old line elements hanging around
    for(vector< boost::shared_ptr<LineElement> >::iterator it = m_freeLineElements.begin(); it != m_freeLineElements.end(); ++it ){
        //Zif(it->get()->getLifePercent() > 1.0f) it->reset();
    }
}
