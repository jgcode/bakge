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

#ifndef BAKGE_MATH_MATRIX_H
#define BAKGE_MATH_MATRIX_H

#include <bakge/Bakge.h>

namespace bakge
{

/* *
 * 4x4 matrix. Used to store matrices for use in OpenGL
 * The matrices are stored in column-major form, much like OpenGL's, for
 * faster multiplication.
 *
 * They will most often be used to store matrix transforms that need to be
 * quickly loaded into OpenGL on a regular bases -- such as projection
 * matrices for 2D and 3D renderers.
 *
 * Position and/or rotation data can be described with a Node or Pawn object.
 * */
class BGE_API Matrix
{
    Scalar Val[16];


public:

    static const Matrix Identity;

    Matrix();
    ~Matrix();

    BGE_INL Scalar BGE_NCP operator[](int BGE_NCP At) const
    {
        return Val[At];
    }


    BGE_INL Scalar& operator[](int BGE_NCP At)
    {
        return Val[At];
    }

    /* Set to an identity matrix */
    Matrix BGE_NCP SetIdentity();

    /* Create a perspective matrix transform */
    Matrix BGE_NCP SetPerspective(Scalar FOV, Scalar Aspect, Scalar NearClip,
                                                            Scalar FarClip);

    /* Create a viewing matrix transform */
    Matrix BGE_NCP SetLookAt(Vector4 BGE_NCP Position, Vector4 BGE_NCP Target,
                                                    Vector4 BGE_NCP UpVector);

}; /* Matrix */

} /* bakge */

#endif /* BAKGE_MATH_MATRIX_H */
