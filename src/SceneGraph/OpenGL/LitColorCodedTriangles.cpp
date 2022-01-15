#include <Vectoid/SceneGraph/OpenGL/LitColorCodedTriangles.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/DataSet/ThreeIds.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::make_unique;
using std::shared_ptr;
using std::to_string;
using std::unordered_set;
using std::vector;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;
using Vectoid::DataSet::ThreeIds;
using Vectoid::DataSet::Triangles;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LitColorCodedTriangles::LitColorCodedTriangles(const shared_ptr<Context> &context,
                                               const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::LitColorCodedTriangles(context, triangleProvider),
          vboInvalid_(false),
          numTriangles_(0),
          gouraudShadingEnabled_(false) {
    // Nop.
}

void LitColorCodedTriangles::EnableGouraudShading(bool enabled) {
    if (enabled != gouraudShadingEnabled_) {
        gouraudShadingEnabled_ = enabled;
        vboInvalid_            = true;
    }
}

void LitColorCodedTriangles::Render() {
    if (vboInvalid_) {
        if (vbo_) {
            glDeleteBuffers(1, &*vbo_);
            Log::Print(Log::Level::Debug, this, [&]{ return "deleted VBO " + to_string(*vbo_); });
            vbo_.reset();
        }
        vboInvalid_ = false;
    }

    if (gouraudShadingEnabled_) {
        RenderGouraud();
    } else {
        RenderFlat();
    }
}

void LitColorCodedTriangles::RenderFlat() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);
    triangleProvider_->PrepareToProvideTriangles();
    ThreePoints   triangle;
    Vector<float> normal;
    Vector<float> color;
    while (triangleProvider_->ProvideNextTriangle(&triangle)) {
        triangleProvider_->ProvideNormal(&normal);
        glNormal3f(normal.x, normal.y, normal.z);
        color = GetColor(triangle.point0);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(triangle.point0.x, triangle.point0.y, triangle.point0.z);
        color = GetColor(triangle.point1);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(triangle.point1.x, triangle.point1.y, triangle.point1.z);
        color = GetColor(triangle.point2);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(triangle.point2.x, triangle.point2.y, triangle.point2.z);
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
}

void LitColorCodedTriangles::RenderGouraud() {
    if (!vbo_) {
        GenerateGouraudResources();
    }
    if (vbo_) {
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);

        glBindBuffer(GL_ARRAY_BUFFER, *vbo_);
        glVertexPointer(3, GL_FLOAT, 9 * sizeof(GLfloat), nullptr);
        glNormalPointer(GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void *>(12u));
        glColorPointer(3, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void *>(24u));
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glColor3f(1.0f, 1.0f, 1.0f);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
    }
}

Vector<float> LitColorCodedTriangles::GetColor(const Vector<float> &vertex) {
    auto color = colorCodingFunction_ ? colorCodingFunction_(vertex) : Vector<float>(.5f, .5f, .5f);
    color.ClampComponents(0.0f, 1.0f);
    return color;
}

void LitColorCodedTriangles::GenerateGouraudResources() {
    Triangles triangles(triangleProvider_.get());
    if (triangles.Size()) {
        int numVertices = triangles.Vertices()->Size();
        vector<Vector<float>> normals(static_cast<vector<Vector<float>>::size_type>(numVertices));

        unordered_set<int> neighbors;
        ThreePoints        triangle;
        Vector<float>      normal;
        Vector<float>      normalSum;
        for (int i = 0; i < numVertices; ++i) {
            triangles.GetTrianglesSharingVertex(i, &neighbors);
            for (int neighbor : neighbors) {
                triangles.GetTriangleVertices(neighbor, &triangle);
                triangle.ComputeNormal(&normal);
                normalSum += normal;
            }
            normalSum.Normalize();
            if (normalSum.Valid()) {
                normals[i] = normalSum;
            } else {
                normals[i] = Vector<float>(1.0f, 0.0f, 0.0f);
                Log::Print(Log::Level::Warning, this, [&]{
                    return "failed to compute vertex normal, substituting default";
                });
            }
        }

        vector<GLfloat> data;
        ThreeIds        vertexIds;
        for (int i = 0; i < triangles.Size(); ++i) {
            triangles.GetTriangleVertexIds(i, &vertexIds);
            for (int j = 0; j < 3; ++j) {
                int vertexId = vertexIds[j];
                const Vector<float> &vertex = (*triangles.Vertices())[vertexId];
                data.push_back(vertex.x);
                data.push_back(vertex.y);
                data.push_back(vertex.z);
                const Vector<float> &normal = normals[vertexId];
                data.push_back(normal.x);
                data.push_back(normal.y);
                data.push_back(normal.z);
                const Vector<float> color = GetColor(vertex);
                data.push_back(color.x);
                data.push_back(color.y);
                data.push_back(color.z);
            }
        }

        GLuint name;
        glGenBuffers(1u, &name);
        glBindBuffer(GL_ARRAY_BUFFER, name);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);
        vbo_          = name;
        numTriangles_ = triangles.Size();

        Log::Print(Log::Level::Debug, this, [&]{
            return "generated VBO " + to_string(*vbo_) + " for Gouraud shading, size="
                + to_string(data.size() * sizeof(GLfloat));
        });
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
