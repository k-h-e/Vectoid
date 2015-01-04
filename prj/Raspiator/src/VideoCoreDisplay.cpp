#include "VideoCoreDisplay.h"

#include <cassert>
#include <EGL/eglext.h>
#include <bcm_host.h>


namespace Raspiator {

VideoCoreDisplay::VideoCoreDisplay() {
    bcm_host_init();
    
    display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(display_ != EGL_NO_DISPLAY);
    EGLBoolean result = eglInitialize(display_, nullptr, nullptr);
    assert(result);
   
    const EGLint attributeList[] = {
       EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 24,
       EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };
    EGLConfig config;
    EGLint    numConfig;
    result = eglChooseConfig(display_, attributeList, &config, 1, &numConfig);
    assert(result);
    context_ = eglCreateContext(display_, config, EGL_NO_CONTEXT, nullptr);
    assert(context_ != EGL_NO_CONTEXT);
   
    int32_t success = graphics_get_display_size(0, &screenWidth_, &screenHeight_);
    assert(success >= 0);
    VC_RECT_T dstRect;
    dstRect.x      = 0;
    dstRect.y      = 0;
    dstRect.width  = screenWidth_;
    dstRect.height = screenHeight_;   
    VC_RECT_T srcRect;
    srcRect.x      = 0;
    srcRect.y      = 0;
    srcRect.width  = screenWidth_  << 16;
    srcRect.height = screenHeight_ << 16;        
    DISPMANX_DISPLAY_HANDLE_T display = vc_dispmanx_display_open(0);
    DISPMANX_UPDATE_HANDLE_T  update  = vc_dispmanx_update_start(0);
    DISPMANX_ELEMENT_HANDLE_T element = vc_dispmanx_element_add(
        update, display, 0, &dstRect, 0, &srcRect, DISPMANX_PROTECTION_NONE, 0, 0,
        DISPMANX_NO_ROTATE);
    window_.element = element;
    window_.width   = screenWidth_;
    window_.height  = screenHeight_;
    vc_dispmanx_update_submit_sync(update);
    surface_ = eglCreateWindowSurface(display_, config, &window_, nullptr);
    assert(surface_ != EGL_NO_SURFACE);
    
    result = eglMakeCurrent(display_, surface_, surface_, context_);
    assert(result);
}

VideoCoreDisplay::~VideoCoreDisplay() {
    eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(display_, surface_);
    eglDestroyContext(display_, context_);
    eglTerminate(display_);
}

int VideoCoreDisplay::Width() {
    return (int)screenWidth_;
}

int VideoCoreDisplay::Height() {
    return (int)screenHeight_;
}

void VideoCoreDisplay::BeginFrame() {
    // Nop.
}

void VideoCoreDisplay::EndFrame() {
    eglSwapBuffers(display_, surface_);
}

}
