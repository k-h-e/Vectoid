#include "Indicatower.h"

#include <cassert>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/Transform.h>

using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

const Vector Indicatower::greenColor(0.0f, 0.75f, 0.0f),
             Indicatower::redColor(0.75f, 0.0f, 0.0f),
             Indicatower::yellowColor(0.75f, 0.75f, 0.0f);

Indicatower::Indicatower(float radius, int numSectors, float stretch)
        : numSectors_(numSectors),
          radius_(radius),
          stretch_(stretch),
          top_(0.0f),
          mid_(0.0f),
          progressPercent_(100) {
    assert(numSectors_ >= 3);
    assert(stretch_ > 0.0f);

    hullVertices_.resize(numSectors_ * 18);
    hullNormals_.resize(numSectors_ * 18);
    coverVertices_.resize(numSectors_ * 9);
    coverNormals_.resize(numSectors_ * 9);

    ComputeCover(0.0f);
}

void Indicatower::SetCounts(int num, int numTotal, int progressPercent) {
    if (numTotal < 0)
        numTotal = 0;
    NumberTools::Clamp(&num, 0, numTotal);
    NumberTools::Clamp(&progressPercent, 0, 100);
    top_             = stretch_ * (float)numTotal;
    mid_             = stretch_ * (float)(numTotal - num);
    progressPercent_ = progressPercent;

    coverColor_ = redColor;
    if (numTotal) {
        float t     = (float)num / (float)numTotal;
        if (t < .5f) {
            t *= 2.0f;
            coverColor_ = (1.0f - t)*greenColor + t*yellowColor;
        }
        else {
            t = 2.0f * (t - .5f);
            coverColor_ = (1.0f - t)*yellowColor + t*redColor;
        }
    }

    ComputeCover(top_);
}

void Indicatower::Render(RenderContext *context) {
    glEnable(GL_LIGHTING);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &hullVertices_[0]);
    glNormalPointer(GL_FLOAT, 0, &hullNormals_[0]);
    ComputeHull(mid_, 0.0f);
    GLfloat color[4];
    color[0] = greenColor.x;  color[1] = greenColor.y;  color[2] = greenColor.z;  color[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glDrawArrays(GL_TRIANGLES, 0, numSectors_ * 6);

    ComputeHull(top_, mid_);
    color[0] = redColor.x;  color[1] = redColor.y;  color[2] = redColor.z;  color[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glDrawArrays(GL_TRIANGLES, 0, numSectors_ * 6);

    int numSectors = numSectors_;
    if (progressPercent_ < 100) {
        numSectors = (int)((float)progressPercent_/100.0f*numSectors_ + .5f);
        NumberTools::Clamp(&numSectors, 0, numSectors_);
    }
    int numSectorsMissing = numSectors_ - numSectors;
    glVertexPointer(3, GL_FLOAT, 0, &coverVertices_[0]);
    glNormalPointer(GL_FLOAT, 0, &coverNormals_[0]);
    Vector col = coverColor_;
    color[0] = col.x;  color[1] = col.y;    color[2] = col.z;    color[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glDrawArrays(GL_TRIANGLES, 0, numSectors * 3);

    glVertexPointer(3, GL_FLOAT, 0, &coverVertices_[numSectors * 9]);
    glNormalPointer(GL_FLOAT, 0, &coverNormals_[numSectors * 9]);
    col = .8f * coverColor_;
    color[0] = col.x;  color[1] = col.y;    color[2] = col.z;    color[3] = 1.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glDrawArrays(GL_TRIANGLES, 0, numSectorsMissing * 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisable(GL_LIGHTING);
}

void Indicatower::ComputeHull(float top, float bottom) {
    GLfloat *ptr  = &hullVertices_[0],
            *nptr = &hullNormals_[0];
    Vector lastArm;
    for (int i = 0; i <= numSectors_; ++i) {
        Vector arm(radius_, 0.0f, 0.0f);
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
        Vector arm(radius_, 0.0f, 0.0f);
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

