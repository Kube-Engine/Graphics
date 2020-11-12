project(KubeGraphics)

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

get_filename_component(KubeGraphicsDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(KubeGraphicsSources
    ${KubeGraphicsDir}/VulkanFlags.hpp
    ${KubeGraphicsDir}/VulkanEnums.hpp
    ${KubeGraphicsDir}/Vulkan.hpp
    ${KubeGraphicsDir}/Vulkan.cpp

    ${KubeGraphicsDir}/VulkanHandle.hpp

    ${KubeGraphicsDir}/RendererObject.hpp

    ${KubeGraphicsDir}/Renderer.hpp
    ${KubeGraphicsDir}/Renderer.cpp

    ${KubeGraphicsDir}/Instance.hpp
    ${KubeGraphicsDir}/Instance.cpp

    ${KubeGraphicsDir}/Surface.hpp
    ${KubeGraphicsDir}/Surface.cpp

    ${KubeGraphicsDir}/PhysicalDevice.hpp
    ${KubeGraphicsDir}/PhysicalDevice.cpp

    ${KubeGraphicsDir}/QueueManager.hpp
    ${KubeGraphicsDir}/QueueManager.cpp

    ${KubeGraphicsDir}/LogicalDevice.hpp
    ${KubeGraphicsDir}/LogicalDevice.cpp

    ${KubeGraphicsDir}/Swapchain.hpp
    ${KubeGraphicsDir}/Swapchain.cpp

    ${KubeGraphicsDir}/Shader.hpp
    ${KubeGraphicsDir}/Shader.cpp

    ${KubeGraphicsDir}/RenderPass.hpp
    ${KubeGraphicsDir}/RenderPass.cpp

    ${KubeGraphicsDir}/PipelineLayout.hpp
    ${KubeGraphicsDir}/PipelineLayout.cpp
    ${KubeGraphicsDir}/PipelineLayoutModel.hpp

    ${KubeGraphicsDir}/Pipeline.hpp
    ${KubeGraphicsDir}/Pipeline.cpp

    ${KubeGraphicsDir}/PipelineManager.hpp
    ${KubeGraphicsDir}/PipelineManager.cpp

    ${KubeGraphicsDir}/Framebuffer.hpp
    ${KubeGraphicsDir}/Framebuffer.cpp
    ${KubeGraphicsDir}/FramebufferModel.hpp

    ${KubeGraphicsDir}/FramebufferManager.hpp
    ${KubeGraphicsDir}/FramebufferManager.cpp

    ${KubeGraphicsDir}/CommandPool.hpp
    ${KubeGraphicsDir}/CommandPool.cpp

    ${KubeGraphicsDir}/CommandPoolManager.hpp
    ${KubeGraphicsDir}/CommandPoolManager.cpp

    ${KubeGraphicsDir}/Semaphore.hpp
    ${KubeGraphicsDir}/Semaphore.cpp

    ${KubeGraphicsDir}/Fence.hpp
    ${KubeGraphicsDir}/Fence.cpp

    ${KubeGraphicsDir}/Buffer.hpp
    ${KubeGraphicsDir}/Buffer.cpp
    ${KubeGraphicsDir}/BufferModel.hpp

    ${KubeGraphicsDir}/Image.hpp
    ${KubeGraphicsDir}/Image.cpp
    ${KubeGraphicsDir}/ImageModel.hpp

    ${KubeGraphicsDir}/ImageView.hpp
    ${KubeGraphicsDir}/ImageView.cpp
    ${KubeGraphicsDir}/ImageViewModel.hpp

    ${KubeGraphicsDir}/MemoryAllocator.hpp
    ${KubeGraphicsDir}/MemoryAllocator.cpp
    ${KubeGraphicsDir}/MemoryAllocationModel.hpp
)

add_library(${PROJECT_NAME} ${KubeGraphicsSources})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    KubeCore
    Vulkan::Vulkan
    VulkanMemoryAllocator
    # glm
    SDL2
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${SDL2_INCLUDE_DIRS}
)

if(${KF_TESTS})
    include(${KubeGraphicsDir}/Tests/GraphicsTests.cmake)
endif()

if(${KF_BENCHMARKS})
    include(${KubeGraphicsDir}/Benchmarks/GraphicsBenchmarks.cmake)
endif()