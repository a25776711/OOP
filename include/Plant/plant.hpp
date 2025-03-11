//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"

class Plant : public Util::GameObject{
  protected:
    int HP;
    int money;

  public:
    void setposition(int x, int y){}
    virtual void behavoir() {}   //爆炸 社子彈..
    



}


#endif //PLANT_HPP
