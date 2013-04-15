//
//  TextRenderer.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#ifndef __GitDive_Cinder__TextRenderer__
#define __GitDive_Cinder__TextRenderer__

#define LINE_HEIGHT 15
#define FONT_SIZE 14
#define FONT_WIDTH 8.5f

#include <iostream>
#include "GitDataTypes.h"
#include "LineElementManager.h"
#include "cinder/timeline.h"
#include "cinder/Easing.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"
#include "CssParser.h"
#include "SyntaxColourTools.h"


class TextRenderer {
public:
    TextRenderer();
    void draw();
    void update();
    void setTargetFile(boost::shared_ptr<GitFile> file){m_targetFile = file; };
    void setLineManager(boost::shared_ptr<LineElementManager> lineManager){ m_lineManager = lineManager; };
    
    //Texturefont reference for drawing text
    cinder::gl::TextureFontRef & getTexFont(){return m_textureFont; };
    
    //Sets line flags to allow for animation
    void setLinesAnimatable();
    
    void setFollowCamera(){ bCameraFollowing = true; };
    void setManualCamera(){ bCameraFollowing = false; };
    
    //Timeline reference for animation
    void setTimeline(cinder::TimelineRef timelineRef){ m_timeline = timelineRef; };
    
    //Sets the position of the file on the screen
    void setTextOffset(float increment);
    void setTextZoom(float zoom);
    void resetView();
    
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
    
    //Target git file we're drawing
    boost::shared_ptr<GitFile> getTargetFile(){ return m_targetFile; };
    
    //Background colour from css theme
    cinder::Color getBackgroundColour(){ return m_backgroundColour; };
    
private:        
    boost::shared_ptr<GitFile> m_targetFile;
    boost::shared_ptr<LineElementManager> m_lineManager;
    
    cinder::gl::TextureFontRef m_textureFont;
    cinder::TimelineRef m_timeline;
    
    float m_textZoom;
    cinder::Anim<cinder::Vec2f> m_textOffset;
    boost::shared_ptr<CssParser> m_cssColours;
    cinder::Color m_backgroundColour;
    bool bCameraFollowing, bDrawSquares;
};

#endif /* defined(__GitDive_Cinder__TextRenderer__) */
