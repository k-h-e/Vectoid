///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/ScalarGrid2D.h>

#include <K/Core/NumberTools.h>

using std::memcpy;
using std::shared_ptr;
using K::Core::NumberTools;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

// Constructor is protected, see below.

ScalarGrid2D::~ScalarGrid2D() {
    delete[] data_;
}

int ScalarGrid2D::NumRows() {
    return numRows_;
}

void ScalarGrid2D::Clear() {
    for (int row = 0; row < numRows_; ++row) {
        for (int column = 0; column < numColumns_; ++column) {
            data_[row*numColumns_ + column] = 0u;
        }
    }
}

void ScalarGrid2D::SetRowData(int row, const uint8_t *data, int dataSize) {
    NumberTools::Clamp(row, 0, numRows_ - 1);
    int numToCopy = (dataSize <= numColumns_) ? dataSize : numColumns_;
    memcpy(&data_[row * numColumns_], data, numToCopy);
}

void ScalarGrid2D::SetRowOffset(int offset) {
    rowOffset_ = offset;
    NumberTools::Clamp(rowOffset_, 0, numRows_ - 1);
}

int ScalarGrid2D::RowOffset() {
    return rowOffset_;
}

// ---

ScalarGrid2D::ScalarGrid2D(const shared_ptr<Context> &context, float width, float height, int numColumns, int numRows)
        : Geometry(context),
          width_{width},
          height_{height},
          numColumns_{numColumns},
          numRows_{numRows},
          rowOffset_{0},
          data_{nullptr} {
    if (!(width_ > 0.0f)) {
        width_ = 1.0f;
    }
    if (!(height_ > 0.0f)) {
        height_ = 1.0f;
    }
    NumberTools::ClampMin(numColumns_, 2);
    NumberTools::ClampMin(numRows_, 2);

    data_ = new uint8_t[numRows_ * numColumns_];

    colorCoding_.AddSupportPoint(  0.0f, Vector<float>( .5f,  .1f,  .1f));
    colorCoding_.AddSupportPoint( 42.5f, Vector<float>( .5f,  .5f,  .1f));
    colorCoding_.AddSupportPoint( 85.0f, Vector<float>( .1f,  .5f,  .1f));
    colorCoding_.AddSupportPoint(127.5f, Vector<float>( .2f,  .2f,  .6f));
    colorCoding_.AddSupportPoint(170.0f, Vector<float>( .4f, 0.0f,  .4f));
    colorCoding_.AddSupportPoint(212.5f, Vector<float>( .2f,  .2f,  .2f));
    colorCoding_.AddSupportPoint(255.0f, Vector<float>(0.0f, 0.0f, 0.0f));

    Clear();

    // TESTING...
    data_[numColumns_ + 1] = 255;
};

float ScalarGrid2D::ColumnPosition(int column) {
    float t = static_cast<float>(column) / static_cast<float>(numColumns_ - 1);
    NumberTools::Clamp(t, 0.0f, 1.0f);
    return (1.0f - t) * (-.5f) * width_ + t * .5f * width_;
}

float ScalarGrid2D::RowPosition(int row) {
    float t = static_cast<float>(row) / static_cast<float>(numRows_ - 1);
    NumberTools::Clamp(t, 0.0f, 1.0f);
    return (1.0f - t) * .5f * height_ + t * (-.5f) * height_;
}

Vector<float> ScalarGrid2D::ColorAt(int column, int row) {
    uint8_t data = data_[ApplyRowOffset(row)*numColumns_ + column];
    if (data == 255u) {
        return Vector<float>{1.0f, 1.0f, 1.0f};
    } else {
        return colorCoding_.Evaluate(255.0f - static_cast<float>(data));
    }
}

int ScalarGrid2D::ApplyRowOffset(int row) {
    row += rowOffset_;
    if (row >= numRows_) {
        row -= numRows_;
    }
    return row;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
