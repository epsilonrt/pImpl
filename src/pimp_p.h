/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#include "pimp.h"
#pragma once

/**
 * @brief The PimpClass::Private class
 * 
 * This class is the private class of the PimpClass class, it is used to hide the implementation of the PimpClass class.
 * Only the PimpClass class and childrens can access it.
 */
struct PimpClass::Private {
    /**
     * @brief Construct a new Private object
     * 
     * Constructor that initializes the q-ptr
     * 
     * @param q pointer to the API class
     */
    Private (PimpClass *q) : q_ptr (q) {}
    
    /**
     * @brief Destroy the Private object
     * 
     * virtual destructor to allow the destruction of the private class from the API class
     */
    virtual ~Private () = default;

    /**
     * @brief q-ptr that points to the API class
     */
    PimpClass *const q_ptr;
};
