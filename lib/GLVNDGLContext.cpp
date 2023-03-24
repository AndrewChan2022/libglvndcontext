//
//  main.cpp
//  myglx
//
//  Created by kai chen on 2/8/23.
//

#include    <stdio.h>
#include    <stdlib.h>
#include    <jni.h>

#ifdef __linux__

#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>


static const EGLint configAttribs[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_DEPTH_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
    EGL_NONE
};    

static const int pbufferWidth = 9;
static const int pbufferHeight = 9;

static const EGLint pbufferAttribs[] = {
    EGL_WIDTH, pbufferWidth,
    EGL_HEIGHT, pbufferHeight,
    EGL_NONE,
};

static EGLDisplay eglDpy;
static EGLSurface eglSurf;
static EGLContext eglCtx;

static bool createContext() {

    // 1. Initialize EGL
    eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("create display error %x\n",err);
        return false;
    }
    
    EGLint major, minor;
    eglInitialize(eglDpy, &major, &minor);
    if (err != EGL_SUCCESS) {
        printf("eglInitialize error %x\n",err);
        return false;
    }

    // 2. Select an appropriate configuration
    EGLint numConfigs;
    EGLConfig eglCfg;
    eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);

    err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("eglChooseConfig error: %x\n", err);
        return false;
    }

    // 3. Create a surface
    eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg, pbufferAttribs);

    err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("eglCreatePbufferSurface error: %x\n", err);
        return false;
    }    

    // 4. Bind the API
    eglBindAPI(EGL_OPENGL_API);

    err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("eglBindAPI error: %x\n", err);
        return false;
    }    

    // 5. Create a context and make it current
    eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT, NULL);

    err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("eglCreateContext error: %x\n", err);
        return false;
    }

    eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);
    err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("eglMakeCurrent error: %x\n", err);
        return false;
    }

    /////////////////////////////////////////////////
    // from now on use your OpenGL context

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("Backend OpenGL version: %d %d\n", major, minor);

    printf("eglCreateContext success\n");
    return true;
}

static bool makeContextCurrent() {
    eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);

    EGLint err = eglGetError();
    if (err != EGL_SUCCESS) {
        printf("eglMakeCurrent error: %x\n", err);
        return false;
    }

    return true;
}

static void destoryContext() {
    if (eglDpy != nullptr) {
        // release display and resources connected to it
        eglTerminate(eglDpy);
        eglDpy = nullptr;
        eglCtx = nullptr;
        eglSurf = nullptr;
        EGLint err = eglGetError();
        if (err != EGL_SUCCESS) {
            printf("eglTerminate error: %x\n", err);
        } else {
            printf("eglTerminate success\n");
        }
    }
}


class GLVNDContext final {
public:
    static GLVNDContext* shared() {
        static GLVNDContext s_GLVNDContext;
        return &s_GLVNDContext;
    }
    ~GLVNDContext() {
        if (m_success) {
            destoryContext();
        }
    }
    bool makeCurrent() {
        if (m_success) {
            return makeContextCurrent();
        }
        return false;
    }

private:
    GLVNDContext() {
        m_success = createContext();
    }

private:
    bool m_success{true};
};

extern "C"
JNIEXPORT jboolean JNICALL
Java_project_android_fastimage_filter_soul_SoulRenderLinuxJNI_setLinuxGLContext(JNIEnv *env) {
    //return GLVNDContext::shared()->makeCurrent();
    return true;
}

extern "C" 
bool test_libglvndglcontext() {
    return GLVNDContext::shared()->makeCurrent();
}

#else

extern "C"
JNIEXPORT jboolean JNICALL
Java_project_android_fastimage_filter_soul_SoulRenderLinuxJNI_setLinuxGLContext(JNIEnv *env) {
    return true;
}

extern "C" 
bool test_libglvndglcontext() {
    return true;
}

#endif