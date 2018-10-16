#if !defined(DEFINITION_H)
#define DEFINITION_H

///Pi definition
#ifndef PI
#define PI			3.14159265358979323846264338327950288
#endif //PI

///radian to degree & degree to radian conversion
#define radian(deg) (deg)*PI/180.0f
#define degree(rad) (rad)*180.0f/PI

///Epsilon definitons
#ifndef EPS6
#define EPS6        1e-6
#endif

#ifndef EPS8
#define EPS8        1e-8
#endif

#ifndef EPS12
#define EPS12       1e-12
#endif

#ifndef EPS20
#define EPS20       1e-20
#endif

#ifndef EPS150
#define EPS150      1e-150
#endif

///limits of a real definitions
#ifndef MAX_REAL_NUMBER
#define MAX_REAL_NUMBER 1E300
#endif

#ifndef MIN_REAL_NUMBER
#define MIN_REAL_NUMBER 1E-300
#endif

///Some functions

//*************************************
//Max functions
float Max2f(float v1, float v2);
float Max3f(float v1, float v2, float v3);
float Max4f(float v1, float v2, float v3, float v4);

int Max2i(int v1, int v2);
int Max3i(int v1, int v2, int v3);
int Max4i(int v1, int v2, int v3, int v4);

unsigned int Max2ui(unsigned int v1, unsigned int v2);
unsigned int Max3ui(unsigned int v1, unsigned int v2, unsigned int v3);
unsigned int Max4ui(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);

//*************************************
//Min functions
float Min2f(float v1, float v2);
float Min3f(float v1, float v2, float v3);
float Min4f(float v1, float v2, float v3, float v4);

int Min2i(int v1, int v2);
int Min3i(int v1, int v2, int v3);
int Min4i(int v1, int v2, int v3, int v4);

unsigned int Min2ui(unsigned int v1, unsigned int v2);
unsigned int Min3ui(unsigned int v1, unsigned int v2, unsigned int v3);
unsigned int Min4ui(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);

//*************************************
//Clamp function
float Clampf(float v, float vmin, float vmax);

#endif // !defined(DEFINITION_H)
