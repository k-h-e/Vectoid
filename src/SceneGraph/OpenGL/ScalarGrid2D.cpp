///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/ScalarGrid2D.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

ScalarGrid2D::ScalarGrid2D(const shared_ptr<SceneGraph::Context> &context, float width, float height, int numColumns,
                           int numRows)
        : SceneGraph::ScalarGrid2D(context, width, height, numColumns, numRows) {
    // Nop.
}

void ScalarGrid2D::Render() {
    glBegin(GL_TRIANGLES);
    for (int row = 1; row < numRows_; ++ row) {
        for (int column = 1; column < numColumns_; ++column) {
            float         left             { ColumnPosition(column - 1) };
            float         right            { ColumnPosition(column) };
            float         top              { RowPosition(row - 1) };
            float         bottom           { RowPosition(row) };
            Vector<float> colorTopLeft     { ColorAt(column - 1, row - 1) };
            Vector<float> colorTopRight    { ColorAt(column,     row - 1) };
            Vector<float> colorBottomLeft  { ColorAt(column - 1, row) };
            Vector<float> colorBottomRight { ColorAt(column,     row) };

            // Top left triangle...
            glColor3f(colorTopLeft.x, colorTopLeft.y, colorTopLeft.z);
            glVertex3f(left, top, 0.0f);
            glColor3f(colorBottomLeft.x, colorBottomLeft.y, colorBottomLeft.z);
            glVertex3f(left,  bottom, 0.0f);
            glColor3f(colorTopRight.x, colorTopRight.y, colorTopRight.z);
            glVertex3f(right, top, 0.0f);

            // Bottom right triangle...
            glColor3f(colorBottomLeft.x, colorBottomLeft.y, colorBottomLeft.z);
            glVertex3f(left,  bottom, 0.0f);
            glColor3f(colorBottomRight.x, colorBottomRight.y, colorBottomRight.z);
            glVertex3f(right,  bottom, 0.0f);
            glColor3f(colorTopRight.x, colorTopRight.y, colorTopRight.z);
            glVertex3f(right, top, 0.0f);
        }
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
