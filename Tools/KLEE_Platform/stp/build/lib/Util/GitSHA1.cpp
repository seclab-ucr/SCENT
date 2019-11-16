/********************************************************************
 * AUTHORS: Mate Soos, Trevor Hansen
 *
 * BEGIN DATE: November, 2005
 *
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
********************************************************************/


#include "stp/Util/GitSHA1.h"
const char* stp::get_git_version_sha()
{
    static const char version_sha[] = "80742b4858e695e741a30f6d4111ee63e6917e9c";
    return version_sha;
}

const char* stp::get_git_version_tag()
{
    static const char version_tag[] = "2.1.2";
    return version_tag;
}

#define STP_TIMESTAMPS 1

const char* stp::get_compilation_env()
{
    static const char compilation_env[] =
    "CMAKE_CXX_COMPILER = /usr/bin/c++ | "
    "CMAKE_CXX_FLAGS =  -Wall -Wextra -Wunused -pedantic -Wsign-compare -fno-omit-frame-pointer -Wtype-limits -Wuninitialized -Wno-deprecated -Wstrict-aliasing -Wpointer-arith -fvisibility=hidden -Wpointer-arith -Wformat-nonliteral -Winit-self -Wparentheses -Wunreachable-code -ggdb3 -fPIC | "
    "COMPILE_DEFINES =  -D__STDC_LIMIT_MACROS | "
    "ONLY_SIMPLE = OFF | "
    "Boost_FOUND = 1 | "
    "STATICCOMPILE = OFF | "
    "TUNE_NATIVE = OFF | "
    "COVERAGE = OFF | "
    "FORCE_CMS = OFF | "
    "LIBS = /usr/lib/libminisat.so | "
    "ENABLE_TESTING = OFF | "
    "ENABLE_PYTHON_INTERFACE = ON | "
    "PYTHON_EXECUTABLE = /usr/bin/python2.7 | "
    "PYTHON_LIBRARY = /usr/lib/x86_64-linux-gnu/libpython2.7.so | "
    "PYTHON_INCLUDE_DIRS = /usr/include/python2.7 | "
    " | compilation date time = "
#ifdef STP_TIMESTAMPS
    __DATE__ " " __TIME__
#else
    "unknown"
#endif
    ;
    return compilation_env;
}
