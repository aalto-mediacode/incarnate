



#pragma once
#include "ofMain.h"

#include "dataParticle.h"

class layer {  
    public:
        layer();
    
        void draw();
    
        void addDataParticle(glm::vec2 pos, glm::vec2 size);
    
        ofColor layerColor;
        
        vector <dataParticle> dp;
};
