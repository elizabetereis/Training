#include "Thresholding.hpp"

namespace signal_generator
{

Thresholding::Thresholding(){

}

float
Thresholding::convertSignal(float value, float amp, float thresh){

	if(value > thresh)
		value = amp;
	else
		value = - amp;

	return value;
}

}