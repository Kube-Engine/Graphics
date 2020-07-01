project(KubeGraphics)

get_filename_component(KubeGraphicsDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(KubeGraphicsSources
    ${KubeGraphicsDir}/Dummy.cpp
)

add_library(${PROJECT_NAME} ${KubeGraphicsSources})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    KubeCore
)

if(${KF_TESTS})
    include(${KubeGraphicsDir}/Tests/GraphicsTests.cmake)
endif()

if(${KF_BENCHMARKS})
    include(${KubeGraphicsDir}/Benchmarks/GraphicsBenchmarks.cmake)
endif()