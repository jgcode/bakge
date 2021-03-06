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

Texture::Texture()
{
    Location = GL_TEXTURE0;
    TextureID = 0;
}


Texture::~Texture()
{
    if(TextureID != 0)
        glDeleteTextures(1, &TextureID);
}


Result Texture::Bind() const
{
    glActiveTexture(Location);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    return BGE_SUCCESS;
}


Result Texture::Unbind() const
{
    glActiveTexture(Location);
    glBindTexture(GL_TEXTURE_2D, 0);
    return BGE_SUCCESS;
}


Texture* Texture::Create(int Width, int Height, GLint Format, GLenum Type,
                                                              void* Data)
{
    Texture* NewTexture = new Texture;

    /* Generate an OpenGL texture */
    glGenTextures(1, &(NewTexture->TextureID));

#ifdef _DEBUG
    /* Check if error occured while generating the texture */
    if(NewTexture->TextureID == 0) {
        printf("Error generating texture\n");
        delete NewTexture;
        return NULL;
    }
#endif /* _DEBUG */

    /* Bind the texture so we can set its parameters below */
    NewTexture->Bind();

    /* *
     * Set some parameters for our texture.
     * */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, Type,
                                                                    Data);

    NewTexture->Unbind();

    return NewTexture;
}

} /* bakge */
