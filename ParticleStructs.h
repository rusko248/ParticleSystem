//
//  ParticleStructs.h
//  assignment2
//
//  Created by Aaron Damashek on 5/8/13.
//
//

#include "Basic.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef assignment2_ParticleStructs_h
#define assignment2_ParticleStructs_h

struct particle {
    particle *prev, *next;
    vector3 pos;
    vector3 prevPos;
    vector3 dir;
    int life;
    GLfloat color[4];
    GLfloat prevColor[4];
    GLfloat deltaColor[4];
};

struct emitter {
    int emitter_id;
    vector3 pos;
    vector3 dir;
    vector3 dirVar;
    float yaw, yawVar;
    float pitch, pitchVar;
    float speed, speedVar;
    particle *particleList;
    int totalParticles;
    int particleCount;
    int emitsPerFrame, emitVar;
    int life, lifeVar;
    GLfloat startColor[4];
    GLfloat startColorVar[4];
    GLfloat endColor[4];
    GLfloat endColorVar[4];
    vector3 force;
    
};

#endif
