//
//  particle.cpp
//  incarnate
//
//  Created by Teodosin on 21/02/2023.
//

#include "particle.h"

//-------------------------------------------
// Constructor, I think?
particle::particle(glm::vec2 poss, glm::vec2 ssize){
    pos = poss;
    size = ssize;
    
    
    activeTarget = false;
}

//-------------------------------------------
// Reset, reinitialise, something something
void particle::reset(){
    // Unique value necessary?
    
    pos.x = ofRandomWidth() - ofGetWidth()/2;
    pos.y = ofRandomHeight() - ofGetHeight()/2;
    
    size.x = ofRandom(5, 100);
    size.y = ofRandom(5, 100);
    
    vel.x = ofRandom(-5.f, 5.f);
    vel.y = ofRandom(-5.f, 5.f);
}

void particle::setBaseColor(ofColor base){ 
    baseColor = base;
    colorVariation = ofColor(ofRandom(255.f), ofRandom(255.f), ofRandom(255.f));
}

//-------------------------------------------------------------------
// Functions for setting if a particle has an active target.
void particle::setActive(dataParticle &trgt, ofColor layerClr, float duration){
    activeTarget = true;
    target = trgt;
    startPos = pos;
    startSize = size;
    movementTime = duration;
    transitionPhase = 0.0;
    
    targetColor = layerClr;
    
}

void particle::setInactive(){
    if (activeTarget == true){
        vel.x = ofRandom(-1.f, 1.f);
        vel.y = ofRandom(-1.f, 1.f);
    }
    activeTarget = false;
    
}

//-----------------------------------------------------------------
void particle::update(){
    if (activeTarget == true){
        // If there's an active target, interpolate position, size.
        
        transitionPhase += 0.09;
        if (transitionPhase >= 1.0){
            transitionPhase = 1.0;
        }
        
        pos.x = ofLerp(startPos.x, target.pos.x + target.size.x / 2, transitionPhase);
        pos.y = ofLerp(startPos.y, target.pos.y + target.size.y / 2, transitionPhase);
        
        size.x = ofLerp(startSize.x, target.size.x, transitionPhase);
        size.y = ofLerp(startSize.y, target.size.y, transitionPhase);
        

    }
    else {

        // UPDATE POSITION
        pos += vel;
        
        // Bounce off edges if hit
        if (pos.x < 0 - ofGetWidth()/2 || pos.x > ofGetWidth()/2){
            vel.x *= -1.f;
        }
        if (pos.y < 0 - ofGetHeight()/2 || pos.y > ofGetHeight()/2){
            vel.y *= -1.f;
        }
    }
}

//-----------------------------------------------------------------
void particle::draw(){
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
        
    ofFill();
    
    ofColor clr = baseColor;
    
    // The backward transition is only relevant for color,
    // since we want to keep their transformed size and position.
    if (activeTarget == false){
        transitionPhase -= 0.12;
        if (transitionPhase <= 0.0) {
            transitionPhase = 0.0;
        }
    }
    
    clr = baseColor;
    clr.lerp(targetColor, transitionPhase);

    ofSetColor(clr);
    
    ofDrawRectangle(-size.x / 2, -size.y / 2, size.x, size.y);
    
    // Debug text
    ofSetColor(255,255,255);
    //ofDrawBitmapString(ofToString(transitionPhase), 0, 0);
    //ofDrawBitmapString(activeTarget, 0, 0);
    //ofDrawBitmapString(&activeTarget, 0, 20);
    
    ofPopMatrix();
}

/*
 How should a swarm of particles choose their targets?
 * Only one particle per dataParticle
 * particles smoothly move and resize to the target dataParticle
 
 I need to lerp them, and I need to keep track of the time.
 
 get milliseconds for the time of start () variable
 have a length of time for the movements () variable
 
 for each dataParticle, find the closest particle without an activeTarget and set the dataParticle as its target
 
 */
