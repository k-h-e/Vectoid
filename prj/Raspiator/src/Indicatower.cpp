#include "Indicatower.h"

#include <cassert>
#include <Vectoid/Transform.h>

using namespace kxm::Vectoid;


namespace Raspiator {

Indicatower::Indicatower(int numSectors, float stretch)
        : numSectors_(numSectors),
          stretch_(stretch),
          top_(0.0f),
          mid_(0.0f) {
    assert(numSectors_ >= 3);
    assert(stretch_ > 0.0f);
    color_[0] = .8f;    color_[1] = .8f;    color_[2] = .2f;    color_[3] = 1.0f;

    hullVertices_.resize(numSectors_ * 18);
    hullNormals_.resize(numSectors_ * 18);
    coverVertices_.resize(numSectors_ * 9);
    coverNormals_.resize(numSectors_ * 9);

    ComputeCover(0.0f);
}

void Indicatower::SetCounts(int num, int numTotal) {
    if (numTotal < 0)
        numTotal = 0;
    if (num < 0)
        num = 0;
    if (num > numTotal)
        num = numTotal;
    top_ = stretch_ * (float)numTotal;
    mid_ = stretch_ * (float)num;
    ComputeCover(top_);
}

void Indicatower::Render(RenderContext *context) {
    glEnable(GL_LIGHTING);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &hullVertices_[0]);
    glNormalPointer(GL_FLOAT, 0, &hullNormals_[0]);
    ComputeHull(mid_, 0.0f);
    color_[0] = .2f;    color_[1] = .8f;    color_[2] = .2f;    color_[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_);
    glDrawArrays(GL_TRIANGLES, 0, numSectors_ * 6);

    ComputeHull(top_, mid_);
    color_[0] = .8f;    color_[1] = .2f;    color_[2] = .2f;    color_[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_);
    glDrawArrays(GL_TRIANGLES, 0, numSectors_ * 6);

    glVertexPointer(3, GL_FLOAT, 0, &coverVertices_[0]);
    glNormalPointer(GL_FLOAT, 0, &coverNormals_[0]);
    glDrawArrays(GL_TRIANGLES, 0, numSectors_ * 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisable(GL_LIGHTING);
}

void Indicatower::ComputeHull(float top, float bottom) {
    GLfloat *ptr  = &hullVertices_[0],
            *nptr = &hullNormals_[0];
    Vector lastArm;
    for (int i = 0; i <= numSectors_; ++i) {
        Vector arm(1.0f, 0.0f, 0.0f);
        Transform(YAxis, (float)i / (float)numSectors_ * 360.0f).ApplyTo(&arm);
        if (!i) {
            lastArm = arm;
            continue;
        }

        *ptr++  = lastArm.x;  *ptr++  = bottom;  *ptr++  = lastArm.z;
        *nptr++ = lastArm.x;  *nptr++ = 0.0f;    *nptr++ = lastArm.z;
        *ptr++  = arm.x;      *ptr++  = bottom;  *ptr++  = arm.z;
        *nptr++ = arm.x;      *nptr++ = 0.0f;    *nptr++ = arm.z;
        *ptr++  = arm.x;      *ptr++  = top;     *ptr++  = arm.z;
        *nptr++ = arm.x;      *nptr++ = 0.0f;    *nptr++ = arm.z;

        *ptr++  = lastArm.x;  *ptr++  = bottom;  *ptr++  = lastArm.z;
        *nptr++ = lastArm.x;  *nptr++ = 0.0f;    *nptr++ = lastArm.z;
        *ptr++  = arm.x;      *ptr++  = top;     *ptr++  = arm.z;
        *nptr++ = arm.x;      *nptr++ = 0.0f;    *nptr++ = arm.z;
        *ptr++  = lastArm.x;  *ptr++  = top;     *ptr++  = lastArm.z;
        *nptr++ = lastArm.x;  *nptr++ = 0.0f;    *nptr++ = lastArm.z;

        lastArm = arm;
    }
}

void Indicatower::ComputeCover(float top) {
    GLfloat *ptr  = &coverVertices_[0],
            *nptr = &coverNormals_[0];
    Vector lastArm;
    for (int i = 0; i <= numSectors_; ++i) {
        Vector arm(1.0f, 0.0f, 0.0f);
        Transform(YAxis, (float)i / (float)numSectors_ * 360.0f).ApplyTo(&arm);
        if (!i) {
            lastArm = arm;
            continue;
        }

        *ptr++  = 0.0f;       *ptr++  = top;     *ptr++  = 0.0f;
        *nptr++ = 0.0;        *nptr++ = 1.0f;    *nptr++ = 0.0f;
        *ptr++  = lastArm.x;  *ptr++  = top;     *ptr++  = lastArm.z;
        *nptr++ = 0.0;        *nptr++ = 1.0f;    *nptr++ = 0.0f;
        *ptr++  = arm.x;      *ptr++  = top;     *ptr++  = arm.z;
        *nptr++ = 0.0;        *nptr++ = 1.0f;    *nptr++ = 0.0f;

        lastArm = arm;
    }
}

}    // Namespace Raspiator.

