//
//  soundPlayer.cpp
//  incarnate
//
//  Created by Teodosin Viktor on 22/02/2023.
//

#include "ofMain.h"
#include "soundPlayer.h"

soundPlayer::soundPlayer(){
    sound1.load("ambiance_track.mp3");
}

void soundPlayer::playSound(){
    sound1.play();
    sound1.setLoop(true);
}

void soundPlayer::draw(){
    int nBands = 128;
    int width = 200 / nBands;
    float scale = 150;
    float *mySpectrum = ofSoundGetSpectrum(nBands); // First time using a pointer
    
    ofSetColor(255, 255, 255);
    ofFill();
    for (unsigned int i = 0; i < nBands; i++){
        ofDrawRectangle(20 + i*width, ofGetHeight() - 70 -mySpectrum[i] * scale, width, mySpectrum[i] * scale * 2);
    }
}
