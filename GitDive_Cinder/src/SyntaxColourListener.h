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
#include "srchilite/highlighteventlistener.h"
#include "srchilite/highlightevent.h"
#include "GitDataTypes.h"

using namespace srchilite;

class SyntaxColourListener : public srchilite::HighlightEventListener{
public:
    SyntaxColourListener();
    virtual ~SyntaxColourListener();
    virtual void notify(const srchilite::HighlightEvent &event);
    void setTargetLine(boost::shared_ptr<Line> target){m_targetLine = target; };

private:
    boost::shared_ptr<Line> m_targetLine;
};

#endif /* defined(__GitDive_Cinder__SyntaxColourListener__) */
