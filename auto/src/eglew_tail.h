/* ------------------------------------------------------------------------ */

/* error codes */
#define GLEW_ERROR_NO_EGL_VERSION 1  /* missing EGL version */
#define GLEW_ERROR_EGL_VERSION_10_ONLY 2 /* need at least EGL 1.1 */

#ifdef GLEW_MX

typedef struct EGLEWContextStruct EGLEWContext;
extern GLenum eglewContextInit (EGLEWContext* ctx);
extern GLboolean eglewContextIsSupported (const EGLEWContext* ctx, const char* name);

#define eglewInit() eglewContextInit(eglewGetContext())
#define eglewIsSupported(x) eglewContextIsSupported(eglewGetContext(), x)

#define EGLEW_GET_VAR(x) (*(const GLboolean*)&(eglewGetContext()->x))
#ifdef _WIN32
#  define EGLEW_GET_FUN(x) eglewGetContext()->x
#else
#  define EGLEW_GET_FUN(x) x
#endif

#else /* GLEW_MX */

#define EGLEW_GET_VAR(x) (*(const GLboolean*)&x)
#define EGLEW_GET_FUN(x) x

extern GLboolean eglewIsSupported (const char* name);

#endif /* GLEW_MX */

extern GLboolean eglewGetExtension (const char* name);

#ifdef __cplusplus
}
#endif

#undef GLEWAPI

#endif /* __eglew_h__ */
