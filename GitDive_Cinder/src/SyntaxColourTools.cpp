//
//  SyntaxColourListener.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 6/04/13.
//
//

#include "SyntaxColourTools.h"


SyntaxColourListener::SyntaxColourListener(){
}

SyntaxColourListener::~SyntaxColourListener(){
}

void SyntaxColourListener::notify(const srchilite::HighlightEvent &event){
    cout << event.type << " on line " << m_targetLine->getStr() << endl;
    switch (event.type) {
        case HighlightEvent::FORMAT:
            // print information about the rule
            if (event.token.rule) {
                cout << event.token.rule->getAdditionalInfo() << endl;
                //cout << "expression: \"" << event.token.rule->toString() << "\""<< endl;
            }
            
            // now format the matched strings
            for (MatchedElements::const_iterator it = event.token.matched.begin(); it
                 != event.token.matched.end(); ++it) {
                cout << "formatting \"" << it->second << "\" as " << it->first
                << endl;
            }
            break;
        case HighlightEvent::FORMATDEFAULT:
            cout << "formatting \"" << event.token.matched.front().second
            << "\" as default" << endl;
            break;
        case HighlightEvent::ENTERSTATE:
            cout << "entering state: " << event.token.rule->getNextState()->getId()
            << endl;
            break;
        case HighlightEvent::EXITSTATE:
            int level = event.token.rule->getExitLevel();
            cout << "exiting state, level: ";
            if (level < 0)
                cout << "all";
            else
                cout << level;
            cout << endl;
            break;
    }
}


LineFormatterManager::LineFormatterManager(FormatterPtr _defaultFormatter) : FormatterManager(_defaultFormatter)
{
}


void LineFormatterManager::setTargetLine(boost::shared_ptr<Line> target){
    m_targetLine = target;
    
    for(FormatterMap::iterator it = formatterMap.begin(); it != formatterMap.end(); ++it){
        boost::shared_ptr<LineFormatter> formatter = boost::dynamic_pointer_cast<LineFormatter>(it->second);
        formatter->setTargetLine(m_targetLine);
    }
}


FormatterPtr LineFormatterManager::getFormatter(const std::string &elem) const{
    if (!formatterMap[elem].get()) {
        formatterMap[elem] = boost::shared_ptr<LineFormatter>(new LineFormatter(elem, m_targetLine));
    }
    
    return formatterMap[elem];
}




void LineFormatter::format(const std::string &s, const srchilite::FormatterParams *params) {
    
    if(elem == "") elem = "normal";

    //The highlighter adds newlines automatically to the end of the line. Chuck em!
    string str = s;
    Utils::strip(str, "\n");
    
    std::cout << "Adding " << elem << " to line " << m_targetLine->getLinePos() << " at pos " << params->start << "|" << str << "|" << endl;

    m_targetLine->addLineElement(LineElement(elem, str, params->start));
}

string LineFormatter::getFileLangType(string filename){
    string inputLang = "cpp.lang";
    srchilite::LangMap langMap(DATADIR, "lang.map");
    string lang = langMap.getMappedFileNameFromFileName(filename);
    if (lang == "") lang = inputLang;
    
    return lang;
}


void LineFormatter::syntaxParseLines(vector<boost::shared_ptr<Line> > lines, string lang){
    
    //Set up highlighter based on language
    srchilite::RegexRuleFactory ruleFactory;
    srchilite::LangDefManager langDefManager(&ruleFactory);
    srchilite::SourceHighlighter highlighter(langDefManager.getHighlightState(DATADIR, lang));
    
    //Set up formatters to modify our lines
    boost::shared_ptr<LineFormatter> passthroughLineFormatter(new LineFormatter("", boost::shared_ptr<Line>()));
    boost::shared_ptr<LineFormatterManager> formatterManager(new LineFormatterManager(passthroughLineFormatter));
    highlighter.setFormatterManager(formatterManager.get());
    
    //Set up params to hold the element position from the start of the line
    srchilite::FormatterParams params;
    highlighter.setFormatterParams(&params);
    
    //    //Set up listener to modify the output - handled in the formatter now
    //    boost::shared_ptr< SyntaxColourListener > colourListener(new SyntaxColourListener());
    //    highlighter.addListener(colourListener.get());
    
    //Iterate over the lines and highlight as we go
    //The formatter needs to follow along with the current line target at the same time
    for(int i = 0; i < lines.size(); i++){
        cout << "Line state:" << lines[i]->getLineState() << endl;
        if(lines[i]->getLineState() == Line::LINE_ADDED){
            params.start = 0;
            formatterManager->setTargetLine(lines[i]);
            //colourListener->setTargetLine(lines[i]);
            highlighter.highlightParagraph(lines[i]->getStr());
        }
    }
}
