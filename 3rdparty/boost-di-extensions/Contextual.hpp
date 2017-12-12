//
// Copyright (c) 2012-2017 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cassert>
#include <string>
#include <vector>

#include <boost/di.hpp>

namespace di = boost::di;

//<-
template <class T>
auto get_type() {
#if defined(_MSC_VER)
    auto type = std::string{&__FUNCSIG__[28]};
  const auto i = type[0] == ' ' ? 1 : 0;
  return type.substr(i, type.length() - 7 - i);
#elif defined(__clang__)
    auto type = std::string{&__PRETTY_FUNCTION__[21]};
  return type.substr(0, type.length() - 1);
#elif defined(__GCC__)
    auto type = std::string{&__PRETTY_FUNCTION__[26]};
  return type.substr(0, type.length() - 1);
#else
#error "Platform not supported!"
#endif
}

struct context_type : std::string {};
struct contexts_list : std::vector<std::string> {};

template <class TInjector>
auto context(const TInjector& injector) noexcept {
    return injector.template create<context_type&>();
}

class contextual_bindings : public di::config {
public:
    template <class TInjector>
    static auto policies(const TInjector* injector) noexcept {
        return di::make_policies([&](auto type) {
            if (std::is_same<typename decltype(type)::type, context_type&>::value ||
                                                                        std::is_same<typename decltype(type)::type, contexts_list&>::value) {
            return;
        }
            using T = decltype(type);
            auto& v = injector->template create<contexts_list&>();
            using given = di::aux::decay_t<typename decltype(type)::type>;
            std::string element;
            if (!v.empty()) {
                element = v.back() + "->";
                auto& context = injector->template create<context_type&>();
                context.assign(v.back());
                v.pop_back();
            }
            auto ctor_size = T::arity::value;
            while (ctor_size--) {
                v.push_back(element + get_type<given>());
            }
        });
    }
};
