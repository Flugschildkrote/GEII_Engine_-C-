#include <stdio.h>
#include <stdlib.h>

//Les librairies pour openGL + glut
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>

#include "MainApp.h"

// ========================================================
// Gestion fenetrage windows
// ========================================================
#if defined (WIN32)
#include <windows.h>
static WNDPROC currentWndProc;
static HWND handle  = NULL;

//Fonction pour detruire les allocations
void DestroyEnd()
{
    MainAppDelete();
}

static LRESULT CALLBACK winProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_CLOSE:
            DestroyEnd();
            exit(0);
            break;
        case WM_DESTROY:
            DestroyEnd();
            exit(0);
            break;
        default:
            return CallWindowProc(currentWndProc, handle, Msg, wParam, lParam);
            break;
    }
    return 0;
}

static void fixCloseWindowOnWin32()
{
    handle = WindowFromDC(wglGetCurrentDC());
    DragAcceptFiles (handle, TRUE);
    currentWndProc = (WNDPROC)GetWindowLongPtr(handle, GWL_WNDPROC);
    SetWindowLongPtr(handle, GWL_WNDPROC, (long)winProc);
}
#endif //WIN32
// ========================================================
// Gestion fenetrage windows
// ========================================================

int main(int argc, char *argv[])
{
//Initialisation de glut
    glutInit(&argc,argv);
//Initialisation du programme principal
    if(!MainAppInitialize())
        return 0;

//Gestion de la fenetre sous windows
    #if defined (WIN32)
    fixCloseWindowOnWin32();
    #endif //WIN32

//Une boucle infinie
    glutMainLoop();
    return 0;
}
