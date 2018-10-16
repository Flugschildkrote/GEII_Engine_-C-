#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>

#include "ImageIO.h"

typedef GLuint TTexture;

void TextureCopy(TTexture *pdest, TTexture *psrc);

void TextureDelete(TTexture *ptex);

int TextureCreateWhite(TTexture *ptex);
int TextureCreateFromFile(TTexture *ptex, char *sfile, unsigned int size);

#endif // !defined(TEXTURE_H)
