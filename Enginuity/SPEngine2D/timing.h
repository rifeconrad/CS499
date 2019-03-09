#pragma once

namespace SPEngine2D
{
	class FPSLimiter
	{
	public:
		FPSLimiter();

		void init(float fps);
		void setMaxFPS(float fps);
		void calculateFPS();

		void begin();
		void end();   

	private:
		float max_fps;
		float frame_time;
		float fps;

		unsigned int start_ticks;
	};
}