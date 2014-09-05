#pragma once

#include "MeshParticleEmitter.h"
#include "BaseParticle.h"
#include "ofMain.h"

class MeshParticle: public BaseParticle {
    public:
        MeshParticle();
        virtual ~MeshParticle();

        ofVec3f calculateNormal(bool positive, ofVec3f a, ofVec3f b, ofVec3f c);

        void draw(bool drawMesh);
        void update(float dt, bool targetPresent, ofVec3f target);

        void addVertex(ofVec3f v, int i, ofColor c);
        void addNormal(ofVec3f n);
        void addTriangleToMesh(int a, int b, int c);

        ofVec3f lastTop;
        ofVec3f lastLeft;
        ofVec3f lastRight;


        std::vector< std::vector<int> > faces;
        std::vector< ofVec3f > vertices;
        std::vector< ofVec3f > normals;

        bool drawNormals = false;

        float temporalResolution = 0.1;
        float timer = 999999999.0;

        ofMesh mesh;
        int vertNum=0;


};
