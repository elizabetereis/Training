/** @file test_signal_generatoe.cpp
 *  @brief Main function for define and running test cases.
 *  This file contains three test cases: SignalGeneratorComponentCheck, 
 *  DigitalConverterCheck and DynamicPropertyCheck for generator component.
 *  @author Elizabete
 *  @bug Don't execute the three tests in the same execution, for example, 
 *  when execute generator check and converter check, the dynamic check don't execute.
 */

#include <hyro/DigitalConverterComponent.h>
#include <hyro/SignalGeneratorComponent.h>
#include <hyro/core/StateMachine.h>
#include <hyro/utils/DynamicPropertyAccess.h>
#include <hyro/test/ComponentTester.h>

#include <gtest/gtest.h>

static void
__assert_and_run_state_machine(hyro::StateMachine& sm,
                               const hyro::ComponentConfiguration& conf,
                               const hyro::ConnectionConfiguration& endpoint)
{
  ASSERT_EQ(hyro::Result::RESULT_OK, sm.init(conf));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.start());

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.connect(endpoint));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.check());
}

#define ASSERT_AND_RUN_STATE_MACHINE(sm, conf, endpoint) \
  __assert_and_run_state_machine(sm, conf, endpoint)

namespace hyro
{
namespace test
{


TEST (SignalGeneratorTest, SignalGeneratorComponentCheck)
{
  auto genConf = 
  "{"
      "outputs: {"
          "signals: { protocol: 'api' },"
          "fix_dynamic: { protocol: 'api' }"
      "}"
  "}";

  StateMachine generator_sm(std::make_shared<signal_generator::SignalGeneratorComponent>("/generator"_uri));
  
  ASSERT_AND_RUN_STATE_MACHINE(generator_sm, ComponentConfiguration(genConf), ConnectionConfiguration());
  
  auto inputSignal = std::make_shared<FakeInput<Signal>>("inputSignal"_uri, "api", "/generator/signals");
  ASSERT_TRUE(inputSignal->connect());

  auto result = generator_sm.update();
  ASSERT_EQ(Result::RESULT_OK, result);

  auto valueSignal = std::shared_ptr<const Signal>();
  
  ReceiveStatus ret = inputSignal->receive(valueSignal, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);

  ASSERT_EQ(valueSignal->value,0.0);

  generator_sm.reset();
}


TEST (SignalGeneratorTest, ConverterComponentCheck)
{
 
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
        "endpoint: 'fake_output' " 
      "}" 
  "}"; 

  auto fake_output = std::make_shared<FakeOutput<Signal>>("fake_output"_uri, "api");
  ASSERT_TRUE(fake_output->start());
 
  hyro::StateMachine converter_sm(std::make_shared<signal_generator::DigitalConverterComponent>("/converter"_uri));

  ASSERT_AND_RUN_STATE_MACHINE(converter_sm, ComponentConfiguration(converter_configuration), ConnectionConfiguration(connect_configuration));
  
  auto fake_input = std::make_shared<FakeInput<Signal>>("fake_input"_uri, "api", "/converter/digital_signals");
  ASSERT_TRUE(fake_input->connect());

  auto result = converter_sm.update();
  ASSERT_EQ(Result::RESULT_OK, result);

  Signal signalTest;
  signalTest.value = -1;
  fake_output->sendAsync(signalTest);

  converter_sm.update();

  auto outputValue = std::shared_ptr<const Signal>();
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, fake_input->receive(outputValue, 0ms));

  //signalvalue sended is negative, default threshold is positive,
  //so the return has to be negative amplitude
  float default_amp = 3.0f;
  EXPECT_EQ(outputValue->value, -default_amp);

  converter_sm.reset();
}


// TEST (SignalGeneratorTest, DynamicPropertyCheck)
// {   
//   auto genConf = 
//   "{"
//       "outputs: {"
//           "signals: { protocol: 'api' },"
//           "fix_dynamic: { protocol: 'api' }"
//       "}"
//   "}";
    
//   StateMachine generator_sm(std::make_shared<signal_generator::SignalGeneratorComponent>("/generator"_uri));
//   ASSERT_AND_RUN_STATE_MACHINE(generator_sm, ComponentConfiguration(genConf), ConnectionConfiguration());

//   auto outputSignal = std::make_shared<FakeOutput<Signal>>("outputSignal"_uri, "api");
//   ASSERT_TRUE(outputSignal->start());

//   auto inputSignal = std::make_shared<FakeInput<Signal>>("inputSignal"_uri, "api", "/generator/signals");
//   ASSERT_TRUE(inputSignal->connect());

//   DynamicPropertyAccess dynamic_property_access("/generator"_uri);
  
//   float not_exits;
//   ASSERT_ANY_THROW(dynamic_property_access.get("not_exists", not_exits));

//   float amplitude = 0.0;
//   float frequency = 0.5;
//   bool cosine = false;

//   ASSERT_TRUE(dynamic_property_access.set("amplitude", amplitude));

//   ASSERT_TRUE(dynamic_property_access.set("frequency", frequency));
//   ASSERT_TRUE(dynamic_property_access.set("cosine", cosine));

//   ASSERT_TRUE(dynamic_property_access.get("amplitude", amplitude));
//   ASSERT_TRUE(dynamic_property_access.get("frequency", frequency));
//   ASSERT_TRUE(dynamic_property_access.get("cosine", cosine));

//   Signal signalTest;
//   outputSignal->sendAsync(signalTest);

//   generator_sm.update();

//   auto value = std::shared_ptr<const Signal>();
//   ASSERT_EQ(ReceiveStatus::RECEIVE_OK, inputSignal->receive(value, 0ms));
  
//   //amplitude = 0, signal generated value has to be 0
//   EXPECT_EQ(value->value, amplitude);

//   generator_sm.reset();
// }

int main (int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}
}

