#if !defined(COORDINATESYSTEM_H)
#define COORDINATESYSTEM_H

#include <math.h>

///**Coordonnees spheriques
//r     :   La distance à l'origine du repere
//phi   :   L'angle azimuth
//theta :   L'angle zenith

///**Coordonnees cylindriques
//rho   :   Le rayon du cylindre
//phi   :   L'angle azimuth
//z     :   La hauteur par rapport au repere

void CartesianToSpherical(float X, float Y, float Z, float *r, float *phi, float *theta);

void SphericalToCartesian(float r, float phi, float theta, float *X, float *Y, float *Z);

void SphericalToCylindrical(float r, float phi, float theta, float *rho, float *Z);

void CylindricalToSpherical(float rho, float phi, float Z, float *r, float *theta);

void CartesianToCylindrical(float X, float Y, float Z, float *rho, float *phi);

void CylindricalToCartesian(float rho, float phi, float Z, float *X, float *Y);

#endif //COORDINATESYSTEM_H
