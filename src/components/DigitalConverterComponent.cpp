#include <hyro/DigitalConverterComponent.hpp>

using namespace hyro;

namespace signal_generator
{

std::shared_ptr<hyro::HyroLogger> DigitalConverterComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("DigitalConverterComponent");

DigitalConverterComponent::DigitalConverterComponent (const hyro::URI & uri)
  : hyro::Component(uri)
{
  m_amplitude = 5.0;
  m_threshold = 0.0;

};

hyro::Result
DigitalConverterComponent::init (const hyro::ComponentConfiguration & config)
{
  m_signals = this->registerInput<Signal>("signals"_uri, config);

  m_digital_signals = this->registerOutput<Signal>("digital_signals"_uri, config);

  auto onSendEvent = [](const IIdentifiable * sender, const SendEvent & event)
  {
    auto result = (event.result == SendEvent::SEND_OK ? "Message sent" : "Error: " + event.error_message);
    s_logger->info(sender, "-> [{}] {}", event.input_uri, result);
  };

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
  Signal resp;
  Signal genSignal;
  float digSignal;
  
  if (ret == ReceiveStatus::RECEIVE_OK)
  {
    genSignal = *value;
    digSignal = thresholding.convertSignal(genSignal.value, m_amplitude, m_threshold); 
    resp.frame_id = "Answer";
    resp.timestamp = 2;
    resp.value = digSignal;
  
    m_digital_signals->sendAsync(resp);
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