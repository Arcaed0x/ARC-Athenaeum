/*
  DO NOT REMOVE THIS COPYRIGHT INFORMATION
  PROPERTY OF ARCAEDOX COPYRIGHT 2014. ALL RIGHTS RESERVED
  @AUTHOR : ARCAEDOX
  @VERSION: 0.1.5 [ALPHA]
  @DATE: 24 - 04 - 2015
*/

#pragma once

#include <algorithm>
#include <vector>
#include <functional>

namespace ARC
{

  template <typename DT>
  class Functor
  {
    public:
      template <typename T>
      Functor(T& d):data{std::move(d)}{};

      template <typename P>
      Functor& filter(P p){ data.erase(std::remove_if(data.begin(), data.end(), p), data.end()); return *this;}

      template <typename FN>
      Functor& map(FN f) { std::transform(data.begin(), data.end(), data.begin(), f); return *this;}

      std::vector<DT> getData(){return std::move(data);}

    private:
      std::vector<DT> data;
  };

  template <typename T,typename TX>
  class Functi
  {
    using VecOfFunctions = std::vector<std::function<TX (T)>>;
    public:
      Functi():funcs{[](T x){return x;}}{};
      Functi(VecOfFunctions fs):funcs{std::move(fs)}{};

      void operator+=(std::function<TX (T)> f){
        funcs.push_back(f);
      }

      template <typename V>
      TX operator()(V a){
        V val = a;
        for (auto& f: funcs){
          val = f(val);
        }
        return val;
      }


    private:
      VecOfFunctions funcs;
      //V val;
  };
}
