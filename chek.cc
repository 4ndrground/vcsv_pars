#include <vector>
#include <iostream>
#include <string>

#include "main_lib.h"

namespace pars{
void check(std::vector<pars::DigSignalStream> const bstor,
           double TS, double delay){
    bool corch;
    bool globcorch = true;
    std::string chname;

    for (int i = 0; i < bstor[0].length(); i++){
      corch = true;
      std::vector<bool> a;
      std::vector<bool> b;
      std::vector<bool> S;
      std::string chstring;
      for (int n = 0; n < bstor.size(); n++){
        if (bstor[n][i].cor == false) {
          std::cout << "#" << i <<" "<< bstor[n].name() <<" is uncorrect\n";
        }
        corch = corch & bstor[n][i].cor;
        chname = bstor[n].name();
        if ('A' == chname[0]) a.emplace_back(bstor[n][i].val);
        if ('B' == chname[0]) b.emplace_back(bstor[n][i].val);
        if ('S' == chname[0]) S.emplace_back(bstor[n][i].val);
      }
      if(pars::gold(a, b) == S && corch == true) globcorch = globcorch & true;
      else {
        std::cout << "\nin string #" << i << " at time:" <<(delay + i*TS);
        std::cout<< std::endl;
        std::cout << "an uncorrected value was found!\n";
        std::cout << "A value:\n";
        for(auto const& x:a) std::cout << x;
        std::cout << "\nB value:\n";
        for(auto const& x:b) std::cout << x;
        std::cout << "\ngold model value:\n";
        for(auto const& x:pars::gold(a,b)) std::cout << x;
        std::cout << "\nmodel value:\n";
        for(auto const& x:S) std::cout << x;
        std::cout << std::endl;
        globcorch = globcorch & false;
       }
    }
    if (globcorch == true) std::cout << "model is correct\n";
    else std::cout << "model is uncorrect\n";
}//vois chek
}//namespace pars

              
