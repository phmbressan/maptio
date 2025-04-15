#pragma once

#include <maptio/polation.hpp> 

class Linear2DInterpolation : public Polation2D {
    public:
     using Polation::polate;
     explicit Linear2DInterpolation(
         const std::vector<std::vector<double> >& dataset);
 
     void polation_setup() override;
     double polate(double x) override;
 };