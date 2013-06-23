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

#ifndef BAKGE_EXAMPLE_SIMPLEENGINE_H
#define BAKGE_EXAMPLE_SIMPLEENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

/* *
 * SimpleEngine is a primitive engine class
 * which does no event handling and just draws
 * a shaded sphere to the screen. Just an example of
 * setting up an Engine class to wrap required components
 * of the application together.
 * */
class SimpleEngine : bakge::Engine
{

public:

    SimpleEngine();
    ~SimpleEngine();

    bakge::Result Initialize();
    bakge::Result ShutDown();
    int Run();

    bakge::Result Update(bakge::Seconds DeltaTime);

    bakge::Result PreRenderStage();
    bakge::Result RenderStage();
    bakge::Result PostRenderStage();


protected:

    bakge::Window* AppWindow;
    bakge::FrontRenderer* SceneRenderer;

    GLUquadric* Quadric;

};

#endif /* BAKGE_EXAMPLE_SIMPLEENGINE_H */
