#ifndef VECTOID_DATASET_CONSTRAINEDDELAUNEYTRIANGULATIONXY_H_
#define VECTOID_DATASET_CONSTRAINEDDELAUNEYTRIANGULATIONXY_H_

#include <unordered_set>
#include <K/Core/Interface.h>
#include <Vectoid/DataSet/SimpleTriangleList.h>
#include <Vectoid/DataSet/VertexSet.h>
#include <Vectoid/DataSet/TwoIds.h>

namespace Vectoid {

namespace Core {
    class TwoPoints;
}

namespace DataSet {

//! Generates a constrained Delauney triangulation in the <c>x/y</c>-plane.
class ConstrainedDelauneyTriangulationXY : public virtual K::Core::Interface {
  public:
    ConstrainedDelauneyTriangulationXY();
    ConstrainedDelauneyTriangulationXY(const ConstrainedDelauneyTriangulationXY &other)             = delete;
    ConstrainedDelauneyTriangulationXY &operator=(const ConstrainedDelauneyTriangulationXY &other)  = delete;
    ConstrainedDelauneyTriangulationXY(const ConstrainedDelauneyTriangulationXY &&other)            = delete;
    ConstrainedDelauneyTriangulationXY &operator=(const ConstrainedDelauneyTriangulationXY &&other) = delete;

    //! Adds the specified point.
    /*!
     *  The <c>z</c> coordinate will get nulled. Duplicates will get ignored.
     */
    void AddPoint(const Vectoid::Core::Vector<float> &vertexXY);
    //! Adds the specified line segment.
    /*!
     *  The <c>z</c> coordinates will get nulled. Duplicates will get ignored.
     *
     *  Segments must not intersect.
     */
    void AddSegment(const Vectoid::Core::TwoPoints &segmentXY);
    //! Computes the constrained triangulation from the data added previously.
    /*!
     *
     *  \return <nullptr> in case of failure.
     */
    std::unique_ptr<Vectoid::DataSet::SimpleTriangleList> Compute();

  private:
    bool WriteTriangleInputFile();
    bool RunTriangle();
    std::unique_ptr<std::vector<Vectoid::Core::Vector<float>>> ReadTriangleVertexFile();
    std::unique_ptr<Vectoid::DataSet::SimpleTriangleList> ReadTriangleTrianglesFile();

    Vectoid::DataSet::VertexSet                      vertices_;
    std::unordered_set<TwoIds, TwoIds::HashFunction> segments_;    // In canonical form.
    std::string                                      workingDirectory_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_CONSTRAINEDDELAUNEYTRIANGULATIONXY_H_
