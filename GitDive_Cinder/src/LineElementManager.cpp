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
//    vector< boost::shared_ptr<LineElement> >::iterator elem;
//    
//    if(m_freeLineElements.size() > 0){
////        for(elem = m_freeLineElements.begin(); elem != m_freeLineElements.end(); ++elem){
////            if(elem->get()->elem == elemType && elem->get()->getStr() == search){
////                lineElem = (boost::shared_ptr<LineElement>)elem->get();
////                lineElem->isFloating = false;
////                m_freeLineElements.erase(elem);
////                break;
////            }
////        }
//        
//        for(int i = 0; i < m_freeLineElements.size(); i++){
//            lineElem = m_freeLineElements[i];
//            
//            if(lineElem->elem == elemType && lineElem->getStr() == search){
//        
//                lineElem->isFloating = false;
//                lineElem->markAsCreated();
//                lineElem->markAsAnimatable();
//                m_freeLineElements.erase(m_freeLineElements.begin() + i);
//
//                break;
//            }
//        }
//    }
//    
//    //If we didn't find a free element, return a new one
//    if(!lineElem){
//        lineElem = boost::shared_ptr<LineElement>(new LineElement(elemType, search, index));
//        lineElem->setPosition(m_targetLine->getPosition());
//    }
//    
    lineElem = boost::shared_ptr<LineElement>(new LineElement(elemType, search, index));
    lineElem->setPosition(m_targetLine->getPosition());
    
    return lineElem;
}


void LineElementManager::update(){
    
    
    //Remove old line elements hanging around
    for(vector< boost::shared_ptr<LineElement> >::iterator it = m_freeLineElements.begin(); it != m_freeLineElements.end(); ++it ){
        cout << m_freeLineElements.size() << " elements lying around" << endl;
        it->get()->update();
    }
    
    m_freeLineElements.erase(
                 std::remove_if(m_freeLineElements.begin(), m_freeLineElements.end(),
                                [](const boost::shared_ptr<LineElement> elem) {
                                    return (elem->markedForDeletion() && elem->isFloating);
                                }),
                 m_freeLineElements.end());
    
}


void LineElementManager::salvageLine( vector< boost::shared_ptr<LineElement> > lineElements ){
    
    //Rescue line elements first
    for(int i = 0; i < lineElements.size(); i++){
        m_freeLineElements.push_back(lineElements[i]);
        m_freeLineElements.back()->isFloating = true;        
        m_freeLineElements.back()->markAsFreed();
        m_freeLineElements.back()->markAsAnimatable();
    }
    
    lineElements.clear();
}

