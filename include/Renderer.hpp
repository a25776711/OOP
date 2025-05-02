#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>

#include "GameObject.hpp"

class App;

/**
 * @class Renderer
 * @brief A class handling GameObjects' Draw()
 * @see GameObject
 */
class Renderer final {
public:
    /**
     * @brief Parameterized constructor.
     *`
     *
     * @param children The GameObject needing to be managed by Renderer.
     */
    Renderer(const std::vector<std::shared_ptr<GameObject>> &children = {});

    /**
     * @brief Add a child to Renderer.
     *
     * @param child The GameObject needing to be managed by Renderer.
     */
    void AddChild(const std::shared_ptr<GameObject> &child);

    /**
     * @brief Add children to Renderer.
     *
     * @param children The GameObjects needing to be managed by Renderer.
     */
    void AddChildren(const std::vector<std::shared_ptr<GameObject>> &children);

    /**
     * @brief Remove the child.
     *
     * @param child The GameObject being removed.
     */
    void RemoveChild(std::shared_ptr<GameObject> child);

    /**
     * @brief Get all children managed by this Renderer.
     *
     * @return A vector containing all children.
     */
    const std::vector<std::shared_ptr<GameObject>> &GetChildren() const { return m_Children; }

    /**
     * @brief Draw children according to their z-index.
     *
     * @param offset 渲染的偏移量
     */
    void Update(const glm::vec2& offset = {0, 0});

private:
    std::vector<std::shared_ptr<GameObject>> m_Children;
};

#endif
