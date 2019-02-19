/** @file SignalConverterComponent.h
 *  @brief This file contains function prototypes for the signal generator component class.
 *  @author Elizabete
 *  @bug No known bugs.
*/

#pragma once

#ifndef SIGNAL_GENERATOR_COMPONENT_H
#define SIGNAL_GENERATOR_COMPONENT_H

#include <signal_generator_components_export.h> 
#include <hyro/core/Component.h>
#include <hyro/msgs/Signal.h>
#include <hyro/msgs/common/Basic.h>
#include "../src/internal/SignalGenerator.h"

namespace signal_generator
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalGeneratorComponent : public hyro::Component
{
public:

	using hyro::Component::Component;
  	
	virtual
	~SignalGeneratorComponent () override = default;
	
/** @brief Initialize all input and output channels, register dynamic properties 
 	* @return Result.
	*/
	virtual hyro::Result
	init (const hyro::ComponentConfiguration & config) override;

/** @brief reset all channels inputs and outputs. 
	* @return Result.
	*/
	virtual hyro::Result
	reset () override;

/** @brief check if connection is up for channels inputs. 
	* @return Result.
	*/
	virtual hyro::Result
	check () override;
/** @brief start the component. 
	* @return Result.
	*/
	virtual hyro::Result
	start () override;
	
/** @brief Uses SignalGenerator class to create a signal based on 
 *  cosine, amplitude and frequency values. Writes the generated signal 
 *  in the output channel. 
 *  @return Result.
	*/
	virtual hyro::Result
	update () override;

private:
		
	float m_amplitude;
	float m_frequency;
	bool m_cosine;
	std::string m_name;

	SignalGenerator signalGen;

	static std::shared_ptr<hyro::HyroLogger> s_logger;

	std::shared_ptr<hyro::ChannelOutput<hyro::Signal>> m_outputsignal;
	std::shared_ptr<hyro::ChannelOutput<std::vector<int>>> m_dummy;

	/** @brief return the attribute m_amplitude. 
		* @return float.
		*/
	float getAmplitude();

/** @brief set the attribute m_amplitude with the value parameter. 
	* @return bool.
	*/
	bool setAmplitude(float value);

/** @brief return the attribute m_frequency. 
	* @return float.
	*/
	float getFrequency();

/** @brief set the attribute m_frequency with the value parameter. 
	* @return bool.
	*/
	bool setFrequency(float value);

/** @brief return the attribute m_cosine. 
	* @return float.
	*/
	bool getCosine();

/** @brief set the attribute m_cosine with the value parameter. 
	* @return bool.
	*/
	bool setCosine(bool value);      
    
};

}//namespace signalgenerator

#endif // SIGNAL_GENERATOR_COMPONENT_H