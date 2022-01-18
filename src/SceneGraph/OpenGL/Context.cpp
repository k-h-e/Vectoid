#include <Vectoid/SceneGraph/OpenGL/Context.h>

#include <K/Core/Log.h>
#include <K/Core/StringTools.h>
#include <Vectoid/SceneGraph/Node.h>

using std::to_string;
using K::Core::Log;
using K::Core::StringTools;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Context::Context() {
    // Nop.
}

Context::~Context() {
    Log::Print(Log::Level::Debug, this, [&]{ return "signing off..."; });

    int numNodes = 0;
    for (Node *node : nodes_.Iterate(0)) {
        node->DropGraphicsResources();
        ++numNodes;
    }

    if (numNodes) {
        Log::Print(Log::Level::Error, this, [&]{ return to_string(numNodes) + " left-over scene graph nodes"; });
    } else {
        Log::Print(Log::Level::Debug, this, [&]{ return "no left-over scene graph nodes"; });
    }

    bool resourcesLeaked = false;
    if (!vbosToRelease_.empty()) {
        resourcesLeaked = true;
        Log::Print(Log::Level::Error, this, [&]{
            return "leaking " + to_string(vbosToRelease_.size()) + " VBOs";
        });
    }

    if (!resourcesLeaked) {
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

    int numNodes = 0;
    for (Node *node : nodes_.Iterate(0)) {
        node->DropGraphicsResources();
        ++numNodes;
    }
    Log::Print(Log::Level::Debug, this, [&]{
        return "asked " + to_string(numNodes) + " scene graph nodes to drop their OpenGL resources";
    });

    int numReleased = ReleaseScheduledOpenGLResources();
    if (numReleased)  {
        Log::Print(Log::Level::Debug, this, [&]{ return "released " + to_string(numReleased) + " OpenGL resources"; });
    } else {
        Log::Print(Log::Level::Debug, this, [&]{ return "no OpenGL resources to release"; });
    }
}

int Context::ReleaseScheduledOpenGLResources() {
    int numReleased = 0;

    for (GLuint vbo : vbosToRelease_) {
        glDeleteBuffers(1, &vbo);
        ++numReleased;
        Log::Print(Log::Level::Debug, this, [&]{ return "deleted VBO " + to_string(vbo); });
    }
    vbosToRelease_.clear();

    for (GLuint texture : texturesToRelease_) {
        glDeleteTextures(1, &texture);
        ++numReleased;
        Log::Print(Log::Level::Debug, this, [&]{ return "deleted texture " + to_string(texture); });
    }
    texturesToRelease_.clear();

    return numReleased;
}

void Context::ScheduleTextureForRelease(GLuint texture, Node *node) {
    texturesToRelease_.push_back(texture);
    Log::Print(Log::Level::Debug, this, [&]{
        return "Texture " + to_string(texture) + " scheduled for release by a "
            + StringTools::GetCleanClassName(node, 1) + " node";
    });
}

void Context::ScheduleVBOForRelease(GLuint vbo, Node *node) {
    vbosToRelease_.push_back(vbo);
    Log::Print(Log::Level::Debug, this, [&]{
        return "VBO " + to_string(vbo) + " scheduled for release by a " + StringTools::GetCleanClassName(node, 1)
            + " node";
    });
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
