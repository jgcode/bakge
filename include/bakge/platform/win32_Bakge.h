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

#ifndef BAKGE_PLATFORM_WIN32_BAKGE_H
#define BAKGE_PLATFORM_WIN32_BAKGE_H

/* Disable some pesky MSVC warnings */
#pragma warning(disable : 4193)
#pragma warning(disable : 4005)
#define _CRT_SECURE_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN /* Really? */
#define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */

#include <windows.h>
#include <winsock2.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <bakge/mutex/win32_Mutex.h>
#include <bakge/thread/win32_Thread.h>
#include <bakge/socket/win32_Socket.h>

#endif /* BAKGE_PLATFORM_WIN32_BAKGE_H */
