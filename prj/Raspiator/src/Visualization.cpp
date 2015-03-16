#include "Visualization.h"

#include <cassert>
#include <sstream>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include "Glyphs.h"
#include "Indicatower.h"
#include "TextRing.h"

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace Raspiator {

struct Visualization::JobInfo {
    JobInfo();
    // Default copy and move would be okay.

    std::string                             id,
                                            jenkinsJob;
    bool                                    buildJob;
    int                                     numRed,
                                            numTotal;
    std::shared_ptr<Indicatower>            tower;
    std::shared_ptr<TextRing>               textRing,
                                            innerTextRing;
    std::shared_ptr<kxm::Vectoid::CoordSys> towerCoordSys,
                                            textRingCoordSys,
                                            innerTextRingCoordSys;
    float                                   textRingAngle,
                                            innerTextRingAngle,
                                            stretch;
    int                                     progressPercent;
    float                                   updateIntervalS,
                                            timeToUpdateS;
};

Visualization::Visualization(
    const string &jenkinsServer,
    float indicatowerDistance, float indicatowerRadius, float indicatowerStretch,
    float glyphWidth, float glyphHeight, float groupDistanceModifier, Vector groupTranslation)
        : currentGroup_(nullptr),
          currentSubGroup_(nullptr),
          glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          indicatowerRadius_(indicatowerRadius),
          indicatowerDistance_(indicatowerDistance),
          indicatowerStretch_(indicatowerStretch),
          groupDistanceModifier_(groupDistanceModifier),
          groupTranslation_(groupTranslation),
          lastFrameTime_(steady_clock::now()),
          jenkinsAccess_(jenkinsServer),
          timeSinceLastJobUpdateS_(0.0f) {
    auto projection = make_shared<PerspectiveProjection>();
    projection->SetWindowSize(1.0f);
    projection->SetViewingDepth(11.0f);
    projection->SetEyepointDistance(1.0f);
    auto camera = make_shared<Camera>();
    projection->AddChild(camera);

    projection_  = projection;
    camera_      = camera;
    glyphs_      = make_shared<Glyphs>();
    angle_       = 0;
    angle2_      = 0;
    counter_     = 0;
}

void Visualization::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
}

void Visualization::RenderFrame() {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;

    // Animate camera...
    angle_ += 10.0f * frameDeltaTimeS;
    if (angle_ > 360.0f)
        angle_ -= 360.0f;
    angle2_ += 5.0f * frameDeltaTimeS;
    if (angle2_ > 360.0f)
        angle2_ -= 360.0f;
    float cameraAngle  = 90.0f + 30.0f*sin(angle_ * 3.141592654f / 180.0f),
          cameraAngle2 = 20.0f + 20.0f*sin(angle2_ * 3.141592654f / 180.0f);
    float flightRadius = 8.5f * sin(cameraAngle2 * 3.141592654f / 180.0f),
          flightHeight = 8.5f * cos(cameraAngle2 * 3.141592654f / 180.0f);
    Vector position(flightRadius, flightHeight, 0.0f);
    Transform(YAxis, cameraAngle).ApplyTo(&position);
    Vector viewDirection(-position);
    viewDirection.Normalize();
    Vector u(-viewDirection.z, 0.0f, viewDirection.x);
    u.Normalize();
    Vector v = CrossProduct(u, viewDirection);
    v.Normalize();    // Not really necessary.
    camera_->SetTransform(Transform(u, v, -viewDirection));
    camera_->SetPosition(position);

    // Animate text rings...
    float minAngularSpeed = 10.0f,
          maxAngularSpeed = 40.0f;
    for (auto &pair : jobs_) {
        JobInfo &info = *pair.second;
        float angularSpeed = maxAngularSpeed;
        if (info.numTotal) {
            float t = (float)info.numRed / (float)info.numTotal;
            angularSpeed = (1.0f - t)*minAngularSpeed + t*maxAngularSpeed;
        }
        info.textRingAngle -= angularSpeed * frameDeltaTimeS;
        if (info.textRingAngle < 360.0f)
            info.textRingAngle += 360.0f;
        Transform transform;
        info.textRingCoordSys->GetTransform(&transform);
        Vector position = transform.TranslationPart();
        transform = Transform(XAxis, -90.0f);
        transform.Append(Transform(YAxis, info.textRingAngle));
        transform.SetTranslationPart(position);
        info.textRingCoordSys->SetTransform(transform);

        info.innerTextRingAngle -= 1.4f * angularSpeed * frameDeltaTimeS;
        if (info.innerTextRingAngle < 360.0f)
            info.innerTextRingAngle += 360.0f;
        info.innerTextRingCoordSys->GetTransform(&transform);
        position = transform.TranslationPart();
        transform = Transform(XAxis, -90.0f);
        transform.Append(Transform(YAxis, info.innerTextRingAngle));
        transform.SetTranslationPart(position);
        info.innerTextRingCoordSys->SetTransform(transform);

        info.timeToUpdateS -= frameDeltaTimeS;
        if (info.timeToUpdateS < 0.0f) {
            jenkinsAccess_.RequestJobDataUpdate(info.id, info.jenkinsJob, info.buildJob);
            info.timeToUpdateS = info.updateIntervalS;
        }
    }

    timeSinceLastJobUpdateS_ += frameDeltaTimeS;
    if (timeSinceLastJobUpdateS_ > 1.0f) {
        jenkinsAccess_.GetJobData(&jobDataBuffer_);
        for (JenkinsAccess::Data &data : jobDataBuffer_)
            SetJobData(data.id, data.numRed, data.numTotal, data.progressPercent);
        timeSinceLastJobUpdateS_ = 0.0f;
    }

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

void Visualization::NewJob(const std::string &id, const std::string &name, const string &jenkinsJob,
                           bool buildJob, float updateIntervalS) {
    assert(currentSubGroup_);
    if (updateIntervalS < 1.0f)
        updateIntervalS = 600.0f;
    if(jobs_.find(id) != jobs_.end())
        return;

    auto info = make_shared<JobInfo>();
    info->id            = id;
    info->jenkinsJob    = jenkinsJob;
    info->buildJob      = buildJob;
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

    info->updateIntervalS = updateIntervalS;
    uniform_int_distribution<int> distribution(0, (int)updateIntervalS);
    info->timeToUpdateS = (float)distribution(random_);

    currentSubGroup_->jobs.push_back(info);
    jobs_[id] = info;

    SetJobData(id, 0, 0, 100);
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
        info->coordSys->SetPosition(positions[i] + groupTranslation_);
        ++i;
    }
}

void Visualization::SetJobData(const std::string &id, int numRed, int numTotal,
                               int progressPercent) {
    auto infoIter = jobs_.find(id);
    if (infoIter == jobs_.end())
        return;
    if (numTotal < 0)
        numTotal = 0;
    NumberTools::Clamp(&numRed, 0, numTotal);
    NumberTools::Clamp(&progressPercent, 0, 100);

    JobInfo &info = *infoIter->second;
    info.numRed          = numRed;
    info.numTotal        = numTotal;
    info.progressPercent = progressPercent;
    info.tower->SetCounts(numRed, numTotal, progressPercent);
    Vector ringPosition(0.0f, (float)numTotal*info.stretch + .01f, 0.0f);
    info.textRingCoordSys->SetPosition(ringPosition);
    info.innerTextRingCoordSys->SetPosition(ringPosition);
    info.innerTextRing->SetText(  info.buildJob
                                ? "Build" : to_string(numRed) + "/" + to_string(numTotal));
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
    : buildJob(false),
      numRed(0),
      numTotal(0),
      textRingAngle(0.0f),
      innerTextRingAngle(0.0f),
      progressPercent(0),
      updateIntervalS(0.0f),
      timeToUpdateS(0.0f) {
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
