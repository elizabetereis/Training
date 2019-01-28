/** @file SignalGenerator.hpp
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
		float getSignalValue(bool cosine, float amp, float step);
};

}

#endif // SIGNALGENERATOR_H