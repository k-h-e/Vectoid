///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/IO/StlWriter.h>

#include <K/Core/Log.h>
#include <K/Core/ResultAcceptor.h>
#include <K/IO/File.h>
#include <K/IO/Path.h>
#include <K/IO/StreamBuffer.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>

using std::make_shared;
using std::string;
using std::to_string;
using K::Core::SeekableBlockingOutStreamInterface;
using K::Core::Log;
using K::Core::ResultAcceptor;
using K::IO::File;
using K::IO::Path;
using K::IO::StreamBuffer;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace IO {

bool StlWriter::Write(TriangleProviderInterface &triangleProvider, SeekableBlockingOutStreamInterface &outStream) {
    static const int headerSize { 80 };

    int64_t headerPosition { outStream.StreamPosition() };
    outStream.Seek(headerPosition + headerSize + 4);

    uint16_t attributes   { 0u };
    uint32_t numTriangles { 0u };
    triangleProvider.PrepareToProvideTriangles();
    ThreePoints triangle;
    while (triangleProvider.ProvideNextTriangle(triangle)) {
        Vector<float> normal { triangle.Normal() };
        if (!normal.Valid()) {
            return false;
        } else {
            outStream << normal.x;
            outStream << normal.y;
            outStream << normal.z;
            for (int i = 0; i < 3; ++i) {
                Vector<float> &vertex = triangle[i];
                outStream << vertex.x;
                outStream << vertex.y;
                outStream << vertex.z;
            }
            outStream << attributes;
            ++numTriangles;
        }
    }

    int64_t currentPosition = outStream.StreamPosition();
    outStream.Seek(headerPosition);
    char header[headerSize];
    for (int i = 0; i < headerSize; ++i) {
        header[i] = '_';
    }
    WriteItem(outStream, &header, headerSize);
    outStream << numTriangles;
    outStream.Seek(currentPosition);

    return (!triangleProvider.TriangleError() && !outStream.ErrorState());
}

bool StlWriter::Write(TriangleProviderInterface &triangleProvider, const Path &fileName) {
    auto result = make_shared<ResultAcceptor>();
    {
        auto file = make_shared<File>(fileName, File::AccessMode::WriteOnly, true);
        StreamBuffer fileStream(file, File::AccessMode::WriteOnly, 4 * 1024);
        fileStream.SetCloseResultAcceptor(result);
        if (!Write(triangleProvider, fileStream)) {
            result->OnFailure();
        }
    }

    if (result->Success()) {
        Log::Print(Log::Level::Info, nullptr, [&]{
            return "STL file \"" + fileName.ToShortString() + "\" successfully written";
        });
        return true;
    } else {
        Log::Print(Log::Level::Error, nullptr, [&]{
            return "failed to write STL file \"" + fileName.ToShortString() + "\"";
        });
        return false;
    }
}

}    // Namespace IO.
}    // Namespace Vectoid.
