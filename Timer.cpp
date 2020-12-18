#include "Timer.hpp"

#include <string>
#include <chrono>
#include <cstdio>

Timer::Timer(double* _counter){
	m_StartTimePoint = std::chrono::high_resolution_clock::now();
	counter = _counter;
}

Timer::~Timer(){
	Stop();
}

void Timer::Stop(){
	auto duration =duration_now();

	if(counter != nullptr)
	{
		*counter = duration;
		return;
	}


	std::string scale = "us";
	double val = duration;
	if(duration>1000.0){
		val*=0.001;
		scale="ms";
		if(val>1000.0){
			val*=0.001;
			scale="sec";
		}
	}
	// double ms = duration * 0.001;
	// double sec = ms * 0.001;
	if(scale=="us")
		printf("(%d%s)\n" ,(uint32_t)val,scale.c_str());
	else
		printf("(%.2lf%s)\n" ,val,scale.c_str());
} 

double Timer::duration_now(){
	auto endTimePoint = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
	auto duration = end - start;
	return (double)duration;
}

void Timer::BENCHMARK_RATE(uint64_t score){
	auto duration = duration_now();
	//double ms = duration * 0.001;
	//double s = ms * 0.001;
	double rate = (double)score/duration;
	char scale='M';
	if(rate<1.0){
		rate*=1000.0; 
		scale='K';
		if(rate<1.0){
			rate*=1000.0; 
			scale=' ';
		}
	}
	printf(ANSI_COLOR_CYAN "Proccessing rate: %.2f %cnode/sec \n" ANSI_COLOR_RESET,rate,scale);
}
