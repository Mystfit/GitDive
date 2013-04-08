//
//  TextRenderer.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#ifndef __GitDive_Cinder__TextRenderer__
#define __GitDive_Cinder__TextRenderer__

#include <iostream>
#include "GitDataTypes.h"

class TextRenderer {
public:
    TextRenderer();
    
    //Starts tracking a line for rendering
    void trackLine(boost::shared_ptr<Line> line);
    
    //Breaks line into component elements
    void breakLine(boost::shared_ptr<Line> line);
    
    //Adds a new free line element to the pool
    void addFreeLineElem(LineElement lnElem);
    
    //Returns a free line element
    void getFreeLineElem(LineElement searchTarget);
        
private:
    vector<boost::chared_ptr<Line> m_trackedLines;
    vector<LineElement> m_freeLineElements;
    vector<LineElement> m_tweeingElements;
};

#endif /* defined(__GitDive_Cinder__TextRenderer__) */
