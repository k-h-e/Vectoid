///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/SimpleGeometryRenderer.h>

#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/SimpleGeometry.h>
#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;
using K::Core::Log;
using namespace Vectoid::SceneGraph;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<Vectoid::SceneGraph::Vulkan::Context> &context,
                                               const shared_ptr<SimpleGeometry> &geometry)
        : SceneGraph::SimpleGeometryRenderer(geometry),
          context_(context),
          haveResources_(false) {
    createResources();
}

SimpleGeometryRenderer::~SimpleGeometryRenderer() {
    freeResources();
}

void SimpleGeometryRenderer::Render() {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan::SimpleGeometryRenderer::Render()"; });
   
    if (haveResources_) {
        context_->ApplyObjectTransform();
   
        const VkDeviceSize offsets[1] = { 0 };
        vkCmdBindVertexBuffers(context_->commandBuffer, 0, 1, &vertexBuffer_.buffer, offsets);
        vkCmdDraw(context_->commandBuffer, geometry_->numTriangles_ * 3, 1, 0, 0);
    }
}

void SimpleGeometryRenderer::GetVertexInputInfo(VkVertexInputBindingDescription *binding,
                                                VkVertexInputAttributeDescription *attributes) {
    *binding = {};
    binding->binding = 0;
    binding->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    binding->stride = 32;
       
    attributes[0] = {};
    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    attributes[0].offset = 0;
    attributes[1] = {};
    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    attributes[1].offset = 16;
}

void SimpleGeometryRenderer::createResources() {
    if (!context_->Operative()) {
        return;
    }
    
    /*
    struct Vertex {
        float posX, posY, posZ, posW;  // Position data
        float r, g, b, a;              // Color
    };
    #define XYZ1(_x_, _y_, _z_) (_x_), (_y_), (_z_), 1.f
    static const Vertex solidFaceColorsData[] = {
        // red face
        {XYZ1(-1, -1, 1), XYZ1(1.f, 0.f, 0.f)},
        {XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 0.f)},
        {XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 0.f)},
        {XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 0.f)},
        {XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 0.f)},
        {XYZ1(1, 1, 1), XYZ1(1.f, 0.f, 0.f)},
        // green face
        {XYZ1(-1, -1, -1), XYZ1(0.f, 1.f, 0.f)},
        {XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 0.f)},
        {XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f)},
        {XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f)},
        {XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 0.f)},
        {XYZ1(1, 1, -1), XYZ1(0.f, 1.f, 0.f)},
        // blue face
        {XYZ1(-1, 1, 1), XYZ1(0.f, 0.f, 1.f)},
        {XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f)},
        {XYZ1(-1, 1, -1), XYZ1(0.f, 0.f, 1.f)},
        {XYZ1(-1, 1, -1), XYZ1(0.f, 0.f, 1.f)},
        {XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f)},
        {XYZ1(-1, -1, -1), XYZ1(0.f, 0.f, 1.f)},
        // yellow face
        {XYZ1(1, 1, 1), XYZ1(1.f, 1.f, 0.f)},
        {XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f)},
        {XYZ1(1, -1, 1), XYZ1(1.f, 1.f, 0.f)},
        {XYZ1(1, -1, 1), XYZ1(1.f, 1.f, 0.f)},
        {XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f)},
        {XYZ1(1, -1, -1), XYZ1(1.f, 1.f, 0.f)},
        // magenta face
        {XYZ1(1, 1, 1), XYZ1(1.f, 0.f, 1.f)},
        {XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 1.f)},
        {XYZ1(1, 1, -1), XYZ1(1.f, 0.f, 1.f)},
        {XYZ1(1, 1, -1), XYZ1(1.f, 0.f, 1.f)},
        {XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 1.f)},
        {XYZ1(-1, 1, -1), XYZ1(1.f, 0.f, 1.f)},
        // cyan face
        {XYZ1(1, -1, 1), XYZ1(0.f, 1.f, 1.f)},
        {XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 1.f)},
        {XYZ1(-1, -1, 1), XYZ1(0.f, 1.f, 1.f)},
        {XYZ1(-1, -1, 1), XYZ1(0.f, 1.f, 1.f)},
        {XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 1.f)},
        {XYZ1(-1, -1, -1), XYZ1(0.f, 1.f, 1.f)},
    };
    */
    
    vector<float> buffer;
    for (int i = 0; i < geometry_->numTriangles_ * 3; ++i) {
        buffer.push_back(geometry_->vertexArray_[i*3]);
        buffer.push_back(geometry_->vertexArray_[i*3 + 1]);
        buffer.push_back(geometry_->vertexArray_[i*3 + 2]);
        buffer.push_back(1.0f);
        buffer.push_back(geometry_->colorArray_[i*4]);
        buffer.push_back(geometry_->colorArray_[i*4 + 1]);
        buffer.push_back(geometry_->colorArray_[i*4 + 2]);
        buffer.push_back(1.0f);
    }
    
    VkBufferCreateInfo vertexBufferInfo = {};
    vertexBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    vertexBufferInfo.pNext = nullptr;
    vertexBufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    vertexBufferInfo.size = buffer.size() * sizeof(float);
    vertexBufferInfo.queueFamilyIndexCount = 0;
    vertexBufferInfo.pQueueFamilyIndices = nullptr;
    vertexBufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    vertexBufferInfo.flags = 0;
    if (vkCreateBuffer(context_->device, &vertexBufferInfo, nullptr, &vertexBuffer_.buffer) != VK_SUCCESS) {
        return;
    }
    
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(context_->device, vertexBuffer_.buffer, &memoryRequirements);

    VkMemoryAllocateInfo memoryInfo = {};
    memoryInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryInfo.pNext = nullptr;
    memoryInfo.memoryTypeIndex = 0;
    memoryInfo.allocationSize = memoryRequirements.size;
    if (!context_->GetMemoryIndex(memoryRequirements.memoryTypeBits,
                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                  &memoryInfo.memoryTypeIndex)) {
        return;
    }
    if (vkAllocateMemory(context_->device, &memoryInfo, nullptr, &vertexBuffer_.memory) != VK_SUCCESS) {
        return;
    }

    uint8_t *mapped;
    if (vkMapMemory(context_->device, vertexBuffer_.memory, 0, memoryRequirements.size, 0, (void **)&mapped)
            != VK_SUCCESS) {
        return;
    }
    memcpy(mapped, buffer.data(), buffer.size() * sizeof(float));
    vkUnmapMemory(context_->device, vertexBuffer_.memory);

    if (vkBindBufferMemory(context_->device, vertexBuffer_.buffer, vertexBuffer_.memory, 0) != VK_SUCCESS) {
        return;
    }
    
    haveResources_ = true;
    
    Log::Print(Log::Level::Debug, this, []{ return "vertex buffer created"; });
}

void SimpleGeometryRenderer::freeResources() {
    if (vertexBuffer_.buffer != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, this, []{ return "freeing vertex buffer"; });
        vkDestroyBuffer(context_->device, vertexBuffer_.buffer, nullptr);
        vertexBuffer_.buffer = VK_NULL_HANDLE;
    }
    if (vertexBuffer_.memory != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, this, []{ return "freeing vertex buffer memory"; });
        vkFreeMemory(context_->device, vertexBuffer_.memory, nullptr);
        vertexBuffer_.memory = VK_NULL_HANDLE;
    }
    vertexBuffer_ = Vectoid::SceneGraph::Vulkan::BufferInfo();
    
    haveResources_ = false;
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
