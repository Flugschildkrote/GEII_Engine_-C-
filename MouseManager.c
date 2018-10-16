#include "MouseManager.h"

TMouseManager *g_pmouse=NULL;

void MouseManagerInitialize(TMouseManager *pmouse)
{
    if(pmouse==NULL)
    {
        printf("#Error MouseManagerInitialize: pmouse=NULL.\n");
        return;
    }
    g_pmouse=pmouse;
    pmouse->m_start_x=0;
    pmouse->m_start_y=0;
    pmouse->m_move_x=0;
    pmouse->m_move_y=0;
    pmouse->m_modifiers=MOUSE_MANAGER_MODIFIER_NONE;
    pmouse->m_action=MOUSE_MANAGER_ACTION_NONE;
    pmouse->m_pf_motion=NULL;

    glutMouseFunc(MouseManagerButtonCallback);
    glutMotionFunc(MouseManagerMotionCallback);
}

void MouseManagerSetMotionFunction(void (*pf_motion)(void*), void *pdata_motion)
{
    g_pmouse->m_pf_motion=pf_motion;
    g_pmouse->m_pdata_motion=pdata_motion;
}

void MouseManaferSetButtonFunction(void (*pf_button)(void*), void *pdata_button)
{
    g_pmouse->m_pf_button=pf_button;
    g_pmouse->m_pdata_button=pdata_button;
}

///CALLBACK FUNCTIONS
void MouseManagerButtonCallback(int button, int state, int x, int y)
{
    g_pmouse->m_modifiers=glutGetModifiers();
    if(state==GLUT_DOWN)
    {
        g_pmouse->m_action=button;
    }
    else
    {
        g_pmouse->m_action=MOUSE_MANAGER_ACTION_NONE;
    }
    g_pmouse->m_start_x=x;
    g_pmouse->m_start_y=y;
    if(g_pmouse->m_pf_button)
        g_pmouse->m_pf_button(g_pmouse->m_pdata_button);
    glutPostRedisplay();
}

void MouseManagerMotionCallback(int x, int y)
{
    g_pmouse->m_move_x=x;
    g_pmouse->m_move_y=y;
    if(g_pmouse->m_pf_motion)
        g_pmouse->m_pf_motion(g_pmouse->m_pdata_motion);
    glutPostRedisplay();
}
