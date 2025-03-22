//
// Created by bingho on 2025/3/11.
//

#ifndef SUN_HPP
#define SUN_HPP
#include  "Plant/plant.hpp"
#include <glm/glm.hpp>
class Sun : public Plant {
    public:
    explicit  Sun(std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {

    }
    void CollectAndMove(bool start,glm::vec2& des);
    private:

};
#endif //SUN_HPP
