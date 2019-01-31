/** @file DigitalConverterComponent.h
 *  @brief This file contains function prototypes for the digital converter component class.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#pragma once

#ifndef SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H
#define SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H

#include <signal_generator_components_export.h>
#include <hyro/core/Component.h>
#include <hyro/msgs/Signal.h>
#include "../src/internal/Thresholding.h"

namespace signal_generator
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT DigitalConverterComponent : public hyro::Component
{
	
public:

	using hyro::Component::Component;
		
	virtual
	~DigitalConverterComponent () override = default;

	/** @brief Initialize all input and output channels 
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

/** @brief check if some message was received. 
	* In case of true, use SignalGenerator class to generate 
	* a signal output and return as response. 
	* @return Result.
	*/
	virtual hyro::Result
	update () override;

private:
	static std::shared_ptr<hyro::HyroLogger> s_logger;

	float m_amplitude;
	float m_threshold;

	std::shared_ptr<hyro::ChannelOutput<hyro::Signal>> m_digital_signals;
	std::shared_ptr<hyro::ChannelInput<hyro::Signal>> m_signals;       
};

} //namespace signalgenerator

#endif // SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_H