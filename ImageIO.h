#if !defined(IMAGEIO_H)
#define IMAGEIO_H

#include <stdio.h>
#include <stdlib.h>

#include "string.h"

int LoadBmp(String filename, char** image, int *sizeR, int *sizeC);


#endif //IMAGEIO_H
