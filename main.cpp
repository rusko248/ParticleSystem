#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "ParticleManager.h"

using namespace std;

int win_width = 640;
int win_height = 480;
int window_id=0;
const int fps=50;
ParticleManager *particles;

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/fps,timer,window_id);
}

void display( void )
{
    static int frame = 0;
    frame++;
    //cout << "Frame " << frame << endl;
    glClear( GL_COLOR_BUFFER_BIT );

     glEnable ( GL_LIGHTING ) ;
     
     //Ambient Light
     glEnable(GL_LIGHT0);
     
     GLfloat ambientlight[] = {0.15, 0.15, 0.15, 1.0};
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientlight);
     
     GLfloat ambientColor[] = {0.15, 0.15, 0.15, 1.0};
     GLfloat diffuseColor[] = {0.8, 0.8, 0.8, 1.0};
     GLfloat specularColor[] = {0.0, 0.0, 0.0, 1.0};
     GLfloat position[] = {-10.0, 10 , -15.0};
     glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
     glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
     glLightfv(GL_LIGHT0, GL_POSITION, position);

     //Set material behavior
     glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
     glEnable ( GL_COLOR_MATERIAL ) ;
     
     
     
     glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
     glMaterialf(GL_FRONT, GL_SHININESS, 64.0);//shininess of 1 gives a broad highlight, 128 a tight highlight
    particles->display();
    particles->update();
    glFlush();
	glutSwapBuffers();
}

void reshape( int w, int h )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    glOrtho( -1., 1., -1., 1., -1., 1. );
    glViewport( 0, 0, w, h );
    
    win_width = w;
    win_height = h;
    glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y )
{
	switch(key)
	{
        case 27: // Escape key
            exit(0);
            break;
        case 'q':
        case 'Q':
            exit(0);
	}
    glutPostRedisplay();
}

int main (int argc, char *argv[])
{
    cout << "Starting" << endl;
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( win_width, win_height );
    glutPositionWindow(100, 150);
    window_id=glutCreateWindow("Particle System");
	glutSetWindow(window_id);
    
    
    GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat var[] = {0.2, 0.0, 0.0, 1.0};
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    vector3 pos = vector3(0,0,0);
    vector3 fire = vector3(0,-.0001,0);
    vector3 dir = vector3(0,1,0);
    vector3 dirVar = vector3(.01,.01,0);
    particles = new ParticleManager(5000);
    cout << "Pool created" << endl;
    //particles->addEmitter(pos, 0, 30, 0, 30, .01, .001, 200, 5, 2, 40, 0, red, var, white, var, pos);
    
    //particles->addEmitter(pos, 1, 5, -30, 0, .005, 1, 2000, 50, 20, 40, 0, red, var, white, var, pos);
    //particles->addEmitter(pos, 1, 5, -30, 0, .02, 0, 2000, 50, 20, 15, 5, red, var, white, var, fire);
    particles->addEmitter(pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, red, var, white, var, fire);

    cout << "Emitter created" << endl;

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );

	glutTimerFunc(1000/fps,timer,window_id);
    
	glutMainLoop();
}
