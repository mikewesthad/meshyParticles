#include "MeshParticleEmitter.h"

MeshParticleEmitter::MeshParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime){
    maxNumberParticles = _maxNumberParticles;
    emissionRate = _emissionRate;
    emitParticles(_prewarmTime);

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.enableNormals();
    mesh.enableIndices();

    drawMesh = false;
}

MeshParticleEmitter::~MeshParticleEmitter(){}

ofPtr<BaseParticle> MeshParticleEmitter::createParticle() {
    ofPtr<MeshParticle> ptr(new MeshParticle());
    ptr->center = ofVec3f(ofRandom(-50,50), ofRandom(-50,50), ofRandom(-50,50));
    ptr->velocity = ofRandom(200,400);
    ptr->maxAge = 5.0f;
    return ptr;
}

void MeshParticleEmitter::saveParticleMesh(int i) {
    MeshParticle* p = static_cast< MeshParticle* >(&(*particles[i]));
    p->mesh.save(ofToString(i)+"_mesh.ply");
}

void MeshParticleEmitter::draw() {
    sphere.draw();
    if (drawMesh) mesh.draw();
    for(int i=0; i<particles.size(); ++i) {
        MeshParticle* p = static_cast< MeshParticle* >(&(*particles[i]));
        p->draw(false);
    }
}

void MeshParticleEmitter::setDrawMesh(bool _drawMesh) {
    drawMesh = _drawMesh;
}
bool MeshParticleEmitter::getDrawMesh() {
    return drawMesh;
}

void MeshParticleEmitter::eraseParticle(int i) {
    MeshParticle* p = static_cast< MeshParticle* >(&(*particles[i]));
    mesh.append(p->mesh);
    particles.erase(particles.begin()+i);

}

