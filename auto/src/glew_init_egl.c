/* ------------------------------------------------------------------------ */


GLboolean eglewGetExtension(const char* name)
{    
  const GLubyte* start;
  const GLubyte* end;

  start = (GLubyte*)eglQueryString( eglGetCurrentDisplay() , EGL_EXTENSIONS);
  if (0 == start) return GL_FALSE;
  end = start + _glewStrLen(start);
  return _glewSearchExtension(name, start, end);
}


GLenum eglewContextInit (EGLEW_CONTEXT_ARG_DEF_LIST)
{
  const GLubyte* s;
  GLuint dot;
  GLint major, minor;
  const GLubyte* extStart;
  const GLubyte* extEnd;
  s = (GLubyte*)eglQueryString(eglGetCurrentDisplay() , EGL_VERSION);
  dot = _glewStrCLen(s, '.');
  if (dot == 0)
    return GLEW_ERROR_NO_EGL_VERSION;
  
  major = s[dot-1]-'0';
  minor = s[dot+1]-'0';

  if (minor < 0 || minor > 9)
    minor = 0;
  if (major<0 || major>9)
    return GLEW_ERROR_NO_EGL_VERSION;
  

  if (major == 1 && minor == 0)
  {
    return GLEW_ERROR_EGL_VERSION_10_ONLY;
  }
  else
  {
    CONST_CAST(EGLEW_VERSION_1_4) = ( major > 2 )    || ( major == 1 && minor >= 4 ) ? GL_TRUE :GL_FALSE;
    CONST_CAST(EGLEW_VERSION_1_3) = EGLEW_VERSION_1_4 == GL_TRUE || ( major == 1 && minor >= 3 ) ? GL_TRUE :GL_FALSE; 
    CONST_CAST(EGLEW_VERSION_1_2) = EGLEW_VERSION_1_3 == GL_TRUE || ( major == 1 && minor >= 2 ) ? GL_TRUE : GL_FALSE; 
    CONST_CAST(EGLEW_VERSION_1_1) = EGLEW_VERSION_1_2 == GL_TRUE || ( major == 1 && minor >= 1 ) ? GL_TRUE : GL_FALSE; 
  }
 
  /* query opengl extensions string */
  extStart = (GLubyte*)eglQueryString( eglGetCurrentDisplay() , EGL_EXTENSIONS);
  if (extStart == 0)
  extStart = (const GLubyte*)"";
  extEnd = extStart + _glewStrLen(extStart);
  
  /* initialize extensions */


