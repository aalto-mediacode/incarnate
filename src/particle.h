



#pragma once
#include "ofMain.h"
#include "dataParticle.h"

enum particleState{
    PARTICLE_STATE_IDLE,
    PARTICLE_STATE_LOCKED
};

class particle {
    public:
        particle(
                 glm::vec2 pos = glm::vec2(0,0),
                 glm::vec2 size = glm::vec2(0,0)
                 );
        
        void reset();
        void update();
        void draw();
        
        glm::vec2 pos;
        glm::vec2 size;
    
        glm::vec2 vel;
        glm::vec2 lookat;
        float angle = 0;
    
        bool activeTarget;
        dataParticle target;
        glm::vec2 startPos;
        glm::vec2 startSize;
        int movementTime;
        float transitionPhase;
    
        ofColor baseColor;
        ofColor targetColor;
        ofColor colorVariation;
    
        void setBaseColor(ofColor base);
    
        void setActive(dataParticle &trgt, ofColor layerClr, float duration);
        void setInactive();
    
};
