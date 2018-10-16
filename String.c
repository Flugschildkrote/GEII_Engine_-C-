#include "String.h"


unsigned int StringFindLast(String pst, const char letter)
{
    int pt;
    unsigned pos=strlen(pst);
    for(pt=pos+1; pt>0; --pt)
    {
        if(pst[pt]==letter)
            return pt;
    }
    return (unsigned int)(-1);
}
