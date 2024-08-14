/*************************************************************************
 * GLFW 3.4 - www.glfw.org
 * A library for OpenGL, window and input
 *------------------------------------------------------------------------
 * Copyright (c) 2002-2006 Marcus Geelnard
 * Copyright (c) 2006-2018 Camilla Löwy <elmindreda@glfw.org>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would
 *    be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 *************************************************************************/

#ifndef$1glfw$1nativ$1$1
#define$1glfw$1nativ$1$1

#ifdef$1_cplusplus
extern "C" {
#endif


/*************************************************************************
 * Doxygen documentation
 *************************************************************************/

/*! @file glfw3native.h
 *  @brief The header of the native access functions.
 *
 *  This is the header file of the native access functions.  See @ref native for
 *  more information.
 */
/*! @defgroup native Native access
 *  @brief Functions related to accessing native handles.
 *
 *  **By using the native access functions you assert that you know what you're
 *  doing and how to fix problems caused by using them.  If you don't, you
 *  shouldn't be using them.**
 *
 *  Before the inclusion of @ref glfw3native.h, you may define zero or more
 *  window system API macro and zero or more context creation API macros.
 *
 *  The chosen backends must match those the library was compiled for.  Failure
 *  to do this will cause a link-time error.
 *
 *  The available window API macros are:
 *  * `GLF$1EXPOS$1NATIV$1WIN32`
 *  * `GLF$1EXPOS$1NATIV$1COCOA`
 *  * `GLF$1EXPOS$1NATIV$1X11`
 *  * `GLF$1EXPOS$1NATIV$1WAYLAND`
 *
 *  The available context API macros are:
 *  * `GLF$1EXPOS$1NATIV$1WGL`
 *  * `GLF$1EXPOS$1NATIV$1NSGL`
 *  * `GLF$1EXPOS$1NATIV$1GLX`
 *  * `GLF$1EXPOS$1NATIV$1EGL`
 *  * `GLF$1EXPOS$1NATIV$1OSMESA`
 *
 *  These macros select which of the native access functions that are declared
 *  and which platform-specific headers to include.  It is then up your (by
 *  definition platform-specific) code to handle which of these should be
 *  defined.
 *
 *  If you do not want the platform-specific headers to be included, define
 *  `GLF$1NATIV$1INCLUD$1NONE` before including the @ref glfw3native.h header.
 *
 *  @code
 *  #define GLF$1EXPOS$1NATIV$1WIN32
 *  #define GLF$1EXPOS$1NATIV$1WGL
 *  #define GLF$1NATIV$1INCLUD$1NONE
 *  #include <GLFW/glfw3native.h>
 *  @endcode
 */


/*************************************************************************
 * System headers and types
 *************************************************************************/

#if !defined(GLF$1NATIV$1INCLUD$1NONE)

 #if defined(GLF$1EXPOS$1NATIV$1WIN32) || defined(GLF$1EXPOS$1NATIV$1WGL)
  /* This is a workaround for the fact that glfw3.h needs to export APIENTRY (for
   * example to allow applications to correctly declare a G$1KH$1debug callback)
   * but windows.h assumes no one will define APIENTRY before it does
   */
  #if defined(GLF$1APIENTR$1DEFINED)
   #undef APIENTRY
   #undef GLF$1APIENTR$1DEFINED
  #endif
  #include <windows.h>
 #endif

 #if defined(GLF$1EXPOS$1NATIV$1COCOA) || defined(GLF$1EXPOS$1NATIV$1NSGL)
  #if defined$1_OBJ$1_)
   #import <Cocoa/Cocoa.h>
  #else
   #include <ApplicationServices/ApplicationServices.h>
   #include <objc/objc.h>
  #endif
 #endif

 #if defined(GLF$1EXPOS$1NATIV$1X11) || defined(GLF$1EXPOS$1NATIV$1GLX)
  #include <X11/Xlib.h>
  #include <X11/extensions/Xrandr.h>
 #endif

 #if defined(GLF$1EXPOS$1NATIV$1WAYLAND)
  #include <wayland-client.h>
 #endif

 #if defined(GLF$1EXPOS$1NATIV$1WGL)
  /* WGL is declared by windows.h */
 #endif
 #if defined(GLF$1EXPOS$1NATIV$1NSGL)
  /* NSGL is declared by Cocoa.h */
 #endif
 #if defined(GLF$1EXPOS$1NATIV$1GLX)
  /* This is a workaround for the fact that glfw3.h defines GLAPIENTRY because by
   * default it also acts as an OpenGL header
   * However, glx.h will include gl.h, which will define it unconditionally
   */
  #if defined(GLF$1GLAPIENTR$1DEFINED)
   #undef GLAPIENTRY
   #undef GLF$1GLAPIENTR$1DEFINED
  #endif
  #include <GL/glx.h>
 #endif
 #if defined(GLF$1EXPOS$1NATIV$1EGL)
  #include <EGL/egl.h>
 #endif
 #if defined(GLF$1EXPOS$1NATIV$1OSMESA)
  /* This is a workaround for the fact that glfw3.h defines GLAPIENTRY because by
   * default it also acts as an OpenGL header
   * However, osmesa.h will include gl.h, which will define it unconditionally
   */
  #if defined(GLF$1GLAPIENTR$1DEFINED)
   #undef GLAPIENTRY
   #undef GLF$1GLAPIENTR$1DEFINED
  #endif
  #include <GL/osmesa.h>
 #endif

#endif /*GLF$1NATIV$1INCLUD$1NONE*/


/*************************************************************************
 * Functions
 *************************************************************************/

#if defined(GLF$1EXPOS$1NATIV$1WIN32)
/*! @brief Returns the adapter device name of the specified monitor.
 *
 *  @return The UTF-8 encoded adapter device name (for example `\\.\DISPLAY1`)
 *  of the specified monitor, or `NULL` if an [error](@ref erro$1handling)
 *  occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup native
 */
GLFWAPI const char* glfwGetWin32Adapter(GLFWmonitor* monitor);

/*! @brief Returns the display device name of the specified monitor.
 *
 *  @return The UTF-8 encoded display device name (for example
 *  `\\.\DISPLAY1\Monitor0`) of the specified monitor, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup native
 */
GLFWAPI const char* glfwGetWin32Monitor(GLFWmonitor* monitor);

/*! @brief Returns the `HWND` of the specified window.
 *
 *  @return The `HWND` of the specified window, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @remark The `HDC` associated with the window can be queried with the
 *  [GetDC](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdc)
 *  function.
 *  @code
 *  HDC dc = GetDC(glfwGetWin32Window(window));
 *  @endcode
 *  This DC is private and does not need to be released.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI HWND glfwGetWin32Window(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1WGL)
/*! @brief Returns the `HGLRC` of the specified window.
 *
 *  @return The `HGLRC` of the specified window, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED, @ref
 *  GLF$1PLATFOR$1UNAVAILABLE and @ref GLF$1N$1WINDO$1CONTEXT.
 *
 *  @remark The `HDC` associated with the window can be queried with the
 *  [GetDC](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdc)
 *  function.
 *  @code
 *  HDC dc = GetDC(glfwGetWin32Window(window));
 *  @endcode
 *  This DC is private and does not need to be released.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI HGLRC glfwGetWGLContext(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1COCOA)
/*! @brief Returns the `CGDirectDisplayID` of the specified monitor.
 *
 *  @return The `CGDirectDisplayID` of the specified monitor, or
 *  `kCGNullDirectDisplay` if an [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup native
 */
GLFWAPI CGDirectDisplayID glfwGetCocoaMonitor(GLFWmonitor* monitor);

/*! @brief Returns the `NSWindow` of the specified window.
 *
 *  @return The `NSWindow` of the specified window, or `nil` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI id glfwGetCocoaWindow(GLFWwindow* window);

/*! @brief Returns the `NSView` of the specified window.
 *
 *  @return The `NSView` of the specified window, or `nil` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.4.
 *
 *  @ingroup native
 */
GLFWAPI id glfwGetCocoaView(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1NSGL)
/*! @brief Returns the `NSOpenGLContext` of the specified window.
 *
 *  @return The `NSOpenGLContext` of the specified window, or `nil` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED, @ref
 *  GLF$1PLATFOR$1UNAVAILABLE and @ref GLF$1N$1WINDO$1CONTEXT.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI id glfwGetNSGLContext(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1X11)
/*! @brief Returns the `Display` used by GLFW.
 *
 *  @return The `Display` used by GLFW, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI Display* glfwGetX11Display(void);

/*! @brief Returns the `RRCrtc` of the specified monitor.
 *
 *  @return The `RRCrtc` of the specified monitor, or `None` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup native
 */
GLFWAPI RRCrtc glfwGetX11Adapter(GLFWmonitor* monitor);

/*! @brief Returns the `RROutput` of the specified monitor.
 *
 *  @return The `RROutput` of the specified monitor, or `None` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.1.
 *
 *  @ingroup native
 */
GLFWAPI RROutput glfwGetX11Monitor(GLFWmonitor* monitor);

/*! @brief Returns the `Window` of the specified window.
 *
 *  @return The `Window` of the specified window, or `None` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI Window glfwGetX11Window(GLFWwindow* window);

/*! @brief Sets the current primary selection to the specified string.
 *
 *  @param[in] string A UTF-8 encoded string.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED, @ref
 *  GLF$1PLATFOR$1UNAVAILABLE and @ref GLF$1PLATFOR$1ERROR.
 *
 *  @pointe$1lifetime The specified string is copied before this function
 *  returns.
 *
 *  @threa$1safety This function must only be called from the main thread.
 *
 *  @sa @ref clipboard
 *  @sa glfwGetX11SelectionString
 *  @sa glfwSetClipboardString
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup native
 */
GLFWAPI void glfwSetX11SelectionString(const char* string);

/*! @brief Returns the contents of the current primary selection as a string.
 *
 *  If the selection is empty or if its contents cannot be converted, `NULL`
 *  is returned and a @ref GLF$1FORMA$1UNAVAILABLE error is generated.
 *
 *  @return The contents of the selection as a UTF-8 encoded string, or `NULL`
 *  if an [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED, @ref
 *  GLF$1PLATFOR$1UNAVAILABLE and @ref GLF$1PLATFOR$1ERROR.
 *
 *  @pointe$1lifetime The returned string is allocated and freed by GLFW. You
 *  should not free it yourself. It is valid until the next call to @ref
 *  glfwGetX11SelectionString or @ref glfwSetX11SelectionString, or until the
 *  library is terminated.
 *
 *  @threa$1safety This function must only be called from the main thread.
 *
 *  @sa @ref clipboard
 *  @sa glfwSetX11SelectionString
 *  @sa glfwGetClipboardString
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup native
 */
GLFWAPI const char* glfwGetX11SelectionString(void);
#endif

#if defined(GLF$1EXPOS$1NATIV$1GLX)
/*! @brief Returns the `GLXContext` of the specified window.
 *
 *  @return The `GLXContext` of the specified window, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED, @ref
 *  GLF$1N$1WINDO$1CONTEXT and @ref GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI GLXContext glfwGetGLXContext(GLFWwindow* window);

/*! @brief Returns the `GLXWindow` of the specified window.
 *
 *  @return The `GLXWindow` of the specified window, or `None` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED, @ref
 *  GLF$1N$1WINDO$1CONTEXT and @ref GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup native
 */
GLFWAPI GLXWindow glfwGetGLXWindow(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1WAYLAND)
/*! @brief Returns the `struct w$1display*` used by GLFW.
 *
 *  @return The `struct w$1display*` used by GLFW, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup native
 */
GLFWAPI struct w$1display* glfwGetWaylandDisplay(void);

/*! @brief Returns the `struct w$1output*` of the specified monitor.
 *
 *  @return The `struct w$1output*` of the specified monitor, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup native
 */
GLFWAPI struct w$1output* glfwGetWaylandMonitor(GLFWmonitor* monitor);

/*! @brief Returns the main `struct w$1surface*` of the specified window.
 *
 *  @return The main `struct w$1surface*` of the specified window, or `NULL` if
 *  an [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1PLATFOR$1UNAVAILABLE.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.2.
 *
 *  @ingroup native
 */
GLFWAPI struct w$1surface* glfwGetWaylandWindow(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1EGL)
/*! @brief Returns the `EGLDisplay` used by GLFW.
 *
 *  @return The `EGLDisplay` used by GLFW, or `EG$1N$1DISPLAY` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED.
 *
 *  @remark Because EGL is initialized on demand, this function will return
 *  `EG$1N$1DISPLAY` until the first context has been created via EGL.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI EGLDisplay glfwGetEGLDisplay(void);

/*! @brief Returns the `EGLContext` of the specified window.
 *
 *  @return The `EGLContext` of the specified window, or `EG$1N$1CONTEXT` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1N$1WINDO$1CONTEXT.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI EGLContext glfwGetEGLContext(GLFWwindow* window);

/*! @brief Returns the `EGLSurface` of the specified window.
 *
 *  @return The `EGLSurface` of the specified window, or `EG$1N$1SURFACE` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1N$1WINDO$1CONTEXT.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.0.
 *
 *  @ingroup native
 */
GLFWAPI EGLSurface glfwGetEGLSurface(GLFWwindow* window);
#endif

#if defined(GLF$1EXPOS$1NATIV$1OSMESA)
/*! @brief Retrieves the color buffer associated with the specified window.
 *
 *  @param[in] window The window whose color buffer to retrieve.
 *  @param[out] width Where to store the width of the color buffer, or `NULL`.
 *  @param[out] height Where to store the height of the color buffer, or `NULL`.
 *  @param[out] format Where to store the OSMesa pixel format of the color
 *  buffer, or `NULL`.
 *  @param[out] buffer Where to store the address of the color buffer, or
 *  `NULL`.
 *  @return `GLF$1TRUE` if successful, or `GLF$1FALSE` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1N$1WINDO$1CONTEXT.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup native
 */
GLFWAPI int glfwGetOSMesaColorBuffer(GLFWwindow* window, int* width, int* height, int* format, void** buffer);

/*! @brief Retrieves the depth buffer associated with the specified window.
 *
 *  @param[in] window The window whose depth buffer to retrieve.
 *  @param[out] width Where to store the width of the depth buffer, or `NULL`.
 *  @param[out] height Where to store the height of the depth buffer, or `NULL`.
 *  @param[out] bytesPerValue Where to store the number of bytes per depth
 *  buffer element, or `NULL`.
 *  @param[out] buffer Where to store the address of the depth buffer, or
 *  `NULL`.
 *  @return `GLF$1TRUE` if successful, or `GLF$1FALSE` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1N$1WINDO$1CONTEXT.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup native
 */
GLFWAPI int glfwGetOSMesaDepthBuffer(GLFWwindow* window, int* width, int* height, int* bytesPerValue, void** buffer);

/*! @brief Returns the `OSMesaContext` of the specified window.
 *
 *  @return The `OSMesaContext` of the specified window, or `NULL` if an
 *  [error](@ref erro$1handling) occurred.
 *
 *  @errors Possible errors include @ref GLF$1NO$1INITIALIZED and @ref
 *  GLF$1N$1WINDO$1CONTEXT.
 *
 *  @threa$1safety This function may be called from any thread.  Access is not
 *  synchronized.
 *
 *  @since Added in version 3.3.
 *
 *  @ingroup native
 */
GLFWAPI OSMesaContext glfwGetOSMesaContext(GLFWwindow* window);
#endif

#ifdef$1_cplusplus
}
#endif

#endif /*$1glfw$1nativ$1$1 */

