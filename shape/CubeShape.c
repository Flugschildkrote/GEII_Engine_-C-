#include "CubeShape.h"

static const float CubeNormalArray[] = {
    0.0f, 0.0f, 1.0f,        //Front
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,       //Right
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, -1.0f,      //Back
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    -1.0f, 0.0f, 0.0f,      //Left
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,       //Top
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,       //Bottom
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f
};

static const float CubeUVArray[] = {
    0.0f,       0.5f,        //Front
    1.0f/3.0f,  0.5f,
    1.0f/3.0f,  1.0f,
    0.0f,       1.0f,
    1.0f/3.0f,  0.5f,       //Right
    2.0f/3.0f,  0.5f,
    2.0f/3.0f,  1.0f,
    1.0f/3.0f,  1.0f,
    2.0f/3.0f,  0.5f,      //Back
    1.0f,       0.5f,
    1.0f,       1.0f,
    2.0f/3.0f,  1.0f,
    0.0f,       0.0f,      //Left
    1.0f/3.0f,  0.0f,
    1.0f/3.0f,  0.5f,
    0.0f,       0.5f,
    1.0f/3.0f,  0.0f,       //Top
    2.0f/3.0f,  0.0f,
    2.0f/3.0f,  0.5f,
    1.0f/3.0f,  0.5f,
    2.0f/3.0f,  0.0f,       //Bottom
    1.0f,       0.0f,
    1.0f,       0.5f,
    2.0f/3.0f,  0.5f
};

static unsigned int CubeIndiceArray[] = {
	0,1,2,      2,3,0,          //Front
	7,6,5,      5,4,7,          //Right
	11,10,9,    9,8,11,         //Back
	15,14,13,   13,12,15,       //Left
	19,18,17,   17,16,19,       //Top
	23,22,21,   21,20,23        //Bottom
};

int CubeCreate(TVBOShape* pvbo, float halfsize)
{
    float CubeVerticeArray[] = {
	-halfsize, -halfsize, halfsize,       //Front
	halfsize,  -halfsize, halfsize,
	halfsize,  halfsize,  halfsize,
	-halfsize, halfsize,  halfsize,
	halfsize,  -halfsize, halfsize,       //Right
	halfsize,  -halfsize, -halfsize,
	halfsize,  halfsize,  -halfsize,
	halfsize,  halfsize,  halfsize,
	halfsize,  -halfsize, -halfsize,       //Back
	-halfsize, -halfsize, -halfsize,
	-halfsize, halfsize,  -halfsize,
	halfsize,  halfsize,  -halfsize,
	-halfsize, -halfsize, -halfsize,      //Left
	-halfsize, -halfsize, halfsize,
	-halfsize, halfsize,  halfsize,
	-halfsize, halfsize,  -halfsize,
	-halfsize, halfsize,  halfsize,       //Top
	halfsize,  halfsize,  halfsize,
	halfsize,  halfsize,  -halfsize,
	-halfsize, halfsize,  -halfsize,
	halfsize,  -halfsize, halfsize,       //Bottom
	-halfsize, -halfsize, halfsize,
	-halfsize, -halfsize, -halfsize,
	halfsize,  -halfsize, -halfsize
    };

    if(!VBOShapeCreate(pvbo, CubeVerticeArray,CubeNormalArray,CubeUVArray,24,CubeIndiceArray,36))
    {
        printf("#Error CubeCreate: VBOShapeCreate's function return 0.\n");
        return 0;
    }
    return 1;
}
