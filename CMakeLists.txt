# CMakeList.txt : CMake project for ${PROJECT_NAME}, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("StereoX")

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}" )


include(FetchContent)
find_package(Qt6 REQUIRED COMPONENTS 3DCore 3DExtras 3DInput 3DRender Core Gui)

set(QT_DIR "${Qt6_DIR}")

set (BUILD_EXAMPLES OFF CACHE INTERNAL "Turn off examples")
FetchContent_Declare(
  ads
  GIT_REPOSITORY https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System.git
)
FetchContent_MakeAvailable(ads)

qt_add_executable(${PROJECT_NAME})

# Add source to this project's executable.
target_sources(${PROJECT_NAME} 
    PRIVATE
        "src/EntryMain.cpp" 
        "src/Scene.cpp"
        "src/TransformController.cpp"
        "src/RenderGraph.cpp"
        "src/App.cpp" "src/MainWindow.cpp"
        "include/pch.h" 
    PUBLIC
        "include/App.h" 
        "include/Scene.h"  
        "include/TransformController.h"    
        "include/Camera.h"
        "include/RenderGraph.h"
        "include/MainWindow.h"
        "include/SceneControl.h"
 "src/SceneControl.cpp" "include/CameraController.h" "src/CameraController.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 23
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_precompile_headers(${PROJECT_NAME} PUBLIC "include/pch.h")
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::3DCore
    Qt::3DExtras
    Qt::3DInput
    Qt::3DRender
    Qt::Core
    Qt::Gui

    ads::qtadvanceddocking
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ads::qtadvanceddocking>  $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)

#if(WIN32)
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#      COMMAND_EXPAND_LISTS
#    )
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND "${CMAKE_COMMAND}" -E
#            env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
#                --verbose 0
#                --no-compiler-runtime
#                \"$<TARGET_FILE:${PROJECT_NAME}>\"
#        COMMENT "Deploying Qt..."
#    )
#endif(WIN32)
#qt6_add_resources(${PROJECT_NAME} "resources"
#    PREFIX
#        "/"
#    FILES
#        "main.qml"
#)


install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "examples"
    BUNDLE DESTINATION "examples"
    LIBRARY DESTINATION "examples"
)
