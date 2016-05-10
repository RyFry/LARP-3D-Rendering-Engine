#pragma once

#include "LarpPrerequisites.hpp"

namespace Larp
{
	class Time
	{
	public:
		static GLfloat current_time(void);
		static GLfloat delta_time(void);
		static GLfloat last_frame_time(void);
		static void update_time(void);
		static GLfloat lerp_scalar(GLfloat start, GLfloat duration);
	private:	
		static GLfloat d_time;
		static GLfloat lf_time;
	};
}