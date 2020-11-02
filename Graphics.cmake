project(KubeGraphics)

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

get_filename_component(KubeGraphicsDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(KubeGraphicsSources
    ${KubeGraphicsDir}/Vulkan.hpp
    ${KubeGraphicsDir}/Vulkan.cpp
    ${KubeGraphicsDir}/RendererObject.hpp
    ${KubeGraphicsDir}/Renderer.hpp
    ${KubeGraphicsDir}/Renderer.cpp
    ${KubeGraphicsDir}/Instance.hpp
    ${KubeGraphicsDir}/Instance.cpp
    ${KubeGraphicsDir}/Surface.hpp
    ${KubeGraphicsDir}/Surface.cpp
    ${KubeGraphicsDir}/PhysicalDevice.hpp
    ${KubeGraphicsDir}/PhysicalDevice.cpp
    ${KubeGraphicsDir}/QueueHandler.hpp
    ${KubeGraphicsDir}/QueueHandler.cpp
    ${KubeGraphicsDir}/LogicalDevice.hpp
    ${KubeGraphicsDir}/LogicalDevice.cpp
    ${KubeGraphicsDir}/Swapchain.hpp
    ${KubeGraphicsDir}/Swapchain.cpp
    ${KubeGraphicsDir}/Shader.hpp
    ${KubeGraphicsDir}/Shader.cpp
    ${KubeGraphicsDir}/RenderPass.hpp
    ${KubeGraphicsDir}/RenderPass.cpp
    ${KubeGraphicsDir}/Pipeline.hpp
    ${KubeGraphicsDir}/Pipeline.cpp
    ${KubeGraphicsDir}/PipelinePool.hpp
    ${KubeGraphicsDir}/PipelinePool.cpp
    ${KubeGraphicsDir}/FramebufferHandler.hpp
    ${KubeGraphicsDir}/FramebufferHandler.cpp
    ${KubeGraphicsDir}/CommandPool.hpp
    ${KubeGraphicsDir}/CommandPool.cpp
    ${KubeGraphicsDir}/Drawer.hpp
    ${KubeGraphicsDir}/Drawer.cpp
    ${KubeGraphicsDir}/Semaphore.hpp
    ${KubeGraphicsDir}/Semaphore.cpp
    ${KubeGraphicsDir}/Fence.hpp
    ${KubeGraphicsDir}/Fence.cpp
    ${KubeGraphicsDir}/BufferPool.hpp
    ${KubeGraphicsDir}/BufferPool.cpp
    ${KubeGraphicsDir}/Buffer.hpp
    ${KubeGraphicsDir}/Buffer.cpp
    ${KubeGraphicsDir}/BufferModel.hpp
    ${KubeGraphicsDir}/MemoryAllocator.hpp
    ${KubeGraphicsDir}/MemoryAllocator.cpp
    ${KubeGraphicsDir}/MemoryAllocationModel.hpp
    ${KubeGraphicsDir}/MemoryAllocationModel.ipp
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

# target_compile_definitions(${PROJECT_NAME} PUBLIC KUBE_HAS_DYNAMIC_WINDOW_RESIZE)

if(${KF_TESTS})
    include(${KubeGraphicsDir}/Tests/GraphicsTests.cmake)
endif()

if(${KF_BENCHMARKS})
    include(${KubeGraphicsDir}/Benchmarks/GraphicsBenchmarks.cmake)
endif()