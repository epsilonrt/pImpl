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
