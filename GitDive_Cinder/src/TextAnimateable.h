//
//  TextAnimateable.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#ifndef __GitDive_Cinder__TextAnimateable__
#define __GitDive_Cinder__TextAnimateable__

#include <iostream>
#include "cinder/Timeline.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"

using namespace cinder;

class TextAnimateable {
public:
    TextAnimateable();
    virtual void animIn( Timeline &timeline, Vec2<float> destVec )
    {
        timeline.apply( &mColorCur, mColorDest, 1.0f, EaseOutAtan( 20 ) );
        timeline.apply( &mMatrix, matrix, 0.5f, EaseOutAtan( 10 ) ).finishFn( std::bind( &TextAnimateable::onAnimIn, this ) );
    }
    
    virtual void animOut( Timeline &timeline, Vec2<float> destVec )
    {
        mDestMatrix = matrix;
        timeline.apply( &mColorCur, mColorStart, 1.0f, EaseOutQuad() ).finishFn( bind( &TextAnimateable::onAnimOut, this ) );
        timeline.apply( &mMatrix, matrix, 1.0f, EaseOutQuad() );
    }
    
    virtual void onAnimIn();
    virtual void onAnimOut();
private:
    Vec2<float> m_position;
    Color; m_colour;
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
