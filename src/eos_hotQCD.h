// Copyright 2018 @ Chun Shen

#ifndef SRC_EOS_hotQCD_H_
#define SRC_EOS_hotQCD_H_

#include "eos_base.h"

class EOS_hotQCD : public EOS_base {
 private:
   
 public:
    EOS_hotQCD();
    ~EOS_hotQCD() {}
    
    void initialize_eos();
    double get_cs2        (double e, double rhob) const;
    double p_rho_func     (double e, double rhob) const {return(0.0);}
    double p_e_func       (double e, double rhob) const;
    double get_temperature(double e, double rhob) const;
    double get_mu         (double e, double rhob) const {return(0.0);}
    double get_muS        (double e, double rhob) const {return(0.0);}
    double get_pressure   (double e, double rhob) const;
    double get_s2e        (double s, double rhob) const;

    void check_eos() const {check_eos_no_muB();}
};

#endif  // SRC_EOS_hotQCD_H_
