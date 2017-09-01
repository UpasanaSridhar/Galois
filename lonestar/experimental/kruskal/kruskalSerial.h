/** Kruskal Serial ordered version -*- C++ -*-
 * @file
 * @section License
 *
 * Galois, a framework to exploit amorphous data-parallelism in irregular
 * programs.
 *
 * Copyright (C) 2011, The University of Texas at Austin. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT AND WARRANTIES OF
 * PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE ARISE FROM COURSE OF
 * DEALING OR USAGE OF TRADE.  NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH
 * RESPECT TO THE USE OF THE SOFTWARE OR DOCUMENTATION. Under no circumstances
 * shall University be liable for incidental, special, indirect, direct or
 * consequential damages or loss of profits, interruption of business, or
 * related expenses which may arise from use of Software or Documentation,
 * including but not limited to those resulting from defects in Software and/or
 * Documentation, or loss or inaccuracy of data of any kind.
 *
 * @section Description
 *
 * Kruskal Serial ordered version.
 *
 * @author <ahassaan@ices.utexas.edu>
 */

#ifndef _KRUSKAL_SERIAL_H_
#define _KRUSKAL_SERIAL_H_

#include "kruskalData.h"
#include "kruskalFunc.h"
#include "kruskal.h"

class KruskalSerial: public Kruskal<KNode> {
protected:

  virtual const std::string getVersion () const { return "Serial Ordered Kruskal"; }

  virtual void runMST (VecKNode_ty& nodes, VecKEdge_ty& edges,
      size_t& mstWeight, size_t& totalIter) {


    std::sort (edges.begin (), edges.end (), KEdge<KNode>::PtrComparator ());

    size_t mstSum = 0;
    size_t iter = 0;
    size_t numUnions = 0;

    for (VecKEdge_ty::const_iterator i = edges.begin (), ei = edges.end ();
        i != ei; ++i) {

      ++iter;

      if (kruskal::contract (**i)) {
        ++numUnions;
        mstSum += (*i)->weight;
      }
      

      if (numUnions == (nodes.size () - 1)) {
        break;
      }

    }

    mstWeight = mstSum;
    totalIter = iter;

  }

};

#endif // _KRUSKAL_SERIAL_H_