project(KubeRenderer)

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

set(KubeRendererDir ${KubeSourcesDir}/Renderer)

set(KubeRendererSources
    ${KubeRendererDir}/Vulkan.hpp
    ${KubeRendererDir}/Vulkan.cpp
    ${KubeRendererDir}/RendererObject.hpp
    ${KubeRendererDir}/Renderer.hpp
    ${KubeRendererDir}/Renderer.cpp
    ${KubeRendererDir}/Instance.hpp
    ${KubeRendererDir}/Instance.cpp
    ${KubeRendererDir}/Surface.hpp
    ${KubeRendererDir}/Surface.cpp
    ${KubeRendererDir}/PhysicalDevice.hpp
    ${KubeRendererDir}/PhysicalDevice.cpp
    ${KubeRendererDir}/QueueHandler.hpp
    ${KubeRendererDir}/QueueHandler.cpp
    ${KubeRendererDir}/LogicalDevice.hpp
    ${KubeRendererDir}/LogicalDevice.cpp
    ${KubeRendererDir}/Swapchain.hpp
    ${KubeRendererDir}/Swapchain.cpp
    ${KubeRendererDir}/Shader.hpp
    ${KubeRendererDir}/Shader.cpp
    ${KubeRendererDir}/RenderPass.hpp
    ${KubeRendererDir}/RenderPass.cpp
    ${KubeRendererDir}/Pipeline.hpp
    ${KubeRendererDir}/Pipeline.cpp
    ${KubeRendererDir}/PipelinePool.hpp
    ${KubeRendererDir}/PipelinePool.cpp
    ${KubeRendererDir}/FramebufferHandler.hpp
    ${KubeRendererDir}/FramebufferHandler.cpp
    ${KubeRendererDir}/CommandPool.hpp
    ${KubeRendererDir}/CommandPool.cpp
    ${KubeRendererDir}/Drawer.hpp
    ${KubeRendererDir}/Drawer.cpp
    ${KubeRendererDir}/Semaphore.hpp
    ${KubeRendererDir}/Semaphore.cpp
    ${KubeRendererDir}/Fence.hpp
    ${KubeRendererDir}/Fence.cpp
    ${KubeRendererDir}/BufferPool.hpp
    ${KubeRendererDir}/BufferPool.cpp
    ${KubeRendererDir}/Buffer.hpp
    ${KubeRendererDir}/Buffer.cpp
    ${KubeRendererDir}/BufferModel.hpp
)

add_library(${PROJECT_NAME} ${KubeRendererSources})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    KubeCore
    Vulkan::Vulkan
    SDL2
    # VulkanMemoryAllocator
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${SDL2_INCLUDE_DIRS}
)

# target_compile_definitions(${PROJECT_NAME} PUBLIC KUBE_NO_DYNAMIC_RESIZE)

if (${KUBE_TESTS})
    include(${KubeRendererDir}/Tests/RendererTests.cmake)
endif ()