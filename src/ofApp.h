#pragma once


#include "ofxGui.h"

#include "ofMain.h"

#include "soundPlayer.h"

#include "particle.h"
#include "layer.h"

class ofApp : public ofBaseApp{

	public:
        // The basic functions
		void setup();
		void update();
		void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        //---------------------------------------------------------
    
        // Audio player
        soundPlayer audioboi;

        // Button event callback functions
        void layerAdded();
        void moveToPreviousLayer();
        void moveToNextLayer();
        void moveToRandomLayer();
    
        // Helper functions
        void resetParticles();
        void addLayer();
        void changeLayerColor();
        void spawnParticle(glm::vec2 pos, glm::vec2 size);
    
        void setAllInactive();
        void incarnateLayer();
        void activateClosestParticle(dataParticle trgt);

    
        // Helpful data
        int currentLayer;
        bool performanceMode = false;
    
        glm::vec2 center;
    
    
        
        // Layers panel
        ofxPanel gui_layers;
 
        ofxButton createLayer;
    
        ofxColorSlider particlesColor;
        ofxColorSlider layerColor;
        
        ofxLabel currentLayerLabel;
        ofxLabel layerAmountLabel;
        ofxButton previousLayer;
        ofxButton nextLayer;
    
        bool layersHide;
    
        // Debug panel
        ofxPanel gui_debug;
        ofxLabel screenCenter;
    
        bool debugHide;
		
        // Arrays for the app
        vector <particle> p; // for storing particles
        vector <layer> layers; // for storing layers 
    
};
