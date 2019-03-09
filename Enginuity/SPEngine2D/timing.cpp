#include "timing.h"

#include <SDL2/SDL.h>

#include <iostream>

namespace SPEngine2D
{
	FPSLimiter::FPSLimiter()
	{
	}

	void FPSLimiter::init(float fps)
	{
		this->setMaxFPS(fps);
	}

	void FPSLimiter::setMaxFPS(float fps)
	{
		this->max_fps = fps;
	}

	void FPSLimiter::calculateFPS()
	{
		// # of frames we want to average
		static const int NUM_SAMPLES = 10;
		// a collection of the frame times
		static float frame_times[NUM_SAMPLES];
		// the current frame time
		static int curr_frame = 0;

		// initialize the ticks for this frame
		static float prev_ticks = SDL_GetTicks();

		// obtain the current ticks
		float curr_ticks;
		curr_ticks = SDL_GetTicks();

		// how long has this frame taken?
		this->frame_time = curr_ticks - prev_ticks;

		// do a circular storage of the frames
		frame_times[curr_frame % NUM_SAMPLES] = this->frame_time;

		// set our previous ticks to our current ticks for the next call to this method
		prev_ticks = curr_ticks;

		// increment the # of frames we have had
		curr_frame++;

		// determine which frame we are on now
		int count;
		if (curr_frame < NUM_SAMPLES)
			count = curr_frame; // if we are less than 10 frames, we need to account for that
		else
			count = NUM_SAMPLES; // anything more than 10 frames

		// loop through each stored frame and sum them up
		float avg_frame_time = 0;
		for (int i = 0; i < count; i++)
		{
			avg_frame_time += frame_times[i];
		}

		// calculate the average of the summed up frames
		avg_frame_time /= count;

		// check if the avg_frame_time is equal to 0 (avoids division by 0)
		if (avg_frame_time > 0)
		{
			// if not, we have our FPS!
			this->fps = 1000.f / avg_frame_time;
		}
		else
		{
			// if so, print off a generic value
			this->fps = 60.f;
		}
	}

	void FPSLimiter::begin()
	{
		this->start_ticks = SDL_GetTicks();
	}

	void FPSLimiter::end()
	{
		this->calculateFPS();

		// limit FPS display
		static int frame_counter = 0;
		frame_counter++;
		if (frame_counter == 10)
		{
			std::cerr << this->fps << "\n";
			frame_counter = 0;
		}

		float actual_frame_time = SDL_GetTicks() - start_ticks;

		// FPS limiter
		// if our frame was quicker than intended
		float desired_frame_time = 1000.f / this->max_fps;
		if (desired_frame_time > actual_frame_time)
		{
			// delay the frame to our desired frame time
			SDL_Delay(desired_frame_time - actual_frame_time);
		}
	}
}