//
//  LineElementFactory.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 13/04/13.
//
//

#include "LineElementFactory.h"

LineElementManager::LineElementFactory(){
    
}

boost::shared_ptr<LineElement> LineElementFactory::getFreeLineElement(string elemType, string search, int index){
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