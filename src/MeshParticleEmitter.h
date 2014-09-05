#pragma once

#include "ofMain.h"
#include "ParticleEmitter.h"
#include "MeshParticle.h"

class MeshParticleEmitter: public ParticleEmitter {
    public:
        MeshParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime);
        virtual ~MeshParticleEmitter();

        void draw();
        void setDrawMesh(bool _drawMesh);
        bool getDrawMesh();
        ofPtr<BaseParticle> createParticle();
        void eraseParticle(int i);
        void saveParticleMesh(int i);
        ofMesh mesh;
        bool drawMesh;



    protected:
    private:
};
