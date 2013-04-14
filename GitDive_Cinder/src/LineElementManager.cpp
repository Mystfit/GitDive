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
            lineElem->isFloating = false;
            m_freeLineElements.erase(elem);
            break;
        }
    }
    
    if(!lineElem){
        lineElem = boost::shared_ptr<LineElement>(new LineElement(elemType, search, index));
    }
    
    return lineElem;
}


void LineElementManager::update(){
        
    //Remove old line elements hanging around
    for(vector< boost::shared_ptr<LineElement> >::iterator it = m_freeLineElements.begin(); it != m_freeLineElements.end(); ++it ){
        it->get()->update();
        if(it->get()->getLifePercent() > 1.0f && it->get()->isFloating) it->reset();
    }
}


void LineElementManager::salvageLine( vector< boost::shared_ptr<LineElement> > lineElements ){
    
    //Rescue line elements first
    for(int i = 0; i < lineElements.size(); i++){
        m_freeLineElements.push_back(lineElements[i]);
        m_freeLineElements.back()->isFloating = true;
        m_freeLineElements.back()->setColour(cinder::Color(128,128,128));
        //m_freeLineElements.back()->animOut(m_timeline, m_freeLineElements.back()->getPosition(), cinder::Color(0,0,0), 10.0f);
    }
}

