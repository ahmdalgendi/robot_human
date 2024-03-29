//#include<windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <GL/glut.h>
//#include<stdbool.h>
//#include <math.h>
//#include <time.h>
///// texture struct
//typedef struct BMPImagem {
//    int   width;
//    int   height;
//    char *data;
//}BMPImage;
//
//GLuint texture_id[15];
//void getBitmapImageData( char *pFileName, BMPImage *pImage )
//{
//    FILE *pFile = NULL;
//    unsigned short nNumPlanes;
//    unsigned short nNumBPP;
//	int i;
//
//    if( (pFile = fopen(pFileName, "rb") ) == NULL )
//		printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);
//
//    // Seek forward to width and height info
//    fseek( pFile, 18, SEEK_CUR );
//
//    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
//		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);
//
//    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
//		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);
//
//    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
//		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);
//
//    if( nNumPlanes != 1 )
//		printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);
//
//    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
//		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);
//
//    if( nNumBPP != 24 )
//		printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);
//
//    fseek( pFile, 24, SEEK_CUR );
//
//    int nTotalImagesize = (pImage->width * pImage->height) * 3;
//
//    pImage->data = (char*) malloc( nTotalImagesize );
//
//    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
//		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);
//
//	char charTemp;
//    for( i = 0; i < nTotalImagesize; i += 3 )
//	{
//		charTemp = pImage->data[i];
//		pImage->data[i] = pImage->data[i+2];
//		pImage->data[i+2] = charTemp;
//    }
//}
//
//void CarregaTextura(char* Filename, int id)
//{
//
//    BMPImage textura;
//
//    getBitmapImageData( Filename, &textura);
//
//    glEnable(GL_TEXTURE_2D);
//    glGenTextures(1, &texture_id[id]);
//
//    glBindTexture(GL_TEXTURE_2D, texture_id[id]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.width, textura.height, 0,
//                                    GL_RGB, GL_UNSIGNED_BYTE, textura.data);
//    glTexGenf(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//    glTexGenf(GL_T,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
//
//}
//
//bool head_right_done , head_left_done, rot_head_flag , left_arm_flag  , moving;
//
///// array that controls the moving
//bool is_moving[15];
//float angle_moving[15],rot_val[11]={1.2,-1.2,-1.2,-1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2};
//
///**
//every flag and what it refers to
//-----------------
//0 -> head
//1 -> left arm
//2 -> left elbow
//3 -> left hand
//4 -> right hand
//5 -> right  elbow
//6 -> right hand
//7 -> left leg
//8 -> left knee
//9 -> right leg
//10 -> right knee
//**/
//
//float
//
//        left_armX =0, left_armZ=0,
//        angle = 45, fAspect, angx = 0, angy = 0, angz = 0,
//        moveZ = -5.0, eyeZ = 0.0, eyeX = 0.0,
//        eyeY = 0.0,  moveX = 0.0, tamTela = 400.0, eye_centerX = 0.0, eye_centerY = 0.0,
//        eye_centerZ = 0.0;
//float head_rotate = 0, rotval=-1.2 ;
//
//
//
//GLfloat ambient_light2[4] = {0.4, 0.4, 0.4, 1.0};
//GLfloat ambient_light[4] = {0.0, 0.0, 0.0, 1.0};
//
//GLfloat difuse_light[4] = {0.2, 0.2, 0.2, 1.0};
//GLfloat dspec_light[4] = {0.3, 0.3, 0.3, 1.0};
//
//GLfloat light_pos0[4] = {2.0, 4.0, -5.0, 1.0};
//GLfloat light_dir0[4] = {-2.0, -4.0, -5.0, 1.0};
//
//GLfloat light_pos1[4] = {-2.0, 4.0, -3.0, 1.0};
//GLfloat light_dir1[4] = {3.0, -5.0, -3.0, 1.0};
//
//GLfloat light_pos2[4] = {-2.0, 4.0, -12.0, 1.0};
//GLfloat light_dir2[4] = {3.0, -5.0, -12.0, 1.0};
//
//GLfloat light_pos3[4] = {2.0, 4.0, -18.0, 1.0};
//GLfloat light_dir3[4] = {-2.0, -4.0, -18.0, 1.0};
//
//GLfloat light_pos4[4] = {0.0, 1.0, -5.0, 1.0};
//
//GLfloat obj_Amb[4] = {0.3, 0.2, 0.1, 1.0};
//GLfloat obj_Dif[4] = {0.2, 0.2, 0.2, 1.0};
//GLfloat obj_Esp[4] = {0.1, 0.1, 0.1, 1.0};
//
//
//void Viewing()	{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//    gluPerspective(angle,fAspect,0.1,800);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//
//    gluLookAt( eyeX,eyeY,eyeZ -10,
//               eye_centerX,eye_centerY,eye_centerZ,
//               0,1,0);
//
//}
//
//void ChangeSize(GLsizei w, GLsizei h)	{
//
//	if ( h == 0 )
//		h = 1;
//        glViewport(0, 0, w, w);
//
//	fAspect = (GLfloat)w/(GLfloat)h;
//	Viewing();
//	tamTela = w/2.0;
//}
//
//
//
//void init(void) {
//    for(int i =0;i<15;i++)
//        rot_val[i] = 1.2;
//	glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);
//    glLoadIdentity();
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse_light );
//    glLightfv(GL_LIGHT0, GL_SPECULAR, dspec_light );
//    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0 );
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir0);
//    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);
//    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 40.0);
//
//    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, difuse_light );
//    glLightfv(GL_LIGHT1, GL_SPECULAR, dspec_light );
//    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1 );
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
//
//    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light);
//    glLightfv(GL_LIGHT2, GL_DIFFUSE, difuse_light );
//    glLightfv(GL_LIGHT2, GL_SPECULAR, dspec_light );
//    glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
//    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_dir2);
//    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 80.0);
//    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 40.0);
//
//    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient_light);
//    glLightfv(GL_LIGHT3, GL_DIFFUSE, difuse_light );
//    glLightfv(GL_LIGHT3, GL_SPECULAR, dspec_light );
//    glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
//    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_dir3);
//    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 80.0);
//    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 40.0);
//
//    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient_light2);
//    glLightfv(GL_LIGHT4, GL_DIFFUSE, difuse_light);
//    glLightfv(GL_LIGHT4, GL_SPECULAR, dspec_light);
//    glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);
//
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obj_Amb);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obj_Dif);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obj_Esp);
//    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 2);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT4);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_DEPTH_TEST);
//
//}
//
//
//
//void my_man() {
//
//  //   glColor3f(0.0, 0.0, 1.0);
//    glPushMatrix();
//        glTranslatef(moveX, -1.0, moveZ);
//        glRotatef(angx,1.0,0.0,0.0);
//        glRotatef(angy,0.0,1.0,0.0);
//        glRotatef(angz,0.0,0.0,1.0);
//        glScalef(1.2, 0.7, 0.4);
//
//
//        ///HEAD///
//
//        glPushMatrix();  // head
//
//        glRotatef(head_rotate, 0,1,0);
//            glPushMatrix();///skull
//                glRotatef(90, 1.0, 0.0, 0.0);
//                 glColor3f(234/255.0  , 192/255.0, 134/255.0);
//                glutSolidCube(0.3 );
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix(); /// nose
//                glTranslatef(0.0, -0.05, -0.2);
//                 glRotatef(50, 1.0, 0.0, 0.0);
//                glRotatef(-10, 0.0, 1.0, 0.0);
//                glScalef(0.1, 0.1, 0.1);
//                glColor3f(1  , 15/255.0, 134/255.0);
//                glutSolidSphere(.3, 10,10);
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix();///right eye
//                glColor3f(0,0,0);
//                glTranslatef(0.1, 0.1, -0.2);
//                glScalef(0.2, 0.2, 0.2);
//                glutSolidCube(0.3 );
//                glColor3f(1,1,1);
//                glScalef(0.5,.5,.8);
//                glTranslatef(0,0,-.15);
//                glutSolidCube(0.3 );
//                glTranslatef(0,0,-.15);
//                glColor3f(.1,0.1,0.1);
//                glutSolidSphere(.1, 20, 20);
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix();/// left eye
//                glColor3f(0,0,0);
//                glTranslatef(-0.1, 0.1, -0.2);
//                glScalef(0.2, 0.2, 0.2);
//                glutSolidCube(0.3 );
//                glColor3f(1,1,1);
//                glScalef(0.5,.5,.8);
//                glTranslatef(0,0,-.15);
//                glutSolidCube(0.3 );
//                glTranslatef(0,0,-.15);
//                glColor3f(.1,0.1,0.1);
//                glutSolidSphere(.1, 20, 20);
//                glColor3f(1,1,1);
//            glPopMatrix();
//
//
//        glPopMatrix(); ///head done
//        ///mouth///
//        glPushMatrix(); ///mouth
//            glColor3f(.7,0,0);
//            glTranslatef(0.0, -0.25, 0.0);
//            glScalef(0.3, 0.2, 0.5);
//            glRotatef(90, 1.0, 0.0, 0.0);
//            gluCylinder(gluNewQuadric(), 0.5, 0.3, 0.3, 20,10);
//            glColor3f(1,1,1);
//        glPopMatrix();
//        ///body///
//        glPushMatrix();
//            glColor3f(17/255.0  , 53/255.0, 114/255.0);
//            glTranslatef(0.0, -0.75, 0.0);
//            glScalef(0.7, 1.2, 1.0);
//            glRotatef(90, 1.0, 0.0, 0.0);
//            glutSolidCube(0.4 );
//            glColor3f(1,1,1);
//        glPopMatrix();
//        ///left arm///
//        glPushMatrix();
//            glTranslatef(0.13, 0.18, 0.0);
//            glScalef(1.5, 1.5, 1.5);
//            glTranslatef(-0.2, -0.4, 0.0);
//            glRotatef(0, 1.0, 0.0, 0.0);
//            glRotatef(head_rotate, 0.0, 0.0, 1.0);
//            glRotatef(20, 0.0, 0.0, 1.0);
//            glTranslatef(0.2, 0.4, 0.0);
//
//            glPushMatrix();
//
//                glColor3f(17/255.0  , 53/255.0, 114/255.0);
//                glTranslatef(-0.3, -0.5, 0.0);
//                glRotatef(-45, 0.0, 0.0, 1.0);
//                glScalef(0.5, 1.3, 0.8);
//                glRotatef(90, 1.0, 0.0, 0.0);
//                glutSolidCube(0.1 );
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix();
//                glTranslatef(-0.39, -0.56, 0.0);
//                glRotatef(0, 1.0, 0.0, 0.0);
//                glRotatef(0, 0.0, 0.0, 1.0);
//                glRotatef(10, 0.0, 0.0, 1.0);
//                glTranslatef(0.39, 0.56, 0.0);
//                glPushMatrix(); ///left upper arm
//                    glColor3f(17/255.0  , 53/255.0, 114/255.0);
//                    glTranslatef(-0.45, -0.65, 0.0);
//                    glRotatef(-45, 0.0, 0.0, 1.0);
//                    glScalef(0.5, 1.3, 0.8);
//                    glRotatef(90, 1.0, 0.0, 0.0);
//                    glutSolidCube(0.1 );
//                    glColor3f(1,1,1);
//                glPopMatrix();
//                glPushMatrix(); ///left lower arm
//                    glTranslatef(-0.52, -0.72, 0.0);
//                    glRotatef(0, 1.0, 0.0, 0.0);
//                    glRotatef(0, 0.0, 0.0, 1.0);
//                    glTranslatef(0.52, 0.72, 0.0);
//                    glPushMatrix(); ///left hand
//                        glColor3f(234/255.0  , 192/255.0, 134/255.0);
//                        glTranslatef(-0.55, -0.75, 0.0);
//                        glRotatef(-45, 0.0, 0.0, 1.0);
//                        glScalef(0.5, 1.3, 0.8);
//                        glRotatef(90, 1.0, 0.0, 0.0);
//                        glutSolidCube(0.05 );
//                        glColor3f(1,1,1);
//                    glPopMatrix();
//                glPopMatrix();
//            glPopMatrix();
//        glPopMatrix();
//        glPushMatrix();
//            glTranslatef(-0.13, 0.18, 0.0);
//            glScalef(1.5, 1.5, 1.5);
//            glTranslatef(0.2, -0.4, 0.0);
//            glRotatef(0, 1.0, 0.0, 0.0);
//            glRotatef(0, 0.0, 0.0, 1.0);
//            glRotatef(-20, 0.0, 0.0, 1.0);
//            glTranslatef(-0.2, 0.4, 0.0);
//            glPushMatrix(); ///right upper arm
//                glColor3f(17/255.0  , 53/255.0, 114/255.0);
//                glTranslatef(0.3, -0.5, 0.0);
//                glRotatef(45, 0.0, 0.0, 1.0);
//                glScalef(0.5, 1.3, 0.8);
//                glRotatef(90, 1.0, 0.0, 0.0);
//                glutSolidCube(0.1 );
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix();
//                glTranslatef(0.39, -0.56, 0.0);
//                glRotatef(0, 1.0, 0.0, 0.0);
//                glRotatef(0, 0.0, 0.0, 1.0);
//                glRotatef(-10, 0.0, 0.0, 1.0);
//                glTranslatef(-0.39, 0.56, 0.0);
//                    glPushMatrix(); ///right lower arm
//                        glColor3f(17/255.0  , 53/255.0, 114/255.0);
//                        glTranslatef(0.45, -0.65, 0.0);
//                        glRotatef(45, 0.0, 0.0, 1.0);
//                        glScalef(0.5, 1.3, 0.8);
//                        glRotatef(90, 1.0, 0.0, 0.0);
//                        glutSolidCube(0.1 );
//                        glColor3f(1,1,1);
//                    glPopMatrix();
//                    glPushMatrix(); ///right hand
//
//                        glTranslatef(-0.52, -0.72, 0.0);
//                        glRotatef(0, 1.0, 0.0, 0.0);
//                        glRotatef(0, 0.0, 0.0, 1.0);
//                        glTranslatef(0.52, 0.72, 0.0);
//                        glPushMatrix(); ///hummer
//                            glColor3f(0,0,0);
//                            glTranslatef(0.55, -0.75, 0.0);
//                            glRotatef(45, 0.0, 0.0, 1.0);
//                            glScalef(0.5, 1.5, 0.8);
//                            glRotatef(90, 1.0, 0.0, 0.0);
//                            glutSolidCube(0.15 );
//                            glColor3f(1,1,1);
//                        glPopMatrix();
//                    glPopMatrix();
//                glPopMatrix();
//        glPopMatrix();
//        ///Left leg//
//        glPushMatrix(); ///open leg
//            glTranslatef(0.05, 0.7, 0);
//            glScalef(1.6, 1.6, 1.6);
//            glTranslatef(-0.03, -1.2, 0.0);
//            glRotatef(0, 1.0, 0.0, 0.0);
//            glRotatef(0, 0.0, 0.0, 1.0);
//            glTranslatef(0.03, 1.2, 0.0);
//            glPushMatrix(); ///left thigh
//                glColor3f(139/255.0, 69/255.0, 19.0/255);
//                glTranslatef(-0.1, -1.25, 0.0);
//                glScalef(0.5, 1.3, 1.0);
//                glRotatef(90, 1.0, 0.0, 0.0);
//                glutSolidCube(0.1 );
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix();
//                glTranslatef(-0.03, -1.35, 0.0);
//                glRotatef(0, 1.0, 0.0, 0.0);
//                glRotatef(0, 0.0, 0.0, 1.0);
//                glTranslatef(0.03, 1.35, 0.0);
//                glPushMatrix(); ///left lower leg
//                    glColor3f(139/255.0, 69/255.0, 19.0/255);
//
//                    glTranslatef(-0.1, -1.45, 0.0);
//                    glScalef(0.5, 1.3, 1.0);
//                    glRotatef(90, 1.0, 0.0, 0.0);
//                    glutSolidCube(0.1 );
//                    glColor3f(1,1,1);
//                glPopMatrix();
//                glPushMatrix(); ///left foot
//                    glColor3f(0.11,.01,0.01);
//                    glTranslatef(-0.1, -1.60, 0.0);
//                    glScalef(0.5, 0.3, 1.4);
//                    glRotatef(90, 1.0, 0.0, 0.0);
//                    glutSolidCube(0.19 );
//                    glColor3f(1,1,1);
//                glPopMatrix();
//            glPopMatrix();
//        glPopMatrix();
//        ///right leg//
//        glPushMatrix();
//            glTranslatef(-0.05, 0.7, 0);
//            glScalef(1.6, 1.6, 1.6);
//            glTranslatef(0.03, -1.2, 0.0);
//            glRotatef(0, 1.0, 0.0, 0.0);
//            glRotatef(0, 0.0, 0.0, 1.0);
//            glTranslatef(-0.03, 1.2, 0.0);
//            glPushMatrix(); ///right upper leg
//                glColor3f(139/255.0, 69/255.0, 19.0/255);
//                glTranslatef(0.1, -1.25, 0.0);
//                glScalef(0.5, 1.3, 1.0);
//                glRotatef(90, 1.0, 0.0, 0.0);
//                glutSolidCube(0.1 );
//                glColor3f(1,1,1);
//            glPopMatrix();
//            glPushMatrix(); ///right lower leg
//                glTranslatef(0.03, -1.35, 0.0);
//                glColor3f(139/255.0, 69/255.0, 19.0/255);
//                glRotatef(0, 1.0, 0.0, 0.0);
//                glRotatef(0, 0.0, 0.0, 1.0);
//                glTranslatef(-0.03, 1.35, 0.0);
//                glPushMatrix();
//                    glTranslatef(0.1, -1.45, 0.0);
//                    glScalef(0.5, 1.3, 1.0);
//                    glRotatef(90, 1.0, 0.0, 0.0);
//                    glutSolidCube(0.1 );
//                glPopMatrix();
//                glPushMatrix();
//                    glColor3f(0,0,0);
//                    glTranslatef(0.1, -1.60, 0.0);
//                    glScalef(0.5, 0.3, 1.4);
//                    glRotatef(90, 1.0, 0.0, 0.0);
//                    glutSolidCube(0.19 );
//                glPopMatrix();
//            glColor3f(1,1,1);
//            glPopMatrix();
//        glPopMatrix();
//
//    glPopMatrix();
//
//}
//
//
//void bigWall() {
//
//    glPushMatrix();
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
//        glTranslatef(-3.0, 1.0, -30);
//        glScalef(5.0, 5.0, 1.0);
//        glutSolidCube(1.0);
//        glDisable(GL_TEXTURE_2D);
//    glPopMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
//    glPushMatrix();
//        glTranslatef(4.7, -2.0, -5.0);
//        glScalef(50.0, 0.1, 100.0);
//        glRotatef(90, 1.0, 0.0, 0.0);
//        glutSolidCube(1.0);
//    glPopMatrix();
//
//
//glDisable(GL_TEXTURE_2D);
//}
//
//
//void playGame(void)	{
//
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    	glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);
//    glPushMatrix();
//     glTranslatef(0.0, 0.35, 0.0);
//        bigWall();
//       my_man();
//
//       head_rotate_();
//    glPopMatrix();
//    glutSwapBuffers();
//}
//void head_rotate_()
//{
//
//    if(rot_head_flag){
//        printf("%f\n" , head_rotate);
//        head_rotate+= rotval;
//        if(head_rotate <= -90)
//            rotval *=-1 , head_left_done =1;
//        if(head_rotate >= 90)
//            rotval *=-1, head_right_done =1 ;
//        if( abs(head_rotate - 0) <=1 && head_left_done && head_right_done)
//        {
//            head_left_done = head_right_done = 0;
//            rot_head_flag = 0;
//
//        }
//    }
//}
//void move_func()
//{
//    for(int i = 0;i<11 ; i++)
//    {
//        if(is_moving[i])
//        {
//
//        }
//    }
//}
//
//
//
//void keyboard (unsigned char key, int x, int y){
//  switch (key) {
//  case '8':
//      moveZ  += .42;
//    break;
//    case '2':
//      moveZ-= .42;
//    break;
//    case '4':
//      moveX+= .42;
//    break;
//    case '6':
//      moveX-= .42;
//    break;
//
//    case 'h':
//        rot_head_flag = 1;
//        break;
//    case 'z':
//        head_rotate+=.8;
//        head_rotate  = head_rotate > 90 ? 90 : head_rotate;
//        break;
//    case'x' :
//        head_rotate -= .8;
//        head_rotate = head_rotate< -90 ? -90 : head_rotate;
//        break;
//   case 'd':
//        eye_centerZ -= .1;
//        break;
//   case 'e':
//        eye_centerZ += .1;
//        break;
//    case 's':
//        eye_centerX -= .1;
//        break;
//    case 'w':
//        eye_centerX += .1;
//        break;
//    case 'q':
//        eye_centerY += .1;
//        break;
//    case 'a':
//        eye_centerY -= .1;
//        break;
//
//    case 'u':
//        eyeX += 0.1;
//        break;
//    case 'j':
//        eyeX -= 0.1;
//        break;
//    case 'o':
//        eyeZ += 0.1;
//        break;
//    case 'l':
//        eyeZ -= 0.1;
//        break;
//
//    case 'i':
//        eyeY += 0.1;
//        break;
//    case 'k':
//        eyeY -= 0.1;
//        break;
//
//}
//
//
//Viewing();
//glutPostRedisplay();
//}
//
//
//
//void Timer(int extra) {
//     glutPostRedisplay();
//     glutTimerFunc(20,Timer,10);
//}
//
//
//
//int  main ( int argc, char** argv ){
//
//    glutInit  (&argc, argv );
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  | GLUT_RGBA);
//	glutInitWindowSize(600,600);
//	glutCreateWindow("Douglas");
//    glutReshapeFunc(ChangeSize);
//    CarregaTextura("D:\\ACM\\new_glut\\head.bmp", 0);
//    CarregaTextura("D:\\ACM\\new_glut\\grama.bmp", 21);
//
//	init();
//	glutDisplayFunc(playGame);
//    glutKeyboardFunc(keyboard);
//    glutTimerFunc(0,Timer,10);
//
//	glutMainLoop();
//
//}
