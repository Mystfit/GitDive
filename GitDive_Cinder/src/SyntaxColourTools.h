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
#include "srchilite/highlighttoken.h"
#include "srchilite/highlightrule.h"
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





class InfoFormatter: public srchilite::Formatter {
    /// the language element represented by this formatter
    std::string elem;
    
public:
    InfoFormatter(const std::string &elem_ = "normal") :
    elem(elem_) {
    }
    
    void setLine(boost::shared_ptr<Line> line){m_targetLine = line; };
    
    virtual void format(const std::string &s,
                        const srchilite::FormatterParams *params = 0) {
        // do not print anything if normal or string to format is empty
        //if (elem != "normal" || !s.size()) {
        std::cout << elem << ": " << s;
        if (params)
            std::cout << ", start: " << params->start;
        std::cout << std::endl;
        
        m_targetLine->addLineElement(LineElement(elem, s, params->start));
        //}
    }
private:
    boost::shared_ptr<Line> m_targetLine;
};

/// shared pointer for InfoFormatter
typedef boost::shared_ptr<InfoFormatter> InfoFormatterPtr;

#endif /* defined(__GitDive_Cinder__SyntaxColourListener__) */
