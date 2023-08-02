/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#include "pimp_p.h"

// protected constructor
PimpClass::PimpClass (Private &dd) : d_ptr (&dd) {}

// default destructor
PimpClass::~PimpClass() {}
