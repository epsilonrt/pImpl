/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#include "pimp.h"
#pragma once

struct PimpClass::Private {
    Private (PimpClass *q) : q_ptr (q) {} // constructor that initializes the q-ptr
    // default destructor, not default because of the unique_ptr ()
    virtual ~Private () = default;
    PimpClass *const q_ptr;  // q-ptr that points to the API class
};
