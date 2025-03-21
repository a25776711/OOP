//
// Created by bingho on 2025/3/11.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include "plant.hpp"

class Peashooter : public Plant{
  public:
  explicit Peashooter();
  protected:
    int shootspeed;
    int hurt;

  public:


#endif //PEASHOOTER_HPP
