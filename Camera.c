#include "Camera.h"

void CameraInitialize(TCamera *pcamera,
                      unsigned int type, unsigned int xres, unsigned int yres,
                      vec3f eye, vec3f center, vec3f up,
                      float fov, float ratio, float znear, float zfar)
{
    if(pcamera==NULL)
    {
        printf("#Error CameraInitialize: pcamera=NULL.\n");
        return;
    }
    Vec3fCopy(pcamera->m_PEye,eye);
    Vec3fCopy(pcamera->m_PCenter,center);
    Vec3fCopy(pcamera->m_Up,up);
    pcamera->m_FieldOfViewAngle=fov;
    pcamera->m_Ratio=ratio;
    pcamera->m_Znear=znear;
    pcamera->m_Zfar=zfar;
    pcamera->m_Xres=xres;
    pcamera->m_Yres=yres;
    pcamera->m_Type=type;
}

inline void CameraGetProjectionMatrix(TCamera *pcamera, TMatrix4x4f m)
{
    if(pcamera->m_Type==CAMERA_PERSPECTIVE)
    {
        Matrix4x4fPerspective(m,pcamera->m_FieldOfViewAngle,pcamera->m_Ratio,pcamera->m_Znear,pcamera->m_Zfar);
    }
    else
    {
        float tfov=tan(radian(pcamera->m_FieldOfViewAngle/2.0f));
        float hnear=tfov*pcamera->m_Znear;
        float wnear=hnear*pcamera->m_Ratio;
        Matrix4x4fOrthographic(m,-wnear,wnear,-hnear,hnear,pcamera->m_Znear,pcamera->m_Zfar);
    }
}

inline void CameraGetModelViewMatrix(TCamera *pcamera, TMatrix4x4f m)
{
    Matrix4x4fLookAt(m,pcamera->m_PEye,pcamera->m_PCenter,pcamera->m_Up);
}

inline void CameraLookAt(TCamera *pcamera, vec3f eye, vec3f center, vec3f up)
{
    Vec3fCopy(pcamera->m_PEye,eye);
    Vec3fCopy(pcamera->m_PCenter,center);
    Vec3fCopy(pcamera->m_Up,up);
}

void CameraForward(TCamera *pcamera, float go)
{
    vec3f dir;
    if(Vec3fIsEqual(pcamera->m_PEye,pcamera->m_PCenter))
    {
        dir[0]=0.0f;
        dir[1]=0.0f;
        dir[2]=1.0f;
    }
    else
    {
        Vec3fSub2(dir,pcamera->m_PCenter,pcamera->m_PEye);
        Vec3fNormalize(dir);
    }
    Vec3fMulC(dir,go);
    Vec3fAdd(pcamera->m_PEye,dir);
    Vec3fAdd(pcamera->m_PCenter,dir);
}

void CameraForwardEye(TCamera *pcamera, float go, float limit)
{
    vec3f dir;
    float lp;
    if(Vec3fIsEqual(pcamera->m_PEye,pcamera->m_PCenter))
        return;
    else
    {
        Vec3fSub2(dir,pcamera->m_PCenter,pcamera->m_PEye);
        lp=Vec3fLength(dir);
        dir[0]/=lp;
        dir[1]/=lp;
        dir[2]/=lp;
    }
    if((lp-go)<limit)
        go=lp-limit;
    Vec3fMulC(dir,go);
    Vec3fAdd(pcamera->m_PEye,dir);
}

void CameraBackward(TCamera *pcamera, float go)
{
    vec3f dir;
    if(Vec3fIsEqual(pcamera->m_PEye,pcamera->m_PCenter))
    {
        dir[0]=0.0f;
        dir[1]=0.0f;
        dir[2]=1.0f;
    }
    else
    {
        Vec3fSub2(dir,pcamera->m_PCenter,pcamera->m_PEye);
        Vec3fNormalize(dir);
    }
    Vec3fMulC(dir,go);
    Vec3fSub(pcamera->m_PEye,dir);
    Vec3fSub(pcamera->m_PCenter,dir);
}

void CameraBackwardEye(TCamera *pcamera, float go, float limit)
{
    vec3f dir;
    float lp;
    if(Vec3fIsEqual(pcamera->m_PEye,pcamera->m_PCenter))
        return;
    else
    {
        Vec3fSub2(dir,pcamera->m_PCenter,pcamera->m_PEye);
        lp=Vec3fLength(dir);
        dir[0]/=lp;
        dir[1]/=lp;
        dir[2]/=lp;
    }
    if((lp+go)<limit)
        go=limit-lp;
    Vec3fMulC(dir,go);
    Vec3fSub(pcamera->m_PEye,dir);
}

void CameraRotateTheta(TCamera *pcamera, float rot, float lmin, float lmax)
{
    vec3f pos;
    float r,phi,theta;
    Vec3fSub2(pos,pcamera->m_PEye,pcamera->m_PCenter);
    CartesianToSpherical(pos[0],pos[2],pos[1],&r,&phi,&theta);
    theta=degree(theta)+rot;
    theta=Clampf(theta,lmin,lmax);
    SphericalToCartesian(r,phi,radian(theta),&pos[0],&pos[2],&pos[1]);
    Vec3fAdd2(pcamera->m_PEye,pcamera->m_PCenter,pos);
}

void CameraRotatePhi(TCamera *pcamera, float rot, float lmin, float lmax)
{
    vec3f pos;
    float r,phi,theta;
    Vec3fSub2(pos,pcamera->m_PEye,pcamera->m_PCenter);
    CartesianToSpherical(pos[0],pos[2],pos[1],&r,&phi,&theta);
    phi=degree(phi)+rot;
    phi=Clampf(phi,lmin,lmax);
    SphericalToCartesian(r,radian(phi),theta,&pos[0],&pos[2],&pos[1]);
    Vec3fAdd2(pcamera->m_PEye,pcamera->m_PCenter,pos);
}

inline void CameraSetResolution(TCamera *pcamera, int resx, int resy)
{
    pcamera->m_Xres=resx;
    pcamera->m_Yres=resy;
    pcamera->m_Ratio=(float)resx/(float)resy;
}
