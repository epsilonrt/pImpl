/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#pragma once
#include "pImpl.h"

/**
 * @brief The PimplClass::Private class
 * 
 * This class is the private class of the PimplClass class, it is used to hide the implementation of the PimplClass class.
 * Only the PimplClass class and childrens can access it.
 */
struct PimplClass::Private {
    /**
     * @brief Construct a new Private object
     * 
     * Constructor that initializes the q-ptr
     * 
     * @param q pointer to the API class
     */
    Private (PimplClass *q) : q_ptr (q) {}
    
    /**
     * @brief Destroy the Private object
     * 
     * virtual destructor to allow the destruction of the private class from the API class
     */
    virtual ~Private () = default;

    /**
     * @brief q-ptr that points to the API class
     */
    PimplClass *const q_ptr;
};
