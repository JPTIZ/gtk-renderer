#ifndef __UTILS_SIGNALS_H
#define __UTILS_SIGNALS_H

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "../app/app.h"

namespace utils {

using Rudolph = rudolph::app::Rudolph;
using BuilderPtr = Glib::RefPtr<Gtk::Builder>;

template <typename T>
using fn = std::function<T>;

template <typename R, typename ...T>
using Proxy = Glib::SignalProxy<R, T...>;

// template <typename ProxyType, typename T>
// using Signal = fn<ProxyType(T*)>;

using Bind = std::tuple<std::string, fn<void()>, fn<void()>>;

/**
 * Extracts element of type T from builder with given ID.
 */
template <typename T>
T& extract(
        Rudolph::ElementMap& elms,
        const BuilderPtr builder,
        const std::string& id
) {
    auto elm = utils::get_widget<T>(builder, id);
    elms[id] = elm;
    return *elm;
}

/**
 * Expected callback signature for each event type.
 */
template <typename R, typename ...T>
struct CallbackBase {
    using BareSig = R(T...);
    using Function = fn<BareSig>;
    using Proxy = utils::Proxy<R, T...>;

    using WidgetType = void;

    template<typename Y>
    struct Signal {};
};

/**
 * Define custom Callbacks here!
 */
struct Callback {
    struct Clicked: CallbackBase<void> {};
    struct Draw: CallbackBase<bool, const Cairo::RefPtr<Cairo::Context>&> {};
};

/**
 * Set the function that gives the Glib::SignalProxy for each Widget.
 */
template <typename CallbackType, typename WidgetType>
struct Signal {};

template <typename T>
struct Signal<Callback::Clicked, T> {
    constexpr static auto SignalFunction = &T::signal_clicked;
};

template <typename T>
struct Signal<Callback::Draw, T> {
    constexpr static auto SignalFunction = &T::signal_draw;
};

template <typename CallbackType>
using Connection = std::tuple<std::string, typename CallbackType::Function>;

/**
 * Connects an element's signal with callback.
 * What element is defined by its ID on current UI file opened on builder.
 *
 * ProxyType is the expected Glib::SignalProxy to bem connected (e.g.
 * "signal_clicked").
 *
 * Callback is the callback signature expected by ProxyType.
 */
template <typename CallbackType, typename WidgetType>
void sig(
        Rudolph::ElementMap& elms,
        const BuilderPtr builder,
        const std::string& id,
        typename CallbackType::Function c
) {
    auto sog = Signal<CallbackType, WidgetType>::SignalFunction;

    auto seg = std::function<typename CallbackType::Proxy(WidgetType*)>(sog);
    auto& elm = extract<WidgetType>(elms, builder, id);
    seg(&elm).connect(c);
}


/**
 * Links all signals into their callbacks.
 */
template <typename CallbackType, typename WidgetType>
void link_all(
    Rudolph::ElementMap& elms,
    const BuilderPtr builder,
    const std::vector<Connection<CallbackType>>& signals
) {
    for (auto& btn: signals) {
        sig<CallbackType, WidgetType>(
            elms,
            builder,
            std::get<0>(btn),
            std::get<1>(btn)
        );
    }
}

/**
 * Just to make typing "std::make_tuple" easier.
 */
template <typename... T>
std::tuple<T...> signal(T&& ...args)
{
    return std::make_tuple(std::forward<T>(args)...);
}

}

#endif
