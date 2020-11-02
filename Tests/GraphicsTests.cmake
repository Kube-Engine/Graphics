project(KubeGraphicsTests)

get_filename_component(KubeGraphicsTestsDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(KubeGraphicsTestsSources
    ${KubeGraphicsTestsDir}/tests_Renderer.cpp
    ${KubeGraphicsTestsDir}/tests_MemoryAllocationModel.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${KubeGraphicsTestsSources})

add_test(NAME ${CMAKE_PROJECT_NAME} COMMAND ${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}
PUBLIC
    KubeGraphics
    GTest::GTest GTest::Main
)