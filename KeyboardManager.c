#include "KeyboardManager.h"

TKeyboardManager *g_pkeyboard=NULL;

void KeyboardManagerInitialize(TKeyboardManager *pkeyboard)
{
    if(pkeyboard==NULL)
    {
        printf("#Error KeyboardManagerInitialize: pkeyboard=NULL.\n");
        return;
    }
    g_pkeyboard=pkeyboard;
    pkeyboard->m_mouse_x=0;
    pkeyboard->m_mouse_y=0;
    pkeyboard->m_modifiers=KEYBOARD_MANAGER_MODIFIER_NONE;
    pkeyboard->m_key=-1;
    pkeyboard->m_special_key=-1;
    pkeyboard->m_pf_key=NULL;
    pkeyboard->m_pdata_key=NULL;
    pkeyboard->m_pf_special_key=NULL;
    pkeyboard->m_pdata_special_key=NULL;

    glutKeyboardFunc(KeyboardManagerKeyboardCallback);
    glutSpecialFunc(KeyboardManagerSpecialCallback);
}

void KeyboardManagerSetKeyFunction(void (*pf_key)(void*), void *pdata_key)
{
    g_pkeyboard->m_pf_key=pf_key;
    g_pkeyboard->m_pdata_key=pdata_key;
}

void KeyboardManagerSetSpecialKeyFunction(void (*pf_special_key)(void*), void *pdata_special_key)
{
    g_pkeyboard->m_pf_special_key=pf_special_key;
    g_pkeyboard->m_pdata_special_key=pdata_special_key;
}

///CALLBACK FUNCTIONS
void KeyboardManagerKeyboardCallback(unsigned char key, int x, int y)
{
    g_pkeyboard->m_modifiers=glutGetModifiers();
    g_pkeyboard->m_mouse_x=x;
    g_pkeyboard->m_mouse_y=y;
    g_pkeyboard->m_key=key;
    if(g_pkeyboard->m_pf_key)
        g_pkeyboard->m_pf_key(g_pkeyboard->m_pdata_key);
    glutPostRedisplay();
}

void KeyboardManagerSpecialCallback(int key, int x, int y)
{
    g_pkeyboard->m_modifiers=glutGetModifiers();
    g_pkeyboard->m_mouse_x=x;
    g_pkeyboard->m_mouse_y=y;
    g_pkeyboard->m_special_key=key;
    if(g_pkeyboard->m_pf_special_key)
        g_pkeyboard->m_pf_special_key(g_pkeyboard->m_pdata_special_key);
    glutPostRedisplay();
}

