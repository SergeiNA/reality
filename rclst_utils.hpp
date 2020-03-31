#pragma once

#include "rclst_common.hpp"

#include <iostream>
#include <string>

Samples getSamples(std::istream& in =std::cin);

std::string saveLSamples(const Samples& samples, const Labels&  lables, std::string fout);



