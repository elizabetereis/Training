#include "Thresholding.hpp"

namespace signal_generator
{

Thresholding::Thresholding(){

}

/** @brief convert analog signal value, in negative or positive, 
 *	acording to the amplitude and threshold parameters.
 *  @param value: analog signal value 
 *         amp: amplitude value
 *				 thresh: threshold value.
 *  @return float.
 */
float
Thresholding::convertSignal(float value, float amp, float thresh){

	if(value > thresh)
		value = amp;
	else
		value = - amp;

	return value;
}

}