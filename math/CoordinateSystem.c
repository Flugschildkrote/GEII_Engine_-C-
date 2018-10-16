#include "CoordinateSystem.h"

void CartesianToSpherical(float X, float Y, float Z, float *r, float *phi, float *theta)
{
    (*r)=sqrt(X*X+Y*Y+Z*Z);
    (*theta)=acos(Z/(*r));
    (*phi)=atan2(Y,X);
}

void SphericalToCartesian(float r, float phi, float theta, float *X, float *Y, float *Z)
{
    double st=r*sin(theta);
    (*X)=st*cos(phi);
    (*Y)=st*sin(phi);
    (*Z)=r*cos(theta);
}

void SphericalToCylindrical(float r, float phi, float theta, float *rho, float *Z)
{
    (*rho)=r*sin(theta);
    //Phi=phi
    (*Z)=r*cos(theta);
}

void CylindricalToSpherical(float rho, float phi, float Z, float *r, float *theta)
{
    (*r)=sqrt(rho*rho+Z*Z);
    (*theta)=acos(Z/(*r));
    //phi=phi
}

void CartesianToCylindrical(float X, float Y, float Z, float *rho, float *phi)
{
    double r=sqrt(X*X+Y*Y+Z*Z);
    double theta=acos(Z/r);
    (*rho)=r*sin(theta);
    (*phi)=atan2(Y,X);
    //Z=Z
}

void CylindricalToCartesian(float rho, float phi, float Z, float *X, float *Y)
{
    double r=sqrt(rho*rho+Z*Z);
    double theta=acos(Z/r);
    double st=r*sin(theta);
    (*X)=st*cos(phi);
    (*Y)=st*sin(phi);
    //Z=Z
}
