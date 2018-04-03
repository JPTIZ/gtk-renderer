#ifndef RUDOLPH_DRAWABLE_H
#define RUDOLPH_DRAWABLE_H

#include "../utils.h"
#include <string>

namespace rudolph {

class RenderTarget;

class Drawable {
public:
    template <typename T>
    Drawable(T t):
        data{utils::make_unique<ModelImpl<T>>(std::move(t))}
    {}

    Drawable(const Drawable& other):
        data{other.data->copy()}
    {}

    Drawable(Drawable&& other):
        data{std::move(other.data)}
    {}

    void draw(RenderTarget& target) const {
        data->draw(target);
    }

    std::string name() const {
        return data->name();
    }

    void translate() {
        data->translate();
    }

private:
    /**
     * DrawableImpl components' interface
     */
    struct Model {
        virtual ~Model() = default;
        virtual std::unique_ptr<Model> copy() const = 0;
        virtual void draw(RenderTarget&) const = 0;
        virtual std::string name() const = 0;
        virtual void translate() = 0;
    };

    template <typename T>
    struct ModelImpl: Model {
        ModelImpl(T x):
            x{x}
        {}

        std::unique_ptr<Model> copy() const override {
            return utils::make_unique<ModelImpl>(*this);
        }

        void draw(RenderTarget& target) const override {
            x.draw(target);
        }

        std::string name() const override {
            return x.name();
        }

        void translate() override {
            x.translate();
        }

        T x;
    };

    std::unique_ptr<Model> data;
}; // end class Drawable

} // end rudolph namespace

#endif