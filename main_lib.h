#ifndef main_lib_h
#define main_lib_h

#include <vector>
#include <string>
#include <ostream>
 

namespace pars {

struct Dig_point {
  Dig_point() {}
  Dig_point(bool tval, bool tcor) : val{tval}, cor{tcor} {}
  Dig_point(Dig_point const& tdp) : val{tdp.val}, cor{tdp.cor} {}
  Dig_point& operator=(Dig_point const& d){val=d.val, cor=d.cor; return *this;}
  bool val; // цифровое значение
  bool cor; // корректность 
};
inline std::ostream& operator<<(std::ostream& s, Dig_point const& dpt) {
  switch (dpt.cor){
  case 0: return s << "incorrect value" << std::endl;
  case 1: return s << '(' << dpt.val << ')' << std::endl;
  }
}
struct Point {
  Point() {}
  Point(double tp, double vp) : time{tp}, v{vp} {}
  Point(Point const& pt) : time{pt.time}, v{pt.v} {}
  Point& operator=(Point const& pt) { time=pt.time, v=pt.v; return *this; }
  double time; // [s]
  double v; // Всё, что хочется
};

inline std::ostream& operator<<(std::ostream& s, Point const& pt) {
  return s << '(' << pt.time << ',' << pt.v << ')' << std::endl;
}

class SignalStream {
 public:
  SignalStream() : name_("__absent__"), pts_() {}
  SignalStream(char const* name) : name_{name}, pts_() {}
  char const* name() const { return name_.c_str(); }
  void add(Point const& pt) { pts_.push_back(pt); }
  void add(double time, double v) { pts_.emplace_back(time, v); }
  size_t length() const { return pts_.size(); }
  Point const& operator[](size_t idx) const { return pts_[idx]; }
  Point& operator[](size_t idx) { return pts_[idx]; }
 private:
  std::string name_;
  std::vector<Point> pts_;
};

class DigSignalStream { //проверить че каво
 public:
  DigSignalStream() : name_("__absent__"), dpts_() {}
  DigSignalStream(char const* name) : name_{name}, dpts_() {}
  char const* name() const { return name_.c_str(); }
  void add(Dig_point const& dpt) { dpts_.push_back(dpt); }
  void add(bool tval, bool tcor) { dpts_.emplace_back(tval, tcor); }
  size_t length() const { return dpts_.size(); }
  Dig_point const& operator[](size_t idx) const { return dpts_[idx]; }
  Dig_point& operator[](size_t idx) { return dpts_[idx]; }
 private:
  std::string name_;
  std::vector<Dig_point> dpts_;
};

inline std::ostream& operator<<(std::ostream& s, SignalStream const& ss) {
  return s << "SignalStream \"" << ss.name() << '\"' << std::endl;
}
inline std::ostream& operator<<(std::ostream& s, DigSignalStream const& dss) {
  return s << "DigSignalStream \"" << dss.name() << '\"' << std::endl;
}

//..........................функции

std::vector<pars::SignalStream> open(char const* fname);

pars::Dig_point calc(double V, double Vgmax, double Vgmin);

std::vector<bool> gold(std::vector<bool> a, std::vector<bool> b);

void check(std::vector<pars::DigSignalStream> const bstor,
           double TS, double delay);

} // namespace pars

#endif /* main_lib_h */
