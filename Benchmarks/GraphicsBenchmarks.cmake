project(KubeGraphicsBenchmarks)

get_filename_component(KubeGraphicsBenchmarksDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(KubeGraphicsBenchmarksSources
    ${KubeGraphicsBenchmarksDir}/Main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${KubeGraphicsBenchmarksSources})

target_link_libraries(${CMAKE_PROJECT_NAME}
PUBLIC
    KubeGraphics
    benchmark::benchmark
)