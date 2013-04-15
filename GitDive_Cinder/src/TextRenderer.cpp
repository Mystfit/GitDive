//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    cinder::Font customFont( cinder::Font( "GohuFont", FONT_SIZE ) );
	cinder::gl::TextureFont::Format f;
	f.enableMipmapping( true );
    string supportedChars = cinder::gl::TextureFont::defaultChars() + "{}";
	m_textureFont = cinder::gl::TextureFont::create( customFont, f, supportedChars );
    
    string cssPath = DATADIR;
    string cssFile = "sh_golden.css";
    m_cssColours = boost::shared_ptr<CssParser>(new CssParser());
    m_cssColours->loadFile( cssPath + "/" + cssFile );
}


void TextRenderer::makeLineFromFreeElements(boost::shared_ptr<Line> line){

}

void TextRenderer::animLinesIn(vector<boost::shared_ptr<Line> > lines){
    for(vector<boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
        if(it->get()->getLineState() == Line::LINE_ADDED){
            it->get()->applyCss(m_cssColours);
            it->get()->setPosition(cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT));
            it->get()->animIn(m_timeline, cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT), cinder::Color(255,255,255));
        } else if(it->get()->getLineState() == Line::LINE_NORMAL){
            it->get()->animIn(m_timeline, cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT), cinder::Color(255,255,255));
        }
    }
}


void TextRenderer::breakLine(boost::shared_ptr<Line> line){    
    m_lineManager->salvageLine(line->getLineElements());
    line->animOut(m_timeline, cinder::Vec2f(0, line->getLinePos() * LINE_HEIGHT), cinder::Color(255,0,0));
}

void TextRenderer::update(){
    if(m_targetFile) m_targetFile->update();
    
    vector< boost::shared_ptr<LineElement> > freeElems = m_lineManager->getFloatingElements();
    vector< boost::shared_ptr<LineElement> >::iterator elem;
    
    //Start animation for freed line elements
    for(elem = freeElems.begin(); elem != freeElems.end(); ++elem){
        if(elem->get()->isJustFreed()){
            elem->get()->animOut(m_timeline, elem->get()->getPosition(), cinder::Color(255,255,0), 1.0f);
        }
    }
    
    if(it->get()->isJustCreated()){
        it->get()->animIn(<#cinder::TimelineRef#>, <#cinder::Vec2<float> destVec#>, <#cinder::Color destColour#>)
    }
    
    
}



void TextRenderer::draw(){
    
    vector< boost::shared_ptr<Line> > lines;
    
    if(m_targetFile) lines = m_targetFile->getLines();
    else return;
    
    if(lines.size()){
        for(vector< boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
            it->get()->draw(m_textureFont);
        }
    }
    
    vector< boost::shared_ptr<LineElement> > freeLineElems = m_lineManager->getFloatingElements();
    
    if(freeLineElems.size()){
        //Draws the free-floating line elements
        for(int i = 0; i < freeLineElems.size(); i++){
            freeLineElems[i]->draw(m_textureFont);
        }
    }
}
