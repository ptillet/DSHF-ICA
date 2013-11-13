/* ===========================
 *
 * Copyright (c) 2013 Philippe Tillet - National Chiao Tung University
 *
 * curveica - Hybrid ICA using ViennaCL + Eigen
 *
 * License : MIT X11 - See the LICENSE file in the root folder
 * ===========================*/

#include <cmath>
#include "tests/benchmark-utils.hpp"
#include "curveica.h"
#include "cblas.h"
#include <cstdlib>

#define BENCHMARK_COUNT 1

typedef float ScalarType;
static const unsigned int NC=4;
static const unsigned int NF=100000;
static const unsigned int T=20;

int main(){
    ScalarType * src = new ScalarType[NC*NF];
    ScalarType * mixing = new ScalarType[NC*NC];
    ScalarType * mixed_src = new ScalarType[NC*NF];
    ScalarType * independent_components = new ScalarType[NC*NF];

    for(unsigned int f=0 ; f< NF ; ++f){
        double t = (double)f/(NF-1)*T - T/2;
        src[0*NF + f] = std::sin(3*t) + std::cos(6*t);
        src[1*NF + f] = std::cos(10*t);
        src[2*NF + f] = std::sin(5*t);
        src[3*NF + f]  = std::sin(t*t);
    }

    for(std::size_t i = 0 ; i < NC ; ++i)
        for(std::size_t j = 0 ; j < NC ; ++j)
            mixing[i*NC+j] = static_cast<double>(rand())/RAND_MAX;


    cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,NF,NC,NC,1,src,NF,mixing,NC,0,mixed_src,NF);

    curveica::options options = curveica::make_default_options();
    options.verbosity_level = 2;
    options.optimization_method = curveica::HESSIAN_FREE;
    //options.optimization_method = curveica::SD;
    Timer t;
    t.start();
    for(unsigned int i = 0 ; i < BENCHMARK_COUNT ; ++i)
        curveica::inplace_linear_ica(mixed_src,independent_components,NC,NF,options);

    std::cout << "Execution Time : " << t.get()/BENCHMARK_COUNT << "s" << std::endl;

    delete[] src;
    delete[] mixing;
    delete[] mixed_src;
    delete[] independent_components;
}
