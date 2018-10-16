#if !defined(OBJPARSER_H)
#define OBJPARSER_H

#include <stdio.h>
#include <ctype.h>

#include "String.h"
#include "Scene.h"
#include "math/vector.h"
#include "MtlParser.h"

typedef struct{
    vec3f *m_pVertex;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TObjParserV;

typedef struct{
    vec3f *m_pNormal;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TObjParserVn;

typedef struct{
    vec3ui *m_pIdx;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TObjParserF;

typedef struct{
    vec2f *m_pUV;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TObjParserVt;

typedef struct{
    FILE *m_Stream;                 //Un pointeur sur le fichier.
    char m_FileRep[MAX_PATH];       //Le repertoire de travail.
    char m_RawLine[4096];           //Un buffer pour la gestion des lignes du fichier.
    char *m_pLine;                  //Un pointeur sur la position de la ligne traitee.
    char *m_pLineEnd;               //Un pointeur sur la fin de la ligne traitee.
    char *m_pCmd;                   //Un pointeur sur la commande actuelle.
    TObjParserV m_Vertex;           //La liste des vertex dans le fichier.
    TObjParserVn m_Normal;          //La liste des normales dans le fichier.
    TObjParserVt m_UV;              //La liste des coordonnees UV dans le fichier.
    TObjParserF m_Face;             //La liste des faces dans le fichier.
    TMtlLib m_MtlLib;               //La liste des materiaux.
    unsigned int m_IdMaterial;      //Le materiau actuellement utilise.
    int m_bComputeNormal;           //Un boolean pour indiquer si il faut calculer ou non les normales
}TObjParser;

int ObjParserOpenScene(String filename, TScene *pScene);

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int ObjParserInitialize(TObjParser *pparser);
int ObjParserOpenFile(String filename, TObjParser *pparser);
int ObjParserEnd(TObjParser *pparser);

int ObjParserFindCmd(TObjParser *pparser);
void ObjParserSkipSpace(TObjParser *pparser);
void ObjParserSkipNoSpace(TObjParser * pparser);

int ObjParserCmdv(TObjParser *pparser);
int ObjParserCmdvn(TObjParser *pparser);
int ObjParserCmdvt(TObjParser *pparser);
int ObjParserCmdf(TObjParser *pparser);
int ObjParserCmdusemtl(TObjParser *pparser);
int ObjParserCmdmtllib(TObjParser *pparser, TScene *pScene);

int ObjParserResizeVertexList(TObjParser *pparser);
int ObjParserResizeNormalList(TObjParser *pparser);
int ObjParserResizeUVList(TObjParser *pparser);
int ObjParserResizeFaceList(TObjParser *pparser);

int ObjParserCreateGeometricPrimitive(TObjParser *pparser, TScene *pScene);
int ObjParserGenerateNormal(TObjParser *pparser);
int ObjParserIsConvexPolygon(TObjParser *pparser, unsigned int size, unsigned int *idx);

void ObjParserPrint(TObjParser *pparser);

#endif //OBJPARSER_H
