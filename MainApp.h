#if !defined(MAINAPP_H)
#define MAINAPP_H

//Les librairies pour openGL + glut
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "OGL\OGLInfo.h"

#include "MouseManager.h"
#include "KeyboardManager.h"

#include "Camera.h"
#include "Scene.h"
#include "Render.h"
#include "RenderPicking.h"

#include "OGLDrawImmediate.h"
#include "shape/CubeShape.h"
#include "shape/SphereShape.h"
#include "shape/ConeShape.h"
#include "shape/CylinderShape.h"
#include "shape/TorusShape.h"
#include "GeometricPrimitive.h"

#include "ObjParser.h"

///La structure pour la fenetre principale
typedef struct{
    int m_window;
    unsigned int m_windowsize_x;
    unsigned int m_windowsize_y;
    TMouseManager m_mouse;
    TKeyboardManager m_keyboard;
    TCamera m_camera3D;
    TScene m_Scene;
    TRender m_Render;
    TRenderPicking m_RenderPicking;
    /// NEW
    TGeometricPrimitive *mPickingGeomPrimitive;
    uint8_t m_pickingPixels[4];
}TMainApp;

//Declaration de la structure du programme principal
extern TMainApp g_mainapp;

/// UPDATED
int MainAppInitialize();

void MainAppDelete();

void MainAppDisplayCallback();

void MainAppMouseButtonCallback(void* pdata);
void MainAppMouseMotionCallback(void* pdata);
void MainAppKeyboardKeyCallback(void* pdata);
void MainAppKeyboardSpecialKeyCallback(void* pdata);

#endif //MAINAPP_H
