//
//  TextRenderer.cpp
//  GitDive_Cinder
//
//  Created by Byron Mallett on 8/04/13.
//
//

#include "TextRenderer.h"

TextRenderer::TextRenderer(){
    cinder::Font customFont( cinder::Font( "GohuFont", FONT_SIZE ) );
	cinder::gl::TextureFont::Format f;
	//f.enableMipmapping( true );
    f.textureHeight(2048);
    f.textureWidth(2048);
    string supportedChars = cinder::gl::TextureFont::defaultChars() + "{}";
	m_textureFont = cinder::gl::TextureFont::create( customFont, f, supportedChars );
    
    string cssPath = DATADIR_THEMES;
    string cssFile = "sh_blacknblue.css";
    m_cssColours = boost::shared_ptr<CssParser>(new CssParser());
    m_cssColours->loadFile( cssPath + "/" + cssFile );
    m_backgroundColour = cinder::Color::hex(m_cssColours->getColour(CSS_BACKGROUND));
    cout << "BG:" << m_backgroundColour << endl;
    
    m_textZoom = 1.0f;
}


void TextRenderer::setLinesAnimatable(){
    vector< boost::shared_ptr<Line> > lines;
    if(m_targetFile) lines = m_targetFile->getLines();
    
    if(lines.size()){
        for(vector< boost::shared_ptr<Line> >::iterator line = lines.begin(); line != lines.end(); ++line){
            
            line->get()->markAsAnimatable();
            vector< boost::shared_ptr<LineElement> > lineElems = line->get()->getLineElements();

            for(vector< boost::shared_ptr<LineElement> >::iterator elem = lineElems.begin(); elem != lineElems.end(); ++elem){
                elem->get()->markAsAnimatable();
            }
        }
    }
}


void TextRenderer::setTextOffset(float increment){
    m_textOffset.ptr()->y += increment;
    //m_textOffset.ptr()->x = 1024 * (1.0f / m_textZoom);
//    if(m_targetFile){
//        if(m_textOffset.y < floor(m_targetFile->getLines().size() * LINE_HEIGHT )){
//            m_textOffset.y = floor(m_targetFile->getLines().size() * LINE_HEIGHT);
//        } else if(m_textOffset.y > 0){
//            m_textOffset.y = 0;
//        }
//    }
}

void TextRenderer::setTextZoom(float zoom){
    m_textZoom += zoom;
    if(m_textZoom < 1.0f){
        bDrawSquares = true;
    } else {
        bDrawSquares = false;
    }
}

void TextRenderer::resetView(){
    m_textZoom = 1.0f;
    m_timeline->apply(&m_textOffset, cinder::Vec2f(), 1.0f);
}





void TextRenderer::makeLineFromFreeElements(boost::shared_ptr<Line> line){

}


//void TextRenderer::animLinesIn(vector<boost::shared_ptr<Line> > lines){
//    for(vector<boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
//        if(it->get()->getLineState() == Line::LINE_ADDED){
//            it->get()->applyCss(m_cssColours);
//            it->get()->setPosition(cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT));
//            it->get()->animIn(m_timeline, cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT), cinder::Color(1.0f, 1.0f, 1.0f));
//        } else if(it->get()->getLineState() == Line::LINE_NORMAL){
//            it->get()->animIn(m_timeline, cinder::Vec2f(0, it->get()->getLinePos() * LINE_HEIGHT), cinder::Color(1.0f, 1.0f, 1.0f));
//        }
//    }
//}


void TextRenderer::breakLine(boost::shared_ptr<Line> line){
    m_lineManager->salvageLine(line->getLineElements());
    
    line->markAsAnimatable();
    
    if(line->getLineElements().size() == 0){
        if(line->isJustAnimating()) line->animOut(m_timeline, cinder::Vec2f(0, line->getLinePos() * LINE_HEIGHT), cinder::Color(0.0f,0.0f,0.0f), 8.0f);
    }
}

void TextRenderer::update(){
    if(m_targetFile) m_targetFile->update();
    
    vector< boost::shared_ptr<LineElement> > freeElems = m_lineManager->getFloatingElements();
    vector< boost::shared_ptr<LineElement> >::iterator elem;
    
    //Start animation for freed line elements
    for(elem = freeElems.begin(); elem != freeElems.end(); ++elem){
        if(elem->get()->isJustFreed()){
            elem->get()->animOut(m_timeline, elem->get()->getPosition(), cinder::Color(0.0f, 0.0f, 0.0f), 2.0f);
        }
    }
    
    
    //Start animation for all line elements
    vector< boost::shared_ptr<Line> > lines;
    if(m_targetFile) lines = m_targetFile->getLines();

    if(lines.size()){
        float lineYtotal = 0;
        int lineYcount = 0;
        for(vector< boost::shared_ptr<Line> >::iterator line = lines.begin(); line != lines.end(); ++line){
            
            if(bDrawSquares) line->get()->markDrawSquares();
            else line->get()->markDrawText();

            //if(line->get()->isJustAnimating()){
            if(line->get()->getLineState() == Line::LINE_ADDED){
            //if(line->get()->isJustAnimating()){
                //line->get()->setColour(cinder::Color::hex(m_cssColours->getColour("normal")));
                line->get()->setPosition(cinder::Vec2f(0, line->get()->getLinePos() * LINE_HEIGHT));
                lineYtotal += line->get()->getLinePos() * LINE_HEIGHT;
                lineYcount++;

                //line->get()->animIn(m_timeline, cinder::Vec2f(0, line->get()->getLinePos() * LINE_HEIGHT), cinder::Color(1.0f, 1.0f, 1.0f), 0.2f);
            //}
            } else if(line->get()->getLineState() == Line::LINE_NORMAL){
            //if(line->get()->isJustAnimating()){
                //line->get()->setPosition(cinder::Vec2f(0, line->get()->getLinePos() * LINE_HEIGHT));
                line->get()->animIn(m_timeline, cinder::Vec2f(0, line->get()->getLinePos() * LINE_HEIGHT), cinder::Color(1.0f, 1.0f, 1.0f), 0.2f);
            //}
            }
        
        
            float lineY = line->get()->getLinePos() * LINE_HEIGHT;
        
            vector< boost::shared_ptr<LineElement> > lineElems = line->get()->getLineElements();
            
            for(vector< boost::shared_ptr<LineElement> >::iterator elem = lineElems.begin(); elem != lineElems.end(); ++elem){
                
                if(bDrawSquares) elem->get()->markDrawSquares();
                else elem->get()->markDrawText();
                
                float elemX = (float)elem->get()->position * FONT_WIDTH;
                
                if(elem->get()->isJustAnimating()){
                    //Replace with something better
                    //elem->get()->setColour(cinder::Color::hex(m_cssColours->getColour(elem->get()->elem)));
                    //elem->get()->setPosition(cinder::Vec2f(elemX, lineY));
                    float randTimeOffset = ((float)rand()/(float)RAND_MAX) * 0.4f;
                    elem->get()->animIn(m_timeline, cinder::Vec2f(elemX, lineY), cinder::Color::hex(m_cssColours->getColour(elem->get()->elem)), 0.2f + randTimeOffset );
                }
            }
            
            //Update camera
            if(bCameraFollowing){
                cinder::EaseOutQuart easer;
                
                if(lineYcount){
                    cinder::Vec2f camOffset = cinder::Vec2f(0.0f, lineY * 0.5 * -1.0f);
                    m_timeline->apply(&m_textOffset, camOffset, 0.6f, easer);
                }   
            }
            //}
        }
        
        

    }
}



void TextRenderer::draw(){
    
    cinder::gl::pushMatrices();
    cinder::gl::scale(cinder::Vec2f(m_textZoom, m_textZoom));
    
    vector< boost::shared_ptr<Line> > lines;
    
    if(m_targetFile) lines = m_targetFile->getLines();
    else return;
    
    if(lines.size()){
        for(vector< boost::shared_ptr<Line> >::iterator it = lines.begin(); it != lines.end(); ++it){
            it->get()->draw(m_textureFont, m_textOffset);
        }
    }
    
    vector< boost::shared_ptr<LineElement> > freeLineElems = m_lineManager->getFloatingElements();
    
    if(freeLineElems.size()){
        //Draws the free-floating line elements
        for(int i = 0; i < freeLineElems.size(); i++){
            freeLineElems[i]->draw(m_textureFont, m_textOffset);
        }
    }
    
    cinder::gl::popMatrices();

}
