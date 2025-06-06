///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_POINTS_H_
#define VECTOID_DATASET_POINTS_H_

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include <Vectoid/Core/PointHandlerInterface.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
//! Data structures and algorithms for 3D data processing.
namespace DataSet {

//! Set of points in 3-space.
/*!
 *  Can grow dynamically.
 *
 *  As a point handler, it just accepts and adds points, but ignores any stream error.
 */
class Points : public virtual Core::PointHandlerInterface {
  public:
    Points();
    Points(const Points &other);
    Points &operator=(const Points &other)  = delete;
    Points(Points &&other)                  = delete;
    Points &operator=(Points &&other)       = delete;

    //! Tells the number of points in the set.
    int Size() const;
    //! Adds the specified point, if it is not already present.
    /*!
     * \return
     * Id of the point inside the set.
     */
    int Add(const Core::Vector<float> &point);
    //! Gives access to the specified point.
    /*!
     *  The specified point id must lie in <c>[ 0, Size() )</c>.
     */
    const Core::Vector<float> &operator[](int index) const;
    //! Returns the id of the specified point, or <c>nullopt</c> in case the point is not in the set.
    std::optional<int> Id(const Core::Vector<float> &point);
    //! Drops internal helper data structures in order to free up memory. These will automatically get re-generated when
    //! needed.
    void OptimizeForSpace();
    //! Creates an independent clone of the point set.
    std::unique_ptr<Points> Clone() const;

    // PointHandlerInterface...
    void OnPoint(const Core::Vector<float> &point) override;
    void OnStreamError(K::Core::StreamInterface::Error error) override; 

  private:
    std::unordered_map<Core::Vector<float>, int, Core::Vector<float>::HashFunction> *PointMap();

    std::vector<Core::Vector<float>>                                                                 points_;
    std::unique_ptr<std::unordered_map<Core::Vector<float>, int, Core::Vector<float>::HashFunction>> pointMap_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_POINTS_H_
