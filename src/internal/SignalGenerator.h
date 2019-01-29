/** @file SignalGenerator.h
 *  @brief Function prototypes for the signal generator.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#define PI 3.14159265

#include <math.h>

namespace signal_generator
{

class SignalGenerator
{
public:
	SignalGenerator();

/** @brief generates analog signal 
 *  @param cosine: boolean indicating if the signal value will be sin ou cosine function 
 *         amp: amplitude value
 *				 step: frequency.
 *  @return float.
 */
	float getSignalValue(bool cosine, float amp, float step);
};

}

#endif // SIGNALGENERATOR_H