//
//  LineElementFactory.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 13/04/13.
//
//

#ifndef __GitDive_Cinder__LineElementFactory__
#define __GitDive_Cinder__LineElementFactory__

#include "GitDataTypes.h"

#include "boost/range/algorithm/remove_if.hpp"
#include <iostream>

class LineElementManager {
public:
    LineElementManager();
    
    //Returns a free line element that already exists of a specific type or creates a new one if none are available
    boost::shared_ptr<LineElement> getFreeLineElement(string elemType = "normal", string search = "", int index = 0);
    
    //Rescues line elements from a line
    void salvageLine( vector< boost::shared_ptr<LineElement> > lineElements );
    
    vector< boost::shared_ptr<LineElement> > getFloatingElements(){ return m_freeLineElements; };
    
    boost::shared_ptr<Line> setTargetLine(boost::shared_ptr<Line> target){ m_targetLine = target; };
    boost::shared_ptr<Line> getTargetLine(){ return m_targetLine; };


    void update();

private:
    boost::shared_ptr<Line> m_targetLine;
    vector<boost::shared_ptr<LineElement> > m_freeLineElements;
    
};

#endif /* defined(__GitDive_Cinder__LineElementFactory__) */
