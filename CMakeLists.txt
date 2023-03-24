cmake_minimum_required(VERSION 3.1)

#add_definitions(-DEXCLUDE_LOG_MODULE)
#add_compile_definitions(MG_ENABLE_OPENSSL=1)

# cpp version (be different for other platform, TODO).
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_NAME glvndcontext)
project(${LIB_NAME})

################## java begin
set(NEED_JNI TRUE)
if (${NEED_JNI})
    find_package(Java REQUIRED COMPONENTS Development)
    if(NOT DEFINED ENV{JAVA_HOME})
        message("please export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-xx.x.x.x.jdk/Contents/Home")
        message( FATAL_ERROR "please export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-xx.x.x.x.jdk/Contents/Home" )
    endif()
    set(JAVA_HOME $ENV{JAVA_HOME})
    message("JAVA_HOME = ${JAVA_HOME}")
    message("JAVA_HOME = $ENV{JAVA_HOME}")
    message("Java_JAVA_EXECUTABLE = ${Java_JAVA_EXECUTABLE}")
    message("Java_JAVAC_EXECUTABLE = ${Java_JAVAC_EXECUTABLE}")
    message("Java_JAVAH_EXECUTABLE = ${Java_JAVAH_EXECUTABLE}")
    message("Java_JAVADOC_EXECUTABLE = ${Java_JAVADOC_EXECUTABLE}")
    message("Java_VERSION_STRING = ${Java_VERSION_STRING}")
    message("Java_VERSION = ${Java_VERSION}")

    set(JAVA_AWT_LIBRARY NotNeeded)
    set(JAVA_JVM_LIBRARY NotNeeded)
    set(JAVA_INCLUDE_PATH "$ENV{JAVA_HOME}/include")
    find_path(JAVA_INCLUDE_PATH2 NAMES jni_md.h jniport.h
            PATHS ${JAVA_INCLUDE_PATH}
            ${JAVA_INCLUDE_PATH}/darwin
            ${JAVA_INCLUDE_PATH}/win32
            ${JAVA_INCLUDE_PATH}/linux
            )
    set(JAVA_AWT_INCLUDE_PATH "$ENV{JAVA_HOME}/include")
    #set(JAVA_AWT_INCLUDE_PATH NotNeeded)
    find_package(JNI REQUIRED)

    if (JNI_FOUND)
        # -- JNI_INCLUDE_DIRS=C:/Program Files/Java/jdk1.8.0_191/include;C:/Program Files/Java/jdk1.8.0_191/include/win32;C:/Program Files/Java/jdk1.8.0_191/include
        # -- JNI_LIBRARIES=C:/Program Files/Java/jdk1.8.0_191/lib/jawt.lib;C:/Program Files/Java/jdk1.8.0_191/lib/jvm.lib
        message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
        message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
    endif()
endif() # NEED_JNI
################## java end


################## src
file(GLOB mysrc "./lib/GLVNDGLContext.cpp")

include_directories(./lib)

include_directories(${JNI_INCLUDE_DIRS})

################## lib
add_library(${LIB_NAME} SHARED
    ${mysrc}
)


################## link

if(APPLE)
else()
    find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL GLX)
    message(STATUS "OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
    target_link_libraries(${LIB_NAME} PRIVATE OpenGL::OpenGL OpenGL::EGL OpenGL::GLX)
endif()

########### other prj
add_subdirectory(test)
