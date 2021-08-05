#include "main_lib.h"

namespace pars{
  std::vector<bool> gold(std::vector<bool> a, std::vector<bool> b){
    std::vector<bool> C;
    std::vector<bool> S;
    C.emplace_back((a[0]&b[0]));
    S.emplace_back((!C[0])&(a[0]|b[0]));
      for (int i = 1; 7 >= i; i++){
        C.emplace_back(((a[i]&b[i])|(C[i-1]&(a[i]|b[i]))));
        S.emplace_back((a[i]&b[i]&C[i-1])|((!C[i])&(a[i]|b[i]|C[i-1])));
      }
      S.emplace_back(C[7]);
      return S;
  } // модель сумматора

}
