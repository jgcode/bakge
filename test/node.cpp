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

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

int main(int argc, char* argv[])
{
    bakge::Window* Win;
    bakge::Node* Point;

    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);

    Win = bakge::Window::Create(600, 400);
    if(Win == NULL) {
        printf("Error creating window\n");
        return bakge::Deinit();
    }

    Point = bakge::Node::Create(0, 0, 0);

    glClearColor(0, 0, 1, 1);
    glViewport(0, 0, 600, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.5, 0.1, 500.0);

    /* Make it easy to see our points */
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10);
    glHint(GL_POINT_SMOOTH, GL_NICEST);

    /* *
     * Test out node position setting/getting uses OpenGL buffers
     * */
    Point->Bind();
    /* Test this node's position */
    bakge::Vector4 Pos = Point->GetPosition();
    printf("%02.2lf %02.2lf %02.2lf\n", Pos[0], Pos[1], Pos[2]);

    /* Test at a new position */
    Point->SetPosition(3, 3, 1);
    Pos = Point->GetPosition();
    printf("%02.2lf %02.2lf %02.2lf\n", Pos[0], Pos[1], Pos[2]);
    Point->Unbind();

    while(1) {
        /* Poll events for all windows */
        bakge::Window::PollEvents();

        /* Don't draw if the window has closed */
        if(Win->IsOpen() == false)
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
        glColor3f(1, 1, 1);
        Point->Bind();
        Point->Draw(); /* No renderer for now */
        Point->Unbind();
        glMatrixMode(GL_PROJECTION);
        Win->SwapBuffers();
    }

    if(Win != NULL)
        delete Win;

    if(Point != NULL)
        delete Point;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}
