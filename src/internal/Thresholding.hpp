/** @file Thresholding.hpp
 *  @brief Function prototypes for the thresholding.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#ifndef THRESHOLDING_H
#define THRESHOLDING_H

namespace signal_generator
{

class Thresholding
{
	public:
		Thresholding();
		float convertSignal(float value, float amp, float thresh);
};

}

#endif // THRESHOLDING_H