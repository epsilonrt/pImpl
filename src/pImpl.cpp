/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#include "pImpl_p.h"

// protected constructor
PimplClass::PimplClass (Private &dd) : d_ptr (&dd) {}

// default destructor
PimplClass::~PimplClass() {}

// check if the object is null
bool PimplClass::isNull() const {

  return d_ptr == nullptr;
}

// clear or reset the object
void PimplClass::clear() 
{}