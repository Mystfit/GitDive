//
//  SyntaxColourListener.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 6/04/13.
//
//

#include "SyntaxColourTools.h"

void SourceHighlighter::format(const std::string &elem, const std::string &s) {
    if (suspended)
        return;
    
    if (!s.size())
        return;
    
    // the formatter is allowed to be null
    if (formatterManager) {
        if (!optimize) {
            formatterManager->getFormatter(elem)->format(s, formatterParams);
        } else {
            // otherwise we optmize output generation: delay formatting a specific
            // element until we deal with another element; this way strings that belong
            // to the same element are formatted using only one tag: e.g.,
            // <comment>/* mycomment */</comment>
            // instead of
            // <comment>/*</comment><comment>mycomment</comment><comment>*/</comment>
            if (elem != currentElement) {
                if (currentElement.size())
                    flush();
            }
            
            currentElement = elem;
            currentElementBuffer << s;
        }
    }
}


SyntaxColourListener::SyntaxColourListener(){
}

SyntaxColourListener::~SyntaxColourListener(){
}

void SyntaxColourListener::notify(const srchilite::HighlightEvent &event){
//    cout << event.type << " on line " << m_targetLine->getStr() << endl;
//    switch (event.type) {
//        case HighlightEvent::FORMAT:
//            // print information about the rule
//            if (event.token.rule) {
//                cout << event.token.rule->getAdditionalInfo() << endl;
//                //cout << "expression: \"" << event.token.rule->toString() << "\""<< endl;
//            }
//            
//            // now format the matched strings
//            for (MatchedElements::const_iterator it = event.token.matched.begin(); it
//                 != event.token.matched.end(); ++it) {
//                cout << "formatting \"" << it->second << "\" as " << it->first
//                << endl;
//            }
//            break;
//        case HighlightEvent::FORMATDEFAULT:
//            cout << "formatting \"" << event.token.matched.front().second
//            << "\" as default" << endl;
//            break;
//        case HighlightEvent::ENTERSTATE:
//            cout << "entering state: " << event.token.rule->getNextState()->getId()
//            << endl;
//            break;
//        case HighlightEvent::EXITSTATE:
//            int level = event.token.rule->getExitLevel();
//            cout << "exiting state, level: ";
//            if (level < 0)
//                cout << "all";
//            else
//                cout << level;
//            cout << endl;
//            break;
//    }
}


FormatterPtr ElemFormatManager::getFormatter(const std::string &elem) const{
    
    if (!formatterMap[elem].get()) {
        formatterMap[elem] = boost::shared_ptr<LineFormatter>(new LineFormatter(elem));
    }
            
    return formatterMap[elem];
}




void LineFormatter::format(const std::string &s, const srchilite::FormatterParams *params) {
    m_targetLine->addLineElement(LineElement(elem, s, params->start));
    std::cout << "Adding " << elem << " to line: " << s;
    if (params)
        std::cout << ", start: " << params->start;
    std::cout << std::endl;
}
