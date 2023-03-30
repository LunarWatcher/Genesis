#include "Framebuffer.hpp"
#include "genesis/conf/Settings.hpp"
#include "genesis/rendering/Constants.hpp"

#include <exception>
#include <stdexcept>

namespace genesis {

Framebuffer::Framebuffer(int width, int height) : Framebuffer(0, 0, width, height) {}

Framebuffer::Framebuffer(int x, int y, int width, int height) {
    glGenFramebuffers(1, &fbo);
    glGenRenderbuffers(1, &rbo);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    bind();
    tex = std::make_unique<Texture>(width, height);

    auto texId = tex->getID();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Failed to allocate framebuffer");
    }
    unbind();

    std::vector<GLfloat> positions{

            (GLfloat) x, (GLfloat) y + (GLfloat) height,
            (GLfloat) x, (GLfloat) y,
            (GLfloat) x + (GLfloat) width, (GLfloat) y,
            (GLfloat) x + (GLfloat) width, (GLfloat) y + (GLfloat) height,
    };
    model = std::make_unique<Model>(
        positions,
        [](Model* m) {
            m->createOrSubdataVBO(1, 2, Constants::fullImageUVCoords);
            m->bindIndexBuffer(Constants::fullCubeIndices);
        },
        2
    );


}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &fbo);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::render() {
    tex->bind();

    model->render();
    tex->unbind();
}

}
