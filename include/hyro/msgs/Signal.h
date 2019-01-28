/** @file Signal.h
 *  @brief Struct description for signal message.
 *  @author Elizabete
 *  @bug No known bugs.
 */

#pragma once

#ifndef SIGNAL_GENERATOR_MSG_SIGNAL_H
#define SIGNAL_GENERATOR_MSG_SIGNAL_H

#include <signal_generator_components_export.h>
#include <string>

namespace hyro
{

struct SIGNAL_GENERATOR_COMPONENTS_EXPORT Signal
{
    int timestamp;
    std::string frame_id;
    float value;
};

}

#include <hyro/msgs/Signal.proto.h>

#endif // SIGNAL_H