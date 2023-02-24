//
//  soundPlayer.hpp
//  incarnate
//
//  Created by Teodosin Viktor on 22/02/2023.
//

#pragma once
#include "ofMain.h"

class soundPlayer {
public:
    soundPlayer();
    
    void playSound();
    void draw();
    
    ofSoundPlayer sound1, sound2;
};
