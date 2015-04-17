/*
  DO NOT REMOVE THIS COPYRIGHT INFORMATION
  PROPERTY OF ARCAEDOX COPYRIGHT 2014. ALL RIGHTS RESERVED
  @AUTHOR : ARCAEDOX
  @VERSION: 0.1.1 [ALPHA]
  @DATE: 17 - 04 - 2015
*/

#pragma once

namespace ARC
{
  template <typename T>
  class Functor
  {
    using Predicate = std::function<bool (T)>;
    using Function = std::function<T (T)>;
    public:
      Functor(std::vector<T>& d):data{std::move(d)}{};
      Functor& filter(Predicate p){ data.erase(std::remove_if(data.begin(), data.end(), p), data.end()); return *this;}
      Functor& map(Function f) { std::transform(data.begin(), data.end(), data.begin(), f); return *this;}
      std::vector<T>& getData(){return data;}

    private:
      std::vector<T> data;
  };

  template <typename T,typename TX, typename V>
  class Delegate
  {
    using VecOfFunctions = std::vector<std::function<TX (T)>>;
    public:
      Delegate():val{0},funcs{[](T x){return x;}}{};
      Delegate(VecOfFunctions fs):funcs{std::move(fs)},val{0}{};

      void operator+=(std::function<TX (T)> f){
        funcs.push_back(f);
      }

      V operator()(T a){
        val = a;
        for (auto& f: funcs){
          val = f(val);
        }
        return val;
      }


    private:
      VecOfFunctions funcs;
      V val;
  };
}
