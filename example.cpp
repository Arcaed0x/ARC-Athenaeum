#include <iostream>
#include "ARC.hpp"
#include <list>

bool greaterThan5(int x){ return x > 5; }
int mult5(int x) {return x*5;}
//Create Two functions

using IntFunctions = std::function<int (int)>;
//C++'s version of typedef used here just to make our types more readable

int main()
{
  //Create a vector of ints and vector of IntFunctions (Type alias above..)
  std::vector<int> d {5,7,63,41, 4, 23, 45};
  std::vector<IntFunctions> fs{[](int x){return x + 5;}, [](int x){ return x + 20;}};

  /*Create a delegate passing it three types
    First is the type passed to all functions.
    Second is the type returned by the last function provided to the delegate.
    Lastly is the type which will hold the intermidate values while function composition is occuring.
    the '+=' operator is used to add more functions to the composite function.
  */

  ARC::Functi<int , int, int> cf;
  cf += mult5;

  //The composite function is then called and the paramter is given for it to act on
  //NOTE this type must be the same as the first type provided to the delegate!
  std::cout << "Composite function: " << cf(1) << std::endl;


  //Creates a Functor (something that can be mapped over) by passing the constructor the type of objects contained in
  //the vector we are about to pass it. Then we pass a vector into the constructor.
  ARC::Functor<int> f{d};

  //With our functor we can run a filter on it, all we have to do is pass it a function that takes a paramter of
  //the type that is the same of that passed to the functor template arguments; then the function must return a bool.
  //essentially a predicate

  f .filter([](int x) { return x > 20; })
    .filter(greaterThan5);


  //Functors can also have functions mapped over them , thats what the map funtion is for. Thus map is a function that takes a function
  //and maps that function over every single element in the functor.
  f .map(cf);

  //Here we just want to get the vector back from the Functor and so we use its
  //getData function this returns a refrence to the undetlying vector.

  for (auto& x: f.getData())
  {
    std::cout << "Thing: " << x << std::endl;
  }
  //std::cin.get();
}
