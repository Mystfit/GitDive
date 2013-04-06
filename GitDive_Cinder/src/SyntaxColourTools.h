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
#include "srchilite/sourcehighlighter.h";
#include "srchilite/formatter.h"
#include "srchilite/formattermanager.h"
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




// SyntaxListener that triggers each time the syntax highlighter fires off an event
class ElemFormatManager : public srchilite::FormatterManager
{
public:
    ElemFormatManager(FormatterPtr _defaultFormatter) : FormatterManager(_defaultFormatter){
        cout << "--> USING CUSTOM FORMATTER" << endl;
    };
    
    //Overriden accessor for getting a formatter creates a generic line formatter
    virtual FormatterPtr getFormatter(const std::string &elem) const;
private:
    mutable FormatterMap formatterMap;
    FormatterPtr defaultFormatter;
};



//Passthrough infoformatter that dumps the seperated elements into the current line
class LineFormatter: public srchilite::Formatter
{    
public:
    LineFormatter(const std::string &elem_ = "normal") : elem(elem_) {}
    void setTargetLine(boost::shared_ptr<Line> line){m_targetLine = line; };
    void setNextElemType(string & elem_){ elem = elem_; };
    virtual void format(const std::string &s, const srchilite::FormatterParams *params = 0);
private:
    boost::shared_ptr<Line> m_targetLine;
    std::string elem;
};



//Extended base highlighter class
class LineHighlighter : public srchilite::SourceHighlighter {\
public:
    virtual void format(const std::string &elem, const std::string &s);
    void setElemFormatterManager(boost::shared_ptr<ElemFormatManager> manager){ formatterManager = manager; };
private:
    boost::shared_ptr<ElemFormatManager> formatterManager;
};




/// shared pointer for InfoFormatter
typedef boost::shared_ptr<LineFormatter> LineFormatterPtr;

#endif /* defined(__GitDive_Cinder__SyntaxColourListener__) */
