//
//  SyntaxColourListener.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 6/04/13.
//
//

#ifndef __GitDive_Cinder__SyntaxColourListener__
#define __GitDive_Cinder__SyntaxColourListener__

#include <iostream>
#include "srchilite/debuglistener.h"
#include "srchilite/highlighteventlistener.h"

class SyntaxColourListener : public srchilite::HighlightEventListener{
public:
    SyntaxColourListener(std::ostream &_os = std::cout);
    virtual ~SyntaxColourListener();
    
    virtual void notify(const srchilite::HighlightEvent &event);

private:
};

#endif /* defined(__GitDive_Cinder__SyntaxColourListener__) */
