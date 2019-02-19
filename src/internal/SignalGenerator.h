/** @file SignalGenerator.h
 *  @brief This file contains function prototypes for the signal generator class.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

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

private:
	float m_deg;
};

}

#endif // SIGNALGENERATOR_H