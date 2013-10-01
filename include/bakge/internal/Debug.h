/* *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

/*!
 * @file Debug.h
 * @brief Internal header with debugging macros and global functions.
 */

#ifndef BAKGE_INTERNAL_DEBUG_H
#define BAKGE_INTERNAL_DEBUG_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief GLFW error handler function.
 *
 * GLFW error handler function.
 *
 * @param[in] Code GLFW error code
 * @param[in] Description String description of error.
 */
void GLFWErrorHandler(int Code, const char* Description);

/*! @brief Get a string representation of an OpenGL error flag.
 *
 * Get a string representation of an OpenGL error flag.
 *
 * @return String constant of the OpenGL error flag.
 */
const char* GetGLErrorName(GLenum Error);

} // bakge

#endif // BAKGE_INTERNAL_DEBUG_H
