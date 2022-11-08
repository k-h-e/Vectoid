#include <Vectoid/IO/StlWriter.h>

#include <K/Core/BinaryWriter.h>
#include <K/Core/Log.h>
#include <K/Core/ResultAcceptor.h>
#include <K/IO/File.h>
#include <K/Core/IOOperations.h>
#include <K/IO/StreamBuffer.h>
#include <K/Core/BinaryWriter.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>

using std::make_shared;
using std::string;
using std::to_string;
using K::Core::BinaryWriter;
using K::Core::Log;
using K::Core::ResultAcceptor;
using K::IO::File;
using K::IO::StreamBuffer;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace IO {

bool StlWriter::Write(TriangleProviderInterface *triangleProvider, const string &fileName) {
    static const int headerSize = 80;

    auto result = make_shared<ResultAcceptor>();
    uint32_t numTriangles = 0u;

    {
        auto file = make_shared<File>(fileName, File::AccessMode::WriteOnly, true);
        file->SetFinalResultAcceptor(result);
        auto buffer = make_shared<StreamBuffer>(file, File::AccessMode::WriteOnly, 4 * 1024);
        buffer->SetFinalResultAcceptor(result);
        buffer->Seek(headerSize + 4);
        {
            auto writer = make_shared<BinaryWriter>(buffer);
            writer->SetFinalResultAcceptor(result);

            triangleProvider->PrepareToProvideTriangles();
            ThreePoints   triangle;
            Vector<float> normal;
            uint16_t      numAttributes = 0u;
            while (triangleProvider->ProvideNextTriangle(&triangle)) {
                triangle.ComputeNormal(&normal);
                if (!normal.Valid()) {
                    return false;
                } else {
                    (*writer) << normal.x;
                    (*writer) << normal.y;
                    (*writer) << normal.z;
                    for (int i = 0; i < 3; ++i) {
                        Vector<float> &vertex = triangle[i];
                        (*writer) << vertex.x;
                        (*writer) << vertex.y;
                        (*writer) << vertex.z;
                    }
                    writer->WriteItem(&numAttributes, sizeof(numAttributes));
                    ++numTriangles;
                }
            }
        }

        char header[headerSize];
        for (int i = 0; i < headerSize; ++i) {
            header[i] = '_';
        }
        buffer->Seek(0);
        buffer->WriteBlocking(&header, headerSize);
        buffer->WriteBlocking(&numTriangles, 4);
    }

    bool success = !triangleProvider->TriangleError() && result->Success();
    if (success) {
        Log::Print(Log::Level::Info, nullptr, [&]{
            return to_string(numTriangles) + " triangles written to STL file \"" + fileName + "\"";
        });
    } else {
        Log::Print(Log::Level::Error, nullptr, [&]{ return "failed to write STL file \"" + fileName + "\""; });
    }
    return success;
}

}    // Namespace IO.
}    // Namespace Vectoid.