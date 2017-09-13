/** Runtime Init -*- C++ -*-
 * @file
 * @section License
 *
 * This file is part of Galois.  Galoisis a framework to exploit
 * amorphous data-parallelism in irregular programs.
 *
 * Galois is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Galois is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Galois.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * @section Copyright
 *
 * Copyright (C) 2015, The University of Texas at Austin. All rights
 * reserved.
 *
 * @section Description
 * Initializes the components of Galois::Runtime library
 *
 * @author M. Amber Hassaan<ahassaan@ices.utexas.edu>
 */

#ifndef GALOIS_RUNTIME_INIT_H
#define GALOIS_RUNTIME_INIT_H

#include "Galois/Runtime/Statistics.h"
#include "Galois/Runtime/PagePool.h"
#include "Galois/Substrate/Init.h"

#include <string>

namespace Galois {
namespace Runtime {

template <typename SM>
class SharedMemRuntime: public Galois::Substrate::SharedMemSubstrate {

  using Base = Galois::Substrate::SharedMemSubstrate;


  PageAllocState<> m_pa;
  SM m_sm;

public:
  explicit SharedMemRuntime(const std::string& statFile="")
    : 
      Base(), 
      m_pa(),
      m_sm(statFile)
    {
      setPagePoolState(&m_pa);
      setSysStatManager(&m_sm);
    }

  ~SharedMemRuntime(void) {
    m_sm.print();
    setSysStatManager(nullptr);
    setPagePoolState(nullptr);
  }
};

} // end namespace Runtime
} // end namespace Galois


#endif// GALOIS_RUNTIME_INIT_H
