//
//  dataParticle.hpp
//  incarnate
//
//  Created by Teodosin Viktor on 22/02/2023.
//

#pragma once
#include "ofMain.h"

class dataParticle {
public:
    dataParticle(
             glm::vec2 pos = glm::vec2(0,0),
             glm::vec2 size = glm::vec2(0,0)
             );
    
    glm::vec2 pos;
    glm::vec2 size;
    
    void reset();
    void update();
    void draw();
};
