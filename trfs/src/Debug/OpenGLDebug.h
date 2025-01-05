#pragma once

#define ENABLE_GL_DEBUG 1

#ifdef ENABLE_GL_DEBUG
#define glCheckError() detail::glCheckError_(__FILE__, __LINE__)
#else
#define glCheckError()
#endif

namespace detail
{
	void glCheckError_(const char* file, int line);
} // namespace detail
