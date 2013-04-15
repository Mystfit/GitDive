//
//  Textanimatable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimatable.h"

Textanimatable::Textanimatable(){
    m_colour = cinder::Color(255,255,255);
    m_life = 0;
    markAsCreated();
}

void Textanimatable::update(){
    m_life++;
}

void Textanimatable::setPosition(cinder::Vec2f position){
    m_position = position;
}

void Textanimatable::applyCss(boost::shared_ptr<CssParser> cssParser){
}

void Textanimatable::applyCss(boost::shared_ptr<CssParser> cssParser, string key){
    setColour(cinder::Color::hex(cssParser->getColour(key) ));
}


void Textanimatable::draw(cinder::gl::TextureFontRef & texFont){
    cinder::gl::color( m_colour );
    string str = getStr();

    texFont->drawString( str, m_position);
}

bool Textanimatable::markedForDeletion(){
    if(m_life > MAX_LIFE) return true;
    return false;
}

bool Textanimatable::isJustFreed(){
    if(bIsFree){
        bIsFree = false;
        return true;
    }
    
    return false;
}

bool Textanimatable::isJustCreated(){
    if(bIsCreated){
        bIsCreated = false;
        return true;
    }
    
    return false;
}

bool Textanimatable::isJustAnimating(){
    if(bIsAnimating){
        bIsAnimating = false;
        return true;
    }
    
    return false;
}



void Textanimatable::animIn( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration)
{
    cinder::EaseOutSine easer;
    
    if(isJustAnimating())
    {
        m_colourTween = timeline->apply( &m_colour, destColour, duration,  easer);
        m_posTween = timeline->apply( &m_position, destVec, duration,  easer);
    //    timeline.apply( &m_colour, destColour, 1.0f, easer);
    //    timeline.apply( &m_position, destVec, 0.5f);
    //    timeline.apply( &m_position, destVec, 0.5f).finishFn( std::bind( &Textanimatable::onAnimIn, this ) );
    }
}

void Textanimatable::animOut( cinder::TimelineRef timeline, cinder::Vec2<float> destVec, cinder::Color destColour, float duration)
{
    cinder::EaseInSine easer;
    
    if(isJustAnimating())
    {
        m_colourTween = timeline->apply( &m_colour, destColour, duration,  easer);
        m_posTween = timeline->apply( &m_position, destVec, duration,  easer);
    }

    //timeline.apply( &m_colour, destColour, 1.0f,  easer);
    //timeline.apply( &m_position, destVec, 0.5f, cinder::easeOutAtan( 10 ) ).finishFn( std::bind( &Textanimatable::onAnimIn, this ) );
}


std::string Textanimatable::getStr()
{
    return "";
}