    }
    ret = (len == 0);
  }
  return ret;
}

#if defined(GLEW_ES_ONLY)

#if defined(GLEW_MX)
GLboolean eglewContextIsSupported (const EGLEWContext* ctx, const char* name)
#else
GLboolean eglewIsSupported (const char* name)
#endif
{
  GLubyte* pos = (GLubyte*)name;
  GLuint len = _glewStrLen(pos);
  GLboolean ret = GL_TRUE;
  while (ret && len > 0)
  {
    if (_glewStrSame1(&pos, &len, (const GLubyte*)"EGL_", 4))
    {
