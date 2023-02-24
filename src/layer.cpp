//
//  layer.cpp
//  incarnate
//
//  Created by Teodosin Viktor on 22/02/2023.
//

#include "layer.h"
#include "dataParticle.h"

layer::layer(){

}

void layer::addDataParticle(glm::vec2 pos, glm::vec2 size){
    dataParticle newParticle = dataParticle(pos, size);
    
    dp.push_back(newParticle);
}

void layer::draw(){
    // Draw all particles
    for (unsigned int i = 0; i < dp.size(); i++){
        dp[i].draw();
    }
}
