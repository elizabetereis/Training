#include "SignalGenerator.h"

namespace signal_generator
{

SignalGenerator::SignalGenerator(){
	
	m_deg = 60.0;
}

float
SignalGenerator::getSignalValue(bool cosine, float amp, float step)
{
	float rad = m_deg / 180.0 * M_PI;
	m_deg += step;
  	
	return cosine ? amp * cos(rad) : amp * sin(rad);
}

}