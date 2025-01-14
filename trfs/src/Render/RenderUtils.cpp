#include "RenderUtils.h"
#include "OpenGLConfig.h"

Render::DepthTestGuard::DepthTestGuard()
{
	glEnable(GL_DEPTH_TEST);
}

Render::DepthTestGuard::~DepthTestGuard()
{
	glDisable(GL_DEPTH_TEST);
}
