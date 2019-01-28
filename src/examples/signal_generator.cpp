/** @file signal_generator.cpp
 *  @brief Main function for setting and connecting components.
 *  This file contains the main function that connecting generator
 *  and converter components. Both spinners and state machines are
 *  connected here.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#include <hyro/core/StateMachine.h>
#include <hyro/utils/StateMachineSpinner.h>
#include <hyro/utils/DynamicPropertyAccess.h>
#include <hyro/utils/components/GenericSenderComponent.h>
#include <hyro/utils/components/GenericConsumerComponent.h>
#include <hyro/utils/components/PrintComponent.h>
#include <hyro/DigitalConverterComponent.hpp>
#include <hyro/SignalGeneratorComponent.hpp>
#include <hyro/widgets/WidgetCollection.h>
#include <hyro/msgs/Signal.h>


using namespace hyro;

int
main ()
{
   std::string generator_configuration = 
   "{"
      "outputs: {"
         "signals: { protocol: 'api' },"
         "fix_dynamic: { protocol: 'api' }"
      "}"
   "}";   

   std::string converter_configuration = 
   "{"
      "inputs: {"
         "signals: { protocol: 'api' }"
      "},"
      "outputs: {"
         "digital_signals: { protocol: 'api' }"
      "}"
   "}";

   std::string connect_configuration =
   "{" 
      "signals: {"
         "endpoint: '/generator/signals'" 
      "}" 
  "}"; 

   auto remote_endpoint = ConnectionConfiguration(connect_configuration);   
   
   StateMachine generator_sm(std::make_shared<signal_generator::SignalGeneratorComponent>("/generator"_uri));
   generator_sm.init(
    ComponentConfiguration(generator_configuration));
   generator_sm.start();
   generator_sm.connect();
   generator_sm.check();
   
   StateMachine converter_sm(std::make_shared<signal_generator::DigitalConverterComponent>("/converter"_uri));
   converter_sm.init(
    ComponentConfiguration(converter_configuration));
   converter_sm.start();
   converter_sm.connect(remote_endpoint);
   converter_sm.check();

   DynamicPropertyAccess dynamic_property_access("/generator"_uri);

   CancellationTokenSource cancellation_token;

   StateMachineSpinner generator_spinner(generator_sm, cancellation_token);
   StateMachineSpinner converter_spinner(converter_sm, cancellation_token);

   float amplitude = 5.0;
   float frequency = 2.0;
   bool cosine = false;

   dynamic_property_access.set<float>("amplitude", amplitude);
   dynamic_property_access.set<float>("frequency", frequency);
   dynamic_property_access.set<bool>("cosine", cosine);

   widgets::registerChannelListener<hyro::Signal>("/generator/signals", "api", [](hyro::Signal signal){
    widgets::plot2d<float>("Analog Signal", "/generator/signals", signal.value);
  });

     widgets::registerChannelListener<hyro::Signal>("/converter/digital_signals", "api", [](hyro::Signal signal){
    widgets::plot2d<float>("Digital Signal", "/converter/digital_signals", signal.value);
  });
   
   widgets::exec();
   widgets::reset();
   cancellation_token.cancel();

   generator_spinner.wait();
   converter_spinner.wait();

   generator_sm.reset();
   converter_sm.reset();

   return 0;

}
