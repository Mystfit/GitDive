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

class TextAnimateable {
public:
    TextAnimateable();
    virtual void animIn( cinder::Timeline &timeline, cinder::Vec2<float> destVec )
    {
        mDestMatrix = matrix;
        timeline.apply( &mColorCur, mColorDest, 1.0f, EaseOutAtan( 20 ) );
        timeline.apply( &mMatrix, matrix, 0.5f, EaseOutAtan( 10 ) );
    }
    
    virtual void animOut( cinder::Timeline &timeline, vec )
    {
        mDestMatrix = matrix;
        timeline.apply( &mColorCur, mColorStart, 1.0f, EaseOutQuad() ).finishFn( bind( &Character::onAnimOut, this ) );
        timeline.apply( &mMatrix, matrix, 1.0f, EaseOutQuad() );
    }
    
    virtual void onAnimOut()
    {
    }
private:
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
