cmake_minimum_required(VERSION 3.1)

#add_definitions(-DEXCLUDE_LOG_MODULE)
#add_compile_definitions(MG_ENABLE_OPENSSL=1)

# cpp version (be different for other platform, TODO).
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(testglvndcontext)

################## src
file(GLOB mysrc "./src/main.cpp")

# add include directory
include_directories(./src)


################## include
# add all source files
add_executable(testglvndcontext  
    ${mysrc}
)

################## link

if(APPLE)

    target_link_libraries(testglvndcontext PRIVATE glvndcontext)

else()

    find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL GLX)
    message(STATUS "OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
    # include
    #include_directories( ${OPENGL_INCLUDE_DIR} )
    # lib
    target_link_libraries(testglvndcontext PRIVATE OpenGL::OpenGL OpenGL::EGL OpenGL::GLX glvndcontext)

endif()