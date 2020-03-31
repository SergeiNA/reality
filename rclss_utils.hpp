#pragma once

#include "rclss_common.hpp"

#include <string>

ClusteredSamples getClusteredSamples(std::string fname);

sample_type parseInput(std::string);

void printResults(Samples samples, const sample_type& input);