///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/Context.h>

#include <K/Core/Log.h>
#include <K/Core/StringTools.h>
#include <Vectoid/SceneGraph/Node.h>

using std::nullopt;
using std::optional;
using std::to_string;
using K::Core::Log;
using K::Core::StringTools;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Context::Context()
        : resources_{1} {
    // Nop.
}

Context::~Context() {
    Log::Print(Log::Level::Debug, this, [&]{ return "signing off..."; });

    int numLeaked { 0 };
    for (ResourceInfo &info : resources_.Iterate(0)) {
        if (info.resource) {
            ++numLeaked;
        }
    }

    if (numLeaked) {
        Log::Print(Log::Level::Error, this, [&]{ return "leaking " + to_string(numLeaked) + " OpenGL resources"; });
    } else {
        Log::Print(Log::Level::Debug, this, [&]{ return "not leaking any OpenGL resources"; });
    }
}

void Context::InitializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
}

void Context::ReleaseOpenGLResources() {
    Log::Print(Log::Level::Debug, this, [&]{ return "releasing OpenGL resources..."; });

    int numReleased { 0 };
    for (ResourceInfo &info : resources_.Iterate(0)) {
        if (Release(info)) {
            ++numReleased;
        }
    }

    for (int slot : resourceSlotsToRemove_) {
        resources_.Put(slot);
    }
    resourceSlotsToRemove_.clear();

    if (numReleased)  {
        Log::Print(Log::Level::Debug, this, [&]{ return "released " + to_string(numReleased) + " OpenGL resources"; });
    } else {
        Log::Print(Log::Level::Debug, this, [&]{ return "no OpenGL resources to release"; });
    }
}

void Context::ReleaseScheduledOpenGLResources() {
    int numReleased { 0 };
    for (int slot : resourceSlotsToRemove_) {
        if (Release(resources_.Item(slot))) {
            ++numReleased;
        }
        resources_.Put(slot);
    }
    resourceSlotsToRemove_.clear();

    if (numReleased) {
        Log::Print(Log::Level::Debug, this, [&]{ return "released " + to_string(numReleased) + " OpenGL resources"; });
    }
}

int Context::AddResourceSlot(Context::ResourceType type) {
    int slot;
    resources_.Get(0, slot) = ResourceInfo(type);
    return slot;
}

void Context::RemoveResourceSlot(int slot) {
    ResourceInfo &info { resources_.Item(slot) };
    if (info.resource) {
        resourceSlotsToRemove_.push_back(slot);
    } else {
        resources_.Put(slot);
    }
}

void Context::SetResource(int slot, GLuint resource) {
    ClearResource(slot);
    resources_.Item(slot).resource = resource;
    Log::Print(Log::Level::Debug, this, [&]{
        return "stored resource " + to_string(resource) + " into slot " + to_string(slot);
    });
}

optional<GLuint> Context::GetResource(int slot) {
    return resources_.Item(slot).resource;
}

void Context::ClearResource(int slot) {
    ResourceInfo &info { resources_.Item(slot) };
    if (info.resource) {
        int newSlot;
        resources_.Get(0, newSlot) = info;
        resourceSlotsToRemove_.push_back(newSlot);

        Log::Print(Log::Level::Debug, this, [&]{
            return "removed resource  " + to_string(*info.resource) + " from slot " + to_string(slot);
        });

        info.resource.reset();
    }
}

bool Context::Release(ResourceInfo &info) {
    if (info.resource) {
        switch (info.type) {
            case ResourceType::Vbo:
                glDeleteBuffers(1, &*info.resource);
                Log::Print(Log::Level::Debug, this, [&]{ return "deleted VBO " + to_string(*info.resource); });
                break;
            case ResourceType::Texture:
                glDeleteTextures(1, &*info.resource);
                Log::Print(Log::Level::Debug, this, [&]{ return "deleted texture " + to_string(*info.resource); });
                break;
            default:
                Log::Print(Log::Level::Error, this, [&]{
                    return "leaking OpenGL resource " + to_string(*info.resource) + " of unknown type "
                        + to_string(static_cast<int>(info.type));
                });
                break;
        }

        info.resource.reset();
        return true;
    } else {
        return false;
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
