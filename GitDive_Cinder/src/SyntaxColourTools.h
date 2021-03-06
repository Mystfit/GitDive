//
//  SyntaxColourListener.h
//  GitDive_Cinder
//
//  Created by Byron Mallett on 6/04/13.
//
//

#ifndef __GitDive_Cinder__SyntaxColourListener__
#define __GitDive_Cinder__SyntaxColourListener__

//#define DATADIR_THEMES "../Resources/srchilite/themes"
//#define DATADIR_LANGUAGES "../Resources/srchilite/languages"

#define DATADIR_THEMES "/usr/local/share/source-highlight"
#define DATADIR_LANGUAGES "/usr/local/share/source-highlight"


#include <iostream>
#include "srchilite/sourcehighlighter.h"
#include "srchilite/textstyleformatterfactory.h"
#include "srchilite/textstyles.h"
#include "srchilite/outlangdefparserfun.h"
#include "srchilite/langmap.h"
#include "srchilite/parsestyles.h"
#include "srchilite/preformatter.h"
#include "srchilite/formatter.h"
#include "srchilite/ctagsformatter.h"
#include "srchilite/formattermanager.h"
#include "srchilite/formatterparams.h"
#include "srchilite/highlighteventlistener.h"
#include "srchilite/highlightevent.h"
#include "srchilite/highlighttoken.h"
#include "srchilite/highlightrule.h"
#include "srchilite/langdefmanager.h"
#include "srchilite/regexrulefactory.h"
#include "srchilite/stylefileparser.h"
#include "GitDataTypes.h"
#include "LineElementManager.h"

using namespace srchilite;


/*
 * SyntaxListener that triggers each time the syntax highlighter fires off an event
 */
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




/*
 * Custom FormatterManager that hooks into all the other managers as required
 */
class LineFormatterManager : public srchilite::FormatterManager
{
public:
    //Constructor references the overall line element manager for getting free elements
    LineFormatterManager(boost::shared_ptr<LineElementManager> elemManager);
    
    //Overriden accessor for getting a formatter creates a generic line formatter
    FormatterPtr getFormatter(const std::string &elem) const;
    
    //The formatter manager needs to be targetting a line before doing syntax parsing
    void setTargetLine(boost::shared_ptr<Line> target);
    void syntaxParseLines(vector< boost::shared_ptr<Line> > lines, string lang);


private:
    mutable FormatterMap formatterMap;
    FormatterPtr defaultFormatter;
    boost::shared_ptr<LineElementManager> m_lineElementManger;
    boost::shared_ptr<Line> m_targetLine;
};




/*
 * Custom formatter to actually handle line parsing. Basically just a passthrough
 */
class LineFormatter: public srchilite::Formatter
{    
public:
    LineFormatter(boost::shared_ptr<LineElementManager> elemManager, const std::string &elem_ = "") : m_lineElemManager(elemManager), elem(elem_) {};
    void format(const std::string &s, const srchilite::FormatterParams *params = 0);
    static string getFileLangType(string filename);

private:
    boost::shared_ptr<LineElementManager> m_lineElemManager;
    std::string elem;
};




////Extended base highlighter class
//class LineHighlighter : public srchilite::SourceHighlighter {
//public:
//    LineHighlighter(HighlightStatePtr mainState);
//    virtual void format(const std::string &elem, const std::string &s);
//    void setElemFormatterManager(boost::shared_ptr<ElemFormatManager> manager){ formatterManager = manager; };
//private:
//    boost::shared_ptr<ElemFormatManager> formatterManager;
//};
//



/// shared pointer for InfoFormatter
typedef boost::shared_ptr<LineFormatter> LineFormatterPtr;

#endif /* defined(__GitDive_Cinder__SyntaxColourListener__) */
