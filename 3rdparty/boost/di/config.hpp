//
// Copyright (c) 2012-2017 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_CONFIG_HPP
#define BOOST_DI_CONFIG_HPP

#include "boost/di/aux_/type_traits.hpp"
#include "boost/di/aux_/utility.hpp"
#include "boost/di/concepts/callable.hpp"
#include "boost/di/core/pool.hpp"
#include "boost/di/providers/stack_over_heap.hpp"

#if !defined(BOOST_DI_CFG)                       // __pph__
#define BOOST_DI_CFG BOOST_DI_NAMESPACE::config  // __pph__
#endif                                           // __pph__

template <class... TPolicies, __BOOST_DI_REQUIRES_MSG(concepts::callable<TPolicies...>) = 0>
inline auto make_policies(TPolicies... args) noexcept {
  return core::pool_t<TPolicies...>(static_cast<TPolicies&&>(args)...);
}

struct config {
  template <class T>
  static auto provider(T*) noexcept {
    return providers::stack_over_heap{};
  }
  template <class T>
  static auto policies(T*) noexcept {
    return make_policies();
  }
};

#endif
