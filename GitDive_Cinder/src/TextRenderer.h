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
    
    void addFreeLineElement(LineElement element);
    
private:
    vector<LineElement> m_freeLineElements;
};

#endif /* defined(__GitDive_Cinder__TextRenderer__) */
