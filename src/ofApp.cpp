#include "ofApp.h"

bool creatingRect = false;
glm::vec2 createRectPos(0,0);
glm::vec2 createRectSize(0,0);

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(10, 10, 10);
    
    // For debug purposes
    //ofSetFrameRate(10);
    
    // Get the center of the screen.
    center = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    
    // Add listeners for gui buttons
    createLayer.addListener(this, &ofApp::layerAdded);
    previousLayer.addListener(this, &ofApp::moveToPreviousLayer);
    nextLayer.addListener(this, &ofApp::moveToNextLayer);
        
    
    // Create gui panel for layers and add it's parameters
    gui_layers.setup("layers");
    gui_layers.add(createLayer.setup("add_layer"));
    
    gui_layers.add(layerAmountLabel.setup("amount of layers", ofToString(layers.size())));
    gui_layers.add(currentLayerLabel.setup("current layer", ofToString(currentLayer+1)));

    gui_layers.add(particlesColor.setup(ofColor(20,40,80)));
    gui_layers.add(layerColor.setup(ofColor(40,180,20)));
    
    gui_layers.add(previousLayer.setup("previous layer"));
    gui_layers.add(nextLayer.setup("next layer"));
    
    // Create gui panel for debug info and add it's parameters
    gui_debug.setup("debug");
    gui_debug.add(screenCenter.setup("screen center", ofToString(center.x) + " " + ofToString(center.y)));
    
    debugHide = true; // Then hide it :)
    
                    
    // Add a first layer so the array/vector isn't just empty
    addLayer();
    
    p.assign(500, particle()); // Add a bunch of particles
    resetParticles();
    
    // Audio player is incomplete and doesn't have features apart from
    // simple band visualisation.
    // audioboi.playSound();
}

void ofApp::setAllInactive(){
    for (unsigned int i = 0; i < p.size(); i++){
        p[i].setInactive();
    }
}

//-------------------------------------------------------------------
void ofApp::incarnateLayer(){
    setAllInactive();
    
    // Loop through dataParticles of the current layer.
    // Set the closest as Active and pass the dataParticle to it as its target.
    
    for (unsigned int i = 0; i < layers[currentLayer].dp.size(); i++){
        //p[0].setActive(layers[currentLayer].dp[0], 10.f);
        
        activateClosestParticle(layers[currentLayer].dp[i]);
    }
    
}

void ofApp::activateClosestParticle(dataParticle trgt){
    // Very inefficient but will have to do.
    
    // This method used to return a particle object, and then the incarnateLayer ()
    // method would call the setActive() method on the returned object. For whatever
    // reason (probably a copy/memory related issue) that didn't work, but calling
    // the setActive() directly on p[closestIndex] does.
    
    float closestDist = 10000.f;
    int closestIndex;
    
    for (unsigned int i = 0; i < p.size(); i++ ){
        float dist = glm::distance(p[i].pos, trgt.pos);
        
        // particle must not already have an active target to be selected
        if (dist < closestDist && p[i].activeTarget == false){
            closestDist = dist;
            closestIndex = i;
        }
    }
    
    p[closestIndex].setActive(trgt, layerColor, 10.f);
}

//--------------------------------------
void ofApp::resetParticles(){
    for (unsigned int i = 0; i < p.size(); i++){
        p[i].reset();
    }
}

//---------------------------------------------------------
// Functions relating to layers
void ofApp::layerAdded(){
    addLayer();
}

void ofApp::addLayer(){
    layer newLayer = layer();
    layers.push_back(newLayer);
    
    layerAmountLabel = ofToString(layers.size());
}

void ofApp::changeLayerColor(){
    
}

void ofApp::moveToPreviousLayer(){
    if (layers.size() < 2){
        return; // Can't move between layers if there is only one or none
    }
    
    currentLayer -= 1;
    
    if (currentLayer < 0){
        currentLayer = layers.size() - 1;
    }
    
    currentLayerLabel = ofToString(currentLayer+1);
    
    layers[currentLayer].layerColor = layerColor;
    
}
void ofApp::moveToNextLayer(){
    if (layers.size() < 2){
        return; // Can't move between layers if there is only one or none
    }
    
    currentLayer += 1;
    
    if (currentLayer > layers.size() - 1){
        currentLayer = 0;
    }
    
    currentLayerLabel = ofToString(currentLayer+1);
    
    layers[currentLayer].layerColor = layerColor;
    
}

void ofApp::moveToRandomLayer(){
    currentLayer = (int) ofRandom(layers.size() - 1);
    
    currentLayerLabel = ofToString(currentLayer+1);
    
    layers[currentLayer].layerColor = layerColor;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update all particles
    for (unsigned int i = 0; i < p.size(); i++){
        p[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    // Check if base colors of particles needs to be updated.
    if (p[0].baseColor != particlesColor){
        for (unsigned int i = 0; i < p.size(); i++){
            p[i].setBaseColor(particlesColor);
        }
    }
    // Same but for the current layer color.
    if (layers[currentLayer].layerColor != layerColor){
        layers[currentLayer].layerColor = layerColor;
    }
    
    // Add active particles to their own vector.
    // Draw all inactive particles.
    vector <particle> actives;
    for (unsigned int i = 0; i < p.size(); i++){
        if (p[i].activeTarget == true){
            actives.push_back(p[i]);
            continue;
        }
        p[i].draw();
    }
    
    // Draw all active particles.
    for (unsigned int i = 0; i < actives.size(); i++){
        actives[i].draw();
    }
    
    // Draw the to be created rect particle
    if (creatingRect){
        ofSetColor(255,255,255);
        ofNoFill();
        ofDrawRectangle(createRectPos.x, createRectPos.y,
                        ofGetMouseX() - createRectPos.x - center.x,
                        ofGetMouseY() - createRectPos.y - center.y
        );
    }
    
    // Draw the currently active layer if it's on.
    if (performanceMode == false){
        layers[currentLayer].draw();
    }
    
    ofPopMatrix();
    
    // Audio player is incomplete and doesn't have features apart from
    // simple band visualisation.
    // audioboi.draw();
    
    // Draw gui.
    
    // Display debug panel.
    if(!debugHide){
        gui_debug.draw();
    }
    
    if (performanceMode == false){
        gui_layers.draw();
        
        // Draw instructions for use.
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("HOW TO USE:", 20, ofGetHeight() - 9 * 15);
        ofDrawBitmapString("Use the layers panel to manage layers.", 20, ofGetHeight() - 8 * 15);
        ofDrawBitmapString("Press either mouse button to draw a particle frame on the current layer. ", 20, ofGetHeight() - 7 * 15);
        ofDrawBitmapString("Press LEFT SHIFT to attract the closest particles to the frames.", 20, ofGetHeight() - 6 * 15);
        ofDrawBitmapString("Press the LEFT or RIGHT keys to move between layers.", 20, ofGetHeight() - 4 * 15);
        ofDrawBitmapString("Press the UP key to move to a random layer.", 20, ofGetHeight() - 3 * 15);
    }
    
    // Draw instruction on how to toggle performance mode.
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Press TAB to toggle Performance Mode.", ofGetWidth() - 300, 20);

    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT_SHIFT){
        incarnateLayer();
    }
    
    if (key == OF_KEY_LEFT){
        moveToPreviousLayer();
    }
    if (key == OF_KEY_RIGHT){
        moveToNextLayer();
    }
    if (key == OF_KEY_UP){
        moveToRandomLayer();
    }
    
    if (key == OF_KEY_TAB){
        performanceMode = !performanceMode;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}

    
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    createRectPos.x = x - center.x;
    createRectPos.y = y - center.y;
    creatingRect = true;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    glm::vec2 newPos(createRectPos.x,
                     createRectPos.y);
    glm::vec2 newSize(ofGetMouseX() - createRectPos.x -center.x,
                      ofGetMouseY() - createRectPos.y-center.y);
    
    if (newSize.x < 0){
        newPos.x = createRectPos.x + newSize.x;
        newSize.x *= -1.0;
    }
    if (newSize.y < 0){
        newPos.y = createRectPos.y + newSize.y;
        newSize.y *= -1.0;
    }
    
    layers[currentLayer].addDataParticle(newPos, newSize);

    creatingRect = false;
}

void ofApp::spawnParticle(glm::vec2 pos, glm::vec2 size){
    particle newParticle = particle(pos, size);
    
    p.push_back(newParticle);
    std::cout
        << "\n Position of newParticle: "
        <<int(newParticle.pos.x) << " "
        <<int(newParticle.pos.y)
        << "\n Size of newParticle: "
        <<int(newParticle.size.x) <<" "
        <<int(newParticle.size.y)
    ;
}


//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){}

    
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    center = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    
    screenCenter = ofToString(w/2) + " " + ofToString(h/2);
}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
