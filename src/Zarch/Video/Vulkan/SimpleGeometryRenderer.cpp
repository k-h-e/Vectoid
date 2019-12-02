#include <kxm/Zarch/Video/Vulkan/SimpleGeometryRenderer.h>

#include <kxm/Core/logging.h>
#include <kxm/Vectoid/Vulkan/Context.h>
#include <kxm/Zarch/SimpleGeometry.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Vulkan {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<Vectoid::Vulkan::Context> &context,
                                               const shared_ptr<SimpleGeometry> &geometry)
        : Video::SimpleGeometryRenderer(geometry),
          context_(context) {

}

void SimpleGeometryRenderer::Render() {
    Core::Log().Stream() << "Vulkan::SimpleGeometryRenderer::Render()" << endl;
    
    const VkDeviceSize offsets[1] = { 0 };
    vkCmdBindVertexBuffers(context_->commandBuffer, 0, 1, &context_->vertexBuffer.buffer, offsets);
    vkCmdDraw(context_->commandBuffer, 12 * 3, 1, 0, 0);
}

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

