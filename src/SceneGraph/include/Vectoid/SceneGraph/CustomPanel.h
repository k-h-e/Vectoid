#ifndef VECTOID_SCENEGRAPH_CUSTOMPANEL_H_
#define VECTOID_SCENEGRAPH_CUSTOMPANEL_H_

#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace SceneGraph {

//! Custom panel geometry.
class CustomPanel : public Geometry {
  public:
    CustomPanel(const std::shared_ptr<Context> &context, float width, float height);
    CustomPanel()                                    = delete;
    CustomPanel(const CustomPanel &other)            = delete;
    CustomPanel &operator=(const CustomPanel &other) = delete;
    CustomPanel(CustomPanel &&other)                 = delete;
    CustomPanel &operator=(CustomPanel &&other)      = delete;
    ~CustomPanel()                                   = default;
    
    float Width() const;
    float Height() const;
    //! Sets the panel's background color, including its alpha channel.
    void SetBackgroundColor(const Vectoid::Core::Vector<float> &color, float alpha);
    
  protected:
    float                        width_;
    float                        height_;
    Vectoid::Core::Vector<float> backgroundColor_;
    float                        backgroundAlpha_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_CUSTOMPANEL_H_
