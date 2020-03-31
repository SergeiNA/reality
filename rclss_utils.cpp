
#include "rclss_utils.hpp"

#include <fstream>
#include <algorithm>

void print(const Samples& samples, std::ostream& os){
    for (size_t i = 0; i < samples.size(); ++i) {
            os<<samples[i](0)<<';'
            <<samples[i](1)<<';'
            <<(int)samples[i](2)<<';'
            <<(int)samples[i](3)<<';'
            <<samples[i](4)<<';'
            <<samples[i](5)<<';'
            <<(int)samples[i](6)<<'\n';
    }
}

ClusteredSamples getClusteredSamples(std::string fname){
    fname +=".sam";

    std::ifstream ifs(fname);
    if(!ifs)
        throw "getClusteredSamples() can not open file";
    
    ClusteredSamples csamples;
    for(std::string line; std::getline(ifs,line);){
        
        char delim;
        if (!line.empty()) {
            int cluster;
            std::istringstream iss(std::move(line));
            iss>>cluster>>delim;
            sample_type m;
            iss>>m(0)>>delim // X
               >>m(1)>>delim // Y
               >>m(2)>>delim //rooms
               >>m(3)>>delim //price
               >>m(4)>>delim //size
               >>m(5)>>delim //kitchen
               >>m(6); 
            csamples[cluster].push_back(m);
        }

    }
    return csamples;
}

sample_type parseInput(std::string line){
    char delim;
    sample_type m;
    if (!line.empty()) {
        std::istringstream iss(std::move(line));
        iss>>m(0)>>delim // X
            >>m(1)>>delim // Y
            >>m(2)>>delim //rooms
            >>m(3)>>delim //price
            >>m(4)>>delim //size
            >>m(5)>>delim //kitchen
            >>m(6); 
    }
    return m;
}



void printResults(Samples samples, const sample_type& sample){
    std::sort(samples.begin(),samples.end(),
     [&sample](const auto& lhs, const auto& rhs){
       double lhs_d = pow(lhs(0) - sample(0),2) + pow(lhs(1) - sample(1),2);
       double rhs_d = pow(rhs(0) - sample(0),2) + pow(rhs(1) - sample(1),2);
       return lhs_d < rhs_d;
     }
     );
    std::cout<<"Results:\n";
    print(samples, std::cout);
}