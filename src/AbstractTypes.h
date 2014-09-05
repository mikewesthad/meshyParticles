#pragma once

class BaseParticle;

class AbstractParticleEmitter
{
    public:
        AbstractParticleEmitter() {};
        virtual ~AbstractParticleEmitter() {};

        virtual void update(float dt) = 0;
        virtual void draw() = 0;
        virtual void emitParticles(float dt) = 0;
};
