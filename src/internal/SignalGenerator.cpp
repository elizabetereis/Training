#include "SignalGenerator.hpp"

namespace signal_generator
{

SignalGenerator::SignalGenerator(){

}

/** @brief generates analog signal 
 *  @param cosine: boolean indicating if the signal value will be sin ou cosine function 
 *         amp: amplitude value
 *				 step: frequency.
 *  @return float.
 */
float
SignalGenerator::getSignalValue(bool cosine, float amp, float step)
{
	float deg = 60.0;
	float rad = deg / 180.0 * M_PI;
	deg += step;
	
	if (cosine)
		return amp * cos(rad);
			
	return amp * sin(rad);
}

}