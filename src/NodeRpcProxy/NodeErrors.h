/*
 * Copyright (c) 2017-2018, The Alloy Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Alloy.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#pragma once

#include <string>
#include <system_error>

namespace CryptoNote {
namespace error {

// custom error conditions enum type:
enum NodeErrorCodes {
  NOT_INITIALIZED = 1,
  ALREADY_INITIALIZED,
  NETWORK_ERROR,
  NODE_BUSY,
  INTERNAL_NODE_ERROR,
  REQUEST_ERROR,
  CONNECT_ERROR
};

// custom category:
class NodeErrorCategory : public std::error_category {
public:
  static NodeErrorCategory INSTANCE;

  virtual const char* name() const throw() override {
    return "NodeErrorCategory";
  }

  virtual std::error_condition default_error_condition(int ev) const throw() override {
    return std::error_condition(ev, *this);
  }

  virtual std::string message(int ev) const override {
    switch (ev) {
    case NOT_INITIALIZED:     return "Object was not initialized";
    case ALREADY_INITIALIZED: return "Object has been already initialized";
    case NETWORK_ERROR:       return "Network error";
    case NODE_BUSY:           return "Node is busy";
    case INTERNAL_NODE_ERROR: return "Internal node error";
    case REQUEST_ERROR:       return "Error in request parameters";
    case CONNECT_ERROR:       return "Can't connect to daemon";
    default:                  return "Unknown error";
    }
  }

private:
  NodeErrorCategory() {
  }
};

}
}
 
inline std::error_code make_error_code(CryptoNote::error::NodeErrorCodes e) {
  return std::error_code(static_cast<int>(e), CryptoNote::error::NodeErrorCategory::INSTANCE);
}
