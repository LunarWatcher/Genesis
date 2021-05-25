#pragma once

#include "genesis/rendering/Renderable.hpp"

namespace genesis {

class

    class Text : public Renderable {
private:
    std::string content;

public:
    Text(const std::string& content);
    virtual void render() override;

    void setText(const std::string& content) {
        this->content = content;
    };
    std::string getContent() {
        return content;
    }
};

} // namespace genesis
