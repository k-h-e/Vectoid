#include <kxm/Vectoid/Vulkan/CoordSys.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <kxm/Core/logging.h>
#include <kxm/Vectoid/Vulkan/Context.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : Vectoid::CoordSys(),
          context_(context) {
    // Nop.
}

void CoordSys::Render() {
    Core::Log().Stream() << "Vulkan::CoordSys::Render()" << endl;
    
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(-5, 3, -10),    // Camera is at (-5 ,3, -10), in world space.
                                       glm::vec3(0, 0, 0),       // Camera looks at the origin.
                                       glm::vec3(0, -1, 0));     // Head is up (set to (0, -1, 0) to look upside-down).

    static float angle = 0.0f;
    angle += 1.0f;
    if (angle >= 360.0f) {
       angle -= 360.0f;
    }
    Transform t(YAxis, angle);
    glm::mat4 modelMatrix = glm::mat4(
       t.MatrixElements()[0], t.MatrixElements()[4], t.MatrixElements()[ 8], t.MatrixElements()[12],
       t.MatrixElements()[1], t.MatrixElements()[5], t.MatrixElements()[ 9], t.MatrixElements()[13],
       t.MatrixElements()[2], t.MatrixElements()[6], t.MatrixElements()[10], t.MatrixElements()[14],
       t.MatrixElements()[3], t.MatrixElements()[7], t.MatrixElements()[11], t.MatrixElements()[15]);

    glm::mat4 clippingMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                        0.0f,-1.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f, 0.5f, 0.0f,
                                        0.0f, 0.0f, 0.5f, 1.0f);    // Vulkan clip space has inverted Y and half Z.
    glm::mat4 modelViewProjectionMatrix = clippingMatrix * projectionMatrix * viewMatrix * modelMatrix;
    vkCmdPushConstants(context_->commandBuffer, context_->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                      sizeof(modelViewProjectionMatrix), &modelViewProjectionMatrix);
                   
    
    Vectoid::CoordSys::Render();
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
