#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() {}

ParticleEmitter::ParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime) {
    maxNumberParticles = _maxNumberParticles;
    emissionRate = _emissionRate;
    emitParticles(_prewarmTime);
    isFollowingCamera = false;
    isAvoidingCamera = false;

    sphere.setRadius(10.0);
}

void ParticleEmitter::emitParticles(float dt) {
    int maxToEmit = emissionRate * dt;
    int particlesGenerated = 0;
    while(particles.size()<maxNumberParticles && particlesGenerated<maxToEmit) {
        particles.push_back(createParticle());
        particlesGenerated++;
    }
}

void ParticleEmitter::update(float dt) {
    updateParticles(dt);
    killParticles();
    emitParticles(dt);
}

void ParticleEmitter::updateParticles(float dt) {
    for(int i=0; i<particles.size(); ++i) {
        bool targetPresent = isFollowingCamera || isAvoidingCamera;
        ofVec3f target;
        if (isFollowingCamera) {
            target = cam->getPosition();
            target.x -= ofGetWidth()/2;
            target.y -= ofGetHeight()/2;
        }
        else if (isAvoidingCamera) {
            ofVec3f adustedCamPos = cam->getPosition();
            adustedCamPos.x -= ofGetWidth()/2;
            adustedCamPos.x -= ofGetHeight()/2;

            target = adustedCamPos - particles[i]->center;
            target.normalize();
            target *= -1000.0;
            target.x += particles[i]->center.x;
            target.y += particles[i]->center.y;
        }
        particles[i]->update(dt, targetPresent, target);
    }
}

void ParticleEmitter::killParticles() {
    ofRectangle theScreen(-ofGetWidth()/2,-ofGetHeight()/2,ofGetWidth()/2,ofGetHeight()/2);
    for(int i=particles.size()-1; i>=0; --i) {
        if(particles[i]->isDead) eraseParticle(i);
    }
}

ofPtr<BaseParticle> ParticleEmitter::createParticle() {
    ofPtr<BaseParticle> ptr(new BaseParticle());
    ptr->velocity = ofRandom(50,200);
    ptr->radius = ofRandom(2,5);
    return ptr;
}

void ParticleEmitter::eraseParticle(int i) {
    particles.erase(particles.begin()+i);
}

void ParticleEmitter::avoidCamera() {
    isAvoidingCamera = true;
    stopFollowingCamera();
}

void ParticleEmitter::stopAvoidingCamera() {
    isAvoidingCamera = false;
}

void ParticleEmitter::followCamera() {
    isFollowingCamera = true;
    stopAvoidingCamera();
}

void ParticleEmitter::stopFollowingCamera() {
    isFollowingCamera = false;
}

void ParticleEmitter::setCamera(ofCamera & _cam) {
    cam = &_cam;
}

void ParticleEmitter::draw() {
    sphere.draw();
    for(int i=0; i<particles.size(); ++i) particles[i]->draw();
}

ParticleEmitter::~ParticleEmitter(){}
