namespace Larp
{
	GLfloat Time::d_time = 0;
	GLfloat Time::lf_time = 0;

	static GLfloat Time::current_time()
	{
		return glfwGetTime();
	}

	static GLfloat Time::delta_time()
	{
		return d_time;
	}

	static GLfloat Time::last_frame_time()
	{
		return lf_time;
	}

	static void Time::update_time()
	{
        GLfloat current = glfwGetTime();
        d_time = current - lf_time;
        lf_time = current;	
	}

	static GLfloat Time::lerp_scalar(GLfloat start, GLfloat duration)
	{
		GLfloat diff = glfwGetTime() - start;
		if(diff >= duration)
		{
			return 1;
		}
		GLfloat end = start + duration;
		return diff/end;
	}
}