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
  class Functor
  {
    public:
      template <typename T>
      Functor(T& d):data{std::move(d)}{};

      template <typename P>   
      Functor& filter(P p){ data.erase(std::remove_if(data.begin(), data.end(), p), data.end()); return *this;}
      
      template <typename FN>
      Functor& map(FN f) { std::transform(data.begin(), data.end(), data.begin(), f); return *this;}
      
      template <typename DT>
      DT& getData(){return std::move(data);}

    private:
      auto data;
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
