///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/VertexNormals.h>

#include <chrono>

#include <K/Core/Log.h>
#include <Vectoid/DataSet/BoundingBoxTree.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/DataSet/ThreeIds.h>
#include <Vectoid/DataSet/Triangles.h>

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::to_string;
using std::unique_ptr;
using std::unordered_set;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using K::Core::Log;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Vector;
using Vectoid::DataSet::ThreeIds;

namespace Vectoid {
namespace DataSet {

VertexNormals::VertexNormals(const shared_ptr<Triangles> &triangles)
            : triangles_{triangles},
              currentTriangle_{0} {
    ComputeVertexNormals();
}

void VertexNormals::PrepareToProvideTriangles() {
    currentTriangle_ = 0;
}

bool VertexNormals::ProvideNextTriangle(ThreePoints &outTriangle) {
    if (currentTriangle_ < triangles_->Size()) {
        ThreeIds vertexIds;
        triangles_->GetTriangleVertexIds(currentTriangle_, vertexIds);
        
        for (int i = 0; i < 3; ++i) {
            int vertexId = vertexIds[i];
            outTriangle[i]                   = (*(triangles_->Vertices()))[vertexId];
            currentTriangleVertexNormals_[i] = vertexNormals_[vertexId];
        }
        
        currentTriangleNormal_ = outTriangle.Normal();
        if (!currentTriangleNormal_.Valid()) {
            currentTriangleNormal_ = Vector<float>{1.0f, 0.0f, 0.0f};
            Log::Print(Log::Level::Warning, this, [&]{
                return "failed to compute triangle normal, substituting default";
            });
        }
        
        ++currentTriangle_;
        return true;
    } else {
        return false;
    }
}

void VertexNormals::ProvideNormal(Vector<float> &outNormal) {
    outNormal = currentTriangleNormal_;
}

void VertexNormals::ProvideVertexNormals(ThreePoints &outVertexNormals) {
    outVertexNormals = currentTriangleVertexNormals_;
}

bool VertexNormals::TriangleError() {
    return false;
}

// ---

bool VertexNormals::ComputeVertexNormals() {
    Log::Print(Log::Level::Debug, this, [&]{ return "computing vertex normals..."; });
    
    auto startTime = steady_clock::now();
    
    int numVertices { triangles_->Vertices()->Size() };
    vertexNormals_.clear();

    unordered_set<int> neighbors;
    ThreePoints        triangle;
    Vector<float>      normalSum;
    for (int i = 0; i < numVertices; ++i) {
        triangles_->GetTrianglesSharingVertex(i, neighbors);
        for (int neighbor : neighbors) {
            triangles_->GetTriangleVertices(neighbor, triangle);
            normalSum += triangle.Normal();
        }
        normalSum.Normalize();
        if (normalSum.Valid()) {
            vertexNormals_.push_back(normalSum);
        } else {
            vertexNormals_.push_back(Vector<float>{1.0f, 0.0f, 0.0f});
            Log::Print(Log::Level::Warning, this, [&]{
                return "failed to compute vertex normal, substituting default";
            });
        }
    }
    
    auto stopTime = steady_clock::now();
    int  durationMs { 0 };
    if (stopTime >= startTime) {
        durationMs = static_cast<int>(duration_cast<milliseconds>(stopTime - startTime).count());
    }
    Log::Print(Log::Level::Debug, this, [&]{
        return "computed vertex normals in " + to_string(durationMs) + "ms";
    });
   
    return true;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
