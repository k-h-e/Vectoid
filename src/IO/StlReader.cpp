///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/IO/StlReader.h>

#include <K/Core/BlockingInStreamInterface.h>
#include <K/Core/Log.h>
#include <K/IO/File.h>
#include <K/IO/StreamBuffer.h>
#include <K/IO/SubStream.h>
#include <Vectoid/Core/ThreePoints.h>

using std::make_shared;
using std::to_string;
using K::Core::Log;
using K::IO::File;
using K::IO::Path;
using K::IO::StreamBuffer;
using K::IO::SubStream;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace IO {

StlReader::StlReader(const Path &fileName)
        : fileName_{fileName},
          useSubFile_{false},
          subFileOffset_{0},
          subFileSize_{0},
          error_{false},
          numTriangles_{0u},
          numTrianglesProvided_{0u} {
    // Nop.
}

StlReader::StlReader(const Path &fileName, uint64_t offset, uint64_t size)
        : fileName_{fileName},
          useSubFile_{true},
          subFileOffset_{offset},
          subFileSize_{size},
          error_{false},
          numTriangles_{0u},
          numTrianglesProvided_{0u} {
    // Nop.
}

void StlReader::PrepareToProvideTriangles() {
    auto file   = make_shared<File>(fileName_, File::AccessMode::ReadOnly, false);
    fileStream_ = make_shared<StreamBuffer>(file, File::AccessMode::ReadOnly, 2048);
    if (useSubFile_) {
        fileStream_ = make_shared<SubStream>(fileStream_, subFileOffset_, subFileSize_);
    }
    
    const int headerSize = 80;
    uint8_t header[headerSize];
    ReadItem(fileStream_.get(), &header, headerSize);
    (*fileStream_) >> numTriangles_;
    if (!fileStream_->ErrorState()) {
        numTrianglesProvided_ = 0u;
        normal_               = Vector<float>(0.0f, 1.0f, 0.0f);
        error_                = false;
        Log::Print(Log::Level::Info, this, [&]{
            return "reading STL file \"" + fileName_.ToShortString() + "\" with " + to_string(numTriangles_)
                + " triangles";
        });
        CheckFinished();
    } else {
        fileStream_.reset();
        numTriangles_         = 0u;
        numTrianglesProvided_ = 0u;
        error_                = true;
        Log::Print(Log::Level::Error, this, [&]{
            return "failed to read STL file \"" + fileName_.ToShortString() + "\"!";
        });
    }
}

bool StlReader::ProvideNextTriangle(ThreePoints *outTriangle) {
    if (fileStream_) {
        (*fileStream_) >> normal_.x;
        (*fileStream_) >> normal_.y;
        (*fileStream_) >> normal_.z;
        for (int i = 0; i < 3; ++i) {
            Vector<float> &point = (*outTriangle)[i];
            (*fileStream_) >> point.x;
            (*fileStream_) >> point.y;
            (*fileStream_) >> point.z;
        }
        uint16_t dummy;
        ReadItem(fileStream_.get(), &dummy, 2);
        
        if (!fileStream_->ErrorState() && normal_.Valid() && outTriangle->Valid()) {
            ++numTrianglesProvided_;
            CheckFinished();
            return true;
        } else {
            fileStream_.reset();
            error_ = true;
            Log::Print(Log::Level::Error, this, [&]{
                return "error while reading STL file \"" + fileName_.ToShortString() + "\"!";
            });
        }
    }
    
    return false;
}

void StlReader::ProvideNormal(Vector<float> *outNormal) {
    *outNormal = normal_;
}

bool StlReader::TriangleError() {
    return error_;
}

void StlReader::CheckFinished() {
    if (numTrianglesProvided_ >= numTriangles_) {
        fileStream_.reset();
        Log::Print(Log::Level::Info, this, [&]{
            return "successfully read " + to_string(numTriangles_) + " triangles from STL file \""
                + fileName_.ToShortString() + "\"";
        });
    }
}

}    // Namespace IO.
}    // Namespace Vectoid.
