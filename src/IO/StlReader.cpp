#include <Vectoid/IO/StlReader.h>

#include <K/Core/BinaryReader.h>
#include <K/Core/IOOperations.h>
#include <K/Core/Log.h>
#include <K/IO/File.h>
#include <K/IO/StreamBuffer.h>
#include <Vectoid/Core/ThreePoints.h>

using std::string;
using std::to_string;
using K::Core::BinaryReader;
using K::Core::Log;
using K::IO::File;
using K::IO::StreamBuffer;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace IO {

StlReader::StlReader(const string &fileName)
        : fileName_{fileName},
          error_{false},
          numTriangles_{0u},
          numTrianglesProvided_{0u} {
    // Nop.
}

void StlReader::PrepareToProvideTriangles() {
    auto file   = make_shared<File>(fileName_, File::AccessMode::ReadOnly, false);
    auto buffer = make_shared<StreamBuffer>(file, File::AccessMode::ReadOnly, 2048);
    reader_     = make_shared<BinaryReader>(buffer);
    
    const int headerSize = 80;
    uint8_t header[headerSize];
    reader_->ReadItem(&header, headerSize);
    (*reader_) >> numTriangles_;
    if (!reader_->ReadFailed()) {
        numTrianglesProvided_ = 0u;
        normal_               = Vector<float>(0.0f, 1.0f, 0.0f);
        error_                = false;
        Log::Print(Log::Level::Info, this, [&]{
            return "reading STL file \"" + fileName_ + "\" with " + to_string(numTriangles_) + " triangles";
        });
        CheckFinished();
    } else {
        reader_.reset();
        numTriangles_         = 0u;
        numTrianglesProvided_ = 0u;
        error_                = true;
        Log::Print(Log::Level::Error, this, [&]{
            return "failed to read STL file \"" + fileName_ + "\"!";
        });
    }
}

bool StlReader::ProvideNextTriangle(ThreePoints *outTriangle) {
    if (reader_) {
        (*reader_) >> normal_.x;
        (*reader_) >> normal_.y;
        (*reader_) >> normal_.z;
        for (int i = 0; i < 3; ++i) {
            Vector<float> &point = (*outTriangle)[i];
            (*reader_) >> point.x;
            (*reader_) >> point.y;
            (*reader_) >> point.z;
        }
        uint16_t dummy;
        reader_->ReadItem(&dummy, 2);
        
        if (!reader_->ReadFailed() && normal_.Valid() && outTriangle->Valid()) {
            ++numTrianglesProvided_;
            CheckFinished();
            return true;
        } else {
            reader_.reset();
            error_ = true;
            Log::Print(Log::Level::Error, this, [&]{
                return "error while reading STL file \"" + fileName_ + "\"!";
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
        reader_.reset();
        Log::Print(Log::Level::Info, this, [&]{
            return "successfully read " + to_string(numTriangles_) + " triangles from STL file \""
                + fileName_ + "\"";
        });
    }
}

}    // Namespace IO.
}    // Namespace Vectoid.
