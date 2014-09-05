#include "ofApp.h"
//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetFrameRate(60);
    glEnable(GL_DEPTH_TEST);

    particleEmitter = new MeshParticleEmitter(100, 200.0f, 2.0f);
    particleEmitter->setCamera(cam);
    particleEmitter->setDrawMesh(true);

    light.setPointLight();
    light.setPosition(0,0,0);

    cam.setGlobalPosition(ofGetWidth()/2, ofGetHeight()/2, 100);
    cam.setOrientation(ofVec3f(0,-45,0));
    easyCam.setGlobalPosition(ofGetWidth()/2, ofGetHeight()/2, 100);
    easyCam.setTarget(cam);
    usingEasyCam = false;
    cameraSpeed = 2000.0;

}

//------------------------------------------------------------------------------
void ofApp::update()
{
    // Update the particle emitter
    if (!isPausing) particleEmitter->update(ofGetLastFrameTime());

    // Update the where the camera is looking based on the mouse position
    float dx = mouseX-lastMouseX;
    float dy = mouseY-lastMouseY;
    cam.pan(-dx * turnSensitivity);
    cam.tilt(-dy * turnSensitivity);
    lastMouseX = mouseX;
    lastMouseY = mouseY;

    // If we aren't moving in space, immediately zero out our speed
    if (!movingForward && !movingBackward && !movingLeft && !movingRight) cameraSpeed = 0.0f;

    // Apply the acceleration to our speed and limit the speed by the maxSpeed
    float dt = ofGetLastFrameTime();
    cameraSpeed += cameraAcceleration * dt;
    if (cameraSpeed > maxCameraSpeed) cameraSpeed = maxCameraSpeed;
    float distance = cameraSpeed * dt;

    // Move the camera
    if (movingForward) cam.dolly(-distance);
    if (movingBackward) cam.dolly(distance);
    if (movingLeft) cam.truck(-distance);
    if (movingRight) cam.truck(distance);
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    if (usingEasyCam) {
        easyCam.setTarget(cam);
        easyCam.begin();
        cam.draw();
    }
    else cam.begin();

        ofBackground(0);
        if (areLightsOn) light.enable();
            ofPushMatrix();
                ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                particleEmitter->draw();
            ofPopMatrix();
        if (areLightsOn) light.disable();

    if (usingEasyCam) easyCam.end();
    else cam.end();


    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps",10,15);
    ofDrawBitmapString("Position: "+ofToString(cam.getGlobalPosition()),500,15);
    ofDrawBitmapString("Press p to toggle pause",10,30);
    ofDrawBitmapString("Press m to toggle drawing the mesh",10,45);
    ofDrawBitmapString("Press space to toggle fullscreen",10,60);
    ofDrawBitmapString("Press t to save the mesh",10,75);
    ofDrawBitmapString("Left click to bring particles to you",10,90);
    ofDrawBitmapString("Right click to send particles away from you",10,105);
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'p') isPausing = !(isPausing);
    else if (key == 'm') particleEmitter->setDrawMesh(!particleEmitter->getDrawMesh());
    else if (key == 't') particleEmitter->mesh.save("combined.ply");//particleEmitter->saveParticleMesh(0);
    else if (' ' == key) ofToggleFullscreen();

    if (key == 'w') movingForward = true;
    if (key == 's') movingBackward = true;
    if (key == 'a') movingLeft = true;
    if (key == 'd') movingRight = true;
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == 'w') movingForward = false;
    if (key == 's') movingBackward = false;
    if (key == 'a') movingLeft = false;
    if (key == 'd') movingRight = false;
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if(button == 0) particleEmitter->followCamera();
    else if(button == 2) particleEmitter->avoidCamera();
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(button == 0) particleEmitter->stopFollowingCamera();
    else if(button == 2) particleEmitter->stopAvoidingCamera();
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

