//
//  ParticleManager.h
//  assignment2
//
//  Created by Aaron Damashek on 5/14/13.
//
//

#ifndef __assignment2__ParticleManager__
#define __assignment2__ParticleManager__

#include <iostream>
#include <vector>
#include "ParticleStructs.h"
#include "Emitter.h"

class ParticleManager
{
public:
	ParticleManager(int max);
    void addEmitter(vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, GLfloat startColor[4], GLfloat startColorVar[4],GLfloat endColor[4], GLfloat endColorVar[4], vector3 force);
    void update();
    void display();
private:
    int maxParticles;
    void addEmitter(Emitter *e);
    void createParticleList(int max);
    particle *particlePool;
    std::vector<Emitter*> emitters;
};

#endif /* defined(__assignment2__ParticleManager__) */
