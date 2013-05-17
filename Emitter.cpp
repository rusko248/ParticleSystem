//
//  Emitter.cpp
//  assignment2
//
//  Created by Aaron Damashek on 5/8/13.
//
//

#include "Emitter.h"

Emitter::Emitter(particle *pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, GLfloat startColor[4], GLfloat startColorVar[4],GLfloat endColor[4], GLfloat endColorVar[4], vector3 force){
    
    e = new emitter;
    e->emitter_id = emitter_id;
    e->pos = pos;
    //e->yaw = yaw;
    //e->yawVar = yawVar;
    //e->pitch = pitch;
    //e->pitchVar = pitchVar;
    e->dir = dir;
    e->dirVar = dirVar;
    e->speed = speed;
    e->speedVar = speedVar;
    e->totalParticles = totalParticles;
    e->particleList = NULL;
    e->particleCount = 0;
    e->emitsPerFrame = emitsPerFrame;
    e->emitVar = emitVar;
    e->life = life;
    e->lifeVar = lifeVar;
    for(int i = 0; i < 4; i++){
        e->startColor[i] = startColor[i];
        e->startColorVar[i] = startColorVar[i];
        e->endColor[i] = endColor[i];
        e->endColorVar[i] = endColorVar[i];
    }
    e->force = force;
    
    managerParticleList = pool;
}

inline float randDist(){
    float r = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
    return r;
}

void Emitter::rotationToDirection(float pitch, float yaw, vector3 *direction){
    direction->x = -sin(yaw) * cos(pitch);
    direction->y = sin(pitch);
    direction->z = cos(pitch) * cos(yaw);
}

bool Emitter::addParticle(){
    particle *newParticle;
    GLfloat start[4];
    GLfloat end[4];
    float speed;
    //Particle pool exists and max num particles not exceeded
    if(e != NULL && managerParticleList != NULL && e->particleCount < e->totalParticles){
        newParticle = managerParticleList;
        managerParticleList = managerParticleList->next;
        if(e->particleList != NULL){
            e->particleList->prev = newParticle;
        }
        newParticle->next = e->particleList;
        newParticle->prev = NULL;
        e->particleList = newParticle;
        
        newParticle->pos.x = randDist()/20;
        newParticle->pos.y = 0;
        newParticle->pos.z = 0;
        
        newParticle->prevPos.x = 0;
        newParticle->prevPos.y = 0;
        newParticle->prevPos.z = 0;
        
        //Calculate direction vector
        //yaw = e->yaw + (e->yawVar*randDist());
        //pitch = e->pitch + (e->pitchVar*randDist());
        //rotationToDirection(pitch, yaw, &newParticle->dir);
        newParticle->dir = e->dir + (e->dirVar*randDist());
        
        speed = e->speed + (e->speed * randDist());
        newParticle->dir.x *= speed;
        newParticle->dir.y *= speed;
        newParticle->dir.z *= speed;
        
        start[0] = e->startColor[0] + (e->startColorVar[0] * randDist());
        start[1] = e->startColor[1] + (e->startColorVar[1] * randDist());
        start[2] = e->startColor[2] + (e->startColorVar[2] * randDist());
        end[0] = e->endColor[0] + (e->endColorVar[0] * randDist());
        end[1] = e->endColor[1] + (e->endColorVar[1] * randDist());
        end[2] = e->endColor[2] + (e->endColorVar[2] * randDist());
        
        newParticle->color[0] = start[0];
        newParticle->color[1] = start[1];
        newParticle->color[2] = start[2];
        
        newParticle->life = e->life + (int)((float)e->lifeVar * randDist());
        
        newParticle->deltaColor[0] = (end[0] - start[0]) / newParticle->life;
        newParticle->deltaColor[1] = (end[1] - start[1]) / newParticle->life;
        newParticle->deltaColor[2] = (end[2] - start[2]) / newParticle->life;
        
        e->particleCount++;
        return true;
    }
    return false;
}

bool Emitter::updateParticle(particle *p){
    if(p != NULL && p->life > 0){
        p->prevPos.x = p->pos.x;
        p->prevPos.y = p->pos.y;
        p->prevPos.z = p->pos.z;
        
        p->pos.x += p->dir.x;
        p->pos.y += p->dir.y;
        p->pos.z += p->dir.z;
        
        p->dir.x += e->force.x;
        p->dir.y += e->force.y;
        p->dir.z += e->force.z;
        
        p->prevColor[0] = p->color[0];
        p->prevColor[1] = p->color[1];
        p->prevColor[2] = p->color[2];
        
        p->color[0] += p->deltaColor[0];
        p->color[1] += p->deltaColor[1];
        p->color[2] += p->deltaColor[2];
        
        p->life--;
        return true;
    }else if(p != NULL && p->life == 0){
        if(p->prev != NULL){
            p->prev->next = p->next;
        }else{
            e->particleList = p->next;
        }
        if(p->next != NULL){
            p->next->prev = p->prev;
        }
        p->next = managerParticleList;
        p->prev = NULL;
        managerParticleList = p;
        e->particleCount--;
    }
    
    return false;
}

void Emitter::display(){
    std::cout << "Adding " << e->particleCount << std::endl;
    for(int newP = 0; newP < (e->emitsPerFrame + e->emitVar*randDist()); newP++){
        addParticle();
    }
    glPointSize(2);
    glBegin(GL_POINTS);
    particle *curr = e->particleList;
    while(curr){
        glColor4fv(curr->color);
        glVertex3f(curr->pos.x, curr->pos.y, curr->pos.z);
        curr = curr->next;
    }
    glEnd();
}

void Emitter::update(){
    particle *curr = e->particleList;
    while(curr){
        particle *toUpdate = curr;
        curr = curr->next;
        updateParticle(toUpdate);
    }
}