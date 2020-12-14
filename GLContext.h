#ifndef GLContext_h
#define GLContext_h

#include <stdio.h>


class GLContext {
public:
    GLContext();
    ~GLContext();
    void initGLContext();
    void destoryGL();
    
private:
    EGLDisplay  eglDpy;
    EGLContext eglCtx;
    EGLSurface eglSurf;
};

#endif /* GLContext_hpp */
