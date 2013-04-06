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
#include "srchilite/formatter.h"
#include "srchilite/formatterparams.h"
#include "srchilite/highlighteventlistener.h"
#include "srchilite/highlightevent.h"
#include "srchilite/highlighttoken.h"
#include "srchilite/highlightrule.h"
#include "GitDataTypes.h"

using namespace srchilite;

// SyntaxListener that triggers each time the syntax highlighter fires off an event
class SyntaxColourListener : public srchilite::HighlightEventListener
{
public:
    SyntaxColourListener();
    virtual ~SyntaxColourListener();
    virtual void notify(const srchilite::HighlightEvent &event);
    void setTargetLine(boost::shared_ptr<Line> target){m_targetLine = target; };

private:
    boost::shared_ptr<Line> m_targetLine;
};


//Passthrough infoformatter that dumps the seperated elements into the current line
class InfoFormatter: public srchilite::Formatter
{    
public:
    InfoFormatter(const std::string &elem_ = "normal") : elem(elem_) {}
    void setLine(boost::shared_ptr<Line> setTargetLine){m_targetLine = line; };
    virtual void format(const std::string &s, const srchilite::FormatterParams *params = 0);
private:
    boost::shared_ptr<Line> m_targetLine;
    std::string elem;
};

/// shared pointer for InfoFormatter
typedef boost::shared_ptr<InfoFormatter> InfoFormatterPtr;

#endif /* defined(__GitDive_Cinder__SyntaxColourListener__) */
