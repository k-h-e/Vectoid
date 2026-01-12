///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/VertexNormalTriangleProvider.h>

#include <chrono>
#include <K/Core/Log.h>
#include <Vectoid/DataSet/BoundingBoxTree.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/DataSet/ThreeIds.h>

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

VertexNormalTriangleProvider::VertexNormalTriangleProvider(
        const shared_ptr<TriangleProviderInterface> &triangleProvider)
            : triangleProvider_{triangleProvider},
              currentTriangle_{0},
              error_{false} {
    // Nop.
}

bool VertexNormalTriangleProvider::Precompute() {
    if (!triangles_) {
        Log::Print(Log::Level::Debug, this, [&]{ return "computing vertex normals..."; });
        auto startTime{steady_clock::now()};
        
        triangles_ = make_shared<Triangles>(*triangleProvider_);
        if (triangleProvider_->TriangleError()) {
            triangles_.reset();
            return false;
        }

        if (triangles_->Size()) {
            int numVertices = triangles_->Vertices()->Size();
            vertexNormals_  = make_unique<vector<Vector<float>>>(
                                  static_cast<vector<Vector<float>>::size_type>(numVertices));

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
                    (*vertexNormals_)[i] = normalSum;
                } else {
                    (*vertexNormals_)[i] = Vector<float>(1.0f, 0.0f, 0.0f);
                    Log::Print(Log::Level::Warning, this, [&]{
                        return "failed to compute vertex normal, substituting default";
                    });
                }
            }
        } else {
            vertexNormals_ = make_unique<vector<Vector<float>>>();
        }
    
        auto stopTime{steady_clock::now()};
        int durationMs = 0;
        if (stopTime >= startTime) {
            durationMs = static_cast<int>(duration_cast<milliseconds>(stopTime - startTime).count());
        }
        Log::Print(Log::Level::Debug, this, [&]{
            return "computed vertex normals in " + to_string(durationMs) + "ms";
        });
    }
    
    return true;
}

unique_ptr<BoundingBoxTree> VertexNormalTriangleProvider::MakeBoundingBoxTree() {
    unique_ptr<BoundingBoxTree> tree;
    if (Precompute()) {
        tree = make_unique<BoundingBoxTree>(triangles_);
    }
    return tree;
}

void VertexNormalTriangleProvider::PrepareToProvideTriangles() {
    currentTriangle_ = 0;
    error_           = !Precompute();
}

bool VertexNormalTriangleProvider::ProvideNextTriangle(ThreePoints &outTriangle) {
    if (!error_ && triangles_&& (currentTriangle_ < triangles_->Size())) {
        ThreeIds vertexIds;
        triangles_->GetTriangleVertexIds(currentTriangle_, vertexIds);
        for (int i = 0; i < 3; ++i) {
            int vertexId = vertexIds[i];
            outTriangle[i]                   = (*(triangles_->Vertices()))[vertexId];
            currentTriangleVertexNormals_[i] = (*vertexNormals_)[vertexId];
        }
        currentTriangleNormal_ = outTriangle.Normal();
        if (outTriangle.Valid() && currentTriangleNormal_.Valid()) {
            ++currentTriangle_;
            return true;
        } else {
            error_ = true;
        }
    }
    
    triangles_.reset();
    vertexNormals_.reset();
    return false;
}

void VertexNormalTriangleProvider::ProvideNormal(Vector<float> &outNormal) {
    if (!error_) {
        outNormal = currentTriangleNormal_;
    }
}

void VertexNormalTriangleProvider::ProvideVertexNormals(ThreePoints *outVertexNormals) {
    if (!error_) {
        *outVertexNormals = currentTriangleVertexNormals_;
    }
}

bool VertexNormalTriangleProvider::TriangleError() {
    return error_;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
