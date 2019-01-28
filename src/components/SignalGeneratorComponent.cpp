#include <hyro/SignalGeneratorComponent.hpp>

using namespace hyro;

namespace signal_generator
{

std::shared_ptr<hyro::HyroLogger> SignalGeneratorComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("SignalGeneratorComponent");

SignalGeneratorComponent::SignalGeneratorComponent(const hyro::URI & uri) 
  : hyro::Component(uri)
{
  m_amplitude = 5.0;
  m_frequency = 3.0;
  m_cosine = true;
  std::string m_name = "Signal";
};

hyro::Result
SignalGeneratorComponent::init (const hyro::ComponentConfiguration & config)
{
  //To solve dynamic properties bug
  m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config); 
  
  m_outputsignal = this->registerOutput<Signal>("signals"_uri, config);

  auto onSendEvent = [](const IIdentifiable * sender, const SendEvent & event)
  {
    auto result = (event.result == SendEvent::SEND_OK ? "Message sent" : "Error: " + event.error_message);
    s_logger->info(sender, "-> [{}] {}", event.input_uri, result);
  };

  registerDynamicProperty<float>(
    "amplitude",
    &SignalGeneratorComponent::setAmplitude,
    &SignalGeneratorComponent::getAmplitude,
    this);

  registerDynamicProperty<float>(
    "frequency",
    &SignalGeneratorComponent::setFrequency,
    &SignalGeneratorComponent::getFrequency,
    this);
  
  registerDynamicProperty<bool>(
    "cosine",
    &SignalGeneratorComponent::setCosine,
    &SignalGeneratorComponent::getCosine,
    this);

  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::reset ()
{ 
  m_outputsignal.reset();
  m_dummy.reset();

  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::check ()
{
  
  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::start ()
{
  
  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::update()
{
  Signal signal;
  SignalGenerator signalGen;

  signal.frame_id = "Testing";
  signal.timestamp = 1;
  signal.value = signalGen.getSignalValue(m_cosine, m_amplitude, m_frequency);
 
  m_outputsignal->sendAsync(signal);

  return Result::RESULT_OK;
}

float 
SignalGeneratorComponent::getAmplitude(){ 
  
  return m_amplitude; 
}

bool 
SignalGeneratorComponent::setAmplitude(float value){ 
  
  m_amplitude = value; 
  return true;
}

float 
SignalGeneratorComponent::getFrequency(){ 
  
  return m_frequency; 
}

bool 
SignalGeneratorComponent::setFrequency(float value){ 
  
  m_frequency = value; 
  return true;
}

bool 
SignalGeneratorComponent::getCosine(){ 
  
  return m_cosine; 
}

bool
SignalGeneratorComponent::setCosine(bool value){
  
  m_cosine = value; 
  return true;
}

}