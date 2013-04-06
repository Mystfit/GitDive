//
//  SyntaxColourListener.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 6/04/13.
//
//

#include "SyntaxColourTools.h"


//LineHighlighter::LineHighlighter(HighlightStatePtr mainState) : mainHighlightState(mainState), currentHighlightState(mainState)
//{
//    
//}
//void LineHighLighter::format(const std::string &elem, const std::string &s) {
//    formatterManager->getFormatter(elem);
//    SourceHighlighter::format(elem, s);
//}


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


LineFormatterManager::LineFormatterManager(FormatterPtr _defaultFormatter) : FormatterManager(_defaultFormatter)
{
}


FormatterPtr LineFormatterManager::getFormatter(const std::string &elem) const{
    
    //Update the line pointer
    
    if (!formatterMap[elem].get()) {
        formatterMap[elem] = boost::shared_ptr<LineFormatter>(new LineFormatter(elem));
        FormatterPtr fmtPtr = formatterMap[elem];
        //boost::shared_ptr<LineFormatter> formatter = dynamic_cast< boost::shared_ptr<LineFormatter> >(fmtPtr);
        
        boost::shared_ptr<LineFormatter> formatter = boost::dynamic_pointer_cast<LineFormatter>(formatterMap[elem]));
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
