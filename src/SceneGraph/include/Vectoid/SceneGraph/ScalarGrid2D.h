///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_SCALARGRID2D_H_
#define VECTOID_SCENEGRAPH_SCALARGRID2D_H_

#include <Vectoid/Core/PiecewiseLinearFunction.h>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
    namespace SceneGraph {
        class Context;
    }
}

namespace Vectoid {
namespace SceneGraph {

//! Renders scalar data arranged in a 2D grid.
class ScalarGrid2D : public Geometry {
  public:
    ScalarGrid2D()                                     = delete;
    ScalarGrid2D(const ScalarGrid2D &other)            = delete;
    ScalarGrid2D &operator=(const ScalarGrid2D &other) = delete;
    ScalarGrid2D(ScalarGrid2D &&other)                 = delete;
    ScalarGrid2D &operator=(ScalarGrid2D &&other)      = delete;
    ~ScalarGrid2D();

    //! Tells the number of rows.
    int NumRows();
    //! Sets all data elements to 0.
    void Clear();
    //! Sets the data for the specified row as specified.
    /*!
     *  One byte per grid point.
     */
    void SetRowData(int row, const uint8_t *data, int dataSize);
    //! Sets the row offset as specified.
    /*!
     *  Rows are rendered top to bottom, beginning with the row indicated by the row offset.
     */
    void SetRowOffset(int offset);
    //! Returns the current row offset.
    int RowOffset();

  protected:
    ScalarGrid2D(const std::shared_ptr<Context> &context, float width, float height, int numColumns, int numRows);

    float ColumnPosition(int column);
    float RowPosition(int row);
    Core::Vector<float> ColorAt(int column, int row);
    int ApplyRowOffset(int row);

    float                                              width_;
    float                                              height_;
    int                                                numColumns_;    // >= 2.
    int                                                numRows_;       // >= 2.
    int                                                rowOffset_;     // In [0, numRows_-1].
    uint8_t                                            *data_;
    Core::PiecewiseLinearFunction<Core::Vector<float>> colorCoding_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SCALARGRID2D_H_
