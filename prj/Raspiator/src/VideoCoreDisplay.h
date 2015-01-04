#ifndef RASPIATOR_VIDEOCOREDISPLAY_H_
#define RASPIATOR_VIDEOCOREDISPLAY_H_


#include <EGL/egl.h>


namespace Raspiator {

//! Provides OpenGL ES access to the rpi's VideoCore GPU.
class VideoCoreDisplay {
  public:
    VideoCoreDisplay();
    VideoCoreDisplay(const VideoCoreDisplay &other)            = delete;
    VideoCoreDisplay &operator=(const VideoCoreDisplay &other) = delete;
    VideoCoreDisplay(VideoCoreDisplay &&other)                 = delete;
    VideoCoreDisplay &operator=(VideoCoreDisplay &&other)      = delete;
    ~VideoCoreDisplay();
    
    //! Returns the OpenGL ES display's width (in pixels).
    int Width();
    //! Returns the OpenGL ES display's height (in pixels).
    int Height();
    //! To be called when beginning to render a new frame.
    void BeginFrame();
    //! To be called when finished rendering the current frame.
    void EndFrame();
    
  private:
    EGLDisplay            display_;
    EGLSurface            surface_;
    EGLContext            context_;
    uint32_t              screenWidth_,
                          screenHeight_;
    EGL_DISPMANX_WINDOW_T window_;
};

}    // Namespace Raspiator.

#endif    // RASPIATOR_VIDEOCOREDISPLAY_H_
