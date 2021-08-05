#include <regex>
#include <string>
#include <iostream>
#include <fstream>

#include "main_lib.h"

#define NR "([-+]?[0-9]+[.]?[[0-9]*]?[eE]?[-+]?[[0-9]*]?),?"
#define EX std::ifstream

namespace pars {

std::vector<pars::SignalStream> open(char const* fname){
  std::vector<pars::SignalStream> storage;
  std::string line;
  std::ifstream fin(fname);
  fin.exceptions(EX::failbit | EX::badbit | EX::eofbit);
  std::regex pat(";([A-Za-z0-9_]+),?");
  std::smatch m;
  int lnum = 1;

  std::getline(fin, line);
  ++lnum;
  std::getline(fin, line);
  while (std::regex_search(line, m, pat)) {
    storage.emplace_back(m[1].str().c_str());
    line = m.suffix().str();
  }

  std::cout << "Storage contains " << storage.size() << " elements\n";
  std::cout << "Here they are:\n";
  for (auto const& x:storage) std::cout << x;
  
  std::regex Np(NR);
  std::string cont;
  double time;
  double v;
  int Xn;      
  while (lnum < 7){
    std::getline(fin, line);
    lnum++;
  }
  try{
    for (lnum; !fin.eof(); ++lnum) {
      Xn = 0;
      bool b = true;
      while (std::regex_search(line, m, Np)){
        cont = m[1].str();
        line = m.suffix().str();
        switch (b){
          case true:
            time = stod(cont);
            b = !b;
            break;
          case false: 
            v = stod(cont);
            storage[Xn].add(time, v);
            Xn++;
            b = !b;
            break;
        }
      }
      std::getline(fin, line);
    }
  } catch (std::exception &e) {
      if ((fin.rdstate() & std::ifstream::eofbit) != 0) {
        std::cout << "End of file parsing" << std::endl;
        fin.close();
      }
    } //конец парсинга
  
  std::cout << storage[1].name() << storage[0][0] <<std::endl;
  
  return storage;
} //open

} // namespace pars
