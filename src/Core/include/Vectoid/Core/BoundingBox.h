///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_BOUNDINGBOX_H_
#define VECTOID_CORE_BOUNDINGBOX_H_

#include <Vectoid/Core/Range.h>

#include <Vectoid/Core/Transform.h>

namespace Vectoid {
namespace Core {

template<typename T> class Vector;

//! Bounding box in 3-space.
template<typename T>
class BoundingBox : public virtual K::Core::SafelySerializableInterface  {
  public:
    //! Creates an undefined bounding box.
    /*!
     *  The bounding box will behave as <c>(0, 0, 0)</c> until \ref Grow() is called the first time supplying a point or
     *  a defined other bounding box. Then, it will no longer be undefined, but initialized to the parameter of that
     *  first call to \ref Grow().
     */
    BoundingBox() {}
    // Instances may get copied/moved depending on T.

    //! Tells whether the range is (still) undefined.
    bool Undefined() const { return xRange_.Undefined() || yRange_.Undefined() || zRange_.Undefined(); }
    //! Returns the minimum corner of the bounding box.
    Vector<T> MinCorner() const {
        return Undefined() ? Vector<T>() : Vector<T>(xRange_.Min(), yRange_.Min(), zRange_.Min());
    }
    //! Returns the maximum corner of the bounding box.
    Vector<T> MaxCorner() const {
        return Undefined() ? Vector<T>() : Vector<T>(xRange_.Max(), yRange_.Max(), zRange_.Max());
    }
    //! If necessary, grows the bounding box to include the specified point.
    void Grow(const Vector<T> &point) {
        xRange_.Grow(point.x);
        yRange_.Grow(point.y);
        zRange_.Grow(point.z);
    }
    //! If necessary, grows the bounding box to include the specified other bounding box.
    void Grow(const BoundingBox<T> &other) {
        if (!other.Undefined()) {
            Grow(other.MinCorner());
            Grow(other.MaxCorner());
        }
    }
    //! Expands the bounding box at each side by the specified length.
    void Expand(T length) {
        xRange_.Expand(length);
        yRange_.Expand(length);
        zRange_.Expand(length);
    }
    //! Expands the bounding box at each side by the respective specified length.
    void Expand(T lengthX, T lengthY, T lengthZ) {
        xRange_.Expand(lengthX);
        yRange_.Expand(lengthY);
        zRange_.Expand(lengthZ);
    }
    //! Scales the bounding box by the specified scaling factor.
    void Scale(T scalingFactor) {
        xRange_.Scale(scalingFactor);
        yRange_.Scale(scalingFactor);
        zRange_.Scale(scalingFactor);
    }
    //! Tells wether the bounding box contains the specified point.
    bool Contains(const Vector<T> &point) const {
        return xRange_.Contains(point.x) && yRange_.Contains(point.y) && zRange_.Contains(point.z);
    }
    
    //! Clamps the specified point to the bounding box.
    void Clamp(Vector<T> &point) const {
        xRange_.Clamp(point.x);
        yRange_.Clamp(point.y);
        zRange_.Clamp(point.z);
    }
    
    //! Returns the bounding box's center.
    Vector<T> Center() const {
        return Vector<T>(xRange_.Center(), yRange_.Center(), zRange_.Center());
    }
    //! Returns the bounding box's extents.
    Vector<T> Extents() const {
        return Vector<T>(xRange_.Extent(), yRange_.Extent(), zRange_.Extent());
    }
    //! Tells the axis along which the bounding box has the largest extent.
    Axis LargestExtentAxis() {
        auto extents = Extents();
        Axis axis   = Axis::X;
        T    extent = extents.x;
        if (extents.y > extent) {
            axis   = Axis::Y;
            extent = extents.y;
        }
        if (extents.z > extent) {
            axis   = Axis::Z;
            extent = extents.z;
        }

        return axis;
    }
    
    void Serialize(K::Core::BlockingOutStreamInterface &stream) const override {
        xRange_.Serialize(stream);
        yRange_.Serialize(stream);
        zRange_.Serialize(stream);
    }
    
    void Deserialize(K::Core::BlockingInStreamInterface &stream) override {
        xRange_.Deserialize(stream);
        yRange_.Deserialize(stream);
        zRange_.Deserialize(stream);
    }
    
    bool DeserializeAndValidate(K::Core::BlockingInStreamInterface &stream) override {
        bool valid { true };
        
        if (!xRange_.DeserializeAndValidate(stream)) {
            valid = false;
        }
        if (!yRange_.DeserializeAndValidate(stream)) {
            valid = false;
        }
        if (!zRange_.DeserializeAndValidate(stream)) {
            valid = false;
        }
        
        return valid;
    }
    
  private:
    Range<T> xRange_;
    Range<T> yRange_;
    Range<T> zRange_;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_BOUNDINGBOX_H_
