/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2004 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

/*
** Copyright (c) 2007-2009 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Platform-specific types and definitions for egl.h
 * $Revision: 12306 $ on $Date: 2010-08-25 09:51:28 -0700 (Wed, 25 Aug 2010) $
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by sending them to the public Khronos Bugzilla (http://khronos.org/bugzilla)
 * by filing a bug against product "EGL" component "Registry".
 */

#ifndef __eglew_h__
#define __eglew_h__
#define __EGLEW_H__


#if defined(__egl_h_) || defined (__EGL_H_)
#error egl.h included before glew.h
#endif
#if defined(__eglext_h_) || defined (__EGLEXT_H_)
#error eglext.h included before glew.h
#endif
#if defined(__eglplatform_h_) || defined (__EGLPLATFORM_H_)
#error eglplatform.h included before glew.h
#endif
#if defined(GLES_EGLTYPES_H) || defined (gles_egltypes_h)
#error egltypes.h.h included before glew.h
#endif

#define __egl_h_
#define __EGL_H_
#define __eglext_h_
#define __EGLEXT_H_
#define GLES_EGLTYPES_H
#define gles_egltypes_h
#define __eglplatform_h_
#define __EGLPLATFORM_H_

/* TODO insert license */

/* Includes */
#include <GL/glew.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ifndef EGLAPI
#define EGLAPI KHRONOS_APICALL
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY  KHRONOS_APIENTRY
#endif
#define EGLAPIENTRYP EGLAPIENTRY*

/* The types NativeDisplayType, NativeWindowType, and NativePixmapType
 * are aliases of window-system-dependent types, such as X Display * or
 * Windows Device Context. They must be defined in platform-specific
 * code below. The EGL-prefixed versions of Native*Type are the same
 * types, renamed in EGL 1.3 so all types in the API start with "EGL".
 *
 * Khronos STRONGLY RECOMMENDS that you use the default definitions
 * provided below, since these changes affect both binary and source
 * portability of applications using EGL running on different EGL
 * implementations.
 */

#if defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

typedef HDC     EGLNativeDisplayType;
typedef HBITMAP EGLNativePixmapType;
typedef HWND    EGLNativeWindowType;

#elif defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

typedef int   EGLNativeDisplayType;
typedef void *EGLNativeWindowType;
typedef void *EGLNativePixmapType;

#elif defined(__unix__)

/* X11 (tentative)  */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;

#else
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
typedef khronos_int32_t EGLint;


/* Basic types */
typedef int EGLBoolean;

/* Internal types */
typedef void *EGLDisplay;
typedef void *EGLConfig;
typedef void *EGLSurface;
typedef void *EGLContext;

/* Handle values */
#define EGL_DEFAULT_DISPLAY ((EGLNativeDisplayType)-1)
#define EGL_NO_CONTEXT ((EGLContext)0)
#define EGL_NO_DISPLAY ((EGLDisplay)0)
#define EGL_NO_SURFACE ((EGLSurface)0)
#define EGL_UNKNOWN   	((EGLint)-1)

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------- EGL_VERSION_1_1 ---------------------------- */

#ifndef EGL_VERSION_1_1
#define EGL_VERSION_1_0		1
#define EGL_VERSION_1_1 	1

/*
** Boolean
*/
#define EGL_FALSE		       0
#define EGL_TRUE		       1

/*
** Errors
*/
#define EGL_SUCCESS		       0x3000
#define EGL_NOT_INITIALIZED	       0x3001
#define EGL_BAD_ACCESS		       0x3002
#define EGL_BAD_ALLOC		       0x3003
#define EGL_BAD_ATTRIBUTE	       0x3004
#define EGL_BAD_CONFIG		       0x3005
#define EGL_BAD_CONTEXT		       0x3006
#define EGL_BAD_CURRENT_SURFACE        0x3007
#define EGL_BAD_DISPLAY		       0x3008
#define EGL_BAD_MATCH		       0x3009
#define EGL_BAD_NATIVE_PIXMAP	       0x300A
#define EGL_BAD_NATIVE_WINDOW	       0x300B
#define EGL_BAD_PARAMETER	       0x300C
#define EGL_BAD_SURFACE		       0x300D
#define EGL_CONTEXT_LOST	       0x300E
/* 0x300F - 0x301F reserved for additional errors. */

/*
** Config attributes
*/
#define EGL_BUFFER_SIZE		       0x3020
#define EGL_ALPHA_SIZE		       0x3021
#define EGL_BLUE_SIZE		       0x3022
#define EGL_GREEN_SIZE		       0x3023
#define EGL_RED_SIZE		       0x3024
#define EGL_DEPTH_SIZE		       0x3025
#define EGL_STENCIL_SIZE	       0x3026
#define EGL_CONFIG_CAVEAT	       0x3027
#define EGL_CONFIG_ID		       0x3028
#define EGL_LEVEL		       0x3029
#define EGL_MAX_PBUFFER_HEIGHT	       0x302A
#define EGL_MAX_PBUFFER_PIXELS	       0x302B
#define EGL_MAX_PBUFFER_WIDTH	       0x302C
#define EGL_NATIVE_RENDERABLE	       0x302D
#define EGL_NATIVE_VISUAL_ID	       0x302E
#define EGL_NATIVE_VISUAL_TYPE	       0x302F
/*#define EGL_PRESERVED_RESOURCES	 0x3030*/
#define EGL_SAMPLES		       0x3031
#define EGL_SAMPLE_BUFFERS	       0x3032
#define EGL_SURFACE_TYPE	       0x3033
#define EGL_TRANSPARENT_TYPE	       0x3034
#define EGL_TRANSPARENT_BLUE_VALUE     0x3035
#define EGL_TRANSPARENT_GREEN_VALUE    0x3036
#define EGL_TRANSPARENT_RED_VALUE      0x3037
#define EGL_NONE		       0x3038	/* Also a config value */
#define EGL_BIND_TO_TEXTURE_RGB        0x3039
#define EGL_BIND_TO_TEXTURE_RGBA       0x303A
#define EGL_MIN_SWAP_INTERVAL	       0x303B
#define EGL_MAX_SWAP_INTERVAL	       0x303C

/*
** Config values
*/
#define EGL_DONT_CARE		       ((EGLint) -1)

#define EGL_SLOW_CONFIG		       0x3050	/* EGL_CONFIG_CAVEAT value */
#define EGL_NON_CONFORMANT_CONFIG      0x3051	/* " */
#define EGL_TRANSPARENT_RGB	       0x3052	/* EGL_TRANSPARENT_TYPE value */
#define EGL_NO_TEXTURE		       0x305C	/* EGL_TEXTURE_FORMAT/TARGET value */
#define EGL_TEXTURE_RGB		       0x305D	/* EGL_TEXTURE_FORMAT value */
#define EGL_TEXTURE_RGBA	       0x305E	/* " */
#define EGL_TEXTURE_2D		       0x305F	/* EGL_TEXTURE_TARGET value */

/*
** Config attribute mask bits
*/
#define EGL_PBUFFER_BIT		       0x01	/* EGL_SURFACE_TYPE mask bit */
#define EGL_PIXMAP_BIT		       0x02	/* " */
#define EGL_WINDOW_BIT		       0x04	/* " */

/*
** String names
*/
#define EGL_VENDOR		       0x3053	/* eglQueryString target */
#define EGL_VERSION		       0x3054	/* " */
#define EGL_EXTENSIONS		       0x3055	/* " */

/*
** Surface attributes
*/
#define EGL_HEIGHT		       0x3056
#define EGL_WIDTH		       0x3057
#define EGL_LARGEST_PBUFFER	       0x3058
#define EGL_TEXTURE_FORMAT	       0x3080	/* For pbuffers bound as textures */
#define EGL_TEXTURE_TARGET	       0x3081	/* " */
#define EGL_MIPMAP_TEXTURE	       0x3082	/* " */
#define EGL_MIPMAP_LEVEL	       0x3083	/* " */

/*
** BindTexImage / ReleaseTexImage buffer target
*/
#define EGL_BACK_BUFFER		       0x3084

/*
** Current surfaces
*/
#define EGL_DRAW		       0x3059
#define EGL_READ		       0x305A

/*
** Engines
*/
#define EGL_CORE_NATIVE_ENGINE	       0x305B

/* 0x305C-0x3FFFF reserved for future use */

/*
** Functions
*/

EGLAPI EGLint EGLAPIENTRY eglGetError (void);

EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (NativeDisplayType display);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI const char * EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI void (* EGLAPIENTRY eglGetProcAddress (const char *procname))();

EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);
EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);

EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, NativeWindowType window, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, NativePixmapType pixmap, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value);

/* EGL 1.1 render-to-texture APIs */
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);

/* EGL 1.1 swap control API */
EGLAPI EGLBoolean EGLAPIENTRY eglSwapInterval(EGLDisplay dpy, EGLint interval);

EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (void);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (void);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value);

EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (void);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers (EGLDisplay dpy, EGLSurface draw);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, NativePixmapType target);

#define EGLEW_VERSION_1_1 GLEW_GET_VAR(__EGLEW_VERSION_1_1)

#endif /* EGL_VERSION_1_1 */

