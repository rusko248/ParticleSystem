//
//  ParticleManager.cpp
//  assignment2
//
//  Created by Aaron Damashek on 5/14/13.
//
//

#include "ParticleManager.h"

void ParticleManager::createParticleList(int max){
    particle *head = new particle;
    head->prev = NULL;
    particlePool = head;
    particle *curr = head;
    for(int i = 0; i < max; i++){
        particle *newParticle = new particle;
        newParticle->prev = curr;
        newParticle->next = NULL;
        curr->next = newParticle;
        curr = curr->next;
    }
}

ParticleManager::ParticleManager(int max){
    createParticleList(max);
}

void ParticleManager::addEmitter(vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, GLfloat startColor[4], GLfloat startColorVar[4],GLfloat endColor[4], GLfloat endColorVar[4], vector3 force){
    
    int id = emitters.size();
    Emitter *e = new Emitter(particlePool, id, pos, dir, dirVar, speed, speedVar, totalParticles, emitsPerFrame, emitVar, life, lifeVar, startColor, startColorVar, endColor, endColorVar, force);
    emitters.push_back(e);
}

/*Subclasses use this version*/
void ParticleManager::addEmitter(Emitter *e){
    emitters.push_back(e);
}

/*Update all emitters on the frame*/
void ParticleManager::update(){
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->update();
    }
}

/*Display all emitters on the frame*/
void ParticleManager::display(){
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->display();
    }
}