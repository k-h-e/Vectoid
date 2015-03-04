#include "Visualization.h"

#include <cassert>
#include <sstream>
#include <random>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include "Glyphs.h"
#include "Indicatower.h"
#include "TextRing.h"

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

struct Visualization::JobInfo {
    JobInfo();
    // Default copy and move would be okay.

    std::string                             name;
    int                                     numRed,
                                            numTotal;
    std::shared_ptr<Indicatower>            tower;
    std::shared_ptr<TextRing>               textRing,
                                            innerTextRing;
    std::shared_ptr<kxm::Vectoid::CoordSys> towerCoordSys,
                                            textRingCoordSys,
                                            innerTextRingCoordSys;
    float                                   stretch;
};

Visualization::Visualization(
    float indicatowerDistance, float indicatowerRadius, float glyphWidth, float glyphHeight,
    float groupDistanceModifier)
        : currentGroup_(nullptr),
          currentSubGroup_(nullptr),
          glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          indicatowerRadius_(indicatowerRadius),
          indicatowerDistance_(indicatowerDistance),
          indicatowerStretch_(.001f),
          groupDistanceModifier_(groupDistanceModifier) {
    auto projection = make_shared<PerspectiveProjection>();
    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(10.0f);
    projection->SetEyepointDistance(1.0f);
    auto camera = make_shared<Camera>();
    projection->AddChild(camera);

    projection_  = projection;
    camera_      = camera;
    glyphs_      = make_shared<Glyphs>();
    angle_       = 0;
    counter_     = 0;
}

void Visualization::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
}

void Visualization::RenderFrame() {
    // Animate...
    angle_ += .1f;
    if (angle_ > 360.0f)
        angle_ -= 360.0f;

    // Animate camera...
    float flightRadius = 4.0f,
          flightHeight = 6.0f;
    Vector position(flightRadius, flightHeight, 0.0f);
    Transform(YAxis, angle_).ApplyTo(&position);
    Vector viewDirection(-position);
    viewDirection.Normalize();
    Vector u(-viewDirection.z, 0.0f, viewDirection.x);
    u.Normalize();
    Vector v = CrossProduct(u, viewDirection);
    v.Normalize();    // Not really necessary.
    camera_->SetTransform(Transform(u, v, -viewDirection));
    camera_->SetPosition(position);

    // Render...
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection_->Render(nullptr);
}

void Visualization::NewGroup(const std::string &name, float angle, float distanceModifier) {
    groups_.push_back(unique_ptr<GroupInfo>(new GroupInfo(name, angle, distanceModifier)));
    currentGroup_ = groups_.back().get();
    camera_->AddChild(currentGroup_->coordSys);
}

void Visualization::NewSubGroup(const std::string &name, float angle) {
    assert(currentGroup_);
    currentGroup_->subGroups.push_back(unique_ptr<SubGroupInfo>(new SubGroupInfo(name, angle)));
    currentSubGroup_ = currentGroup_->subGroups.back().get();
    currentGroup_->coordSys->AddChild(currentSubGroup_->coordSys);
}

void Visualization::NewJob(const std::string &id, const std::string &name) {
    assert(currentSubGroup_);
    if(jobs_.find(id) != jobs_.end())
        return;

    auto info = make_shared<JobInfo>();
    info->stretch       = indicatowerStretch_;
    info->tower         = make_shared<Indicatower>(indicatowerRadius_, 30, indicatowerStretch_);
    auto geode          = make_shared<Geode>(info->tower);
    info->towerCoordSys = make_shared<CoordSys>();
    info->towerCoordSys->AddChild(geode);
    currentSubGroup_->coordSys->AddChild(info->towerCoordSys);

    info->textRing = make_shared<TextRing>(indicatowerRadius_ - glyphHeight_,
                                           glyphWidth_, glyphHeight_, glyphs_);
    info->textRing->SetText(name);
    geode = make_shared<Geode>(info->textRing);
    info->textRingCoordSys = make_shared<CoordSys>();
    info->textRingCoordSys->SetTransform(Transform(XAxis, -90.0f));
    info->textRingCoordSys->AddChild(geode);
    info->towerCoordSys->AddChild(info->textRingCoordSys);

    info->innerTextRing = make_shared<TextRing>(indicatowerRadius_ - 2.0f*glyphHeight_,
                                                glyphWidth_, glyphHeight_, glyphs_);
    info->innerTextRingCoordSys = make_shared<CoordSys>();
    info->innerTextRingCoordSys->AddChild(make_shared<Geode>(info->innerTextRing));
    info->innerTextRingCoordSys->SetTransform(Transform(XAxis, -90.0f));
    info->towerCoordSys->AddChild(info->innerTextRingCoordSys);

    currentSubGroup_->jobs.push_back(info);
    jobs_[id] = info;
}

void Visualization::UpdateLayout() {
    assert(currentSubGroup_);
    float maxRadius = 0.0f;
    for (unique_ptr<GroupInfo> &info : groups_) {
        float radius = info->Layout(indicatowerDistance_, indicatowerRadius_);
        if (radius > maxRadius)
            maxRadius = radius;
    }
    std::vector<Vector> positions;
    float               radius;
    LayoutPositions(groups_.size(), 2.0f*maxRadius + groupDistanceModifier_, &positions, &radius);
    int i = 0;
    for (unique_ptr<GroupInfo> &info : groups_) {
        info->coordSys->SetTransform(Transform(YAxis, info->angle));
        info->coordSys->SetPosition(positions[i]);
        ++i;
    }
}

void Visualization::SetJobCounts(const std::string &id, int numRed, int numTotal) {
    auto infoIter = jobs_.find(id);
    if (infoIter == jobs_.end())
        return;
    if (numTotal < 0)
        numTotal = 0;
    NumberTools::Clamp(&numRed, 0, numTotal);

    JobInfo *info = infoIter->second.get();
    info->tower->SetCounts(numRed, numTotal);
    Vector ringPosition(0.0f, (float)numTotal*info->stretch + .01f, 0.0f);
    info->textRingCoordSys->SetPosition(ringPosition);
    info->innerTextRingCoordSys->SetPosition(ringPosition);
    info->innerTextRing->SetText(to_string(numRed) + "/" + to_string(numTotal));
}

void Visualization::LayoutPositions(
        int num, float distance, std::vector<kxm::Vectoid::Vector> *positions, float *radius) {
    positions->clear();
    *radius = 0.0f;
    if (num < 1) {
        // Nop.
    }
    else if (num == 1) {
        positions->push_back(Vector());
    }
    else if (num == 2) {
        positions->push_back(Vector( .5f * distance, 0.0f, 0.0f));
        positions->push_back(Vector(-.5f * distance, 0.0f, 0.0f));
        *radius = .5f * distance;
    }
    else {
        bool haveCenter = false;
        if (num > 3) {
            positions->push_back(Vector());
            haveCenter = true;
            --num;
        }

        float angle = 360.0f / (float)num;
        *radius = .5f * distance / (float)sin(.5f * angle / 180.0f * 3.141592654f);
        if (haveCenter) {
            if (*radius < distance)
                *radius = distance;
        }

        for (int i = 0; i < num; ++i) {
            Vector hand(*radius, 0.0f, 0.0f);
            Transform(YAxis, (float)i*angle).ApplyTo(&hand);
            positions->push_back(hand);
        }
    }
}

Visualization::JobInfo::JobInfo()
    : numRed(0),
      numTotal(0) {
    // Nop.
}

Visualization::GroupInfo::GroupInfo(const std::string &aName, float anAngle,
                                    float aDistanceModifier)
        : name(aName),
          angle(anAngle),
          distanceModifier(aDistanceModifier),
          coordSys(make_shared<CoordSys>()) {
    // Nop.
}

float Visualization::GroupInfo::Layout(float indicatowerDistance, float indicatowerRadius) {
    float maxRadius = 0.0f;
    for (unique_ptr<SubGroupInfo> &info : subGroups) {
        float radius = info->Layout(indicatowerDistance, indicatowerRadius);
        if (radius > maxRadius)
            maxRadius = radius;
    }
    std::vector<Vector> positions;
    float               radius;
    LayoutPositions(subGroups.size(), 2.0f*maxRadius + distanceModifier, &positions, &radius);
    int i = 0;
    for (unique_ptr<SubGroupInfo> &info : subGroups) {
        info->coordSys->SetTransform(Transform(YAxis, info->angle));
        info->coordSys->SetPosition(positions[i]);
        ++i;
    }
    return radius + maxRadius;
}

Visualization::SubGroupInfo::SubGroupInfo(const std::string &aName, float anAngle)
        : name(aName),
          angle(anAngle),
          coordSys(make_shared<CoordSys>()) {
    // Nop.
}

float Visualization::SubGroupInfo::Layout(float indicatowerDistance, float indicatowerRadius) {
    std::vector<Vector> positions;
    float               radius;
    LayoutPositions(jobs.size(), indicatowerDistance, &positions, &radius);
    int i = 0;
    for (shared_ptr<JobInfo> &info : jobs) {
        info->towerCoordSys->SetPosition(positions[i]);
        ++i;
    }
    return radius + indicatowerRadius;
}

}    // Namespace Raspiator.
