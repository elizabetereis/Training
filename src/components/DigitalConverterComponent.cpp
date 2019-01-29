#include <hyro/DigitalConverterComponent.h>

using namespace hyro;

namespace signal_generator
{

std::shared_ptr<hyro::HyroLogger> DigitalConverterComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("DigitalConverterComponent");

DigitalConverterComponent::DigitalConverterComponent (const hyro::URI & uri)
  : hyro::Component(uri)
{

};

hyro::Result
DigitalConverterComponent::init (const hyro::ComponentConfiguration & config)
{
  m_amplitude = config.parameters.getParameter<float>("amplitude", 5.0);
  m_threshold = config.parameters.getParameter<float>("amplitude", 6.0);
  
  m_signals = this->registerInput<Signal>("signals"_uri, config);

  m_digital_signals = this->registerOutput<Signal>("digital_signals"_uri, config);

  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::start ()
{
  
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::check ()
{
  if (m_signals->connectionStatus() != ConnectionStatus::CONNECTION_UP)
    return Result::RESULT_ERROR;

  return Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::update()
{ 
  auto value = std::shared_ptr<const Signal>();
  auto ret = m_signals->receive(value, 1s);
  Thresholding thresholding;
  Signal response_signal;
  Signal input_signal;
  
  if (ret == ReceiveStatus::RECEIVE_OK)
  {
    input_signal = *value;
    response_signal.frame_id = "Answer";
    response_signal.timestamp = TimeUtils::Now_TimeSinceEpoch();;
    response_signal.value = thresholding.convertSignal(input_signal.value, m_amplitude, m_threshold);;
  
    m_digital_signals->sendAsync(response_signal);
  }

  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::reset ()
{
  m_signals.reset();
  m_digital_signals.reset();

  return hyro::Result::RESULT_OK;
}


}