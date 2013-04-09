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
    void update();
    
    void setTargetFile(boost::shared_ptr<GitFile> file){m_targetFile = file; };
    
    //Texturefont reference for drawing text
    cinder::gl::TextureFontRef & getTexFont(){return m_textureFont; };
    
    //Timeline reference for animation
    void setTimeline(cinder::TimelineRef timelineRef){ m_timeline = timelineRef; };
    
    //Sets the position of the file on the screen
    void setTextOffset(cinder::Vec2f position){m_textOffset = position;};
    void setScrollVelocity(cinder::Vec2f velocity){m_scrollVelocity = velocity; };
    void setTextZoom(float zoom){m_textZoom = zoom; };
    
    //Starts tracking a line for rendering
    void makeLineFromFreeElements(boost::shared_ptr<Line> line);
    
    //Breaks line into component elements
    void breakLine(boost::shared_ptr<Line> line);
    
    //Adds a new free line element to the pool
    void addFreeLineElem(LineElement lnElem);
    
    //Returns a free line element
    void getFreeLineElem(LineElement searchTarget);
    
    //Animate lines into position
    void animLinesIn(vector<boost::shared_ptr<Line> > lines);
        
private:    
    vector<LineElement> m_freeLineElements;
    
    boost::shared_ptr<GitFile> m_targetFile;
    
    cinder::gl::TextureFontRef m_textureFont;
    cinder::TimelineRef m_timeline;
    
    float m_textZoom;
    cinder::Vec2f m_textOffset;
    cinder::Vec2f m_scrollVelocity;
};

#endif /* defined(__GitDive_Cinder__TextRenderer__) */
