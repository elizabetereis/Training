/** @file SignalConverterComponent.hpp
 *  @brief Function prototypes for the signal generator component.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#pragma once

#ifndef SIGNAL_GENERATOR_COMPONENT_HPP
#define SIGNAL_GENERATOR_COMPONENT_HPP

#include <signal_generator_components_export.h> 
#include <hyro/core/Component.h>
#include <hyro/msgs/Signal.h>
#include <hyro/msgs/common/Basic.h>
#include "../src/internal/SignalGenerator.hpp"

namespace signal_generator
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalGeneratorComponent : public hyro::Component
{
	public:
		SignalGeneratorComponent(const hyro::URI & uri);
		
		virtual
		~SignalGeneratorComponent () override = default;

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
			
		float m_amplitude;
		float m_frequency;
		bool m_cosine;
		std::string m_name;

		static std::shared_ptr<hyro::HyroLogger> s_logger;

		std::shared_ptr<hyro::ChannelOutput<hyro::Signal>> m_outputsignal;
		std::shared_ptr<hyro::ChannelOutput<std::vector<int>>> m_dummy;

		float getAmplitude();

		bool setAmplitude(float value);

		float getFrequency();

		bool setFrequency(float value);

		bool getCosine();

		bool setCosine(bool value);      
    
};

}//namespace signalgenerator

#endif // SIGNAL_GENERATOR_COMPONENT_HPP