#pragma once
#include <dlib/matrix.h>
#include <dlib/clustering.h>
#include <dlib/svm_threaded.h>

#include <vector>
#include <unordered_map>

using sample_type =  dlib::matrix<double,7,1>;
using Samples = std::vector<sample_type>;
using Labels =  std::vector<double>;
using ClusteredSamples = std::unordered_map<int,Samples>;

using ovo_trainer = dlib::one_vs_one_trainer<dlib::any_trainer<sample_type>>;
using poly_kernel = dlib::polynomial_kernel<sample_type>;
using rbf_kernel  = dlib::radial_basis_kernel<sample_type>;