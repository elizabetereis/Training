/** @file Thresholding.h
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

/** @brief convert analog signal value, in negative or positive, 
 *	acording to the amplitude and threshold parameters.
 *  @param value: analog signal value 
 *         amp: amplitude value
 *				 thresh: threshold value.
 *  @return float.
 */
	float convertSignal(float value, float amp, float thresh);
};

}

#endif // THRESHOLDING_H