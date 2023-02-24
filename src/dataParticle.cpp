//
//  dataParticle.cpp
//  incarnate
//
//  Created by Teodosin Viktor on 22/02/2023.
//

#include "dataParticle.h"

//-------------------------------------------
// Constructor, I think?
dataParticle::dataParticle(glm::vec2 poss, glm::vec2 ssize){
    pos = poss;
    size = ssize;
}

//-------------------------------------------
// Reset, reinitialise, something something
void dataParticle::reset(){

}

//-----------------------------------------------------------------
void dataParticle::update(){
    
}

//-----------------------------------------------------------------
void dataParticle::draw(){
    ofPushMatrix();
    ofTranslate(pos.x + size.x / 2, pos.y + size.y / 2);
    
        
    ofNoFill();
    ofSetColor(255, 180, 255);
    
    ofDrawRectangle(-size.x / 2, -size.y / 2, size.x, size.y);
    
    ofPopMatrix();
}
