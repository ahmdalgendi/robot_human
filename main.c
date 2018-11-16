//#include<windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <GL/glut.h>
//#include <math.h>
//#include <time.h>
//#define MAX_NO_TEXTURES 25
//
//typedef struct BMPImagem {
//    int   width;
//    int   height;
//    char *data;
//}BMPImage;
//
//struct elemento {
//
//float x;
//float z;
//int flagNeedMoveBack;
//int flagNeedMoveLeft;
//int flagNeedMoveOn;
//int flagNeedMoveRight;
//struct elemento *prox;
//int isCesta;
//
//}; typedef struct elemento tipoElemento;
//
///*Lista de pontos*/
//struct listaDE {
//
//    tipoElemento *primeiro;
//    tipoElemento *ultimo;
//    int tamanhoLista;
//}; typedef struct listaDE tipoLDE;
//
//
//tipoLDE listaPontos;
//tipoElemento *p;
//tipoElemento *r;
//
//GLuint texture_id[MAX_NO_TEXTURES];
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
//
//float angle = 45, fAspect, xClick = 0.0, yClick = 0, flag = 0, angx = 0, angy = 0, angz = 0,
//      rotateShoulderRX = 0, rotateShoulderRZ = 0, rotateShoulderLX = 0, rotateShoulderLZ = 0,
//      rotateElbowRX = 0, rotateElbowRZ = 0, rotateElbowLX = 0, rotateElbowLZ = 0, rotateHandLX = 0,
//      rotateHandLZ = 0, rotateHandRX = 0, rotateHandRZ = 0, rotateLegLZ = 0, rotateLegLX = 0,
//      rotateLegRZ = 0, rotateLegRX = 0, rotateKneeLZ = 0, rotateKneeLX = 0, rotateKneeRX = 0,
//      rotateKneeRZ = 0, tLegR = 0.0, tLegL = 0.0, moveZ = -5.0, roofZ = -1.0, camZ = 0.5, camX = 0.0,
//      camY = 0.0, catZ = 0.0, moveX = 0.0, rotateDoorY = 0.0, tamTela = 400.0, angCamX = 0.0, angCamY = 0.0,
//      angCamZ = 0.0;
//float head_rotate = 0;
//
//int  flagShoulderR = 0, flagShoulderL = 0, flagDrawCat = 0, maior = 0,
//      activeZ = 0, flagCall = 0, flagElbowL = 0, flagElbowR = 0, flagLegL = 0, flagLegR = 0, flagKneeL = 0,
//      flagKneeR = 0, flagZoom = 0, flagDrawCesta = 0, flagFinaliza = 0, firstTime = 0, flagDay = 0,
//      flagNeedRotate180 = 0, flagNeedRotateR = 0, flagNeedRotateL = 0, flagNeedMoveOn = 0, flagNeedMoveBack = 0,
//      flagNeedMoveRight = 0, flagNeedMoveLeft = 0, flagNormal = 0, flagMoveRGo = 0, flagMoveRCome = 0,
//      flagMoveLGo = 0, flagMoveLCome = 0, flagMove = 0, flagNormaliza = 0, atualF = 0, atualL = 0, atualR = 0,
//      atualB = 0, cont = 0;
//
//
//
/////Rotinas de Lista///
//
///*Inicia a lista de pontos*/
//void inicializaLista (tipoLDE *listaAux){
//
//    listaAux->primeiro = NULL;
//    listaAux->ultimo = NULL;
//    listaAux->tamanhoLista = 0;
//}
//
///*Insere um elemento na lista*/
//void insereElementoFim(tipoLDE *listaAux, float x, float z,
//int flagNeedMoveBack, int flagNeedMoveLeft, int flagNeedMoveOn, int flagNeedMoveRight, int isCesta) {
//
//    tipoElemento *novoElem = malloc(sizeof(tipoElemento));
//
//    if (novoElem == NULL)
//        printf ("Não foi possível alocar o elemento. Erro!");
//
//
//    novoElem->x = x;
//    novoElem->z = z;
//    novoElem->flagNeedMoveBack = flagNeedMoveBack;
//    novoElem->flagNeedMoveLeft = flagNeedMoveLeft;
//    novoElem->flagNeedMoveOn = flagNeedMoveOn;
//    novoElem->flagNeedMoveRight = flagNeedMoveRight;
//    novoElem->isCesta = isCesta;
//
//
//    //Atualiza lista conforme seu tamanho
//    if (listaAux->tamanhoLista == 0){
//        novoElem->prox = NULL;
//        listaAux->primeiro= novoElem;
//        listaAux->ultimo=novoElem;
//    }
//
//    else {
//    novoElem ->prox = NULL;
//    listaAux->ultimo->prox = novoElem;
//    listaAux->ultimo= novoElem;
//    }
//    //Atualiza tamanho da lista
//    listaAux->tamanhoLista++;
//}
//
/////Rotinhas de textura///
///*Le uma img BMP conforme visto em aula*/
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
///*Carrega uma textura e computa seu ID em um vetor de ID*/
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
/////Rotinas que definem parametros da camera e reposicionamento///
//void Viewing()	{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//    gluPerspective(angle,fAspect,0.1,800);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//    glTranslatef(camX, camY, camZ+1.3);
//	glRotatef(angCamZ, 0.0, 0.0, 1.0);
//	glRotatef(angCamY, 0.0, 1.0, 0.0);
//	glRotatef(angCamX, 1.0, 0.0, 0.0);
//
//
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
/////Rotina que iniciaiza enables e luzes///
//void init(void) {
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//
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
//
//    glEnable(GL_DEPTH_TEST);
//
//}
//
/////Rotinas de desenho///
//
//
//void drawHuman() {
// ///Humano//
//  //   glColor3f(0.0, 0.0, 1.0);
//    glPushMatrix();
//        glTranslatef(moveX, -1.0, moveZ);
//        glRotatef(angx,1.0,0.0,0.0);
//        glRotatef(angy,0.0,1.0,0.0);
//        glRotatef(angz,0.0,0.0,1.0);
//        glScalef(1.2, 0.7, 0.4);
//
//
//        ///Cabeca///
//
//        glPushMatrix();
//
//glRotatef(head_rotate, 0,1,0);
//            glPushMatrix();// /head
//
////            glEnable(GL_TEXTURE_GEN_T);
////            glEnable(GL_TEXTURE_GEN_S);
//            glEnable(GL_TEXTURE_2D);
//
//            glBindTexture(GL_TEXTURE_2D, texture_id[0]);
//
//
//
//            glRotatef(90, 1.0, 0.0, 0.0);
//             glColor3f(234/255.0  , 192/255.0, 134/255.0);
//            glutSolidCube(0.3 );
//            glColor3f(1,1,1);
//            glDisable(GL_TEXTURE_2D);
////            glDisable(GL_TEXTURE_GEN_S);
////            glDisable(GL_TEXTURE_GEN_T);
//
//            glPopMatrix();
//
//            glPushMatrix(); // nose
//            glTranslatef(0.0, -0.05, -0.3);
//             glRotatef(50, 1.0, 0.0, 0.0);
//            glRotatef(-10, 0.0, 1.0, 0.0);
//            glScalef(0.1, 0.1, 0.1);
//            glColor3f(1  , 192/255.0, 134/255.0);
//            glutSolidTetrahedron();
//            glColor3f(1,1,1);
//
//        glPopMatrix();
//            glPushMatrix();///right eye
//                glColor3f(0,0,0);
//                glTranslatef(0.1, 0.1, -0.3);
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
//            glPopMatrix();/// left eye
//              glPushMatrix();
//                glColor3f(0,0,0);
//                glTranslatef(-0.1, 0.1, -0.3);
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
//        glPopMatrix(); ///Fecha cabeca
//        ///Pescoco///
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
//            glRotatef(rotateShoulderLX, 1.0, 0.0, 0.0);
//            glRotatef(rotateShoulderLZ, 0.0, 0.0, 1.0);
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
//                glRotatef(rotateElbowLX, 1.0, 0.0, 0.0);
//                glRotatef(rotateElbowLZ, 0.0, 0.0, 1.0);
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
//                glPopMatrix(); ///Fecha antebraco
//                glPushMatrix(); ///left lower arm
//                    glTranslatef(-0.52, -0.72, 0.0);
//                    glRotatef(rotateHandLX, 1.0, 0.0, 0.0);
//                    glRotatef(rotateHandLZ, 0.0, 0.0, 1.0);
//                    glTranslatef(0.52, 0.72, 0.0);
//                    glPushMatrix(); ///left hand
//                        glColor3f(234/255.0  , 192/255.0, 134/255.0);
//                        glTranslatef(-0.55, -0.75, 0.0);
//                        glRotatef(-45, 0.0, 0.0, 1.0);
//                        glScalef(0.5, 1.3, 0.8);
//                        glRotatef(90, 1.0, 0.0, 0.0);
//                        glutSolidCube(0.05 );
//                        glColor3f(1,1,1);
//                    glPopMatrix(); ///Fecha Mao
//                glPopMatrix();
//            glPopMatrix(); ///Fecha cotovelo
//        glPopMatrix(); ///Fecha braco
//        glPushMatrix(); ///Abre braco
//            glTranslatef(-0.13, 0.18, 0.0);
//            glScalef(1.5, 1.5, 1.5);
//            glTranslatef(0.2, -0.4, 0.0);
//            glRotatef(rotateShoulderRX, 1.0, 0.0, 0.0);
//            glRotatef(rotateShoulderRZ, 0.0, 0.0, 1.0);
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
//                glRotatef(rotateElbowRX, 1.0, 0.0, 0.0);
//                glRotatef(rotateElbowRZ, 0.0, 0.0, 1.0);
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
//                        glRotatef(rotateHandRX, 1.0, 0.0, 0.0);
//                        glRotatef(rotateHandRZ, 0.0, 0.0, 1.0);
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
//            glTranslatef(0.05, 0.7, tLegL);
//            glScalef(1.6, 1.6, 1.6);
//            glTranslatef(-0.03, -1.2, 0.0);
//            glRotatef(rotateLegLX, 1.0, 0.0, 0.0);
//            glRotatef(rotateLegLZ, 0.0, 0.0, 1.0);
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
//                glRotatef(rotateKneeLX, 1.0, 0.0, 0.0);
//                glRotatef(rotateKneeLZ, 0.0, 0.0, 1.0);
//                glTranslatef(0.03, 1.35, 0.0);
//                glPushMatrix(); ///left lower leg ?
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
//            glTranslatef(-0.05, 0.7, tLegR);
//            glScalef(1.6, 1.6, 1.6);
//            glTranslatef(0.03, -1.2, 0.0);
//            glRotatef(rotateLegRX, 1.0, 0.0, 0.0);
//            glRotatef(rotateLegRZ, 0.0, 0.0, 1.0);
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
//                glRotatef(rotateKneeRX, 1.0, 0.0, 0.0);
//                glRotatef(rotateKneeRZ, 0.0, 0.0, 1.0);
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
//    glPopMatrix(); ///fecha humano
//glDisable(GL_TEXTURE);
//}
//
//
//
//void drawCat() {
//
//glPushMatrix(); ///Abre gato
//
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, texture_id[6]);
//
//        glPushMatrix(); ///Abre Cabeca
//            glScalef(0.6, 0.6, 0.6);
//            glTranslatef(0.0, 0.6, 0.0);
//            glRotatef(90, 1.0, 0.0, 0.0);
//            glutSolidSphere(0.3, 20, 20);
//        glPopMatrix(); ///Fecha Cabeca
//        glPushMatrix(); ///Abre corpo
//            glScalef(0.6, 0.6, 0.6);
//            glRotatef(90, 1.0, 0.0, 0.0);
//            glutSolidSphere(0.4, 20, 20);
//        glPopMatrix(); ///Fecha Corpo
//        glPushMatrix(); ///Abre cauda
//            glPushMatrix(); ///Cauda 1
//                glTranslatef(0.0, 0.0, -0.28);
//                glRotatef(30, 1.0, 0.0, 0.0);
//                glScalef(1.0, 0.2, 0.7);
//                glutSolidSphere(0.1, 20, 20);
//            glPopMatrix(); ///Cauda1
//            glPushMatrix(); ///Cauda2
//                glTranslatef(0.0, 0.05, -0.36);
//                glRotatef(30, 1.0, 0.0, 0.0);
//                glScalef(1.0, 0.2, 0.5);
//                glutSolidSphere(0.1, 20, 20);
//            glPopMatrix();
//            glPushMatrix(); ///Cauda3
//                glTranslatef(0.0, 0.09, -0.4);
//                glRotatef(35, 1.0, 0.0, 0.0);
//                glScalef(1.0, 0.2, 0.5);
//                glutSolidSphere(0.1, 20, 20);
//            glPopMatrix();
//            glPushMatrix(); ///Cauda3
//                glTranslatef(0.0, 0.12, -0.45);
//                glRotatef(40, 1.0, 0.0, 0.0);
//                glScalef(1.0, 0.2, 0.5);
//                glutSolidSphere(0.1, 20, 20);
//            glPopMatrix();
//         glPopMatrix();
//            glPushMatrix();  ///Orelha 1
//                glTranslatef(0.1, 0.5, 0.0);
//                glRotatef(60, 0.0, 0.0, 1.0);
//                glScalef(0.1, 0.1, 0.1);
//                glutSolidTetrahedron();
//            glPopMatrix();
//            glPushMatrix();  ///Orelha 1
//                glTranslatef(-0.1, 0.5, 0.0);
//                glScalef(0.1, 0.1, 0.1);
//                glutSolidTetrahedron();
//            glPopMatrix();
//            glPushMatrix();
//                glTranslatef(-0.075, 0.37, 0.16);
//                glScalef(0.1, 0.1, 0.1);
//                glutSolidSphere(0.1, 40, 40);
//            glPopMatrix();
//            glPushMatrix();
//                glTranslatef(0.075, 0.37, 0.16);
//                glScalef(0.1, 0.1, 0.1);
//                glutSolidSphere(0.1, 40, 40);
//            glPopMatrix();
//    glPopMatrix(); ///Fecha Gato*/
//    glDisable(GL_TEXTURE_2D);
//
//}
//
//void drawHouse() {
//
//    glPushMatrix(); ///abre
//        glPushMatrix();
//            glTranslatef(-0.33, -0.5, 0.5);
//            glScalef(0.4, 0.4, 0.4);
//            glRotatef(90, 0.0, 1.0, 0.0);
//            glutSolidCube(1.0);
//        glPopMatrix();
//        glPushMatrix();
//            glTranslatef(-0.33, -0.5, -0.5);
//            glScalef(0.4, 0.4, 0.4);
//            glRotatef(90, 0.0, 1.0, 0.0);
//            glutSolidCube(1.0);
//        glPopMatrix();
//        glPushMatrix();
//         glEnable(GL_TEXTURE_2D);
//         glBindTexture(GL_TEXTURE_2D, texture_id[22]);
//            glTranslatef(-0.2, -0.6, 1.0);
//            glScalef(0.4, 0.8, 0.0);
//            glutSolidCube(1.0);
//        glPopMatrix();
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, texture_id[4]);
//        glPushMatrix(); ///T1
//            glTranslatef(-0.45, 0.0, 0.0);
//            glRotatef(20, 0.0, 0.0, 1.0);
//            glScalef(1.0, 0.1, 2.0);
//            glutSolidCube(1.0);
//        glPopMatrix();
//        glPushMatrix(); ///T2
//            glTranslatef(0.0, 0.0, 0.0);
//            glTranslatef(0.45, 0.0, 0.0);
//            glRotatef(-20, 0.0, 0.0, 1.0);
//            glScalef(1.0, 0.1, 2.0);
//            glutSolidCube(1.0);
//        glPopMatrix();
//        glDisable(GL_TEXTURE_2D);
//        glPushMatrix(); ///Baixo
//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, texture_id[10]);
//            glTranslatef(0.0, -0.5, 0.0);
//            glScalef(1.0, 1.0, 2.0);
//            glutSolidCube(1.0);
//        glPopMatrix();
//
//        glPushMatrix();
//
//            glScalef(1.5, 1.0, 1.0);
//            glutSolidCube(0.3);
//
//        glPopMatrix();
// glDisable(GL_TEXTURE_2D);
//    glPopMatrix();
//}
//
//void cesta() {
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, texture_id[17]);
//    glPushMatrix();
//        glScalef(0.5, 0.5, 0.5);
//        glRotatef(90, 1.0, 0.0, 0.0);
//        gluCylinder(gluNewQuadric(), 0.5, 0.3, 0.3, 20,10);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
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
/////Rotina que roda os cliques e as animacoes
//void playGame(void)	{
//
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//     bigWall();
//
//    glPushMatrix();
//    glPopMatrix();
//
//    glPushMatrix();
//     glTranslatef(0.0, 0.35, 0.0);
//
//       drawHuman();
//    glPopMatrix();
//
//
//
//    if(flagDrawCat == 1 && flagFinaliza == 0) {
//       /*Redesenha os pontos*/
//        if(r != NULL) {
//            if(r->isCesta == 0) {
//
//            }
//
//            if(r->prox == NULL)
//                r = p;
//            else
//            r = r->prox;
//
//        }
//
//
//        if(p->flagNeedMoveRight == 1) {
//            atualR = 1;
//            if(atualF == 1) {
//                if(cont < 90) {
//                    angy -= 1;
//                    cont += 1;
//                }
//                else {
//                    atualF = 0;
//                    cont = 0;
//                }
//            }
//            else if(atualB == 1) {
//                if(cont < 90) {
//                    angy += 1;
//                    cont +=  1;
//                }
//                else {
//                    atualB = 0;
//                    cont = 0;
//                }
//
//            }
//            else {
//                if(moveX < p->x)
//                    moveX += 0.01;
//                else {
//                    p->flagNeedMoveRight = 0;
//
//                }
//            }
//        }
//
//        if(p->flagNeedMoveLeft == 1) {
//             atualL = 1;
//             if(atualF == 1) {
//                if(cont < 90) {
//                    angy += 1;
//                    cont += 1;
//                }
//                else {
//                    atualF = 0;
//                    cont = 0;
//                }
//            }
//            else if(atualB == 1) {
//                if(cont < 90) {
//                    angy -= 1;
//                    cont +=  1;
//                }
//                else {
//                    atualB = 0;
//                    cont = 0;
//                }
//
//            }
//
//            else {
//                if(moveX > p->x)
//                    moveX -= 0.01;
//                else {
//                    p->flagNeedMoveLeft = 0;
//
//                }
//            }
//        }
//
//        if(p->flagNeedMoveOn == 1 && (p->flagNeedMoveLeft == 0 && p->flagNeedMoveRight == 0)) {
//              atualF = 1;
//
//             if(atualL == 1) {
//                if(cont < 90) {
//                    angy -= 1;
//                    cont += 1;
//                }
//                else {
//                    atualL = 0;
//                    cont = 0;
//                }
//            }
//            else if(atualR == 1) {
//                if(cont < 90) {
//                    angy += 1;
//                    cont +=  1;
//                }
//                else {
//                    atualR = 0;
//                    cont = 0;
//                }
//
//            }
//           else {
//                if(p->z < moveZ)
//                    moveZ -= 0.01;
//                else
//                    p->flagNeedMoveOn = 0;
//            }
//
//        }
//        if(p->flagNeedMoveBack == 1 && (p->flagNeedMoveLeft == 0 && p->flagNeedMoveRight == 0)) {
//            atualB = 1;
//
//             if(atualL == 1) {
//                if(cont < 90) {
//                    angy += 1;
//                    cont += 1;
//                }
//                else {
//                    atualL = 0;
//                    cont = 0;
//                }
//            }
//            else if(atualR == 1) {
//                if(cont < 90) {
//                    angy -= 1;
//                    cont +=  1;
//                }
//                else {
//                    atualR = 0;
//                    cont = 0;
//                }
//
//            }
//           else {
//                if(p->z > moveZ)
//                    moveZ += 0.01;
//                else
//                    p->flagNeedMoveBack = 0;
//
//            }
//        }
//
//        if((p->flagNeedMoveBack) == 0 && (p->flagNeedMoveOn) == 0) {
//
//            if(p->prox != NULL) {
//                flagShoulderL = 1;
//                flagShoulderR = 1;
//
//                p = p->prox;
//                if(p->z > moveZ) {
//                    p->flagNeedMoveBack = 1;
//                    p->flagNeedMoveOn = 0;
//                }
//                else {
//                    p->flagNeedMoveBack = 0;
//                    p->flagNeedMoveOn = 1;
//                }
//
//                if(p->x < xClick) {
//                    p->flagNeedMoveLeft = 1;
//                    p->flagNeedMoveRight = 0;
//                }
//                else {
//                    p->flagNeedMoveLeft = 0;
//                    p->flagNeedMoveRight = 1;
//                }
//            }
//
//            else {
//                flagDrawCat = 0;
//                flagMove = 0;
//
//            }
//        }
//    }
//
//
//
//
///*Movimeta partes do corpo separadamente*/
//if(flagShoulderR == 1) {
//        if(rotateShoulderRX < 60)
//            rotateShoulderRX += 5;
//        else
//            flagShoulderR = 0;
//    }
//    if(flagShoulderR == 0) {
//        if(rotateShoulderRX > 0)
//            rotateShoulderRX -= 5;
//    }
//
//     if(flagShoulderL == 1) {
//        if(rotateShoulderLX < 60)
//            rotateShoulderLX += 5;
//        else
//            flagShoulderL = 0;
//    }
//    if(flagShoulderL == 0) {
//        if(rotateShoulderLX > 0)
//            rotateShoulderLX -= 5;
//    }
//
//
//    if(flagElbowL == 1) {
//        if(rotateElbowLX < 60)
//            rotateElbowLX += 1;
//        else
//            flagElbowL = 0;
//    }
//    if(flagElbowL == 0) {
//        if(rotateElbowLX > 0)
//            rotateElbowLX -= 1;
//    }
//
//    if(flagElbowR == 1) {
//        if(rotateElbowRX < 60)
//            rotateElbowRX += 1;
//        else
//            flagElbowR = 0;
//    }
//    if(flagElbowR == 0) {
//        if(rotateElbowRX > 0)
//            rotateElbowRX -= 1;
//    }
//
//    if(flagLegR == 1 && flagMove == 0) {
//        if(rotateLegRX < 60)
//            rotateLegRX += 1;
//        else
//            flagLegR = 0;
//    }
//    if(flagLegR == 0 && flagMove == 0) {
//        if(rotateLegRX > 0)
//            rotateLegRX -= 1;
//    }
//
//    if(flagLegL == 1 && flagMove == 0) {
//        if(rotateLegLX < 60)
//            rotateLegLX += 1;
//        else
//            flagLegL = 0;
//    }
//    if(flagLegL == 0 && flagMove == 0) {
//        if(rotateLegLX > 0)
//            rotateLegLX -= 1;
//    }
//
//     if(flagKneeL == 1 && flagMove == 0) {
//        if(rotateKneeLX > -60)
//            rotateKneeLX -= 1;
//        else
//            flagKneeL = 0;
//    }
//    if(flagKneeL == 0 && flagMove == 0) {
//        if(rotateKneeLX < 0)
//            rotateKneeLX += 1;
//    }
//
//    if(flagKneeR == 1 && flagMove == 0) {
//        if(rotateKneeRX > -60)
//            rotateKneeRX -= 1;
//        else
//            flagKneeR = 0;
//    }
//    if(flagKneeR == 0 && flagMove == 0) {
//        if(rotateKneeRX < 0)
//            rotateKneeRX += 1;
//    }
//
//    if(flagFinaliza == 1) {
//        flagMove = 1;
//        if(angy > 0)
//            angy -= 1;
//        else if(angy < 0)
//            angy += 1;
//
//       else {
//            if(moveZ > -40)
//                moveZ -= 0.01;
//            else {
//                flagFinaliza = -1;
//                exit(0);
//            }
//
//        }
//    }
//
//    if(flagMove == 1) {
//        if(flagMoveRGo == 1) {
//            if(rotateLegRX < 60) {
//                rotateLegRX += 5;
//                if(rotateKneeRX > -30)
//                    rotateKneeRX -= 5;
//            }
//            else {
//                flagMoveRGo = 0;
//                flagMoveRCome = 1;
//            }
//
//        }
//        else if(flagMoveRCome == 1) {
//            if(rotateLegRX > 0) {
//                rotateLegRX -= 5;
//                if(rotateKneeRX < 0)
//                    rotateKneeRX += 5;
//            }
//            else {
//                flagMoveRCome = 0;
//                flagMoveLGo = 1;
//            }
//
//        }
//        else if(flagMoveLGo == 1) {
//             if(rotateLegLX < 60) {
//                rotateLegLX += 5;
//                if(rotateKneeLX > -30)
//                    rotateKneeLX -= 5;
//            }
//            else {
//                flagMoveLGo = 0;
//                flagMoveLCome = 1;
//            }
//
//
//        }
//        else if(flagMoveLCome == 1) {
//             if(rotateLegLX > 0) {
//                rotateLegLX -= 5;
//                if(rotateKneeLX < 0)
//                    rotateKneeLX += 5;
//            }
//            else {
//                flagMoveLCome = 0;
//                flagMoveRGo = 1;
//            }
//
//        }
//
//
//    }
//glutSwapBuffers();
//}
//
/////Rotinas de teclado e mouse///
//
//void MouseInt (int botao, int estado, int coorX, int coorY) {
//
//    switch(botao) {
//        case GLUT_LEFT_BUTTON:
//        if(estado == GLUT_DOWN) {
//
//         srand( (unsigned)time(NULL) );
//         srand( (unsigned)time(NULL) );
//         srand( (unsigned)time(NULL) );
//         float x = rand() % 101;  /*Calculo da posicao aleatoria*/
//         x = x/100;
//         int sinal = rand()%2;
//         if(sinal == 1)
//            x = -x;
//
//         srand( (unsigned)time(NULL) );
//         srand( (unsigned)time(NULL) );
//         srand( (unsigned)time(NULL) );
//         float z = (rand()%3500);
//         z = (z/100);
//         if(z > 0)
//            z = -z;
//         if(z > -5.0)
//            z = -6.0;
//
//         xClick = x;
//         catZ = z;
//         flagDrawCat = 1;
//         if(catZ > moveZ) {
//            flagNeedMoveBack = 1;
//            flagNeedMoveOn = 0;
//         }
//         else {
//            flagNeedMoveBack = 0;
//            flagNeedMoveOn = 1;
//         }
//         if(moveX > xClick) {
//            flagNeedRotateL = 1;
//            flagNeedMoveLeft = 1;
//            flagNeedRotateR = 0;
//            flagNeedMoveRight = 0;
//         }
//         else {
//            flagNeedRotateL = 0;
//            flagNeedMoveLeft = 0;
//            flagNeedRotateR = 1;
//            flagNeedMoveRight = 1;
//         }
//        insereElementoFim(&listaPontos, x, z, flagNeedMoveBack, flagNeedMoveLeft, flagNeedMoveOn, flagNeedMoveRight, 0);
//        insereElementoFim(&listaPontos, 0.0, -4.0, flagNeedMoveBack, flagNeedMoveLeft, flagNeedMoveOn, flagNeedMoveRight, 1);
//        if(firstTime == 0) {
//            p = listaPontos.primeiro;
//            r = p;
//            flagMoveRGo = 1;
//            firstTime = 1;
//            atualF = 1;
//        }
//         flagMove = 1;
//            break;
//        }
//}
//
// Viewing();
// glutPostRedisplay();
//}
//
//void keyboard (unsigned char key, int x, int y){
//  switch (key) {
//    case 'z':
//        head_rotate+=.8;
//        head_rotate  = head_rotate > 90 ? 90 : head_rotate;
//        break;
//    case'x' :
//        head_rotate -= .8;
//        head_rotate = head_rotate< -90 ? -90 : head_rotate;
//        break;
//   case 'a':
//        angCamY -= 1;
//        break;
//   case 'd':
//        angCamY += 1;
//        break;
//    case 'w':
//        angCamX -= 1;
//        break;
//    case 's':
//        angCamX += 1;
//        break;
//    case 'j':
//        camX += 0.1;
//        break;
//    case 'l':
//        camX -= 0.1;
//        break;
//    case 'i':
//        camZ += 0.1;
//        break;
//    case 'k':
//        camZ -= 0.1;
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
//void menuFunc(GLint opcao) {
//
//    switch(opcao) {
//        case 1:
//            flagFinaliza = 1;
//            flagMove = 1;
//            break;
//
//        case 4:
//            flagShoulderR = 1;
//            break;
//        case 5:
//            flagShoulderL = 1;
//            break;
//        case 6:
//            flagElbowL = 1;
//            break;
//        case 7:
//            flagElbowR = 1;
//            break;
//        case 8:
//            flagLegL = 1;
//            break;
//        case 9:
//            flagLegR = 1;
//            break;
//        case 10:
//            flagKneeL = 1;
//            break;
//        case 11:
//            flagKneeR = 1;
//            break;
//        case 12:
//            if(flagZoom == 0)
//                camZ += 3;
//            flagZoom = 1;
//            break;
//        case 13:
//            if(flagZoom == 1)
//                camZ -= 3;
//
//            flagZoom = 0;
//            break;
//        case 14:
//         //   flagMoveR = 1;
//          //  flagLegRGo = 1;
//            break;
//
//    }
//    glutPostRedisplay();
//}
//
//void Timer(int extra) {
//     glutPostRedisplay();
//     glutTimerFunc(20,Timer,10);
//}
//
//
//
//int  main ( int argc, char** argv ){
//    glutInit  (&argc, argv );
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  | GLUT_RGBA);
//	glutInitWindowSize(800,800);
//	glutCreateWindow("Cat Lady");
//    CarregaTextura("D:\\ACM\\new_glut\\head.bmp", 0);
//	CarregaTextura("D:\\ACM\\new_glut\\calcada2.bmp", 1);
//    CarregaTextura("D:\\ACM\\new_glut\\lightpole.bmp", 2);
//    CarregaTextura("D:\\ACM\\new_glut\\roof2.bmp", 3);
//    CarregaTextura("D:\\ACM\\new_glut\\roof1.bmp", 4);
//    CarregaTextura("D:\\ACM\\new_glut\\building1.bmp", 5);
//    CarregaTextura("D:\\ACM\\new_glut\\cat1.bmp", 6);
//    CarregaTextura("D:\\ACM\\new_glut\\cat2.bmp", 7);
//    CarregaTextura("D:\\ACM\\new_glut\\cat4.bmp", 8);
//    CarregaTextura("D:\\ACM\\new_glut\\wall1.bmp", 9);
//    CarregaTextura("D:\\ACM\\new_glut\\wall2.bmp", 10);
//    CarregaTextura("D:\\ACM\\new_glut\\wall3.bmp", 11);
//    CarregaTextura("D:\\ACM\\new_glut\\wall4.bmp", 12);
//	CarregaTextura("D:\\ACM\\new_glut\\wall5.bmp", 13);
//	CarregaTextura("D:\\ACM\\new_glut\\shoes.bmp", 14);
//	CarregaTextura("D:\\ACM\\new_glut\\shirt.bmp", 15);
//	CarregaTextura("D:\\ACM\\new_glut\\skin.bmp", 16);
//	CarregaTextura("D:\\ACM\\new_glut\\palha.bmp", 17);
//	CarregaTextura("D:\\ACM\\new_glut\\jeans.bmp", 18);
//	CarregaTextura("D:\\ACM\\new_glut\\sky.bmp", 19);
//	CarregaTextura("D:\\ACM\\new_glut\\night.bmp", 20);
//	CarregaTextura("D:\\ACM\\new_glut\\grama.bmp", 21);
//	CarregaTextura("D:\\ACM\\new_glut\\door1.bmp", 22);
//	CarregaTextura("D:\\ACM\\new_glut\\door2.bmp", 23);
//	CarregaTextura("D:\\ACM\\new_glut\\bag.bmp", 24);
//    inicializaLista(&listaPontos);
//
//
//	init();
//	glutDisplayFunc(playGame);
//    glutReshapeFunc(ChangeSize);
//    glutMouseFunc(MouseInt);
//    glutKeyboardFunc(keyboard);
//    glutCreateMenu(menuFunc);
//        glutAddMenuEntry("finish", 1);
//        glutAddMenuEntry("Rotate Right Arm", 4);
//        glutAddMenuEntry("Rotate left Arm", 5);
//        glutAddMenuEntry("Rotate Left Elbow", 6);
//        glutAddMenuEntry("Rotating Right Elbow", 7);
//        glutAddMenuEntry("Rotate Left Leg", 8);
//        glutAddMenuEntry("Rotate right Leg", 9);
//        glutAddMenuEntry("Rotate Left Knee", 10);
//        glutAddMenuEntry("Rotate right Knee", 11);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//    glutTimerFunc(0,Timer,10);
//	glutMainLoop();
//	if(flagFinaliza == -1)
//        return(0);
//}
