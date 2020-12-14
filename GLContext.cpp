#ifdef LINUX

#define EGL_EGLEXT_PROTOTYPES
#include "GLContext.h"

GLContext::GLContext() {
    eglDpy = EGL_NO_DISPLAY;
    eglCtx = EGL_NO_CONTEXT;
    eglSurf = EGL_NO_SURFACE;
}

GLContext::~GLContext() {
        destoryGL();
}

void GLContext::initGLContext() {
    const EGLint configAttribs[] = {
       EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
       EGL_BLUE_SIZE, 8,
       EGL_GREEN_SIZE, 8,
       EGL_RED_SIZE, 8,
       EGL_DEPTH_SIZE, 8,
       EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
       EGL_NONE
    };

    const int pbufferWidth = 9;
    const int pbufferHeight = 9;

    const EGLint pbufferAttribs[] = {
     EGL_WIDTH, pbufferWidth,
     EGL_HEIGHT, pbufferHeight,
     EGL_NONE,
    };
    static const int MAX_DEVICES = 4;
    EGLDeviceEXT eglDevs[MAX_DEVICES];
    EGLint numDevices;

    PFNEGLQUERYDEVICESEXTPROC eglQueryDevicesEXT =
      (PFNEGLQUERYDEVICESEXTPROC)
      eglGetProcAddress("eglQueryDevicesEXT");

    eglQueryDevicesEXT(MAX_DEVICES, eglDevs, &numDevices);

    printf("Detected %d devices\n", numDevices);

    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
        (PFNEGLGETPLATFORMDISPLAYEXTPROC)
        eglGetProcAddress("eglGetPlatformDisplayEXT");

    eglDpy = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT,
                                        eglDevs[0], 0);
     if (eglDpy == nullptr) {
          fprintf(stderr, "missing support for GLX_ARB_create");
     }
    EGLint major, minor;
    eglInitialize(eglDpy, &major, &minor);
    EGLint numConfigs;
    EGLConfig eglCfg;
    eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);
    eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg,
                                           pbufferAttribs);
    eglBindAPI(EGL_OPENGL_API);
    eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT,
                                   nullptr);
    if (eglCfg == nullptr || eglSurf == nullptr|| eglCtx == nullptr) {
      return;
    }

    eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);
}

void GLContext::destoryGL() {
    fprintf( stderr, "Destory OpenGL...\n" );
    if (eglDpy != EGL_NO_DISPLAY && eglCtx == EGL_NO_CONTEXT) {
        if (eglSurf != EGL_NO_SURFACE) {
            if (!eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx)) {
                  fprintf(stderr, "Release egl fail !!!");
            }
            eglDestroySurface(eglDpy, eglSurf);
        }
        eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);
        eglDestroyContext(eglDpy, eglCtx);
        eglTerminate(eglDpy);
        eglDpy = EGL_NO_DISPLAY;
        eglCtx = EGL_NO_CONTEXT;
        eglSurf = EGL_NO_SURFACE;
    }
}

#endif

