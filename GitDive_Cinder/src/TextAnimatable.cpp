//
//  TextAnimatable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimatable.h"

TextAnimatable::TextAnimatable(){
    m_colour = cinder::Color(0.0f,0.0f,1.0f);
    m_life = 0;
    markDrawText();
    markAsCreated();
    markAsAnimatable();
}

void TextAnimatable::update(){
    m_life++;
}

void TextAnimatable::setPosition(cinder::Vec2f position){
    m_position = position;
}


void TextAnimatable::applyCss(boost::shared_ptr<CssParser> cssParser){
}

void TextAnimatable::applyCss(boost::shared_ptr<CssParser> cssParser, string key){
    setElemColour(cinder::Color::hex(cssParser->getColour(key) ));
}


void TextAnimatable::draw(cinder::gl::TextureFontRef & texFont, cinder::Vec2f offset){
    cinder::gl::color( m_colour );
    string str = getStr();
    
    if(bDrawSquares) {        
        cinder::Vec2f rectSize = texFont->measureString(str);
        cinder::Rectf rect( *(m_position.ptr()) + offset, *(m_position.ptr()) + offset + rectSize );
        cinder::gl::drawSolidRect(rect);
    } else {
        texFont->drawString( str, *(m_position.ptr()) + offset);
    }
    
    //texFont->drawString( str, *(m_position.ptr()) + offset);

}

bool TextAnimatable::markedForDeletion(){
    if(m_life > MAX_LIFE) return true;
    return false;
}

bool TextAnimatable::isJustFreed(){
    if(bIsFree){
        bIsFree = false;
        return true;
    }
    
    return false;
}

bool TextAnimatable::isJustCreated(){
    if(bIsCreated){
        bIsCreated = false;
        return true;
    }
    
    return false;
}

bool TextAnimatable::isJustAnimating(){
    if(bIsAnimating){
        bIsAnimating = false;
        return true;
    }
    
    return false;
}



void TextAnimatable::animIn( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration)
{
    cinder::EaseInOutSine easer;
    

    m_colourTween = timeline->apply( &m_colour, destColour, duration, easer);
    m_posTween = timeline->apply( &m_position, destVec, duration, easer);
    //    timeline.apply( &m_colour, destColour, 1.0f, easer);
    //    timeline.apply( &m_position, destVec, 0.5f);
    //    timeline.apply( &m_position, destVec, 0.5f).finishFn( std::bind( &TextAnimatable::onAnimIn, this ) );
    
}

void TextAnimatable::animOut( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration)
{
    cinder::EaseInOutSine easer;

    m_colourTween = timeline->apply( &m_colour, destColour, duration, easer);
    m_posTween = timeline->apply( &m_position, destVec, duration, easer);

    //timeline.apply( &m_colour, destColour, 1.0f,  easer);
    //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimatable::onAnimIn, this ) );
}


std::string TextAnimatable::getStr()
{
    return "";
}