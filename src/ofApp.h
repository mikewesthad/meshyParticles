#pragma once


#include "ofMain.h"
#include "MeshParticleEmitter.h"
#include "ParticleEmitter.h"
#include "BaseParticle.h"
#include "MeshParticle.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    MeshParticleEmitter * particleEmitter;

    bool areLightsOn = false;
    ofLight light;

    bool usingEasyCam;
    ofEasyCam easyCam;
    ofCamera cam;
    float lastMouseX;
    float lastMouseY;
    bool isPausing = false;

    float cameraSpeed;                  // Velocity without sign (px/s)
    float cameraAcceleration = 500.0f;  // Change in velocity per second (px/s^2)
    float maxCameraSpeed = 1000.0f;     // Max speed

    bool movingLeft = false;
    bool movingRight = false;
    bool movingForward = false;
    bool movingBackward = false;

    float turnSensitivity = 0.5f;

};
