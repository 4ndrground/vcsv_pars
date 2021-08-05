


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "main_lib.h"

int main(int argc, char* argv[])
{
  try {
    if (5 > argc)
      return std::cerr<<"Usage: $debug <file> <Vgmax> <Vgmin> <TS> <delay>\n", 1;

    
    double const Vgmax = strtod(argv[2], nullptr);
    double const Vgmin = strtod(argv[3], nullptr);
    double const TS = strtod(argv[4], nullptr);
    double const delay = strtod(argv[5], nullptr);

    if (Vgmax < Vgmin)
      return std::cerr << "Warning: Vgmax < Vgmin\n", 1;
    
    std::vector<pars::SignalStream> const storage = pars::open(argv[1]);
    std::vector<pars::DigSignalStream> bstor;

    for (int i=0; i < storage.size(); i++) {
      bstor.emplace_back(storage[i].name());
      int t = 0;
      for (int n=0; n < storage[i].length(); n++){
        if (delay + t*TS + TS/1000 >= storage[i][n].time &&
            delay + t*TS - TS/1000 <= storage[i][n].time){
          bstor[i].add(pars::calc(storage[i][n].v, Vgmax, Vgmin));
          t++;
        }
      }
    } //конец вычленения значений и перевод в двоичную форму
    //.........................проверка
    std::cout << "bstor contains " << bstor.size() << " elements\n";
    std::cout << "Here they are:\n";
    for (auto const& x:bstor) std::cout << x;

    pars::check(bstor, TS, delay);
    
    return 0;
  } catch (std::exception& e) {
    return std::cerr << "Error: " << e.what() << std::endl, 1;
  } catch (...) {
    return std::cerr << "Что-то пошло не так :-[\n", 1;
  }
}
