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

#ifndef BAKGE_CORE_UTILITY_H
#define BAKGE_CORE_UTILITY_H

#include <bakge/Bakge.h>

#ifdef _DEBUG
#define BGE_ASSERT(PRED) \
    if(!(PRED)) { \
        fprintf(stderr, "Assertion failed at line %d in file %s\n" \
                        " - Predicate %s\n", \
        __LINE__, __FILE__, #PRED); \
        exit(-1); \
    }

#define BGE_ASSERT_EX(PRED, MSG) \
    if(!(PRED)) { \
        fprintf(stderr, "%s: at line %d in file %s\n" \
                        " - Predicate %s\n", \
        MSG, __LINE__, __FILE__, #PRED); \
        exit(-1); \
    }
#else
#define BGE_ASSERT(PRED)
#define BGE_ASSERT_EX(PRED, MSG)
#endif

namespace bakge
{

BGE_FUNC Result Init(int argc, char* argv[]);
BGE_FUNC Result Deinit();

BGE_FUNC void SystemInfo();

BGE_WUNUSED BGE_FUNC Byte* LoadFileContents(const char* Path);

} /* bakge */

#endif /* BAKGE_CORE_UTILITY_H */
