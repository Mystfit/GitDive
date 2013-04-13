//
//  LineElementFactory.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 13/04/13.
//
//

#include "LineElementFactory.h"

LineElementFactory::LineElementFactory(){
    
}

boost::shared_ptr<LineElement> LineElementFactory::getFreeLineElement(string elemType, string search){
    boost::shared_ptr<LineElement> lineElem;
    
    vector< boost::shared_ptr<LineElement> >::iterator elem;
    for(elem = m_freeLineElements.begin(); elem != m_freeLineElements.end(); ++elem){
        if(elem->get()->elem == elemType && elem->get()->getStr() == search){
            return elem->get();
        }
    }
    
    
    
    return lineElem;
}