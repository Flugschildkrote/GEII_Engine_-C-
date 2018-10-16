#if !defined(MOUSEMANAGER_H)
#define MOUSEMANAGER_H

//Les librairies pour openGL + glut
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include <stdio.h>

//Les types d'actions possible pour la souris
enum
{
    MOUSE_MANAGER_ACTION_NONE           = -1,
    MOUSE_MANAGER_ACTION_LEFT           = GLUT_LEFT_BUTTON,
    MOUSE_MANAGER_ACTION_RIGHT          = GLUT_RIGHT_BUTTON,
    MOUSE_MANAGER_ACTION_MIDDLE         = GLUT_MIDDLE_BUTTON
};

//Les types de modifieurs pour la souris
enum
{
    MOUSE_MANAGER_MODIFIER_NONE         = -1,
    MOUSE_MANAGER_MODIFIER_SHIFT        = GLUT_ACTIVE_SHIFT,
    MOUSE_MANAGER_MODIFIER_CTRL         = GLUT_ACTIVE_CTRL,
    MOUSE_MANAGER_MODIFIER_ALT          = GLUT_ACTIVE_ALT
};

///La structure pour la gestion de la souris
typedef struct{
    int m_start_x;
    int m_start_y;
    int m_move_x;
    int m_move_y;
    int m_modifiers;
    int m_action;
    void (*m_pf_button)(void*);
    void *m_pdata_button;
    void (*m_pf_motion)(void*);
    void *m_pdata_motion;
}TMouseManager;

void MouseManagerInitialize(TMouseManager *pmouse);

void MouseManagerSetMotionFunction(void (*pf_motion)(void*), void *pdata_motion);
void MouseManaferSetButtonFunction(void (*pf_button)(void*), void *pdata_button);

///CALLBACK FUNCTIONS
void MouseManagerButtonCallback(int button, int state, int x, int y);
void MouseManagerMotionCallback(int x, int y);

#endif //MOUSEMANAGER_H
