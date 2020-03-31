#include "rclst_utils.hpp"

#include <fstream>
#include <sstream>


std::string saveLSamples(const Samples& samples,const Labels& lables, std::string fout){
    fout+=".sam";
    std::ofstream ofs(fout);
    assert(samples.size() == lables.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        ofs << (int)lables[i]<<','
            <<samples[i](0)<<','
            <<samples[i](1)<<','
            <<(int)samples[i](2)<<','
            <<(int)samples[i](3)<<','
            <<samples[i](4)<<','
            <<samples[i](5)<<','
            <<(int)samples[i](6)<<'\n';
    }
    return fout;
}

void formatData(std::string& line){
    auto p = line.find(";;");
    if(p!=std::string::npos)
        line.insert(p,"0");
}

double floorIndicate(std::size_t floor, std::size_t max_floor){
    return (floor == 0 || floor == max_floor) ? 0 :1;
}

Samples getSamples(std::istream& in){
    Samples samples;
    for(std::string line; std::getline(in,line);){
        formatData(line);
        char delim;
        if (!line.empty()) {
            std::size_t floor;
            std::size_t max_floor;
            std::istringstream iss(std::move(line));
            sample_type m;
            iss>>m(0)>>delim // X
               >>m(1)>>delim // Y
               >>m(2)>>delim //rooms
               >>m(3)>>delim //price
               >>m(4)>>delim //size
               >>m(5)>>delim //kitchen
               >>floor>>delim 
               >>max_floor;
            m(6) = floorIndicate(floor,max_floor);
            samples.push_back(m);
        }

    }
    return samples;
}
