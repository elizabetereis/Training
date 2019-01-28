#include "SignalGenerator.hpp"

namespace signal_generator
{

SignalGenerator::SignalGenerator(){

}

float
SignalGenerator::getSignalValue(bool cosine, float amp, float step)
{
	float deg = 50.0;
	float rad = deg / 180.0 * M_PI;
	deg += step;
	
	if (cosine)
		return amp * cos(rad);
			
	return amp * sin(rad);
}

}