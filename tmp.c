#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<stdbool.h>
#include <math.h>
#include <time.h>
#include"list.h"
#define MAX_NO_TEXTURES 25


GLuint texture_id[MAX_NO_TEXTURES];
circ_bbuf_t list ;
bool head_right_done , head_left_done, rot_head_flag;
float rot_speed= 2;
float head_ang = 0, head_rotval, body_rotate ;
bool walkX , walkZ, goingHome;
// glTranslatef(-3 + objectX, -5,30+objectZ);
int dancing, doneflag;

float objectX = 1, objectZ= 1;
bool   rightHand_up_done = 0 ,  rightHand_flag = 0,
       rightElbow_up_done=0 , rightElbow_flag=0,
       leftHand_up_done=0, leftHand_flag=0,
       leftElbow_up_done=0, leftElbow_flag=0,
       rightLeg_up_done =0, rightLeg_flag=0,
       rightKnee_up_done=0, rightKnee_flag=0,
       leftLeg_up_done =0, leftLeg_flag=0,
       leftKnee_up_done=0, leftKnee_flag =0;

float leftHand_ang , leftElbow_ang , rightHand_ang , rightElbow_ang, rightLeg_ang,
      rightKnee_ang , leftLeg_ang  ,  leftKnee_ang ;

float leftHand_rotVal= 1.2, leftElbow_rotVal= 1.2, rightHand_rotVal= 1.2, rightElbow_rotVal=1.2, rightLeg_rotVal=1.2,
      rightKnee_rotVal= 1.2, leftLeg_rotVal = 1.2,  leftKnee_rotVal =1.2;
int angy;
float angle = 80, fAspect, angx = 0,  angz = 0,
     moveZ = 0 , eyeZ = 0.0, eyeX = 0.0,
      eyeY = 0.0,  moveX = 0.0, tamTela = 400.0, eye_centerX = 0.0, eye_centerY = 0.0,
      eye_centerZ =0.0;
bool object_flag;
int number_of_music ;

float absf(float x)
{

    if (x<0)
        return x*-1;
    return x;
}
/* generate a random floating point number from min to max */

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
GLfloat ambient_light2[4] = {0.4, 0.4, 0.4, 1.0};

GLfloat difuse_light[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat dspec_light[4] = {0.3, 0.3, 0.3, 1.0};



GLfloat light_pos4[4] = {0.0, 1.0, -5.0, 1.0};

GLfloat obj_Amb[4] = {0.3, 0.2, 0.1, 1.0};
GLfloat obj_Dif[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat obj_Esp[4] = {0.1, 0.1, 0.1, 1.0};






/// texture struct
typedef struct IMGdata_ {
    int   width;
    int   height;
    char *data;
}IMGdata;

void getIMGdata( char *pFileName, IMGdata *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    ( (pFile = fopen(pFileName, "rb") )  );

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    ( (i = fread(&pImage->width, 4, 1, pFile) )  );

     ( (i = fread(&pImage->height, 4, 1, pFile) ) );

     ( (fread(&nNumPlanes, 2, 1, pFile) ) );


     ( (i = fread(&nNumBPP, 2, 1, pFile)) );


    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

     ( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) );

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}

void loadTexture(char* Filename, int id)
{

    IMGdata textura;

    getIMGdata( Filename, &textura);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture_id[id]);

    glBindTexture(GL_TEXTURE_2D, texture_id[id]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.width, textura.height, 0,
                                    GL_RGB, GL_UNSIGNED_BYTE, textura.data);
    glTexGenf(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenf(GL_T,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

}


void Viewing()	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle,fAspect,0.001,80);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


    gluLookAt( eyeX-1,eyeY+2,eyeZ -5,
               eye_centerX,eye_centerY,eye_centerZ,
                  0,1,0);
    //glTranslatef(eyeX, eyeY, eyeZ);
}

void ChangeSize(GLsizei w, GLsizei h)	{

	if ( h == 0 )
		h = 1;
        glViewport(0, 0, w, w);

	fAspect = (GLfloat)w/(GLfloat)h;
	Viewing();
	tamTela = w/2.0;
}



void init() {
glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);

    leftHand_rotVal= rot_speed, leftElbow_rotVal= rot_speed, rightHand_rotVal= rot_speed, rightElbow_rotVal=rot_speed, rightLeg_rotVal=rot_speed,
    rightKnee_rotVal= - rot_speed, leftLeg_rotVal = rot_speed,  leftKnee_rotVal = -rot_speed , head_rotval = rot_speed;
    init_buf(&list);
    glLoadIdentity();

    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient_light2);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, difuse_light);
    glLightfv(GL_LIGHT4, GL_SPECULAR, dspec_light);
    glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obj_Amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obj_Dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obj_Esp);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 2);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT4);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEPTH_TEST);

    Viewing();

}


void music_box_draw()
{
    if(object_flag){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glTranslatef( objectX,0-0.8,objectZ);
    glScalef(0.2,.2,.2);
    glutSolidCube(2);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    }
}

void bigWall() {
glPushMatrix();


    glTranslatef(0,.6,0);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        glTranslatef(-3.0, 1.0, 50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
    ///--------------------------------///
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);

        glTranslatef(-3.0, 1.0, -50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
///-----------------------///
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        glRotatef(90, 0,1,0);
        glTranslatef(-3.0, 1.0, 50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
///----------------------///
 glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        glRotatef(-90, 0,1,0);
        glTranslatef(-3.0, 1.0, 50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}
/*
    body function
**/
void my_man() {

  //   glColor3f(0.0, 0.0, 1.0);


    glPushMatrix();
    //glLoadIdentity();

        glTranslatef(moveX, 0, moveZ); // translating the whoole man
        glRotatef(angx,1.0,0.0,0.0);
        glRotatef(angy,0.0,1.0,0.0);
        glRotatef(angz,0.0,0.0,1.0);
        glScalef(1.2, 0.7, 0.4);



        ///HEAD///

        glPushMatrix();  // head

        glRotatef(head_ang, 0,1,0);
            glPushMatrix();///skull
                glRotatef(90, 1.0, 0.0, 0.0);
                 glColor3f(234/255.0  , 192/255.0, 134/255.0);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix(); /// nose
                glTranslatef(0.0, -0.05, -0.2);
                 glRotatef(50, 1.0, 0.0, 0.0);
                glRotatef(-10, 0.0, 1.0, 0.0);
                glScalef(0.1, 0.1, 0.1);
                glColor3f(1  , 15/255.0, 134/255.0);
                glutSolidSphere(.3, 10,10);
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();///right eye
                glColor3f(0,0,0);
                glTranslatef(0.1, 0.1, -0.2);
                glScalef(0.2, 0.2, 0.2);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
                glScalef(0.5,.5,.8);
                glTranslatef(0,0,-.15);
                glutSolidCube(0.3 );
                glTranslatef(0,0,-.15);
                glColor3f(.1,0.1,0.1);
                glutSolidSphere(.1, 20, 20);
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();/// left eye
                glColor3f(0,0,0);
                glTranslatef(-0.1, 0.1, -0.2);
                glScalef(0.2, 0.2, 0.2);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
                glScalef(0.5,.5,.8);
                glTranslatef(0,0,-.15);
                glutSolidCube(0.3 );
                glTranslatef(0,0,-.15);
                glColor3f(.1,0.1,0.1);
                glutSolidSphere(.1, 20, 20);
                glColor3f(1,1,1);
            glPopMatrix();


        glPopMatrix(); ///head done
        ///mouth///
        glPushMatrix(); ///mouth
            glColor3f(.7,0,0);
            glTranslatef(0.0, -0.25, 0.0);
            glScalef(0.3, 0.2, 0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            gluCylinder(gluNewQuadric(), 0.5, 0.3, 0.3, 20,10);
            glColor3f(1,1,1);
        glPopMatrix();
        ///body///
        glPushMatrix();
            glColor3f(17/255.0  , 53/255.0, 114/255.0);
            glTranslatef(0.0, -0.75, 0.0);
            glScalef(0.7, 1.2, 1.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCube(0.4 );
            glColor3f(1,1,1);
        glPopMatrix();
        ///left arm///
        glPushMatrix();
            glTranslatef(0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(-0.2, -0.4, 0.0);
            glRotatef(leftHand_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glRotatef(20, 0.0, 0.0, 1.0);
            glTranslatef(0.2, 0.4, 0.0);
            glPushMatrix();
                glColor3f(17/255.0  , 53/255.0, 114/255.0);
                glTranslatef(-0.3, -0.5, 0.0);
                glRotatef(-45, 0.0, 0.0, 1.0);
                glScalef(0.5, 1.3, 0.8);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.39, -0.56, 0.0);
                glRotatef(leftElbow_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glRotatef(10, 0.0, 0.0, 1.0);
                glTranslatef(0.39, 0.56, 0.0);
                glPushMatrix(); ///left upper arm
                    glColor3f(17/255.0  , 53/255.0, 114/255.0);
                    glTranslatef(-0.45, -0.65, 0.0);
                    glRotatef(-45, 0.0, 0.0, 1.0);
                    glScalef(0.5, 1.3, 0.8);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.1 );
                    glColor3f(1,1,1);
                glPopMatrix();
                glPushMatrix(); ///left lower arm
                    glTranslatef(-0.52, -0.72, 0.0);
                    glRotatef(0, 1.0, 0.0, 0.0);
                    glRotatef(0, 0.0, 0.0, 1.0);
                    glTranslatef(0.52, 0.72, 0.0);
                    glPushMatrix(); ///left hand
                        glColor3f(234/255.0  , 192/255.0, 134/255.0);
                        glTranslatef(-0.55, -0.75, 0.0);
                        glRotatef(-45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(90, 1.0, 0.0, 0.0);
                        glutSolidSphere(0.05, 20,20 );
                        glColor3f(1,1,1);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix(); /// right arm
            glTranslatef(-0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(0.2, -0.4, 0.0);
            glRotatef(rightHand_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glTranslatef(-0.2, 0.4, 0.0);
            glPushMatrix(); ///right upper arm
                glColor3f(17/255.0  , 53/255.0, 114/255.0);
                glTranslatef(0.3, -0.5, 0.0);
                glRotatef(45, 0.0, 0.0, 1.0);
                glScalef(0.5, 1.3, 0.8);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.39, -0.56, 0.0);
                glRotatef(rightElbow_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glRotatef(-10, 0.0, 0.0, 1.0);
                glTranslatef(-0.39, 0.56, 0.0);
                    glPushMatrix(); ///right lower arm
                        glColor3f(17/255.0  , 53/255.0, 114/255.0);
                        glTranslatef(0.45, -0.65, 0.0);
                        glRotatef(45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(  90, 1.0, 0.0, 0.0);
                        glutSolidCube(0.1 );
                        glColor3f(1,1,1);
                    glPopMatrix();
                    glPushMatrix(); ///right hand

                        glTranslatef(-0.52, -0.72, 0.0);
                        glRotatef(0, 1.0, 0.0, 0.0);
                        glRotatef(0, 0.0, 0.0, 1.0);
                        glTranslatef(0.52, 0.72, 0.0);
                        glPushMatrix(); ///right hand
                            glColor3f(234/255.0  , 192/255.0, 134/255.0);
                            glTranslatef(0.55, -0.75, 0.0);
                            glRotatef(45, 0.0, 0.0, 1.0);
                            glScalef(0.5, 1.5, 0.8);
                            glRotatef(90, 1.0, 0.0, 0.0);
                            glutSolidSphere(0.05, 20,20 );
                            glColor3f(1,1,1);
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
        glPopMatrix();
        ///Left leg//
        glPushMatrix(); ///open leg
            glTranslatef(0.05, 0.7, 0);
            glScalef(1.6, 1.6, 1.6);
            glTranslatef(-0.03, -1.2, 0.0);
            glRotatef(leftLeg_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glTranslatef(0.03, 1.2, 0.0);
            glPushMatrix(); ///left thigh
                glColor3f(139/255.0, 69/255.0, 19.0/255);
                glTranslatef(-0.1, -1.25, 0.0);
                glScalef(0.5, 1.3, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.03, -1.35, 0.0);
                glRotatef(leftKnee_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glTranslatef(0.03, 1.35, 0.0);
                glPushMatrix(); ///left lower leg
                    glColor3f(139/255.0, 69/255.0, 19.0/255);

                    glTranslatef(-0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(  90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.1 );
                    glColor3f(1,1,1);
                glPopMatrix();
                glPushMatrix(); ///left foot
                    glColor3f(0.11,.01,0.01);
                    glTranslatef(-0.1, -1.60, 0.0);
                    glScalef(0.5, 0.3, 1.4);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.19 );
                    glColor3f(1,1,1);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        ///right leg//
        glPushMatrix();
            glTranslatef(-0.05, 0.7, 0);
            glScalef(1.6, 1.6, 1.6);
            glTranslatef(0.03, -1.2, 0.0);
            glRotatef(rightLeg_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glTranslatef(-0.03, 1.2, 0.0);
            glPushMatrix(); ///right upper leg
                glColor3f(139/255.0, 69/255.0, 19.0/255);
                glTranslatef(0.1, -1.25, 0.0);
                glScalef(0.5, 1.3, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix(); ///right lower leg
                glTranslatef(0.03, -1.35, 0.0);
                glColor3f(139/255.0, 69/255.0, 19.0/255);
                glRotatef(rightKnee_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glTranslatef(-0.03, 1.35, 0.0);
                glPushMatrix();
                    glTranslatef(0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.1 );
                glPopMatrix();
                glPushMatrix();
                    glColor3f(0,0,0);
                    glTranslatef(0.1, -1.60, 0.0);
                    glScalef(0.5, 0.3, 1.4);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.19 );
                glPopMatrix();
            glColor3f(1,1,1);
            glPopMatrix();
        glPopMatrix();
            glPopMatrix();

    glPopMatrix();

}


void head_rotate_()
{

    if(rot_head_flag){
        head_ang+= head_rotval;
        if(head_ang <= -90)
            head_rotval *=-1 , head_left_done =1;
        if(head_ang >= 90)
            head_rotval *=-1, head_right_done =1 ;
        if( absf(head_ang - 0) <=1 && head_left_done && head_right_done)
        {
            head_left_done = head_right_done = 0;
            rot_head_flag = 0;

        }
    }
}

void  rightHand_moving()
{
    if(rightHand_flag)
    {
        rightHand_ang+= rightHand_rotVal;
        if(rightHand_ang >= 60 || rightHand_ang <= -60)
            rightHand_rotVal*=-1 , rightHand_up_done = 1;
        if(absf(rightHand_ang - 0)<=1 && rightHand_up_done)
            rightHand_up_done = 0, rightHand_ang = 0 ,rightHand_flag =0 , rightHand_rotVal *=-1;
    }
}

void  rightElbow_moving()
{
    if(rightElbow_flag)
    {
        rightElbow_ang+= rightElbow_rotVal;
        if(rightElbow_ang >= 80 || rightElbow_ang <= -80)
            rightElbow_rotVal*=-1 , rightElbow_up_done = 1;
        if(absf(rightElbow_ang - 0)<=1 && rightElbow_up_done)
            rightElbow_up_done = 0, rightElbow_ang = 0 ,rightElbow_flag =0 , rightElbow_rotVal *=-1;
    }
}


void  leftHand_moving()
{
    if(leftHand_flag)
    {
        leftHand_ang+= leftHand_rotVal;
        if(leftHand_ang >= 60 || leftHand_ang <= -60)
            leftHand_rotVal*=-1 , leftHand_up_done = 1;
        if(absf(leftHand_ang - 0)<=1 && leftHand_up_done)
            leftHand_up_done = 0, leftHand_ang = 0 ,leftHand_flag =0 , leftHand_rotVal *=-1;
    }
}

void  leftElbow_moving()
{
    if(leftElbow_flag)
    {
        leftElbow_ang+= leftElbow_rotVal;
        if(leftElbow_ang >= 80 || leftElbow_ang <= -80)
            leftElbow_rotVal*=-1 , leftElbow_up_done = 1;
        if(absf(leftElbow_ang - 0)<=1 && leftElbow_up_done)
            leftElbow_up_done = 0, leftElbow_ang = 0 ,leftElbow_flag =0 , leftElbow_rotVal *=-1;
    }
}

void  leftLeg_moving()
{
    if(leftLeg_flag)
    {
        leftLeg_ang+= leftLeg_rotVal;
        if(leftLeg_ang >= 60 || leftLeg_ang <= -60)
            leftLeg_rotVal*=-1 , leftLeg_up_done = 1;
        if(absf(leftLeg_ang - 0)<=1 && leftLeg_up_done)
            leftLeg_up_done = 0, leftLeg_ang = 0 ,leftLeg_flag =0 , leftLeg_rotVal *=-1;
    }
}

void  leftKnee_moving()
{
    if(leftKnee_flag)
    {
        leftKnee_ang+= leftKnee_rotVal;
        if(leftKnee_ang >= 80 || leftKnee_ang <= -80)
            leftKnee_rotVal*=-1 , leftKnee_up_done = 1;
        if(absf(leftKnee_ang - 0)<=1 && leftKnee_up_done)
            leftKnee_up_done = 0, leftKnee_ang = 0 ,leftKnee_flag =0 , leftKnee_rotVal *=-1;
    }
}

void  rightLeg_moving()
{
    if(rightLeg_flag)
    {
        rightLeg_ang+= rightLeg_rotVal;
        if(rightLeg_ang >= 60 || rightLeg_ang <= -60)
            rightLeg_rotVal*=-1 , rightLeg_up_done = 1;
        if(absf(rightLeg_ang - 0)<=1 && rightLeg_up_done)
            rightLeg_up_done = 0, rightLeg_ang = 0 ,rightLeg_flag =0 , rightLeg_rotVal *=-1;
    }
}

void  rightKnee_moving()
{
    if(rightKnee_flag)
    {
        rightKnee_ang+= rightKnee_rotVal;
        if(rightKnee_ang >= 80 || rightKnee_ang <= -80)
            rightKnee_rotVal*=-1 , rightKnee_up_done = 1;
        if(absf(rightKnee_ang - 0)<=1 && rightKnee_up_done)
            rightKnee_up_done = 0, rightKnee_ang = 0 ,rightKnee_flag =0 , rightKnee_rotVal *=-1;
    }
}

void body_walk()
{
    if(walkX)
        {
            if(goingHome)
            {
            if( 0 - moveX > 0 )
                moveX+=.009 ;
            else moveX -= 0.009;
            }

            else if( objectX - moveX > 0 )
                moveX+=.009 ;
            else moveX -= 0.009;
        }
    else if (walkZ)
    {
        if(goingHome)
        {
            if( 0 - moveZ > 0 )
                moveZ+=.009 ;
            else moveZ -= 0.009;
        }
        else if( objectZ - moveZ > 0 )
                moveZ+=.009 ;
            else moveZ -= 0.009;
    }

}


void body_moving()
{
       goto_box();
       goToZero();

       head_rotate_();
       rightHand_moving();
       rightElbow_moving();
       leftElbow_moving();
       leftHand_moving();
       leftLeg_moving();
       leftKnee_moving();
       rightLeg_moving();
       rightKnee_moving();
       if(dancing == 0)
       {

       body_walk();
       if(body_rotate)
       {
           angy+=1;
           if((int) angy%90 == 0)
            body_rotate = 0;
       angy = (int)angy %360; // [0-359]
       }
       }
       dance();
}
void rotate_body()
{
    body_rotate = 1;
    leftHand_flag = leftLeg_flag =1;

}

void moving()
{
bool legleftmp , rightlegtmp ;
    //legleftmp = leftLeg_flag, rightlegtmp = rightLeg_flag;
    if(walkX || walkZ)
    {
         legleftmp = leftLeg_flag, rightlegtmp = rightLeg_flag;
    }
    body_moving();
    if( (walkX||walkZ) && (legleftmp != leftLeg_flag || rightlegtmp != rightLeg_flag))
    {
        if(legleftmp != leftLeg_flag)
            rightLeg_flag = rightHand_flag= !rightLeg_flag;
        else if(rightlegtmp != rightLeg_flag)
            leftHand_flag = leftLeg_flag = !leftLeg_flag;
    }
}
void start_walk()
{
    rightHand_flag = 1;
    rightLeg_flag = 1 ;
}
void stop_walking()
{

    walkX=walkZ=0;
}
bool xdirection_ok()
{
    if(moveX < objectX)
    {
        return angy == 270 ;
    }
    else if (moveX > objectX)
    {
        return angy == 90 ;
    }
}
bool zdirection_ok()
{
    if(moveZ > objectZ)
    {

        return angy == 0;
    }
    else if (moveZ < objectZ)
        return angy == 180 ;
}
int u ;

bool xdirection_okz()
{
    if(moveX< 0)
    {
        return angy == 270 ;
    }
    else if (moveX > 0)
    {
        return angy == 90 ;
    }

}
bool zdirection_okz()
{
    if(moveZ > 0)
    {

        return angy == 0;
    }
    else if (moveZ < 0)
        return angy == 180 ;
}
void goToZero()
{
     if(goingHome)
    {
        if( absf(moveX - 0)  > .001 )
        {


            if(xdirection_okz()==0  )
            {
                rotate_body();
                // makethe robot face the right direction
            }
            else
            {

                    if(walkX==0)
                        start_walk(), walkX = 1;
                        // start the walk in
            }
        }
        else if (absf(moveZ-0) >.001 )
        {
            if(walkX)
                stop_walking();
            if(zdirection_okz()==0)
            {
                rotate_body();

            }
            else{

                    if(walkZ ==0)
                  start_walk();
                    walkZ =1 ;

            }
        }
        else{
            /*
                call the dancing func , make object disapper , go back to 0,0
            */
            walkZ = 0;
            stop_walking();

           goingHome = 0;
        }
    }
}
void dance()
{
    if(dancing== 5)
    {
        rightHand_flag = 1;
        if(rightHand_up_done== 1)
            dancing --;
    }
    else if (dancing ==4)
    {
        leftLeg_flag =1;
        if(leftLeg_up_done == 1)
            dancing -- ;
    }
    else if (dancing==3)
    {
        rightLeg_flag=1;
        if(rightLeg_up_done == 1)
            dancing--;
    }
    else if (dancing==2)
    {
        leftLeg_flag =1;
        if(leftLeg_up_done)
            dancing--;
    }
    else if(dancing==1)
    {
        rot_head_flag = 1;
        leftElbow_flag=1;
        rightElbow_flag= 1;
        if(rightElbow_up_done)
        dancing = -1;
    }
    else if (dancing == -1)
    {
        leftElbow_flag=1;
        rightElbow_flag= 1;
        dancing= 0;
    }
}
void goto_box()
{

    if(object_flag)
    {
        if( absf(moveX - objectX) >0.009 )
        {


            if(xdirection_ok()==0  )
            {
                rotate_body();
                // makethe robot face the right direction
            }
            else
            {

                    if(walkX==0)
                        start_walk(), walkX = 1;
                        // start the walk in
            }
        }
        else if (absf(moveZ-objectZ) >.01)
        {
            if(walkX)
                stop_walking();
            if(zdirection_ok()==0)
            {
                printf("%f, %f\n", moveZ , objectZ);
                rotate_body();

            }
            else{

                    if(walkZ ==0)
                  start_walk();
                    walkZ =1 ;

            }
        }
        else{
            /*
                call the dancing func , make object disapper , go back to 0,0
            */
            walkZ = 0;
            stop_walking();
            dancing = 5;
            music tmp;
            if(list.count)
            {
                object_flag =1;
                cir_buf_pop(&list, &tmp);
                objectX = tmp.x;
                objectZ = tmp.z ;
            }
            else
                object_flag = 0 ;
        }
    }
}
void playGame()	{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //	glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);

    glPushMatrix();
//
      // glTranslatef(0.0, 0.35, 0.0);
     bigWall();
     my_man();

    music_box_draw();
    moving();
    Viewing();
    glutSwapBuffers();
}


void menuFunc(GLint test)
{
    switch(test){
        case 1:
            exit(0);
        break ;
        case 2:
            rightHand_flag = 1;
        break;
        case 3:
            leftHand_flag=1;
            break;
        case 4 :
            leftElbow_flag=1;
            break;
        case 5 :
            rightElbow_flag = 1;
            break;
        case 6:
            leftLeg_flag = 1;
            break;
        case 7:
            rightLeg_flag = 1;
            break;
        case 8:
            leftKnee_flag = 1;
            break;
        case 9:
            rightKnee_flag =1;
            break;
        case 10:
            rot_head_flag = 1;
            break;
        case 20:
            dancing =5;
            break;
    }

}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case '8':
      moveZ  += .42;
    break;
    case '2':
      moveZ-= .42;
    break;
    case '4':
      moveX+= .42;
    break;
    case '6':
      moveX-= .42;
    break;
   case 'd':
        eye_centerZ -= .1;
        break;
   case 'e':
        eye_centerZ += .1;
        break;
    case 's':
        eye_centerX -= .1;
        break;
    case 'w':
        eye_centerX += .1;
        break;
    case 'q':
        eye_centerY += .1;
        break;
    case 'a':
        eye_centerY -= .1;
        break;

    case 'u':
        eyeX += 0.1;
        break;
    case 'j':
        eyeX -= 0.1;
        break;
    case 'o':
        eyeZ += 0.1;
        break;
    case 'l':
        eyeZ -= 0.1;
        break;

    case 'i':
        eyeY += 0.1;
        break;
    case 'k':
        eyeY -= 0.1;
        break;
    case 'z':
        goingHome = 1;
        object_flag=0;
        break;
    case 'v':
       object_flag= 1;
        break;



}

Viewing();
glutPostRedisplay();
}
void MouseInt (int botao, int estado, int coorX, int coorY) {

    switch(botao) {
        case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN) {

           // 25 + ( std::rand() % ( 63 - 25 + 1 ) )
            if(object_flag)
            {
                music tmp ;
                tmp.x = randfrom(-1.6, 1.6);
                tmp.z = randfrom(0,8);
                if(list.count < max_buf)
                cir_buf_push(&list , tmp);
            }
            else{
                object_flag = 1;
                objectX = randfrom(-1.6, 1.6);
                objectZ = randfrom(0,10);
            }
        }


    }
}



void Timer(int time_) {
     glutPostRedisplay();
     glutTimerFunc(20,Timer,1);
}



int  main ( int argc, char** argv ){
    glutInit  (&argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  | GLUT_RGBA);
	glutInitWindowSize(600,600);
	glutCreateWindow("Douglas");

    loadTexture("D:\\ACM\\new_glut\\sky.bmp", 0);
    loadTexture("D:\\ACM\\new_glut\\disco.bmp", 1);

    loadTexture("D:\\ACM\\new_glut\\grama.bmp", 21);

    glutReshapeFunc(ChangeSize);


	init();
	glutDisplayFunc(playGame);
    glutKeyboardFunc(keyboard);
        glutMouseFunc(MouseInt);

    glutCreateMenu(menuFunc);
        glutAddMenuEntry("head", 10);
        glutAddMenuEntry("Right Arm", 2);
         glutAddMenuEntry("Right Elbow", 5);
        glutAddMenuEntry("Right Leg", 7);

        glutAddMenuEntry("Right Knee", 9);
        glutAddMenuEntry("left Arm", 3) ;
        glutAddMenuEntry("Left Elbow", 4);

        glutAddMenuEntry("Left Leg", 6);
        glutAddMenuEntry("Left Knee", 8);
        glutAddMenuEntry("Dance", 20);

        glutAddMenuEntry("Exit", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutTimerFunc(0,Timer,1);
	glutMainLoop();
return 0;
}
