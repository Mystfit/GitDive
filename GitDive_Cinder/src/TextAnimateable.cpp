//
//  TextAnimateable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimateable.h"

TextAnimateable::TextAnimateable(){
    m_colour = cinder::Color(255,255,255);
    m_life = 0;
    markAsCreated();
}

void TextAnimateable::update(){
    m_life++;
}

void TextAnimateable::setPosition(cinder::Vec2f position){
    m_position = position;
}

void TextAnimateable::applyCss(boost::shared_ptr<CssParser> cssParser){
}

void TextAnimateable::applyCss(boost::shared_ptr<CssParser> cssParser, string key){
    setColour(cinder::Color::hex(cssParser->getColour(key) ));
}


void TextAnimateable::draw(cinder::gl::TextureFontRef & texFont){
    cinder::gl::color( m_colour );
    string str = getStr();

    texFont->drawString( str, m_position);
}

bool TextAnimateable::markedForDeletion(){
    if(m_life > MAX_LIFE) return true;
    return false;
}

bool TextAnimateable::isJustFreed(){
    if(bIsFree){
        bIsFree = false;
        return true;
    }
    
    return false;
}

bool TextAnimateable::isJustCreated(){
    if(bIsCreated){
        bIsCreated = false;
        return true;
    }
    
    return false;
}

void TextAnimateable::setPosition(cinder::Vec2f position);
    m_position = position;
}


void TextAnimateable::animIn( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration)
{
    cinder::EaseOutSine easer;
        
    m_colourTween = timeline->apply( &m_colour, destColour, duration,  easer);
    m_posTween = timeline->apply( &m_position, destVec, duration,  easer);
//    timeline.apply( &m_colour, destColour, 1.0f, easer);
//    timeline.apply( &m_position, destVec, 0.5f);
//    timeline.apply( &m_position, destVec, 0.5f).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}

void TextAnimateable::animOut( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration)
{
    cinder::EaseInSine easer;
    m_colourTween = timeline->apply( &m_colour, destColour, duration,  easer);
    m_posTween = timeline->apply( &m_position, destVec, duration,  easer);

    //timeline.apply( &m_colour, destColour, 1.0f,  easer);
    //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
}


std::string TextAnimateable::getStr()
{
    return "";
}