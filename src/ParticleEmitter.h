#pragma once

#include "ofMain.h"
#include "BaseParticle.h"

class ParticleEmitter {
    public:
        ParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime);
        ParticleEmitter();
        virtual ~ParticleEmitter();

        virtual ofPtr<BaseParticle> createParticle();
        virtual void eraseParticle(int i);
        virtual void draw();

        void update(float dt);
        void emitParticles(float dt);
        void updateParticles(float dt);
        void killParticles();

        void setCamera(ofCamera& _cam);
        void followCamera();
        void stopFollowingCamera();
        void avoidCamera();
        void stopAvoidingCamera();

        ofCamera * cam;
        int maxNumberParticles;
        float emissionRate;
        std::vector< ofPtr<BaseParticle> > particles;
        bool isFollowingCamera;
        bool isAvoidingCamera;

        ofSpherePrimitive sphere;

    protected:
    private:
};

