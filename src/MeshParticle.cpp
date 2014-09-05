#include "MeshParticle.h"

MeshParticle::MeshParticle() {
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.enableNormals();
    mesh.enableColors();
    mesh.enableIndices();
}

MeshParticle::~MeshParticle(){}


ofVec3f MeshParticle::calculateNormal(bool positive, ofVec3f a, ofVec3f b, ofVec3f c) {
    ofVec3f v1 = b - a;
    ofVec3f v2 = c - a;
    ofVec3f normal = v1.cross(v2).getNormalized();
    if (positive) return normal;
    else return -normal;
}


void MeshParticle::update(float dt, bool targetPresent, ofVec3f target) {

    this->BaseParticle::update(dt, targetPresent, target);

    timer += dt;
    if (timer >= temporalResolution) {
        timer = 0.0;

        // Get the vertices
        a = lastTop;
        b = lastRight;
        c = lastLeft;
        e = center+top;
        f = center+right;
        g = center+left;

        // Add the newest vertices
        addVertex(e, vertNum, ofColor(255,0,0));
        addVertex(f, vertNum+1, ofColor(255,255,0));
        addVertex(g, vertNum+2, ofColor(255,0,255));
        vertNum+=3;

        // Get the indicies
        int ai = vertNum-6;
        int bi = vertNum-5;
        int ci = vertNum-4;
        int ei = vertNum-3;
        int fi = vertNum-2;
        int gi = vertNum-1;

        if (vertNum==3) {
            // Create the first face
            addTriangleToMesh(gi, fi, ei);
            addNormal(calculateNormal(false, e, f, g));
        }
        else {
            addTriangleToMesh(bi, ei, ai);
            norm1 = calculateNormal(true, b, e, a);
            addNormal(norm1);

            addTriangleToMesh(fi, ei, bi);
            norm2 = calculateNormal(true, f, e, b);
            addNormal(norm2);

            addTriangleToMesh(ai, ei, ci);
            norm3 = calculateNormal(true, a, e, c);
            addNormal(norm3);

            addTriangleToMesh(ei, gi, ci);
            norm4 = calculateNormal(true, e, g, c);
            addNormal(norm4);

            addTriangleToMesh(ci, gi, bi);
            norm5 = calculateNormal(true, c, g, b);
            addNormal(norm5);

            addTriangleToMesh(bi, gi, fi);
            norm6 = calculateNormal(true, b, g, f);
            addNormal(norm6);
        }

        // Store the newest verts
        lastTop = e;
        lastRight = f;
        lastLeft = g;
    }
}

void MeshParticle::addTriangleToMesh(int a, int b, int c) {
    mesh.addTriangle(a, b, c);
    std::vector<int> face;
    face.push_back(a);
    face.push_back(b);
    face.push_back(c);
    faces.push_back(face);
}
void MeshParticle::addVertex(ofVec3f v, int i, ofColor c) {
    mesh.addVertex(v);
    vertices.push_back(v);
    mesh.addIndex(i);
    mesh.addColor(c);
}

void MeshParticle::addNormal(ofVec3f n) {
    mesh.addNormal(n);
    normals.push_back(n);
}


void MeshParticle::draw(bool drawMesh) {
    if (drawMesh) mesh.draw();
    else BaseParticle::draw();

//    ofSetColor(255);
//    vector<ofMeshFace> faces = mesh.getUniqueFaces();
//    for (int i=0; i<faces.size(); i++) {
//        ofMeshFace face = faces[i];
//        ofVec3f v1 = face.getVertex(0);
//        ofVec3f v2 = face.getVertex(1);
//        ofVec3f v3 = face.getVertex(2);
//        ofVec3f c = (v1+v2+v3)/3.0f;
//        ofVec3f n = face.getFaceNormal();
//        ofLine(c, c+n*radius);
//    }

//    if (drawNormals) {
//        ofSetColor(255);
//        ofTriangle(a,e,b);
//        ofLine((a+e+b)/3, (a+e+b)/3+norm1*radius);
//
//        ofSetColor(200);
//        ofTriangle(b, e, f);
//        ofLine((b+e+f)/3, (b+e+f)/3+norm2*radius);
//
//        ofSetColor(160);
//        ofTriangle(a, e, c);
//        ofLine((a+e+c)/3, (a+e+c)/3+norm3*radius);
//
//        ofSetColor(120);
//        ofTriangle(e, g, c);
//        ofLine((e+g+c)/3, (e+g+c)/3+norm4*radius);
//
//        ofSetColor(90);
//        ofTriangle(c, g, b);
//        ofLine((c+g+b)/3, (c+g+b)/3+norm5*radius);
//
//        ofSetColor(60);
//        ofTriangle(b, g, f);
//        ofLine((b+g+f)/3, (b+g+f)/3+norm6*radius);
//    }

}
