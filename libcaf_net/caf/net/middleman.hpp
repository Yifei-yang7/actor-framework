/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright 2011-2019 Dominik Charousset                                     *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#pragma once

#include <thread>

#include "caf/actor_system.hpp"
#include "caf/net/fwd.hpp"

namespace caf {
namespace net {

class middleman : public actor_system::module {
public:
  // -- constructors, destructors, and assignment operators --------------------

  ~middleman() override;

  // -- interface functions ----------------------------------------------------

  void start() override;

  void stop() override;

  void init(actor_system_config&) override;

  id_t id() const override;

  void* subtype_ptr() override;

  // -- factory functions ------------------------------------------------------

  static actor_system::module* make(actor_system&, detail::type_list<>);

  // -- properties -------------------------------------------------------------

  const actor_system_config& config() const noexcept {
    return sys_.config();
  }

  const multiplexer_ptr& mpx() const noexcept {
    return mpx_;
  }

private:
  // -- constructors, destructors, and assignment operators --------------------

  explicit middleman(actor_system& sys);

  // -- member variables -------------------------------------------------------

  /// Points to the parent system.
  actor_system& sys_;

  /// Stores the global socket I/O multiplexer.
  multiplexer_ptr mpx_;

  /// Runs the multiplexer's event loop
  std::thread mpx_thread_;
};

} // namespace net
} // namespace caf
