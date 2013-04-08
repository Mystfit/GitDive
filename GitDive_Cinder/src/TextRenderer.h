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
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"


class TextRenderer {
public:
    TextRenderer();
    void draw();
    
    cinder::gl::TextureFontRef & getTexFont(){return m_textureFont; };
    
    //Starts tracking a line for rendering
    void makeLineFromFreeElements(boost::shared_ptr<Line> line);
    
    //Breaks line into component elements
    void breakLine(boost::shared_ptr<Line> line);
    
    //Adds a new free line element to the pool
    void addFreeLineElem(LineElement lnElem);
    
    //Returns a free line element
    void getFreeLineElem(LineElement searchTarget);
        
private:
    
    vector< boost::shared_ptr<Line> > m_trackedLines;
    vector<LineElement> m_freeLineElements;
    
    cinder::gl::TextureFontRef m_textureFont;
    
};

#endif /* defined(__GitDive_Cinder__TextRenderer__) */
