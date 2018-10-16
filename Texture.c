#include "Texture.h"


inline void TextureCopy(TTexture *pdest, TTexture *psrc)
{
    *pdest = *psrc;
}

void TextureDelete(TTexture *ptex)
{
    glDeleteTextures(1,ptex);
}

int TextureCreateWhite(TTexture *ptex)
{
    //Creation d'une texture
    glGenTextures(1, ptex);
    //Edition de la texture
    GLubyte texData[] = {255, 255, 255};
    glBindTexture(GL_TEXTURE_2D, *ptex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    //Verification de la texture
    if(glIsTexture(*ptex)==GL_FALSE)
    {
        printf("#Error glIsTexture: can not create a texture.\n");
        return 0;
    }
    return 1;
}

int TextureCreateFromFile(TTexture *ptex, char *sfile, unsigned int size)
{
    //Charge l'image
    char *pimage=NULL;
    int sizeR, sizeC;
    if(!LoadBmp(sfile,&pimage,&sizeR,&sizeC))
    {
        printf("#Error TextureCreateFromFile: can not load image\n");
        return 0;
    }
    //Creation d'une texture
    glGenTextures(1, ptex);
    //Fait une texture de taille nxn avec l'image
    char *ptexout=malloc(size*size*3*sizeof(char));
    if(!ptexout)
    {
        printf("#Error TextureCreateFromFile: can not allocate ptexout\n");
        free(pimage);
        return 0;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    if(gluScaleImage(GL_RGB,
                     sizeC,sizeR,GL_UNSIGNED_BYTE,pimage,
                     size,size,GL_UNSIGNED_BYTE,ptexout))
    {
        printf("#Error TextureCreateFromFile: can not create image for texture.\n");
        free(pimage);
        return 0;
    }
    free(pimage);
    //Edition de la texture
    glBindTexture(GL_TEXTURE_2D,*ptex);
    if(glIsTexture(*ptex)==GL_FALSE)
    {
        printf("#Error TextureCreateFromFile: can not create a texture.\n");
        free(ptexout);
        return 0;
    }
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    //Creation de la mipmap
    gluBuild2DMipmaps(GL_TEXTURE_2D,3,size,size,GL_RGB,GL_UNSIGNED_BYTE,ptexout);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    free(ptexout);
    return 1;
}
