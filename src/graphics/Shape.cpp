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

#include <bakge/Bakge.h>

namespace bakge
{

Shape::Shape()
{
    DrawStyle = GL_TRIANGLES;
}


Shape::~Shape()
{
}


Result Shape::SetDrawStyle(BGE_SHAPE_STYLE Style)
{
    switch(Style) {

    case BGE_SHAPE_STYLE_EDGE:
        DrawStyle = GL_LINE_LOOP;
        break;

    case BGE_SHAPE_STYLE_SOLID:
        DrawStyle = GL_TRIANGLES;
        break;

    case BGE_SHAPE_STYLE_WIREFRAME:
        DrawStyle = GL_LINE_LOOP;
        break;

    case BGE_SHAPE_STYLE_POINTS:
        DrawStyle = GL_POINTS;
        break;

    default:
        return BGE_FAILURE;
    }

    return BGE_SUCCESS;
}


Result Shape::Bind() const
{
    Result Errors = BGE_SUCCESS;

    if(Mesh::Bind() == BGE_FAILURE)
        Errors = BGE_FAILURE;

    if(Pawn::Bind() == BGE_FAILURE)
        Errors = BGE_FAILURE;

     return Errors;
}


Result Shape::Unbind() const
{
    /* Always successful, no worries */
    Mesh::Unbind();

    return Pawn::Unbind();
}


Result Shape::Draw() const
{
    glDrawElements(DrawStyle, NumIndices, GL_UNSIGNED_INT, (GLvoid*)0);

    return BGE_SUCCESS;
}

} /* bakge */
