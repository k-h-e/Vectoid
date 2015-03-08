#ifndef RASPIATOR_VISUALIZATION_H_
#define RASPIATOR_VISUALIZATION_H_


#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <random>
#include <Vectoid/Vector.h>
#include "JenkinsAccess.h"


namespace kxm {
namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class CoordSys;
}
}

namespace Raspiator {

class Indicatower;
class Glyphs;
class TextRing;

class Visualization {
  public:
    Visualization(const std::string &jenkinsServer,
                  float indicatowerDistance, float indicatowerRadius, float indicatowerStretch,
                  float glyphWidth, float glyphHeight, float groupDistanceModifier,
                  kxm::Vectoid::Vector groupTranslation);
    Visualization(const Visualization &other)            = delete;
    Visualization &operator=(const Visualization &other) = delete;
    Visualization(Visualization &&other)                 = delete;
    Visualization &operator=(Visualization &&other)      = delete;
    void SetViewPort(int width, int height);
    void RenderFrame();

    //! Starts a new group.
    void NewGroup(const std::string &name, float angle, float distanceModifier);
    //! Starts a new sub group in the current group.
    void NewSubGroup(const std::string &name, float angle);
    //! Adds a new job to the current sub group.
    void NewJob(const std::string &id, const std::string &name, const std::string &jenkinsJob,
                float updateIntervalS);
    //! Layouts the visualization.
    void UpdateLayout();

    //! Updates the data for the specified job.
    void SetJobData(const std::string &id, int numRed, int numTotal, int progressPercent);

  private:
    struct JobInfo;
    struct SubGroupInfo {
        std::string                             name;
        std::vector<std::shared_ptr<JobInfo>>   jobs;
        float                                   angle;
        std::shared_ptr<kxm::Vectoid::CoordSys> coordSys;
        SubGroupInfo(const std::string &aName, float anAngle);
        //! Lays out the sub group's towers around the origin in the xz-plane and returns the radius
        //! of the enclosing circle.
        float Layout(float indicatowerDistance, float indicatowerRadius);
    };
    struct GroupInfo {
        std::string                                name;
        std::vector<std::unique_ptr<SubGroupInfo>> subGroups;
        float                                      angle,
                                                   distanceModifier;
        std::shared_ptr<kxm::Vectoid::CoordSys>    coordSys;
        GroupInfo(const std::string &aName, float anAngle, float aDistanceModifier);
        //! Lays out the group's sub groups around the origin in the xz-plane and returns the radius
        //! of the enclosing circle.
        float Layout(float indicatowerDistance, float indicatowerRadius);
    };

    static void LayoutPositions(
        int num, float distance, std::vector<kxm::Vectoid::Vector> *positions, float *radius);

    std::vector<std::unique_ptr<GroupInfo>>                   groups_;
    GroupInfo                                                 *currentGroup_;
    SubGroupInfo                                              *currentSubGroup_;
    std::unordered_map<std::string, std::shared_ptr<JobInfo>> jobs_;
    std::shared_ptr<kxm::Vectoid::PerspectiveProjection>      projection_;
    std::shared_ptr<kxm::Vectoid::Camera>                     camera_;
    std::shared_ptr<Glyphs>                                   glyphs_;
    float                                                     glyphWidth_, glyphHeight_,
                                                              indicatowerRadius_,
                                                              indicatowerDistance_,
                                                              indicatowerStretch_,
                                                              groupDistanceModifier_,
                                                              angle_, angle2_,
                                                              counter_;
    kxm::Vectoid::Vector                                      groupTranslation_;
    std::chrono::time_point<std::chrono::steady_clock>        lastFrameTime_;
    JenkinsAccess                                             jenkinsAccess_;
    std::vector<JenkinsAccess::Data>                          jobDataBuffer_;
    std::default_random_engine                                random_;
    float                                                     timeSinceLastJobUpdateS_;
};

}    // Namespace Raspiator.

#endif    // RASPIATOR_VISUALIZATION_H_

