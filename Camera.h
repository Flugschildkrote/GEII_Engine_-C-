#if !defined(CAMERA_H)
#define CAMERA_H

#include <stdio.h>

#include "math\vector.h"
#include "math\matrix4x4.h"
#include "math\CoordinateSystem.h"

enum
{
    CAMERA_PERSPECTIVE,
    CAMERA_ORTHOGRAPHIC,
    CAMERA_UNKNOW
};

typedef struct{
    vec3f m_PEye;               //La position de la camera
    vec3f m_PCenter;            //La position regarder
    vec3f m_Up;                 //L'orientation de la camera
    float m_FieldOfViewAngle;   //L'angle d'ouverture de la camera
    float m_Ratio;              //Le ratio de l'angle d'ouverture
    float m_Znear;              //La distance minimale visible.
    float m_Zfar;               //La distance maximale visible.
    unsigned int m_Xres;        //La resolution suivant X.
    unsigned int m_Yres;        //La resolution suivant Y.
    unsigned int m_Type;        //Ortho ou perspective
}TCamera;

void CameraInitialize(TCamera *pcamera,
                      unsigned int type, unsigned int xres, unsigned int yres,
                      vec3f eye, vec3f center, vec3f up,
                      float fov, float ratio, float znear, float zfar);

void CameraGetProjectionMatrix(TCamera *pcamera, TMatrix4x4f m);
void CameraGetModelViewMatrix(TCamera *pcamera, TMatrix4x4f m);

void CameraLookAt(TCamera *pcamera, vec3f eye, vec3f center, vec3f up);

void CameraForward(TCamera *pcamera, float go);
void CameraForwardEye(TCamera *pcamera, float go, float limit);

void CameraBackward(TCamera *pcamera, float go);
void CameraBackwardEye(TCamera *pcamera, float go, float limit);

void CameraRotateTheta(TCamera *pcamera, float rot, float lmin, float lmax);
void CameraRotatePhi(TCamera *pcamera, float rot, float lmin, float lmax);

void CameraSetResolution(TCamera *pcamera, int resx, int resy);

#endif // !defined(CAMERA_H)
