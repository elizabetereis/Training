/** @file DigitalConverterComponent.hpp
 *  @brief Function prototypes for the digital converter component.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#pragma once

#ifndef SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_HPP
#define SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_HPP

#include <signal_generator_components_export.h>
#include <hyro/core/Component.h>
#include <hyro/msgs/Signal.h>
#include "../src/internal/Thresholding.hpp"

namespace signal_generator
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT DigitalConverterComponent : public hyro::Component{
	
	public:
		DigitalConverterComponent(const hyro::URI & uri);
			
		virtual
		~DigitalConverterComponent () override = default;

		virtual hyro::Result
		init (const hyro::ComponentConfiguration & config) override;

		virtual hyro::Result
		reset () override;

		virtual hyro::Result
		check () override;

		virtual hyro::Result
		start () override;

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

#endif // SIGNAL_GENERATOR_DIGITALCONVERTERCOMPONENT_HPP