#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include "rclst_common.hpp"
#include "rclst_utils.hpp"

using namespace std;
using namespace dlib;

double gamma_m =  0.1;
double coeff =  1;
double degree = 2;


int main(int argc, char* argv[]){

    if (argc <= 1) {
        cout << "rclst <n> <isCrv> <nfoldcv> <fname> \n"
                "n -- clusters number 1,2,..N\n"
                "isCrv -- 0 - turn off, 1 -turn on cross-validation\n"
                "nfoldcv -- fold of cross-validation\n"
                "fname --  outut files: .mod - model data, .sam - sapmles with clisters\n"
                "Example: rclst 4 out1\n";
        return 0;
    }

    std::string nClusters(argv[1]);

    if (!(std::all_of(nClusters.begin(), nClusters.end(), ::isdigit))) {
        std::cerr << "Number of clusrers is incorrect" << std::endl;
        return 1;
    }
    std::size_t nclst = std::stoul(nClusters);

    std::string outFiles(argv[2]);
    if(outFiles.empty()){
        std::cerr << "Output file name is empty" << std::endl;
        return 1;
    }

    auto samples = getSamples();
    
    Labels labels;

    // clusterization-----------------------------------------

    kcentroid<rbf_kernel> kc(rbf_kernel(0.1),0.01, 8);
    // kcentroid<rbf_kernel> kc{rbf_kernel{gamma_m}};
    kkmeans<rbf_kernel> test{kc};
    Samples initial_centers;
    test.set_number_of_centers(nclst);
    pick_initial_centers(nclst, initial_centers, samples, test.get_kernel());
    test.train(samples, initial_centers);

    labels.reserve(samples.size());
    for (const auto& s : samples)
        labels.emplace_back(test(s));

    saveLSamples(samples,labels, outFiles);

    // model train -----------------------------------------
    ovo_trainer trainer;

    dlib::krr_trainer<rbf_kernel> rbf_trainer;
    dlib::svm_nu_trainer<poly_kernel> poly_trainer;
    rbf_trainer.set_kernel(rbf_kernel(gamma_m));
    poly_trainer.set_kernel(poly_kernel(gamma_m, coeff, degree));

    // Now tell the one_vs_one_trainer that, by default, it should use the rbf_trainer
    // to solve the individual binary classification subproblems.
    trainer.set_trainer(rbf_trainer);
    // We can also get more specific.  Here we tell the one_vs_one_trainer to use the
    // poly_trainer to solve the class 1 vs class 2 subproblem.  All the others will
    // still be solved with the rbf_trainer.
    trainer.set_trainer(poly_trainer, 1, 2);

    // Next, if you wanted to obtain the decision rule learned by a one_vs_one_trainer you
    // would store it into a one_vs_one_decision_function.
    dlib::one_vs_one_decision_function<ovo_trainer> df = trainer.train(samples, labels);
    // If you want to save a one_vs_one_decision_function to disk, you can do
    // so.  However, you must declare what kind of decision functions it contains.
    dlib::one_vs_one_decision_function<ovo_trainer,
            dlib::decision_function<poly_kernel>,  // This is the output of the poly_trainer
            dlib::decision_function<rbf_kernel>    // This is the output of the rbf_trainer
        > df2;


    // save model data

    // Put df into df2 and then save df2 to disk.  Note that we could have also said
    // df2 = trainer.train(samples, labels);  But doing it this way avoids retraining.
    df2 = df;
    dlib::serialize(outFiles+string(".mod")) << df2;     
}