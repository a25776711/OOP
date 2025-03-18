//
// Created by bingho on 2025/3/11.
//

#ifndef NORMAL_HPP
#define NORMAL_HPP
#include "Zombi/zombi.hpp"


class  normal : public  Zombi {
public:
    explicit normal();
    ~normal();

    virtual int Getreverse();

    virtual void MakeLoop();

    [[nodiscard]] bool IfAnimationEnds() const;

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    void SetPlaying(bool playing) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        if (playing) {
            temp->Play();
        }else {
            temp->Pause();
        }
    }

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }



private:
    int reverse=46;
    std::vector<std::string> m_ImagePaths;

};
#endif //NORMAL_HPP
