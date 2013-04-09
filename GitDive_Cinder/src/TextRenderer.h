//
//  TextRenderer.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#ifndef __GitDive_Cinder__TextRenderer__
#define __GitDive_Cinder__TextRenderer__

#define LINE_HEIGHT 19
#define FONT_SIZE 15

#include <iostream>
#include "GitDataTypes.h"
#include "cinder/timeline.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"


class TextRenderer {
public:
    TextRenderer();
    void draw(vector< boost::shared_ptr<Line> > & lines);
    
    cinder::gl::TextureFontRef & getTexFont(){return m_textureFont; };
    
    void setTimeline(cinder::TimelineRef timelineRef){ m_timeline = timelineRef; };
    
    void setTextOffset(cinder::Vec2f position);
    void setScrollVelocity(cinder::Vec2 velocity);
    
    //Starts tracking a line for rendering
    void makeLineFromFreeElements(boost::shared_ptr<Line> line);
    
    //Breaks line into component elements
    void breakLine(boost::shared_ptr<Line> line);
    
    //Adds a new free line element to the pool
    void addFreeLineElem(LineElement lnElem);
    
    //Returns a free line element
    void getFreeLineElem(LineElement searchTarget);
    
    void removeLine(boost::shared_ptr<Line> line);
    
    void animLinesIn(vector<boost::shared_ptr<Line> > lines);
        
private:    
    vector<LineElement> m_freeLineElements;
    
    cinder::gl::TextureFontRef m_textureFont;
    cinder::TimelineRef m_timeline;
    
    cinder::Vec2f m_textOffset;
    cinder::Vec2f m_kineticVelocity;
};

#endif /* defined(__GitDive_Cinder__TextRenderer__) */
