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
#include <bakge/internal/Utility.h>
#ifdef _DEBUG
#include <bakge/internal/Debug.h>
#endif // _DEBUG
#define HAVE_SNPRINTF // Always use portable_*printf functions
#define PREFER_PORTABLE_SNPRINTF
extern "C"
{
#include <snprintf/snprintf.h>
}

namespace bakge
{

static PHYSFS_File* LogFile = NULL;
static Mutex* LogLock = NULL;

Result Init(int argc, char* argv[])
{
    if(PHYSFS_init(argv[0]) == 0) {
        fprintf(stderr, "Error initializing PhysicsFS\n");
        return Deinit();
    }

    if(PHYSFS_addToSearchPath(".", 0) == 0) {
        fprintf(stderr, "Error mounting running directory: %s\n",
                                            PHYSFS_getLastError());
        return Deinit();
    }

    if(PHYSFS_setWriteDir(".") == 0) {
        fprintf(stderr, "Error setting write directory: %s\n",
                                            PHYSFS_getLastError());
        return Deinit();
    }

    LogFile = PHYSFS_openWrite("bakge.log");
    if(LogFile == NULL) {
        fprintf(stderr, "Error opening log file: %s\n", PHYSFS_getLastError());
        return Deinit();
    }

    LogLock = bakge::Mutex::Create();
    if(LogLock == NULL) {
        fprintf(stderr, "Error creating log mutex\n");
        return Deinit();
    }

    if(!glfwInit()) {
        Log("GLFW initialization failed\n");
        return Deinit();
    }

#ifdef _DEBUG
    glfwSetErrorCallback(GLFWErrorHandler);
#endif // _DEBUG

    /* We don't want the shared context window visible */
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    /* Create our shared context window */
    Window::SharedContext = glfwCreateWindow(16, 16, "", NULL, NULL);
    if(Window::SharedContext == NULL) {
        Log("Error creating shared context\n");
        return Deinit();
    }

    /* Need to make context current so we can init the shader library */
    glfwMakeContextCurrent(Window::SharedContext);

    /* So future GLFW windows are visible */
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        Log("Error initializing GLEW\n");
        return Deinit();
    }

    // Check for required OpenGL extensions to run Bakge
    if(!CheckRequiredExtensions()) {
        return Deinit();
    }

    /* Run platform-specific initialization protocol */
    if(PlatformInit(argc, argv) != BGE_SUCCESS)
        return Deinit();

    /* Initialize our Bakge shader library */
    if(Shader::InitShaderLibrary() != BGE_SUCCESS) {
        Log("Failed to initialize shader library\n");
        return Deinit();
    }

    Log("Bakersfield Game Engine v%d.%d.%d\n", BGE_VER_MAJ, BGE_VER_MIN,
                                                            BGE_VER_REV);

    SystemInfo();

    return BGE_SUCCESS;
}


Result Deinit()
{
    if(LogFile != NULL && PHYSFS_close(LogFile) == 0) {
        fprintf(stderr, "Error closing log file\n");
    }

    if(PHYSFS_isInit() != 0)
        PHYSFS_deinit();

    if(LogLock != NULL)
        delete LogLock;

    /* Run platform-specific deinitialization protocol */
    PlatformDeinit();

    Shader::DeinitShaderLibrary();

    /* Destroy our shared context window */
    if(Window::SharedContext != NULL)
        glfwDestroyWindow(Window::SharedContext);

    glfwTerminate();

    return BGE_FAILURE;
}


void SystemInfo()
{
    extern void PlatformSystemInfo();

    PlatformSystemInfo();

    Log("OpenGL v%s\n", glGetString(GL_VERSION));
    Log("GLSL v%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}


int Log(const char* Format, ...)
{
    va_list ArgList;

    char Buf[1024];
    va_start(ArgList, Format);

    bakge::Microseconds Time = bakge::GetRunningTime();

    // 3.6 billion microseconds per hour
    uint64 Hour = Time / 3600000000;

    // Remaining microseconds (this amounts to less than one hour)
    uint32 Rem = Time % 3600000000;
    uint32 Min = Rem / 60000000;

    // Remaining microseconds now amounts to less than one minute
    Rem %= 60000000;
    uint32 Sec = Rem / 1000000;

    // Our remaining microseconds converted to milliseconds
    Rem %= 1000000;
    Rem /= 1000;

    LogLock->Lock();

    // Write the timestamp
    int Len = portable_snprintf(Buf, 1024, "[%02llu:%02u:%02u.%03u] ",
                                                Hour, Min, Sec, Rem);

    PHYSFS_sint64 Error = PHYSFS_write(LogFile, Buf, 1, Len);
    if(Error < 0) {
        fprintf(stderr, "Error writing to log: %s\n", PHYSFS_getLastError());
        return -1;
    } else if(Error < Len) {
        fprintf(stderr, "Incomplete write to log: %s\n",
                                PHYSFS_getLastError());
    }

#ifdef _DEBUG
    fprintf(stdout, "[%02llu:%02u:%02u.%03u] ", Hour, Min, Sec, Rem);
    vfprintf(stdout, Format, ArgList);
#endif // _DEBUG

    // Now write the message
    Len = portable_vsnprintf(Buf, 1024, Format, ArgList);

    // Write message
    Error = PHYSFS_write(LogFile, Buf, 1, Len);
    if(Error < 0) {
        fprintf(stderr, "Error writing to log: %s\n", PHYSFS_getLastError());
        return -1;
    } else if(Error < Len) {
        fprintf(stderr, "Incomplete write to log: %s\n",
                                    PHYSFS_getLastError());
    }

    // Always flush in case a crash happens
    if(PHYSFS_flush(LogFile) == 0)
        fprintf(stderr, "Error flushing log: %s\n", PHYSFS_getLastError());

    LogLock->Unlock();

    va_end(ArgList);

    return Len;
}

} /* bakge */
