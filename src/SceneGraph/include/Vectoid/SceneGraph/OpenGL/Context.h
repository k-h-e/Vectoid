///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_
#define VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_

#include <optional>
#include <K/Core/ReusableItems.h>
#include <Vectoid/SceneGraph/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Holds context information for the <c>OpenGL</c> renderer.
class Context : public SceneGraph::Context {
  public:
    enum class ResourceType { VBO,
                              Texture };

    Context();
    Context(const Context &other)            = delete;
    Context &operator=(const Context &other) = delete;
    Context(Context &&other)                 = delete;
    Context &operator=(Context &&other)      = delete;
    ~Context();

    //! Initializes the <c>OpenGL</c> state to our definition of "neutral".
    /*!
     *  Interacts with the underlying graphics system (<c>OpenGL</c>).
     */
    void InitializeGL();
    //! Releases the <c>OpenGL</c> resourses currently maintained by all existing scene graph nodes.
    /*!
     *  Interacts with the underlying graphics system (<c>OpenGL</c>).
     */
    void ReleaseOpenGLResources();
    //! Releases the <c>OpenGL</c> resources currently registered with the context for deferred release.
    /*!
     *  Interacts with the underlying graphics system (<c>OpenGL</c>).
     */
    void ReleaseScheduledOpenGLResources();
    //! Adds a slot for maintaining an <c>OpenGL</c> resource of the specified type.
    /*!
     *  Does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    int AddResourceSlot(ResourceType type);
    //! Removes the specified resource slot.
    /*!
     *  If the slot contains a resource, the context will release that resource later at an appropriate time.
     *
     *  The method does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    void RemoveResourceSlot(int slot);
    //! Stores the specified resource in the specified slot.
    /*!
     *  If the slot has already contained a resource, the context will release that old resource later at an appropriate
     *  time.
     *
     *  The method does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    void SetResource(int slot, GLuint resource);
    //! Returns the resource currently stored in the specified slot, or <c>nullopt</c> in case the slot does currently
    //! not contain any resource.
    /*!
     *  Does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    std::optional<GLuint> GetResource(int slot);
    //! Clears the specified resource slot.
    /*!
     *  If the slot has contained a resource, the context will release that resource later at an appropriate time.
     *
     *  The method does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    void ClearResource(int slot);

  private:
    struct ResourceInfo {
        ResourceType          type;
        std::optional<GLuint> resource;

        ResourceInfo() : type(ResourceType::VBO) {}
        ResourceInfo(ResourceType aType) : type(aType) {}
        ResourceInfo(const ResourceInfo &other)            = default;
        ResourceInfo &operator=(const ResourceInfo &other) = default;
        ResourceInfo(ResourceInfo &&other)                 = default;
        ResourceInfo &operator=(ResourceInfo &&other)      = default;
    };

    bool Release(ResourceInfo *info);

    K::Core::ReusableItems<ResourceInfo> resources_;
    std::vector<int>                     resourceSlotsToRemove_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_
