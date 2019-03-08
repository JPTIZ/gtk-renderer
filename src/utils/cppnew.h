#ifndef __UTILS_CPP_NEW_FEATURES_H
#define __UTILS_CPP_NEW_FEATURES_H

#include <memory>

namespace utils {

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}

}

#endif
