#include "Thresholding.h"

namespace signal_generator
{

Thresholding::Thresholding(){

}

float
Thresholding::convertSignal(float value, float amp, float thresh){

	return (value > thresh) ? amp : -amp;
}

}