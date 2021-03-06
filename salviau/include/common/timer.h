#pragma once

#ifndef SALVIAU_COMMON_TIMER_H
#define SALVIAU_COMMON_TIMER_H

#include <salviau/include/salviau_forward.h>

#include <eflib/include/platform/boost_begin.h>
#include <boost/chrono.hpp>
#include <eflib/include/platform/boost_end.h>

BEGIN_NS_SALVIAU();

class SALVIAU_API timer
{
public:
	typedef boost::chrono::high_resolution_clock clock_type;
	typedef clock_type::time_point time_point;
	typedef boost::chrono::duration<double> seconds;
	
	timer();
	void		restart();
	double		elapsed() const;
	time_point	current_time() const;

private:
	clock_type::time_point start_time_;
};

class SALVIAU_API fps_counter
{
public:
	fps_counter(float interval);
	bool on_frame(float& fps);

private:
	timer		timer_;
	uint32_t	elapsed_frame_; 
	float		elapsed_seconds_;
	float		fps_;
	float		interval_;
};

END_NS_SALVIAU();

#endif		// _TIMER_H
