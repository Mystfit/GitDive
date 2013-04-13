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
#include <iostream>

class LineElementManager {
public:
    LineElementManager();
    
    //Returns a free line element that already exists of a specific type or creates a new one if none are available
    boost::shared_ptr<LineElement> getFreeLineElement(string elemType, string search, int index);
    
    //Rescues line elements from a line
    void salvageLine( vector< boost::shared_ptr<LineElement> > lineElements );

        
    void update();

private:
    vector<boost::shared_ptr<LineElement> > m_freeLineElements;
    
};

#endif /* defined(__GitDive_Cinder__LineElementFactory__) */
