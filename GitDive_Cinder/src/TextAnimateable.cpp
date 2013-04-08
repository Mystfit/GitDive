//
//  TextAnimateable.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextAnimateable.h"



TextAnimateable::TextAnimateable(){
    
}
                
TextAnimateable::draw(){
    gl::color( mColorCur );
    gl::pushMatrices();
    Matrix44f m = mMatrix;
    m.scale( Vec3f( 1.0f, -1.0f, 1.0 ) );
    gl::multModelView( m );
    mTextureFont->drawString( mChar, mKernBounds.getCenter() - Vec2f( mKernBounds.getWidth(), 0.0f ) );
    gl::popMatrices();
}
                
gl::color( mColorCur );
gl::pushMatrices();
Matrix44f m = mMatrix;
m.scale( Vec3f( 1.0f, -1.0f, 1.0 ) );
gl::multModelView( m );
mTextureFont->drawString( mChar, mKernBounds.getCenter() - Vec2f( mKernBounds.getWidth(), 0.0f ) );
gl::popMatrices();