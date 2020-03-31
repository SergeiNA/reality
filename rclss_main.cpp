// Help

// parsing cmd

// load model

// classification

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include "rclss_common.hpp"
#include "rclss_utils.hpp"

using namespace std;
using namespace dlib;


int main(int argc, char* argv[]){

    if (argc <= 1) {
        cout << "rclss <fname> \n"
                "fname --  input files: .mod - model data, .sam - sapmles with clisters\n"
                "Example: rclst models1\n";
        return 0;
    }

try
{
    std::string inputFiles(argv[1]);
    if(inputFiles.empty()){
        std::cerr << "Input file name is empty" << std::endl;
        return 1;
    }

    //load samples with into hash map

    auto csamples = getClusteredSamples(inputFiles);

    // load model
    dlib::one_vs_one_decision_function<ovo_trainer,
               dlib::decision_function<poly_kernel>,  // This is the output of the poly_trainer
               dlib::decision_function<rbf_kernel>    // This is the output of the rbf_trainer
           > df3;

    dlib::deserialize(inputFiles+string(".mod")) >> df3;

    //get input and return sorted cluster

    for(std::string line; std::getline(std::cin,line);){
        
        auto input_sample = parseInput(line);

        int predictLabel = (int)df3(input_sample);

        printResults(csamples.at(predictLabel), input_sample);

    }
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

}