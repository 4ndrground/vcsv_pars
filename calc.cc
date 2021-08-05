#include "main_lib.h"

namespace pars {

  pars::Dig_point calc(double V, double Vgmax, double Vgmin){
    bool val;
    bool cor;
    if (V >= Vgmax) {val = 1; cor = 1;}
    else {
      if (V > Vgmin) {val = 0; cor = 0;}
      else {val = 0; cor = 1;}
    }
    pars::Dig_point dp(val, cor);
    return dp;
  }
}
  
