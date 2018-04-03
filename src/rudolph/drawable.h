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

    Point2D center() const {
        data->center();
    }

    void translate(int dx, int dy) {
        data->translate(dx, dy);
    }

    void scale(int sx, int sy) {
        data->scale(sx, sy);
    }

    void rotate_origin(double angle) {
        data->rotate_origin(angle);
    }

    void rotate_pin(double angle, Point2D pin) {
        data->rotate_pin(angle, pin);
    }

    void rotate_center(double angle) {
        data->rotate_center(angle);
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
        virtual Point2D center() const = 0;
        virtual void translate(int dx, int dy) = 0;
        virtual void scale(int sx, int sy) = 0;
        virtual void rotate_origin(double angle) = 0;
        virtual void rotate_pin(double angle, Point2D pin) = 0;
        virtual void rotate_center(double angle) = 0;
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

        Point2D center() const override {
            return x.center();
        }

        void translate(int dx, int dy) override {
            x.translate(dx, dy);
        }

        void scale(int sx, int sy) override {
            x.translate(sx, sy);
        }

        void rotate_origin(double angle) {
            x.rotate_origin(angle);
        }

        void rotate_pin(double angle, Point2D pin) {
            x.rotate_pin(angle, pin);
        }

        void rotate_center(double angle) {
            x.rotate_center(angle);
        }

        T x;
    };

    std::unique_ptr<Model> data;
}; // end class Drawable

} // end rudolph namespace

#endif