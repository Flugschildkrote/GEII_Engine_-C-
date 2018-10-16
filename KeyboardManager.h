#if !defined(KEYBOARDMANAGER_H)
#define KEYBOARDMANAGER_H

//Les librairies pour openGL + glut
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include <stdio.h>

//Les types de modifieurs pour le clavier
enum
{
    KEYBOARD_MANAGER_MODIFIER_NONE         = 0,
    KEYBOARD_MANAGER_MODIFIER_SHIFT        = GLUT_ACTIVE_SHIFT,
    KEYBOARD_MANAGER_MODIFIER_CTRL         = GLUT_ACTIVE_CTRL,
    KEYBOARD_MANAGER_MODIFIER_ALT          = GLUT_ACTIVE_ALT
};

///La structure pour la gestion du clavier
typedef struct{
    int m_mouse_x;
    int m_mouse_y;
    int m_modifiers;
    int m_key;
    int m_special_key;
    void (*m_pf_key)(void*);
    void *m_pdata_key;
    void (*m_pf_special_key)(void*);
    void *m_pdata_special_key;
}TKeyboardManager;

void KeyboardManagerInitialize(TKeyboardManager *pkeyboard);

void KeyboardManagerSetKeyFunction(void (*pf_key)(void*), void *pdata_key);
void KeyboardManagerSetSpecialKeyFunction(void (*pf_special_key)(void*), void *pdata_special_key);

///CALLBACK FUNCTIONS
void KeyboardManagerKeyboardCallback(unsigned char key, int x, int y);
void KeyboardManagerSpecialCallback(int key, int x, int y);

#endif //KEYBOARDMANAGER_H
