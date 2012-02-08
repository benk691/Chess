/** \defgroup group2 Debug
 *  This is the source code group.
 *  \{
 */

/*! \file Debug.h
 *  \brief The code that debugs the program
 *  \author Benjamin Kellogg
 *  \details
 *  E-Mail Address:     benk691@gmail.com
 *
 *  Comments:           This code uses Doxygen styled comments.
 *
 *  Copyright ©2011-2012 Benjamin Kellogg all rights are reserved.
 *  \version 1.0
 *  \date October 25, 2011
 */

#pragma once
#ifndef __DEBUG_H__
#define __DEBUG_H__

//! Defines whether the program should be debugged or not
#define DEBUG 1

/*!
 * Specifies that a class should not be
 * debugged.
 * \param cn the class name.
 */
#define NDEBUG_CLASS(cn) \
    bool DEBUG_##cn = false;

/*!
 * Specifies that a class should be
 * debugged.
 * \param cn the class.
 */
#define DEBUG_CLASS(cn) \
    bool DEBUG_##cn = true;

/*!
 * Specifies that a class member function
 * should be not debugged.
 * \param cn the class name.
 * \param funct the member function name.
 */
#define NDEBUG_CLASS_FUNCT(cn, funct) \
    bool DEBUG_##cn_##funct = false;

/*!
 * Specifies that a class member function
 * should be debugged.
 * \param cn the class name.
 * \param funct the member function name.
 */
#define DEBUG_CLASS_FUNCT(cn, funct) \
    bool DEBUG_##cn_##funct = true;

/*!
 * Specifies that a function
 * should be not debugged.
 * \param funct the function name.
 */
#define NDEBUG_FUNCT(funct) \
    bool DEBUG_##funct = false;

/*!
 * Specifies that a function
 * should be debugged.
 * \param funct the function name.
 */
#define DEBUG_FUNCT(funct) \
    bool DEBUG_##funct = true;

#endif //__DEBUG_H__

/** \} */
