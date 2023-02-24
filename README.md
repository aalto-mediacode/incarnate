# Incarnate
Project for Generative Media Coding 2023.

<img width="1017" alt="Screen Shot 2023-02-24 at 12 02 04" src="https://user-images.githubusercontent.com/31853349/221150263-5c1c8b2e-74c6-422f-994f-40b726f2aafb.png">

## Briefly

"Incarnate" is a bare-bones proof-of-concept for a particle-based visualisation engine. In it, a swarm of particles can be commanded to move to pre-set arrangements and thus form images, smoothly, without hard cuts between different arrangements. The arrangements are "incarnated" from a common soup of material.

This project was created as part of a week-long workshop using openFrameworks.


<img width="1128" alt="Screen Shot 2023-02-24 at 12 03 52" src="https://user-images.githubusercontent.com/31853349/221150698-dc687444-b18c-4a37-8279-38ef821d87dd.png">

## Features

* Create multiple layers and add "Particle Frames" to those layers, which act as the targets for particles. 
* On input, "incarnate" the currently active layer. The closest particles to each frame will choose a target and move to it, and scale themselves accordingly. One particle per frame. When released, particles start moving again from their locked positions, change back to their original color. They retain their sizes, which act as traces of their previous form. 
* Change soup particle color and layer color.
* Toggle between edit and performance modes. Currently layers can still be edited while in performance mode, so it's really just a "hide interface" button. 

## Notable missing features
* Saving and loading. Running the program again means you have to create all layers again. 
* Sequencing and layer lists. There's no way to move to any layer you choose, you have to either get lucky with the random switch of move through the list one by one.
* Individual layer colors. There's an attempted implementation of this in there, but it's broken at the moment. 
* Deleting frames. Once you draw a frame, it's there.
* Deleting layers.
* Audio reactivity. There's a soundPlayer class with a simple visualiser, but it's not connected to anything else so it's commented out.

## How to run

* Download openFrameworks (version used for development was 0.11.2, on MacOS)
* Use the project generator to create a new app with the "ofxGui" addon
* Place the files in this "src" folder in the "src" folder of the app.

That should be enough to make it run. 

