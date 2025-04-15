#pragma once

#include <maptio/polation.hpp> 

class Zero2DExtrapolation : public Polation2D {
    public:
     using Polation::polate;
     explicit Zero2DExtrapolation(
         const std::vector<std::vector<double> >& dataset);
 
     void polation_setup() override;
     double polate(double x) override;
 };