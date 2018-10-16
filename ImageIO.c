#include "ImageIO.h"

//Fonction pour lire un Unsigned char.
unsigned char ReadUnsignedChar(FILE* stream)
{
    return getc(stream);
}

//Fonction pour lire un int.
int ReadInt(FILE* stream)
{
   unsigned int b0,b1,b2,b3;
   b0 = getc(stream);
   b1 = getc(stream);
   b2 = getc(stream);
   b3 = getc(stream);
   int val = (b0&0xFF);
   val += ((b1&0xFF)<<8);
   val += ((b2&0xFF)<<16);
   val += ((b3&0xFF)<<24);
   return val;
}

//Fonction pour lire un short
short ReadShort(FILE* stream)
{
    unsigned b0,b1;
    b0 = getc(stream);
    b1 = getc(stream);
    short val = (b0 & 0xFF);
    val += ((b1&0xFF)<<8);
    return val;
}

int LoadBmp(String filename, char** image, int *sizeR, int *sizeC)
{
    //Ouvre le fichier
    FILE* stream;
    if(!(stream = fopen(filename,"rb")))
       return 0;

    //L'entete
    unsigned char ee;
    ee = ReadUnsignedChar(stream);
    if(ee != 'B')
       return 0;
    ee = ReadUnsignedChar(stream);
    if(ee != 'M')
       return 0;

    //Taille d'une ligne
    int sizeLine = ReadInt(stream);
    if(sizeLine<=0)
      return 0;
    //Reserved
    /*short reserved = */ReadShort(stream);
    /*reserved = */ReadShort(stream);
    //bfOffBits
    int bl = ReadInt(stream);
    if(bl<=0)
       return 0;

    //40
    int n40 = ReadInt(stream);
    if(n40!=40)
       return 0;

    //ligne colonne
    int ncolonne = ReadInt(stream);
    int nligne = ReadInt(stream);

    //les autres info
    /*short val_short = */ReadShort(stream);
    /*val_short = */ReadShort(stream);
    /*int val_int = */ReadInt(stream); /*val_int = */ReadInt(stream);
    /*val_int = */ReadInt(stream); /*val_int = */ReadInt(stream);
    /*val_int = */ReadInt(stream); /*val_int = */ReadInt(stream);
    //unsigned char val_unsigned_char;
    //Ecrit les données
    int bf = (4-((ncolonne*3)%4)) & 0x03; //panding 32 bits
    if(image!=NULL)
        free(image);
    (*image) = malloc(3*nligne*ncolonne*sizeof(unsigned char));
    int  l,c,p;
    //for(l=nligne-1; l>=0; l--)
    for(l=0; l<nligne; l++)
    {
        for(c=0; c<ncolonne; c++)
        {
           (*image)[(l*ncolonne+c)*3+2] = ReadUnsignedChar(stream);
           (*image)[(l*ncolonne+c)*3+1] = ReadUnsignedChar(stream);
           (*image)[(l*ncolonne+c)*3] = ReadUnsignedChar(stream);
        }
        for(p=0; p<bf; p++)
           /*val_unsigned_char = */ReadUnsignedChar(stream);
    }
    *sizeR = nligne;
    *sizeC = ncolonne;
    //ferme le fichier
    fclose(stream);
    return 1;
}
