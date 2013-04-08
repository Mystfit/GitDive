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
#include "cinder/gl/TextureFont.h"

class TextAnimateable {
public:
    TextAnimateable();
    void draw(cinder::gl::TextureFont & texFont);
    
    virtual std::string getStr();
    
    
};

#endif /* defined(__GitDive_Cinder__TextAnimateable__) */
