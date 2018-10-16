#include "OGLDrawImmediate.h"

void OGLDrawImmediateOrthonormal(vec3f position, float size,
                                 vec4f xcolor, vec4f ycolor, vec4f zcolor,
                                 float linewidth)
{
    GLfloat linewidthold;
    glGetFloatv(GL_LINE_WIDTH,&linewidthold);
    glLineWidth(linewidthold*linewidth);
    glColor4fv(xcolor);
    glBegin(GL_LINES);
    glVertex3fv(position);
    position[0]+=size;
    glVertex3fv(position);
    position[0]-=size;
    glEnd();
    glColor4fv(ycolor);
    glBegin(GL_LINES);
    glVertex3fv(position);
    position[1]+=size;
    glVertex3fv(position);
    position[1]-=size;
    glEnd();
    glColor4fv(zcolor);
    glBegin(GL_LINES);
    glVertex3fv(position);
    position[2]+=size;
    glVertex3fv(position);
    position[2]-=size;
    glEnd();
    glLineWidth(linewidthold);
}

void OGLDrawImmediateLine(vec3f pstart, vec3f pend, vec4f color)
{
    glColor4fv(color);
    glBegin(GL_LINES);
    glVertex3fv(pstart);
    glVertex3fv(pend);
    glEnd();
}

void OGLDrawImmediatePoint(vec3f p, vec4f color)
{
    glColor4fv(color);
    glBegin(GL_POINTS);
    glVertex3fv(p);
    glEnd();
}
