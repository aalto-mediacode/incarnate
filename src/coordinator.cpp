//
//  coordinator.cpp
//  incarnate
//
//  Created by Teodosin on 22/02/2023.
//

#include "coordinator.h"
#include "ofMain.h"

// Functions to convert a -1 to 1 value to screen coordinates
float pixX(float deciX){
    
    float pixelX = center.x + deciX * center.x;

    return pixelX;
}

float pixY(float deciY){
    
    float pixelY = center.y + deciY * center.y;

    return pixelY;
}


// Functions to convert screen coordinates to -1, 1 values based on screen center
float decX(float pixelX){
    
    float deciX = 1.f / pixelX - center.x;

    return deciX;
}
float decY(float pixelY){
    
    float deciY = 1.f / pixelY - center.y;

    return deciY;
}
