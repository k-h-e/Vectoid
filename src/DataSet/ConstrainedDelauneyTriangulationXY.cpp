#include <Vectoid/DataSet/ConstrainedDelauneyTriangulationXY.h>

#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include <cerrno>
#include <K/Core/Log.h>
#include <K/Core/Result.h>
#include <K/Core/StringTools.h>
#include <K/IO/File.h>
#include <K/IO/IOTools.h>
#include <K/IO/StreamBuffer.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/DataSet/TwoIds.h>

using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using std::string;
using K::Core::Log;
using K::Core::Result;
using K::Core::StringTools;
using K::IO::File;
using K::IO::StreamBuffer;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::Vector;
using Vectoid::DataSet::TwoIds;
using Vectoid::DataSet::VertexSet;

namespace Vectoid {
namespace DataSet {

ConstrainedDelauneyTriangulationXY::ConstrainedDelauneyTriangulationXY()
        : workingDirectory_("./Triangulation") {
    // Nop.
}

void ConstrainedDelauneyTriangulationXY::AddPoint(const Vector<float> &vertexXY) {
    vertices_.Add(Vector<float>(vertexXY.x, 0.0f, vertexXY.z));
}

void ConstrainedDelauneyTriangulationXY::AddSegment(const TwoPoints &segmentXY) {
    int vertex0 = vertices_.Add(Vector(segmentXY.point0.x, segmentXY.point0.y, 0.0f));
    int vertex1 = vertices_.Add(Vector(segmentXY.point1.x, segmentXY.point1.y, 0.0f));
    segments_.insert(TwoIds(vertex0, vertex1).MakeCanonical());
}

bool ConstrainedDelauneyTriangulationXY::Compute() {
    if (vertices_.Count() >= 3) {
        if (WriteTriangleInputFile()) {
            if (RunTriangle()) {
                auto vertices = ReadTriangleVertexFile();
                if (vertices) {
                    return true;
                }
            }
        }
    }

    return false;
}

void ConstrainedDelauneyTriangulationXY::PrepareToProvideTriangles() {

}

bool ConstrainedDelauneyTriangulationXY::ProvideNextTriangle(ThreePoints *outTriangle) {
    return false;
}

void ConstrainedDelauneyTriangulationXY::ProvideNormal(Vector<float> *outNormal) {

}

bool ConstrainedDelauneyTriangulationXY::TriangleError() {
    return false;
}

bool ConstrainedDelauneyTriangulationXY::WriteTriangleInputFile() {
    auto result = make_shared<Result>();
    {
        auto buffer = make_shared<StreamBuffer>(
                    make_shared<File>(workingDirectory_ + "/" + "triangulation.poly", File::AccessMode::WriteOnly,
                                      true),
                    File::AccessMode::WriteOnly,
                    4 * 1024, result);

        char line[200];
        std::sprintf(line, "%d 2 0 0\n", vertices_.Count());
        *buffer << line;
        for (int i = 0; i < vertices_.Count(); ++i) {
            const Vector<float> &point = vertices_[i];
            std::sprintf(line, "%d %.12f %.12f\n", (i + 1), point.x, point.y);
            *buffer << line;
        }

        std::sprintf(line, "%d 0\n", static_cast<int>(segments_.size()));
        *buffer << line;
        int segmentIndex = 0;
        for (const TwoIds &segment : segments_) {
            std::sprintf(line, "%d %d %d\n", (segmentIndex + 1), segment.id0 + 1, segment.id1 + 1);
            *buffer << line;
            ++segmentIndex;
        }

        std::sprintf(line, "0\n");    // No holes.
        *buffer << line;
    }
    return result->Success();
}

bool ConstrainedDelauneyTriangulationXY::RunTriangle() {
    Log::Print(Log::Level::Debug, this, []{ return "running triangle tool..."; });
    pid_t id = fork();
    if (id == -1) {
        return false;
    } else if (id == 0) {
        auto fileName = workingDirectory_ + "/" + "triangulation.poly";
        exit(execlp("triangle", "triangle", fileName.c_str(), nullptr));
    } else {
        int status;
        while (true) {
            pid_t result = waitpid(id, &status, 0);
            if (result == id) {
                Log::Print(Log::Level::Debug, this, [&]{
                    return "triangle tool reported status " + to_string(status);
                });
                return (status == 0);
            } else if (result == -1) {
                if (errno != EINTR) {
                    return false;
                }
            }
        }
    }
}

unique_ptr<VertexSet> ConstrainedDelauneyTriangulationXY::ReadTriangleVertexFile() {
    auto buffer = make_shared<StreamBuffer>(
        make_shared<File>(workingDirectory_ + "/" + "triangulation.1.node", File::AccessMode::ReadOnly, false),
        File::AccessMode::ReadOnly,
        4 * 1024);

    string line;
    Read(buffer.get(), '\n', &line);
    if (!Good(buffer.get())) {
        return nullptr;
    }
    int numVertices;
    auto tokens = StringTools::Tokenize(line, " \t", true);
    if ((tokens.size() != 4u) || !StringTools::Parse(tokens[0], &numVertices)) {
        return nullptr;
    }

    Log::Print(Log::Level::Debug, this, [&]{ return "num_vertices=" + to_string(numVertices); });
    auto vertices = make_unique<VertexSet>();
    double x;
    double y;
    for (int i = 0; i < numVertices; ++i) {
        Read(buffer.get(), '\n', &line);
        if (!Good(buffer.get())) {
            return nullptr;
        }
        tokens = StringTools::Tokenize(line, " \t", true);
        if ((tokens.size() != 4u) || !StringTools::Parse(tokens[1], &x) || !StringTools::Parse(tokens[2], &y)) {
            return nullptr;
        }
        Log::Print(Log::Level::Debug, this, [&]{ return "have point, x=" + to_string(x) + ", y=" + to_string(y); });
    }

    return vertices;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
