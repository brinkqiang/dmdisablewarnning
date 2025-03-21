// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMLOG_H__
#define __DMLOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

#include <chrono>


/*** Start of inlined file: dmutil.h ***/
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMUTIL_H_INCLUDE__
#define __DMUTIL_H_INCLUDE__


/*** Start of inlined file: dmos.h ***/
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMOS_H_INCLUDE__
#define __DMOS_H_INCLUDE__

#ifdef _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <csignal>

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <list>

#include <set>
#include <map>

#include <sstream>
#include <fstream>
#include <iostream>

#include <winsock2.h>

#include <windows.h>
#include <direct.h>
#include <process.h>
#include <conio.h>
#include <io.h>

#pragma comment(lib, "ws2_32.lib")

namespace stdext {

}

namespace std {
	using namespace stdext;
}

#define VSNPRINTF _vsnprintf
#define SleepMs(x) Sleep(x)
#ifndef INFINITE
#define INFINITE 0xffffffff
#endif

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <csignal>

#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <list>

#include <set>
#include <map>

#include <sstream>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <signal.h>
#include <netdb.h>
#include <limits.h>
#include <unistd.h>

#ifndef MAX_PATH
#define MAX_PATH    260
#endif
#define VSNPRINTF vsnprintf
#define SleepMs(x) usleep(x*1000)
#ifndef INFINITE
#define INFINITE 0xffffffff
#endif
#endif

#define PATH_IS_DELIMITER(x)  ('\\' == x || '/' == x)

#ifdef _WIN32
#define PATH_DELIMITER '\\'
#else
#define PATH_DELIMITER '/'
#endif

#ifdef _WIN32
#define PATH_DELIMITER_STR "\\"
#else
#define PATH_DELIMITER_STR "/"
#endif
#define DMASSERT assert

#ifdef _WIN32
#define DMAPI __stdcall
typedef HANDLE DMHANDLE;
#define DMINVALID_HANDLE  NULL
#else
#define DMAPI
typedef int DMHANDLE;
#define DMINVALID_HANDLE  0
#endif

#endif // __DMOS_H_INCLUDE__

/*** End of inlined file: dmos.h ***/

#include <string>
#include <atomic>
#include <mutex>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

// tolua_begin

#ifdef _WIN32
static inline struct tm *localtime_r(const time_t *timep, struct tm *result)
{
    localtime_s(result, timep);
    return result;
}
static inline struct tm *gmtime_r(const time_t *timep, struct tm *result)
{
    gmtime_s(result, timep);
    return result;
}
#endif

static inline std::string DMFormatIP(unsigned int dwIP)
{
    sockaddr_in s;
    s.sin_family = AF_INET;
    s.sin_addr.s_addr = dwIP;
    return inet_ntoa(s.sin_addr);
}

static inline unsigned int DMFormatIP(const std::string &strIp)
{
    return inet_addr(strIp.c_str());
}

static inline unsigned short DMFormatPort(const std::string &strPort)
{
    return htons(atoi(strPort.c_str()));
}

static inline unsigned short DMFormatPort(unsigned short wPort)
{
    return htons(wPort);
}

static inline std::string DMFormatDateTime(time_t tVal = time(0),
                                           const char *pFormat = "%Y-%m-%d %H:%M:%S")
{
    struct tm Tm = {0};

    if (localtime_r(&tVal, &Tm))
    {
        char szBuf[128];
        strftime(szBuf, sizeof(szBuf), pFormat, &Tm);
        return szBuf;
    }

    return "";
}

static inline time_t DMFormatDateTime(const std::string &strTime,
                                      const char *pFormat = "%d-%d-%d %d:%d:%d")
{
    time_t ret = 0;
    struct tm tmMake = {0};

    if (6 == sscanf(strTime.c_str(), pFormat, &tmMake.tm_year, &tmMake.tm_mon,
                    &tmMake.tm_mday, &tmMake.tm_hour, &tmMake.tm_min, &tmMake.tm_sec))
    {
        tmMake.tm_year -= 1900;
        tmMake.tm_mon -= 1;
        ret = mktime(&tmMake);
    }

    return ret;
}

static bool DMIsFile(const char* file_name) {
#ifdef _WIN32
	int ret = GetFileAttributesA(file_name);

	if (ret == -1) {
		return false; // Path doesn't exist or error in accessing attributes.
	}

	return !(FILE_ATTRIBUTE_DIRECTORY & ret); // True if not a directory.
#else
	struct stat fileStat;
	int ret = stat(file_name, &fileStat);

	if (ret == 0) {
		return S_ISREG(fileStat.st_mode); // True if it's a regular file.
	}

	return false; // Path doesn't exist or error in accessing attributes.
#endif
}

static inline bool DMIsDirectory(const char *dir_name)
{
#ifdef _WIN32
    int ret = GetFileAttributesA(dir_name);

    if (ret == -1)
    {
        return false;
    }

    return !!(FILE_ATTRIBUTE_DIRECTORY & ret);
#else
    struct stat fileStat;
    int ret = stat(dir_name, &fileStat);

    if (ret == 0)
    {
        return S_ISDIR(fileStat.st_mode);
    }

    return false;
#endif
}

static inline bool DMCreateDirectory(const char *dir_name)
{
#ifdef _WIN32
    int ret = mkdir(dir_name);
#else
    int ret = mkdir(dir_name, S_IRWXU | S_IRWXG | S_IXOTH);
#endif

    if (0 != ret)
    {
        return false;
    }

    return true;
}

static inline bool DMCreateDirectories(const char *dir_name)
{
    if (access(dir_name, 0) == 0)
    {
        if (DMIsDirectory(dir_name))
        {
            return true;
        }

        return false;
    }

    char path[MAX_PATH];
    strncpy(path, dir_name, sizeof(path));

    char *p = strrchr(path, PATH_DELIMITER);

    if (NULL == p)
    {
        return DMCreateDirectory(path);
    }

    *(p) = '\0';
    DMCreateDirectories(path);
    return DMCreateDirectory(dir_name);
}

static inline std::string DMGetRootPath()
{

#ifdef _WIN32
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        GetModuleFileNameA( 0, path, sizeof( path ) );
        char* p = strrchr( path, '\\' );
        if(p)
        {
            *( p ) = '\0';
        }
    });

    return path;
#elif __APPLE__
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        uint32_t size = sizeof( path );
        int nRet = _NSGetExecutablePath( path, &size );

        if ( nRet != 0 ) {
            strcpy(path, "./");
            return;
        }

        char* p = strrchr( path, '/' );
        if(p)
        {
            *( p ) = '\0';
        }
    });
    return path;
#else
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        int nRet = readlink( "/proc/self/exe", path, MAX_PATH );

        if ( nRet < 0 || nRet >= MAX_PATH ) {
            strcpy(path, "./");
            return;
        }

        char* p = strrchr( path, '/' );
        if(p)
        {
            *( p ) = '\0';
        }
     });

    return path;
#endif
}

static inline std::string DMGetExePath()
{
#ifdef _WIN32
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    { 
        GetModuleFileNameA(0, path, sizeof(path));
    });

    return path;
#elif __APPLE__
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        uint32_t size = sizeof( path );
        int nRet = _NSGetExecutablePath( path, &size );

        if ( nRet != 0 )
        {
            strcpy(path, "./");
            return;
        }
    });
    return path;
#else
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        int nRet = readlink( "/proc/self/exe", path, MAX_PATH );

        if ( nRet < 0 || nRet >= MAX_PATH )
        {
            strcpy(path, "./");
            return;
        }
    });

    return path;
#endif
}

static inline std::string DMGetExeName()
{
#ifdef _WIN32
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        char temp[MAX_PATH];
        GetModuleFileNameA(0, temp, sizeof(path));

        char* point = strrchr(temp, '.');

        if (NULL == point) {
            strcpy(path, temp);
            return;
        }

        *point = '\0';

        char* del = strrchr(temp, PATH_DELIMITER);

        if (NULL == del) {
            strcpy(path, temp);
            return;
        }

        strcpy(path, del + 1);
    });

    return path;
#elif __APPLE__
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        char temp[MAX_PATH];
        uint32_t size = sizeof(temp);
        int ret = _NSGetExecutablePath(temp, &size);

        if (ret != 0) {
            strcpy(path, temp);
            return;
        }

        char* point = strrchr(temp, '.');

        if (NULL == point) {
            strcpy(path, temp);
            return;
        }

        *point = '\0';

        char* del = strrchr(temp, PATH_DELIMITER);

        if (NULL == del) {
            strcpy(path, temp);
            return;
        }

        strcpy(path, del + 1);
    });
    return path;
#else
    static char path[MAX_PATH];
    static std::once_flag init_flag;
    std::call_once(init_flag, []()
    {
        char temp[MAX_PATH];
        int ret = readlink("/proc/self/exe", temp, MAX_PATH);

        if (ret < 0 || ret >= MAX_PATH) {
            strcpy(path, temp);
            return;
        }
        temp[ret] = '\0';
        char* del = strrchr(temp, PATH_DELIMITER);

        if (NULL == del) {
            strcpy(path, temp);
            return;
        }

        strcpy(path, del + 1);
    });

    return path;
#endif
}

static inline std::string DMGetExeNameString()
{
    return DMGetExeName();
}

static inline std::string DMGetWorkPath()
{
    char szPath[MAX_PATH];
    getcwd(szPath, sizeof(szPath));
    return szPath;
}

static inline bool DMSetWorkPath(std::string &strPath)
{
    if (0 != chdir(strPath.c_str()))
    {
        return false;
    }
    return true;
}

static inline bool DMSetWorkPath()
{
    std::string strPath = DMGetRootPath() + "\\..\\";
    return DMSetWorkPath(strPath);
}

// tolua_end

#endif // __DMUTIL_H_INCLUDE__


/*** End of inlined file: dmutil.h ***/


/*** Start of inlined file: dmformat.h ***/
#ifndef __DMFORMAT_H_INCLUDE__
#define __DMFORMAT_H_INCLUDE__

#define FMT_HEADER_ONLY
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <memory>
#include <stdexcept>
#include <cstdint>

#ifdef __clang__
# define FMT_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#else
# define FMT_CLANG_VERSION 0
#endif

#ifdef __INTEL_COMPILER
# define FMT_ICC_VERSION __INTEL_COMPILER
#elif defined(__ICL)
# define FMT_ICC_VERSION __ICL
#else
# define FMT_ICC_VERSION 0
#endif


/*** Start of inlined file: dmformatcore.h ***/
// Formatting library for C++ - the core API
//
// Copyright (c) 2012 - present, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

#ifndef __DMFORMATCORE_H_INCLUDE__
#define __DMFORMATCORE_H_INCLUDE__

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <string>
#include <type_traits>

// The fmt library version in the form major * 10000 + minor * 100 + patch.
#define FMT_VERSION 50100

#ifdef __has_feature
# define FMT_HAS_FEATURE(x) __has_feature(x)
#else
# define FMT_HAS_FEATURE(x) 0
#endif

#ifdef __has_include
# define FMT_HAS_INCLUDE(x) __has_include(x)
#else
# define FMT_HAS_INCLUDE(x) 0
#endif

#ifdef __has_cpp_attribute
# define FMT_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
# define FMT_HAS_CPP_ATTRIBUTE(x) 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define FMT_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#else
# define FMT_GCC_VERSION 0
#endif

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
# define FMT_HAS_GXX_CXX11 FMT_GCC_VERSION
#else
# define FMT_HAS_GXX_CXX11 0
#endif

#ifdef _MSC_VER
# define FMT_MSC_VER _MSC_VER
#else
# define FMT_MSC_VER 0
#endif

// Check if relaxed c++14 constexpr is supported.
// GCC doesn't allow throw in constexpr until version 6 (bug 67371).
#ifndef FMT_USE_CONSTEXPR
# define FMT_USE_CONSTEXPR \
  (FMT_HAS_FEATURE(cxx_relaxed_constexpr) || FMT_MSC_VER >= 1910 || \
   (FMT_GCC_VERSION >= 600 && __cplusplus >= 201402L))
#endif
#if FMT_USE_CONSTEXPR
# define FMT_CONSTEXPR constexpr
# define FMT_CONSTEXPR_DECL constexpr
#else
# define FMT_CONSTEXPR inline
# define FMT_CONSTEXPR_DECL
#endif

#ifndef FMT_OVERRIDE
# if FMT_HAS_FEATURE(cxx_override) || \
	 (FMT_GCC_VERSION >= 408 && FMT_HAS_GXX_CXX11) || \
	 FMT_MSC_VER >= 1900
#  define FMT_OVERRIDE override
# else
#  define FMT_OVERRIDE
# endif
#endif

#if FMT_HAS_FEATURE(cxx_explicit_conversions) || \
	FMT_MSC_VER >= 1800
# define FMT_EXPLICIT explicit
#else
# define FMT_EXPLICIT
#endif

#ifndef FMT_NULL
# if FMT_HAS_FEATURE(cxx_nullptr) || \
   (FMT_GCC_VERSION >= 408 && FMT_HAS_GXX_CXX11) || \
   FMT_MSC_VER >= 1600
#  define FMT_NULL nullptr
#  define FMT_USE_NULLPTR 1
# else
#  define FMT_NULL NULL
# endif
#endif

#ifndef FMT_USE_NULLPTR
# define FMT_USE_NULLPTR 0
#endif

#if FMT_HAS_CPP_ATTRIBUTE(noreturn)
# define FMT_NORETURN [[noreturn]]
#else
# define FMT_NORETURN
#endif

// Check if exceptions are disabled.
#if defined(__GNUC__) && !defined(__EXCEPTIONS)
# define FMT_EXCEPTIONS 0
#elif FMT_MSC_VER && !_HAS_EXCEPTIONS
# define FMT_EXCEPTIONS 0
#endif
#ifndef FMT_EXCEPTIONS
# define FMT_EXCEPTIONS 1
#endif

// Define FMT_USE_NOEXCEPT to make fmt use noexcept (C++11 feature).
#ifndef FMT_USE_NOEXCEPT
# define FMT_USE_NOEXCEPT 0
#endif

#if FMT_USE_NOEXCEPT || FMT_HAS_FEATURE(cxx_noexcept) || \
	(FMT_GCC_VERSION >= 408 && FMT_HAS_GXX_CXX11) || \
	FMT_MSC_VER >= 1900
# define FMT_DETECTED_NOEXCEPT noexcept
#else
# define FMT_DETECTED_NOEXCEPT throw()
#endif

#ifndef FMT_NOEXCEPT
# if FMT_EXCEPTIONS
#  define FMT_NOEXCEPT FMT_DETECTED_NOEXCEPT
# else
#  define FMT_NOEXCEPT
# endif
#endif

// This is needed because GCC still uses throw() in its headers when exceptions
// are disabled.
#if FMT_GCC_VERSION
# define FMT_DTOR_NOEXCEPT FMT_DETECTED_NOEXCEPT
#else
# define FMT_DTOR_NOEXCEPT FMT_NOEXCEPT
#endif

#ifndef FMT_BEGIN_NAMESPACE
# if FMT_HAS_FEATURE(cxx_inline_namespaces) || FMT_GCC_VERSION >= 404 || \
	 FMT_MSC_VER >= 1900
#  define FMT_INLINE_NAMESPACE inline namespace
#  define FMT_END_NAMESPACE }}
# else
#  define FMT_INLINE_NAMESPACE namespace
#  define FMT_END_NAMESPACE } using namespace v5; }
# endif
# define FMT_BEGIN_NAMESPACE namespace fmt { FMT_INLINE_NAMESPACE v5 {
#endif

#if !defined(FMT_HEADER_ONLY) && defined(_WIN32)
# ifdef FMT_EXPORT
#  define FMT_API __declspec(dllexport)
# elif defined(FMT_SHARED)
#  define FMT_API __declspec(dllimport)
# endif
#endif
#ifndef FMT_API
# define FMT_API
#endif

#ifndef FMT_ASSERT
# define FMT_ASSERT(condition, message) assert((condition) && message)
#endif

#define FMT_DELETED = delete

// A macro to disallow the copy construction and assignment.
#define FMT_DISALLOW_COPY_AND_ASSIGN(Type) \
	Type(const Type &) FMT_DELETED; \
	void operator=(const Type &) FMT_DELETED

// libc++ supports string_view in pre-c++17.
#if (FMT_HAS_INCLUDE(<string_view>) && \
	  (__cplusplus > 201402L || defined(_LIBCPP_VERSION))) || \
	(defined(_MSVC_LANG) && _MSVC_LANG > 201402L && _MSC_VER >= 1910)
# include <string_view>
# define FMT_USE_STD_STRING_VIEW
#elif (FMT_HAS_INCLUDE(<experimental/string_view>) && \
	   __cplusplus >= 201402L)
# include <experimental/string_view>
# define FMT_USE_EXPERIMENTAL_STRING_VIEW
#endif

// std::result_of is defined in <functional> in gcc 4.4.
#if FMT_GCC_VERSION && FMT_GCC_VERSION <= 404
# include <functional>
#endif

FMT_BEGIN_NAMESPACE

namespace internal {

// An implementation of declval for pre-C++11 compilers such as gcc 4.
template <typename T>
typename std::add_rvalue_reference<T>::type declval() FMT_NOEXCEPT;

// Casts nonnegative integer to unsigned.
template <typename Int>
FMT_CONSTEXPR typename std::make_unsigned<Int>::type to_unsigned(Int value) {
  FMT_ASSERT(value >= 0, "negative value");
  return static_cast<typename std::make_unsigned<Int>::type>(value);
}

}

/**
  An implementation of ``std::basic_string_view`` for pre-C++17. It provides a
  subset of the API. ``fmt::basic_string_view`` is used for format strings even
  if ``std::string_view`` is available to prevent issues when a library is
  compiled with a different ``-std`` option than the client code (which is not
  recommended).
 */
template <typename Char>
class basic_string_view {
 private:
  const Char *data_;
  size_t size_;

 public:
  typedef Char char_type;
  typedef const Char *iterator;

  // Standard basic_string_view type.
#if defined(FMT_USE_STD_STRING_VIEW)
  typedef std::basic_string_view<Char> type;
#elif defined(FMT_USE_EXPERIMENTAL_STRING_VIEW)
  typedef std::experimental::basic_string_view<Char> type;
#else
  struct type {
	const char *data() const { return FMT_NULL; }
	size_t size() const { return 0; }
  };
#endif

  FMT_CONSTEXPR basic_string_view() FMT_NOEXCEPT : data_(FMT_NULL), size_(0) {}

  /** Constructs a string reference object from a C string and a size. */
  FMT_CONSTEXPR basic_string_view(const Char *s, size_t count) FMT_NOEXCEPT
	: data_(s), size_(count) {}

  /**
	\rst
	Constructs a string reference object from a C string computing
	the size with ``std::char_traits<Char>::length``.
	\endrst
   */
  basic_string_view(const Char *s)
	: data_(s), size_(std::char_traits<Char>::length(s)) {}

  /** Constructs a string reference from a ``std::basic_string`` object. */
  template <typename Alloc>
  FMT_CONSTEXPR basic_string_view(
	  const std::basic_string<Char, Alloc> &s) FMT_NOEXCEPT
  : data_(s.c_str()), size_(s.size()) {}

  FMT_CONSTEXPR basic_string_view(type s) FMT_NOEXCEPT
  : data_(s.data()), size_(s.size()) {}

  /** Returns a pointer to the string data. */
  const Char *data() const { return data_; }

  /** Returns the string size. */
  FMT_CONSTEXPR size_t size() const { return size_; }

  FMT_CONSTEXPR iterator begin() const { return data_; }
  FMT_CONSTEXPR iterator end() const { return data_ + size_; }

  FMT_CONSTEXPR void remove_prefix(size_t n) {
	data_ += n;
	size_ -= n;
  }

  // Lexicographically compare this string reference to other.
  int compare(basic_string_view other) const {
	size_t str_size = size_ < other.size_ ? size_ : other.size_;
	int result = std::char_traits<Char>::compare(data_, other.data_, str_size);
	if (result == 0)
	  result = size_ == other.size_ ? 0 : (size_ < other.size_ ? -1 : 1);
	return result;
  }

  friend bool operator==(basic_string_view lhs, basic_string_view rhs) {
	return lhs.compare(rhs) == 0;
  }
  friend bool operator!=(basic_string_view lhs, basic_string_view rhs) {
	return lhs.compare(rhs) != 0;
  }
  friend bool operator<(basic_string_view lhs, basic_string_view rhs) {
	return lhs.compare(rhs) < 0;
  }
  friend bool operator<=(basic_string_view lhs, basic_string_view rhs) {
	return lhs.compare(rhs) <= 0;
  }
  friend bool operator>(basic_string_view lhs, basic_string_view rhs) {
	return lhs.compare(rhs) > 0;
  }
  friend bool operator>=(basic_string_view lhs, basic_string_view rhs) {
	return lhs.compare(rhs) >= 0;
  }
};

typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;

template <typename Context>
class basic_format_arg;

template <typename Context>
class basic_format_args;

// A formatter for objects of type T.
template <typename T, typename Char = char, typename Enable = void>
struct formatter;

namespace internal {

/** A contiguous memory buffer with an optional growing ability. */
template <typename T>
class basic_buffer {
 private:
  FMT_DISALLOW_COPY_AND_ASSIGN(basic_buffer);

  T *ptr_;
  std::size_t size_;
  std::size_t capacity_;

 protected:
  basic_buffer(T *p = FMT_NULL, std::size_t sz = 0, std::size_t cap = 0)
	FMT_NOEXCEPT: ptr_(p), size_(sz), capacity_(cap) {}

  /** Sets the buffer data and capacity. */
  void set(T *buf_data, std::size_t buf_capacity) FMT_NOEXCEPT {
	ptr_ = buf_data;
	capacity_ = buf_capacity;
  }

  /** Increases the buffer capacity to hold at least *capacity* elements. */
  virtual void grow(std::size_t capacity) = 0;

 public:
  typedef T value_type;
  typedef const T &const_reference;

  virtual ~basic_buffer() {}

  T *begin() FMT_NOEXCEPT { return ptr_; }
  T *end() FMT_NOEXCEPT { return ptr_ + size_; }

  /** Returns the size of this buffer. */
  std::size_t size() const FMT_NOEXCEPT { return size_; }

  /** Returns the capacity of this buffer. */
  std::size_t capacity() const FMT_NOEXCEPT { return capacity_; }

  /** Returns a pointer to the buffer data. */
  T *data() FMT_NOEXCEPT { return ptr_; }

  /** Returns a pointer to the buffer data. */
  const T *data() const FMT_NOEXCEPT { return ptr_; }

  /**
	Resizes the buffer. If T is a POD type new elements may not be initialized.
   */
  void resize(std::size_t new_size) {
	reserve(new_size);
	size_ = new_size;
  }
  void clear() { size_ = 0; }
  /** Reserves space to store at least *capacity* elements. */
  void reserve(std::size_t new_capacity) {
	if (new_capacity > capacity_)
	  grow(new_capacity);
  }

  void push_back(const T &value) {
	reserve(size_ + 1);
	ptr_[size_++] = value;
  }

  /** Appends data to the end of the buffer. */
  template <typename U>
  void append(const U *begin, const U *end);

  T &operator[](std::size_t index) { return ptr_[index]; }
  const T &operator[](std::size_t index) const { return ptr_[index]; }
};

typedef basic_buffer<char> buffer;
typedef basic_buffer<wchar_t> wbuffer;

// A container-backed buffer.
template <typename Container>
class container_buffer : public basic_buffer<typename Container::value_type> {
 private:
  Container &container_;

 protected:
  void grow(std::size_t capacity) FMT_OVERRIDE {
	container_.resize(capacity);
	this->set(&container_[0], capacity);
  }

 public:
  explicit container_buffer(Container &c)
	: basic_buffer<typename Container::value_type>(&c[0], c.size(), c.size()),
	  container_(c) {}
};

struct error_handler {
  FMT_CONSTEXPR error_handler() {}
  FMT_CONSTEXPR error_handler(const error_handler &) {}

  // This function is intentionally not constexpr to give a compile-time error.
  FMT_API void on_error(const char *message);
};

// Formatting of wide characters and strings into a narrow output is disallowed:
//   fmt::format("{}", L"test"); // error
// To fix this, use a wide format string:
//   fmt::format(L"{}", L"test");
template <typename Char>
inline void require_wchar() {
  static_assert(
	  std::is_same<wchar_t, Char>::value,
	  "formatting of wide characters into a narrow output is disallowed");
}

template <typename Char>
struct named_arg_base;

template <typename T, typename Char>
struct named_arg;

template <typename T>
struct is_named_arg : std::false_type {};

template <typename T, typename Char>
struct is_named_arg<named_arg<T, Char>> : std::true_type {};

enum type {
  none_type, named_arg_type,
  // Integer types should go first,
  int_type, uint_type, long_long_type, ulong_long_type, bool_type, char_type,
  last_integer_type = char_type,
  // followed by floating-point types.
  double_type, long_double_type, last_numeric_type = long_double_type,
  cstring_type, string_type, pointer_type, custom_type
};

FMT_CONSTEXPR bool is_integral(type t) {
  FMT_ASSERT(t != internal::named_arg_type, "invalid argument type");
  return t > internal::none_type && t <= internal::last_integer_type;
}

FMT_CONSTEXPR bool is_arithmetic(type t) {
  FMT_ASSERT(t != internal::named_arg_type, "invalid argument type");
  return t > internal::none_type && t <= internal::last_numeric_type;
}

template <typename T, typename Char, bool ENABLE = true>
struct convert_to_int {
  enum {
	value = !std::is_arithmetic<T>::value && std::is_convertible<T, int>::value
  };
};

template <typename Char>
struct string_value {
  const Char *value;
  std::size_t size;
};

template <typename Context>
struct custom_value {
  const void *value;
  void (*format)(const void *arg, Context &ctx);
};

// A formatting argument value.
template <typename Context>
class value {
 public:
  typedef typename Context::char_type char_type;

  union {
	int int_value;
	unsigned uint_value;
	long long long_long_value;
	unsigned long long ulong_long_value;
	double double_value;
	long double long_double_value;
	const void *pointer;
	string_value<char_type> string;
	string_value<signed char> sstring;
	string_value<unsigned char> ustring;
	custom_value<Context> custom;
  };

  FMT_CONSTEXPR value(int val = 0) : int_value(val) {}
  value(unsigned val) { uint_value = val; }
  value(long long val) { long_long_value = val; }
  value(unsigned long long val) { ulong_long_value = val; }
  value(double val) { double_value = val; }
  value(long double val) { long_double_value = val; }
  value(const char_type *val) { string.value = val; }
  value(const signed char *val) {
	static_assert(std::is_same<char, char_type>::value,
				  "incompatible string types");
	sstring.value = val;
  }
  value(const unsigned char *val) {
	static_assert(std::is_same<char, char_type>::value,
				  "incompatible string types");
	ustring.value = val;
  }
  value(basic_string_view<char_type> val) {
	string.value = val.data();
	string.size = val.size();
  }
  value(const void *val) { pointer = val; }

  template <typename T>
  explicit value(const T &val) {
	custom.value = &val;
	custom.format = &format_custom_arg<T>;
  }

  const named_arg_base<char_type> &as_named_arg() {
	return *static_cast<const named_arg_base<char_type>*>(pointer);
  }

 private:
  // Formats an argument of a custom type, such as a user-defined class.
  template <typename T>
  static void format_custom_arg(const void *arg, Context &ctx) {
	// Get the formatter type through the context to allow different contexts
	// have different extension points, e.g. `formatter<T>` for `format` and
	// `printf_formatter<T>` for `printf`.
	typename Context::template formatter_type<T>::type f;
	auto &&parse_ctx = ctx.parse_context();
	parse_ctx.advance_to(f.parse(parse_ctx));
	ctx.advance_to(f.format(*static_cast<const T*>(arg), ctx));
  }
};

template <typename Context, type TYPE>
struct typed_value : value<Context> {
  static const type type_tag = TYPE;

  template <typename T>
  FMT_CONSTEXPR typed_value(const T &val) : value<Context>(val) {}
};

template <typename Context, typename T>
FMT_CONSTEXPR basic_format_arg<Context> make_arg(const T &value);

#define FMT_MAKE_VALUE(TAG, ArgType, ValueType) \
  template <typename C> \
  FMT_CONSTEXPR typed_value<C, TAG> make_value(ArgType val) { \
	return static_cast<ValueType>(val); \
  }

#define FMT_MAKE_VALUE_SAME(TAG, Type) \
  template <typename C> \
  FMT_CONSTEXPR typed_value<C, TAG> make_value(Type val) { \
	return val; \
  }

FMT_MAKE_VALUE(bool_type, bool, int)
FMT_MAKE_VALUE(int_type, short, int)
FMT_MAKE_VALUE(uint_type, unsigned short, unsigned)
FMT_MAKE_VALUE_SAME(int_type, int)
FMT_MAKE_VALUE_SAME(uint_type, unsigned)

// To minimize the number of types we need to deal with, long is translated
// either to int or to long long depending on its size.
typedef std::conditional<sizeof(long) == sizeof(int), int, long long>::type
		long_type;
FMT_MAKE_VALUE(
	(sizeof(long) == sizeof(int) ? int_type : long_long_type), long, long_type)
typedef std::conditional<sizeof(unsigned long) == sizeof(unsigned),
						 unsigned, unsigned long long>::type ulong_type;
FMT_MAKE_VALUE(
	(sizeof(unsigned long) == sizeof(unsigned) ? uint_type : ulong_long_type),
	unsigned long, ulong_type)

FMT_MAKE_VALUE_SAME(long_long_type, long long)
FMT_MAKE_VALUE_SAME(ulong_long_type, unsigned long long)
FMT_MAKE_VALUE(int_type, signed char, int)
FMT_MAKE_VALUE(uint_type, unsigned char, unsigned)
FMT_MAKE_VALUE(char_type, char, int)

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)
template <typename C>
inline typed_value<C, char_type> make_value(wchar_t val) {
  require_wchar<typename C::char_type>();
  return static_cast<int>(val);
}
#endif

FMT_MAKE_VALUE(double_type, float, double)
FMT_MAKE_VALUE_SAME(double_type, double)
FMT_MAKE_VALUE_SAME(long_double_type, long double)

// Formatting of wide strings into a narrow buffer and multibyte strings
// into a wide buffer is disallowed (https://github.com/fmtlib/fmt/pull/606).
FMT_MAKE_VALUE(cstring_type, typename C::char_type*,
			   const typename C::char_type*)
FMT_MAKE_VALUE(cstring_type, const typename C::char_type*,
			   const typename C::char_type*)

FMT_MAKE_VALUE(cstring_type, signed char*, const signed char*)
FMT_MAKE_VALUE_SAME(cstring_type, const signed char*)
FMT_MAKE_VALUE(cstring_type, unsigned char*, const unsigned char*)
FMT_MAKE_VALUE_SAME(cstring_type, const unsigned char*)
FMT_MAKE_VALUE_SAME(string_type, basic_string_view<typename C::char_type>)
FMT_MAKE_VALUE(string_type,
			   typename basic_string_view<typename C::char_type>::type,
			   basic_string_view<typename C::char_type>)
FMT_MAKE_VALUE(string_type, const std::basic_string<typename C::char_type>&,
			   basic_string_view<typename C::char_type>)
FMT_MAKE_VALUE(pointer_type, void*, const void*)
FMT_MAKE_VALUE_SAME(pointer_type, const void*)

#if FMT_USE_NULLPTR
FMT_MAKE_VALUE(pointer_type, std::nullptr_t, const void*)
#endif

// Formatting of arbitrary pointers is disallowed. If you want to output a
// pointer cast it to "void *" or "const void *". In particular, this forbids
// formatting of "[const] volatile char *" which is printed as bool by
// iostreams.
template <typename C, typename T>
typename std::enable_if<!std::is_same<T, typename C::char_type>::value>::type
	make_value(const T *) {
  static_assert(!sizeof(T), "formatting of non-void pointers is disallowed");
}

template <typename C, typename T>
inline typename std::enable_if<
	std::is_enum<T>::value && convert_to_int<T, typename C::char_type>::value,
	typed_value<C, int_type>>::type
  make_value(const T &val) { return static_cast<int>(val); }

template <typename C, typename T, typename Char = typename C::char_type>
inline typename std::enable_if<
	!convert_to_int<T, Char>::value &&
	!std::is_convertible<T, basic_string_view<Char>>::value,
	// Implicit conversion to std::string is not handled here because it's
	// unsafe: https://github.com/fmtlib/fmt/issues/729
	typed_value<C, custom_type>>::type
  make_value(const T &val) { return val; }

template <typename C, typename T>
typed_value<C, named_arg_type>
	make_value(const named_arg<T, typename C::char_type> &val) {
  basic_format_arg<C> arg = make_arg<C>(val.value);
  std::memcpy(val.data, &arg, sizeof(arg));
  return static_cast<const void*>(&val);
}

// Maximum number of arguments with packed types.
enum { max_packed_args = 15 };

template <typename Context>
class arg_map;

template <typename>
struct result_of;

template <typename F, typename... Args>
struct result_of<F(Args...)> {
  // A workaround for gcc 4.4 that doesn't allow F to be a reference.
	typedef typename std::invoke_result<F, Args...>::type type;
};
}

// A formatting argument. It is a trivially copyable/constructible type to
// allow storage in basic_memory_buffer.
template <typename Context>
class basic_format_arg {
 private:
  internal::value<Context> value_;
  internal::type type_;

  template <typename ContextType, typename T>
  friend FMT_CONSTEXPR basic_format_arg<ContextType>
	internal::make_arg(const T &value);

  template <typename Visitor, typename Ctx>
  friend FMT_CONSTEXPR typename internal::result_of<Visitor(int)>::type
	visit(Visitor &&vis, basic_format_arg<Ctx> arg);

  friend class basic_format_args<Context>;
  friend class internal::arg_map<Context>;

  typedef typename Context::char_type char_type;

 public:
  class handle {
   public:
	explicit handle(internal::custom_value<Context> custom): custom_(custom) {}

	void format(Context &ctx) const { custom_.format(custom_.value, ctx); }

   private:
	internal::custom_value<Context> custom_;
  };

  FMT_CONSTEXPR basic_format_arg() : type_(internal::none_type) {}

  FMT_EXPLICIT operator bool() const FMT_NOEXCEPT {
	return type_ != internal::none_type;
  }

  internal::type type() const { return type_; }

  bool is_integral() const { return internal::is_integral(type_); }
  bool is_arithmetic() const { return internal::is_arithmetic(type_); }
};

// Parsing context consisting of a format string range being parsed and an
// argument counter for automatic indexing.
template <typename Char, typename ErrorHandler = internal::error_handler>
class basic_parse_context : private ErrorHandler {
 private:
  basic_string_view<Char> format_str_;
  int next_arg_id_;

 public:
  typedef Char char_type;
  typedef typename basic_string_view<Char>::iterator iterator;

  explicit FMT_CONSTEXPR basic_parse_context(
	  basic_string_view<Char> format_str, ErrorHandler eh = ErrorHandler())
	: ErrorHandler(eh), format_str_(format_str), next_arg_id_(0) {}

  // Returns an iterator to the beginning of the format string range being
  // parsed.
  FMT_CONSTEXPR iterator begin() const FMT_NOEXCEPT {
	return format_str_.begin();
  }

  // Returns an iterator past the end of the format string range being parsed.
  FMT_CONSTEXPR iterator end() const FMT_NOEXCEPT { return format_str_.end(); }

  // Advances the begin iterator to ``it``.
  FMT_CONSTEXPR void advance_to(iterator it) {
	format_str_.remove_prefix(internal::to_unsigned(it - begin()));
  }

  // Returns the next argument index.
  FMT_CONSTEXPR unsigned next_arg_id();

  FMT_CONSTEXPR bool check_arg_id(unsigned) {
	if (next_arg_id_ > 0) {
	  on_error("cannot switch from automatic to manual argument indexing");
	  return false;
	}
	next_arg_id_ = -1;
	return true;
  }
  void check_arg_id(basic_string_view<Char>) {}

  FMT_CONSTEXPR void on_error(const char *message) {
	ErrorHandler::on_error(message);
  }

  FMT_CONSTEXPR ErrorHandler error_handler() const { return *this; }
};

typedef basic_parse_context<char> parse_context;
typedef basic_parse_context<wchar_t> wparse_context;

namespace internal {
// A map from argument names to their values for named arguments.
template <typename Context>
class arg_map {
 private:
  FMT_DISALLOW_COPY_AND_ASSIGN(arg_map);

  typedef typename Context::char_type char_type;

  struct entry {
	basic_string_view<char_type> name;
	basic_format_arg<Context> arg;
  };

  entry *map_;
  unsigned size_;

  void push_back(value<Context> val) {
	const internal::named_arg_base<char_type> &named = val.as_named_arg();
	map_[size_] = entry{named.name, named.template deserialize<Context>()};
	++size_;
  }

 public:
  arg_map() : map_(FMT_NULL), size_(0) {}
  void init(const basic_format_args<Context> &args);
  ~arg_map() { delete [] map_; }

  basic_format_arg<Context> find(basic_string_view<char_type> name) const {
	// The list is unsorted, so just return the first matching name.
	for (entry *it = map_, *end = map_ + size_; it != end; ++it) {
	  if (it->name == name)
		return it->arg;
	}
	return basic_format_arg<Context>();
  }
};

template <typename OutputIt, typename Context, typename Char>
class context_base {
 public:
  typedef OutputIt iterator;

 private:
  basic_parse_context<Char> parse_context_;
  iterator out_;
  basic_format_args<Context> args_;

 protected:
  typedef Char char_type;
  typedef basic_format_arg<Context> format_arg;

  context_base(OutputIt out, basic_string_view<char_type> format_str,
			   basic_format_args<Context> ctx_args)
  : parse_context_(format_str), out_(out), args_(ctx_args) {}

  // Returns the argument with specified index.
  format_arg do_get_arg(unsigned arg_id) {
	format_arg arg = args_.get(arg_id);
	if (!arg)
	  parse_context_.on_error("argument index out of range");
	return arg;
  }

  // Checks if manual indexing is used and returns the argument with
  // specified index.
  format_arg get_arg(unsigned arg_id) {
	return this->parse_context().check_arg_id(arg_id) ?
	  this->do_get_arg(arg_id) : format_arg();
  }

 public:
  basic_parse_context<char_type> &parse_context() {
	return parse_context_;
  }

  internal::error_handler error_handler() {
	return parse_context_.error_handler();
  }

  void on_error(const char *message) { parse_context_.on_error(message); }

  // Returns an iterator to the beginning of the output range.
  iterator out() { return out_; }
  iterator begin() { return out_; }  // deprecated

  // Advances the begin iterator to ``it``.
  void advance_to(iterator it) { out_ = it; }

  basic_format_args<Context> args() const { return args_; }
};

// Extracts a reference to the container from back_insert_iterator.
template <typename Container>
inline Container &get_container(std::back_insert_iterator<Container> it) {
  typedef std::back_insert_iterator<Container> bi_iterator;
  struct accessor: bi_iterator {
	accessor(bi_iterator iter) : bi_iterator(iter) {}
	using bi_iterator::container;
  };
  return *accessor(it).container;
}
}  // namespace internal

// Formatting context.
template <typename OutputIt, typename Char>
class basic_format_context :
  public internal::context_base<
	OutputIt, basic_format_context<OutputIt, Char>, Char> {
 public:
  /** The character type for the output. */
  typedef Char char_type;

  // using formatter_type = formatter<T, char_type>;
  template <typename T>
  struct formatter_type { typedef formatter<T, char_type> type; };

 private:
  internal::arg_map<basic_format_context> map_;

  FMT_DISALLOW_COPY_AND_ASSIGN(basic_format_context);

  typedef internal::context_base<OutputIt, basic_format_context, Char> base;
  typedef typename base::format_arg format_arg;
  using base::get_arg;

 public:
  using typename base::iterator;

  /**
   Constructs a ``basic_format_context`` object. References to the arguments are
   stored in the object so make sure they have appropriate lifetimes.
   */
  basic_format_context(OutputIt out, basic_string_view<char_type> format_str,
				basic_format_args<basic_format_context> ctx_args)
	: base(out, format_str, ctx_args) {}

  format_arg next_arg() {
	return this->do_get_arg(this->parse_context().next_arg_id());
  }
  format_arg get_arg(unsigned arg_id) { return this->do_get_arg(arg_id); }

  // Checks if manual indexing is used and returns the argument with the
  // specified name.
  format_arg get_arg(basic_string_view<char_type> name);
};

template <typename Char>
struct buffer_context {
  typedef basic_format_context<
	std::back_insert_iterator<internal::basic_buffer<Char>>, Char> type;
};
typedef buffer_context<char>::type format_context;
typedef buffer_context<wchar_t>::type wformat_context;

namespace internal {
template <typename Context, typename T>
struct get_type {
  typedef decltype(make_value<Context>(
		declval<typename std::decay<T>::type&>())) value_type;
  static const type value = value_type::type_tag;
};

template <typename Context>
FMT_CONSTEXPR unsigned long long get_types() { return 0; }

template <typename Context, typename Arg, typename... Args>
FMT_CONSTEXPR unsigned long long get_types() {
  return get_type<Context, Arg>::value | (get_types<Context, Args...>() << 4);
}

template <typename Context, typename T>
FMT_CONSTEXPR basic_format_arg<Context> make_arg(const T &value) {
  basic_format_arg<Context> arg;
  arg.type_ = get_type<Context, T>::value;
  arg.value_ = make_value<Context>(value);
  return arg;
}

template <bool IS_PACKED, typename Context, typename T>
inline typename std::enable_if<IS_PACKED, value<Context>>::type
	make_arg(const T &value) {
  return make_value<Context>(value);
}

template <bool IS_PACKED, typename Context, typename T>
inline typename std::enable_if<!IS_PACKED, basic_format_arg<Context>>::type
	make_arg(const T &value) {
  return make_arg<Context>(value);
}
}

/**
  \rst
  An array of references to arguments. It can be implicitly converted into
  `~fmt::basic_format_args` for passing into type-erased formatting functions
  such as `~fmt::vformat`.
  \endrst
 */
template <typename Context, typename ...Args>
class format_arg_store {
 private:
  static const size_t NUM_ARGS = sizeof...(Args);

  // Packed is a macro on MinGW so use IS_PACKED instead.
  static const bool IS_PACKED = NUM_ARGS < internal::max_packed_args;

  typedef typename std::conditional<IS_PACKED,
	internal::value<Context>, basic_format_arg<Context>>::type value_type;

  // If the arguments are not packed, add one more element to mark the end.
  static const size_t DATA_SIZE =
		  NUM_ARGS + (IS_PACKED && NUM_ARGS != 0 ? 0 : 1);
  value_type data_[DATA_SIZE];

  friend class basic_format_args<Context>;

  static FMT_CONSTEXPR long long get_types() {
	return IS_PACKED ?
	  static_cast<long long>(internal::get_types<Context, Args...>()) :
	  -static_cast<long long>(NUM_ARGS);
  }

 public:
#if FMT_USE_CONSTEXPR
  static constexpr long long TYPES = get_types();
#else
  static const long long TYPES;
#endif

#if (FMT_GCC_VERSION && FMT_GCC_VERSION <= 405) || \
	(FMT_MSC_VER && FMT_MSC_VER <= 1800)
  // Workaround array initialization issues in gcc <= 4.5 and MSVC <= 2013.
  format_arg_store(const Args &... args) {
	value_type init[DATA_SIZE] =
	  {internal::make_arg<IS_PACKED, Context>(args)...};
	std::memcpy(data_, init, sizeof(init));
  }
#else
  format_arg_store(const Args &... args)
	: data_{internal::make_arg<IS_PACKED, Context>(args)...} {}
#endif
};

#if !FMT_USE_CONSTEXPR
template <typename Context, typename ...Args>
const long long format_arg_store<Context, Args...>::TYPES = get_types();
#endif

/**
  \rst
  Constructs an `~fmt::format_arg_store` object that contains references to
  arguments and can be implicitly converted to `~fmt::format_args`. `Context` can
  be omitted in which case it defaults to `~fmt::context`.
  \endrst
 */
template <typename Context, typename ...Args>
inline format_arg_store<Context, Args...>
	make_format_args(const Args & ... args) {
  return format_arg_store<Context, Args...>(args...);
}

template <typename ...Args>
inline format_arg_store<format_context, Args...>
	make_format_args(const Args & ... args) {
  return format_arg_store<format_context, Args...>(args...);
}

/** Formatting arguments. */
template <typename Context>
class basic_format_args {
 public:
  typedef unsigned size_type;
  typedef basic_format_arg<Context>  format_arg;

 private:
  // To reduce compiled code size per formatting function call, types of first
  // max_packed_args arguments are passed in the types_ field.
  unsigned long long types_;
  union {
	// If the number of arguments is less than max_packed_args, the argument
	// values are stored in values_, otherwise they are stored in args_.
	// This is done to reduce compiled code size as storing larger objects
	// may require more code (at least on x86-64) even if the same amount of
	// data is actually copied to stack. It saves ~10% on the bloat test.
	const internal::value<Context> *values_;
	const format_arg *args_;
  };

  typename internal::type type(unsigned index) const {
	unsigned shift = index * 4;
	unsigned long long mask = 0xf;
	return static_cast<typename internal::type>(
	  (types_ & (mask << shift)) >> shift);
  }

  friend class internal::arg_map<Context>;

  void set_data(const internal::value<Context> *values) { values_ = values; }
  void set_data(const format_arg *args) { args_ = args; }

  format_arg do_get(size_type index) const {
	long long signed_types = static_cast<long long>(types_);
	if (signed_types < 0) {
	  unsigned long long num_args = static_cast<unsigned long long>(-signed_types);
	  return index < num_args ? args_[index] : format_arg();
	}
	format_arg arg;
	if (index > internal::max_packed_args)
	  return arg;
	arg.type_ = type(index);
	if (arg.type_ == internal::none_type)
	  return arg;
	internal::value<Context> &val = arg.value_;
	val = values_[index];
	return arg;
  }

 public:
  basic_format_args() : types_(0) {}

  /**
   \rst
   Constructs a `basic_format_args` object from `~fmt::format_arg_store`.
   \endrst
   */
  template <typename... Args>
  basic_format_args(const format_arg_store<Context, Args...> &store)
  : types_(static_cast<unsigned long long>(store.TYPES)) {
	set_data(store.data_);
  }

  /** Returns the argument at specified index. */
  format_arg get(size_type index) const {
	format_arg arg = do_get(index);
	return arg.type_ == internal::named_arg_type ?
		  arg.value_.as_named_arg().template deserialize<Context>() : arg;
  }

  unsigned max_size() const {
	long long signed_types = static_cast<long long>(types_);
	return static_cast<unsigned>(
		signed_types < 0 ?
		-signed_types : static_cast<long long>(internal::max_packed_args));
  }
};

/** An alias to ``basic_format_args<context>``. */
// It is a separate type rather than a typedef to make symbols readable.
struct format_args: basic_format_args<format_context> {
  template <typename ...Args>
  format_args(Args && ... arg)
  : basic_format_args<format_context>(std::forward<Args>(arg)...) {}
};
struct wformat_args : basic_format_args<wformat_context> {
  template <typename ...Args>
  wformat_args(Args && ... arg)
  : basic_format_args<wformat_context>(std::forward<Args>(arg)...) {}
};

namespace internal {
template <typename Char>
struct named_arg_base {
  basic_string_view<Char> name;

  // Serialized value<context>.
  mutable char data[sizeof(basic_format_arg<format_context>)];

  named_arg_base(basic_string_view<Char> nm) : name(nm) {}

  template <typename Context>
  basic_format_arg<Context> deserialize() const {
	basic_format_arg<Context> arg;
	std::memcpy(&arg, data, sizeof(basic_format_arg<Context>));
	return arg;
  }
};

template <typename T, typename Char>
struct named_arg : named_arg_base<Char> {
  const T &value;

  named_arg(basic_string_view<Char> name, const T &val)
	: named_arg_base<Char>(name), value(val) {}
};
}

/**
  \rst
  Returns a named argument to be used in a formatting function.

  **Example**::

	fmt::print("Elapsed time: {s:.2f} seconds", fmt::arg("s", 1.23));
  \endrst
 */
template <typename T>
inline internal::named_arg<T, char> arg(string_view name, const T &arg) {
  return internal::named_arg<T, char>(name, arg);
}

template <typename T>
inline internal::named_arg<T, wchar_t> arg(wstring_view name, const T &arg) {
  return internal::named_arg<T, wchar_t>(name, arg);
}

// This function template is deleted intentionally to disable nested named
// arguments as in ``format("{}", arg("a", arg("b", 42)))``.
template <typename S, typename T, typename Char>
void arg(S, internal::named_arg<T, Char>) FMT_DELETED;

#ifndef FMT_EXTENDED_COLORS
// color and (v)print_colored are deprecated.
enum color { black, red, green, yellow, blue, magenta, cyan, white };
FMT_API void vprint_colored(color c, string_view format, format_args args);
FMT_API void vprint_colored(color c, wstring_view format, wformat_args args);
template <typename... Args>
inline void print_colored(color c, string_view format_str,
						  const Args & ... args) {
  vprint_colored(c, format_str, fmt::make_format_args(args...));
}
template <typename... Args>
inline void print_colored(color c, wstring_view format_str,
						  const Args & ... args) {
  vprint_colored(c, format_str, fmt::make_format_args<wformat_context>(args...));
}
#endif

format_context::iterator vformat_to(
	internal::buffer &buf, string_view format_str, format_args args);
wformat_context::iterator vformat_to(
	internal::wbuffer &buf, wstring_view format_str, wformat_args args);

template <typename Container>
struct is_contiguous : std::false_type {};

template <typename Char>
struct is_contiguous<std::basic_string<Char>> : std::true_type {};

template <typename Char>
struct is_contiguous<internal::basic_buffer<Char>> : std::true_type {};

/** Formats a string and writes the output to ``out``. */
template <typename Container>
typename std::enable_if<
  is_contiguous<Container>::value, std::back_insert_iterator<Container>>::type
	vformat_to(std::back_insert_iterator<Container> out,
			   string_view format_str, format_args args) {
  auto& container = internal::get_container(out);
  internal::container_buffer<Container> buf(container);
  vformat_to(buf, format_str, args);
  return std::back_inserter(container);
}

template <typename Container>
typename std::enable_if<
  is_contiguous<Container>::value, std::back_insert_iterator<Container>>::type
  vformat_to(std::back_insert_iterator<Container> out,
			 wstring_view format_str, wformat_args args) {
  auto& container = internal::get_container(out);
  internal::container_buffer<Container> buf(container);
  vformat_to(buf, format_str, args);
  return std::back_inserter(container);
}

std::string vformat(string_view format_str, format_args args);
std::wstring vformat(wstring_view format_str, wformat_args args);

/**
  \rst
  Formats arguments and returns the result as a string.

  **Example**::

	#include <dmcore.h>
	std::string message = fmt::format("The answer is {}", 42);
  \endrst
*/
template <typename... Args>
inline std::string format(string_view format_str, const Args & ... args) {
  // This should be just
  // return vformat(format_str, fmt::make_format_args(args...));
  // but gcc has trouble optimizing the latter, so break it down.
  format_arg_store<format_context, Args...> as{args...};
  return vformat(format_str, as);
}
template <typename... Args>
inline std::wstring format(wstring_view format_str, const Args & ... args) {
  format_arg_store<wformat_context, Args...> as{args...};
  return vformat(format_str, as);
}

FMT_API void vprint(std::FILE *f, string_view format_str, format_args args);
FMT_API void vprint(std::FILE *f, wstring_view format_str, wformat_args args);

/**
  \rst
  Prints formatted data to the file *f*.

  **Example**::

	fmt::print(stderr, "Don't {}!", "panic");
  \endrst
 */
template <typename... Args>
inline void print(std::FILE *f, string_view format_str, const Args & ... args) {
  format_arg_store<format_context, Args...> as(args...);
  vprint(f, format_str, as);
}
/**
  Prints formatted data to the file *f* which should be in wide-oriented mode set
  via ``fwide(f, 1)`` or ``_setmode(_fileno(f), _O_U8TEXT)`` on Windows.
 */
template <typename... Args>
inline void print(std::FILE *f, wstring_view format_str, const Args & ... args) {
  format_arg_store<wformat_context, Args...> as(args...);
  vprint(f, format_str, as);
}

FMT_API void vprint(string_view format_str, format_args args);
FMT_API void vprint(wstring_view format_str, wformat_args args);

/**
  \rst
  Prints formatted data to ``stdout``.

  **Example**::

	fmt::print("Elapsed time: {0:.2f} seconds", 1.23);
  \endrst
 */
template <typename... Args>
inline void print(string_view format_str, const Args & ... args) {
  format_arg_store<format_context, Args...> as{args...};
  vprint(format_str, as);
}

template <typename... Args>
inline void print(wstring_view format_str, const Args & ... args) {
  format_arg_store<wformat_context, Args...> as(args...);
  vprint(format_str, as);
}
FMT_END_NAMESPACE

#endif // __DMFORMATCORE_H_INCLUDE__

/*** End of inlined file: dmformatcore.h ***/

#if FMT_GCC_VERSION >= 406 || FMT_CLANG_VERSION
# pragma GCC diagnostic push

// Disable the warning about declaration shadowing because it affects too
// many valid cases.
# pragma GCC diagnostic ignored "-Wshadow"

// Disable the warning about implicit conversions that may change the sign of
// an integer; silencing it otherwise would require many explicit casts.
# pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#ifdef _SECURE_SCL
# define FMT_SECURE_SCL _SECURE_SCL
#else
# define FMT_SECURE_SCL 0
#endif

#if FMT_SECURE_SCL
# include <iterator>
#endif

#ifdef __has_builtin
# define FMT_HAS_BUILTIN(x) __has_builtin(x)
#else
# define FMT_HAS_BUILTIN(x) 0
#endif

#ifdef __GNUC_LIBSTD__
# define FMT_GNUC_LIBSTD_VERSION (__GNUC_LIBSTD__ * 100 + __GNUC_LIBSTD_MINOR__)
#endif

#ifndef FMT_THROW
# if FMT_EXCEPTIONS
#  if FMT_MSC_VER
FMT_BEGIN_NAMESPACE
namespace internal {
template <typename Exception>
inline void do_throw(const Exception &x) {
  // Silence unreachable code warnings in MSVC because these are nearly
  // impossible to fix in a generic code.
  volatile bool b = true;
  if (b)
	throw x;
}
}
FMT_END_NAMESPACE
#   define FMT_THROW(x) fmt::internal::do_throw(x)
#  else
#   define FMT_THROW(x) throw x
#  endif
# else
#  define FMT_THROW(x) do { static_cast<void>(sizeof(x)); assert(false); } while(false);
# endif
#endif

#ifndef FMT_USE_USER_DEFINED_LITERALS
// For Intel's compiler both it and the system gcc/msc must support UDLs.
# if (FMT_HAS_FEATURE(cxx_user_literals) || \
	  FMT_GCC_VERSION >= 407 || FMT_MSC_VER >= 1900) && \
	  (!FMT_ICC_VERSION || FMT_ICC_VERSION >= 1500)
#  define FMT_USE_USER_DEFINED_LITERALS 1
# else
#  define FMT_USE_USER_DEFINED_LITERALS 0
# endif
#endif

#if FMT_USE_USER_DEFINED_LITERALS && !defined(FMT_ICC_VERSION) && \
	((FMT_GCC_VERSION >= 600 && __cplusplus >= 201402L) || \
	(defined(FMT_CLANG_VERSION) && FMT_CLANG_VERSION >= 304))
# define FMT_UDL_TEMPLATE 1
#else
# define FMT_UDL_TEMPLATE 0
#endif

#ifndef FMT_USE_EXTERN_TEMPLATES
# ifndef FMT_HEADER_ONLY
#  define FMT_USE_EXTERN_TEMPLATES \
	 ((FMT_CLANG_VERSION >= 209 && __cplusplus >= 201103L) || \
	  (FMT_GCC_VERSION >= 303 && FMT_HAS_GXX_CXX11))
# else
#  define FMT_USE_EXTERN_TEMPLATES 0
# endif
#endif

#if FMT_HAS_GXX_CXX11 || FMT_HAS_FEATURE(cxx_trailing_return) || \
	FMT_MSC_VER >= 1600
# define FMT_USE_TRAILING_RETURN 1
#else
# define FMT_USE_TRAILING_RETURN 0
#endif

#if FMT_HAS_GXX_CXX11 || FMT_HAS_FEATURE(cxx_rvalue_references) || \
	FMT_MSC_VER >= 1600
# define FMT_USE_RVALUE_REFERENCES 1
#else
# define FMT_USE_RVALUE_REFERENCES 0
#endif

#ifndef FMT_USE_GRISU
# define FMT_USE_GRISU 0
#endif

// __builtin_clz is broken in clang with Microsoft CodeGen:
// https://github.com/fmtlib/fmt/issues/519
#ifndef _MSC_VER
# if FMT_GCC_VERSION >= 400 || FMT_HAS_BUILTIN(__builtin_clz)
#  define FMT_BUILTIN_CLZ(n) __builtin_clz(n)
# endif

# if FMT_GCC_VERSION >= 400 || FMT_HAS_BUILTIN(__builtin_clzll)
#  define FMT_BUILTIN_CLZLL(n) __builtin_clzll(n)
# endif
#endif

// A workaround for gcc 4.4 that doesn't support union members with ctors.
#if (FMT_GCC_VERSION && FMT_GCC_VERSION <= 404) || \
	(FMT_MSC_VER && FMT_MSC_VER <= 1800)
# define FMT_UNION struct
#else
# define FMT_UNION union
#endif

// Some compilers masquerade as both MSVC and GCC-likes or otherwise support
// __builtin_clz and __builtin_clzll, so only define FMT_BUILTIN_CLZ using the
// MSVC intrinsics if the clz and clzll builtins are not available.
#if FMT_MSC_VER && !defined(FMT_BUILTIN_CLZLL) && !defined(_MANAGED)
# include <intrin.h>  // _BitScanReverse, _BitScanReverse64

FMT_BEGIN_NAMESPACE
namespace internal {
// Avoid Clang with Microsoft CodeGen's -Wunknown-pragmas warning.
# ifndef __clang__
#  pragma intrinsic(_BitScanReverse)
# endif
inline uint32_t clz(uint32_t x) {
  unsigned long r = 0;
  _BitScanReverse(&r, x);

  assert(x != 0);
  // Static analysis complains about using uninitialized data
  // "r", but the only way that can happen is if "x" is 0,
  // which the callers guarantee to not happen.
# pragma warning(suppress: 6102)
  return 31 - r;
}
# define FMT_BUILTIN_CLZ(n) fmt::internal::clz(n)

# if defined(_WIN64) && !defined(__clang__)
#  pragma intrinsic(_BitScanReverse64)
# endif

inline uint32_t clzll(uint64_t x) {
  unsigned long r = 0;
# ifdef _WIN64
  _BitScanReverse64(&r, x);
# else
  // Scan the high 32 bits.
  if (_BitScanReverse(&r, static_cast<uint32_t>(x >> 32)))
	return 63 - (r + 32);

  // Scan the low 32 bits.
  _BitScanReverse(&r, static_cast<uint32_t>(x));
# endif

  assert(x != 0);
  // Static analysis complains about using uninitialized data
  // "r", but the only way that can happen is if "x" is 0,
  // which the callers guarantee to not happen.
# pragma warning(suppress: 6102)
  return 63 - r;
}
# define FMT_BUILTIN_CLZLL(n) fmt::internal::clzll(n)
}
FMT_END_NAMESPACE
#endif

FMT_BEGIN_NAMESPACE
namespace internal {

// An equivalent of `*reinterpret_cast<Dest*>(&source)` that doesn't produce
// undefined behavior (e.g. due to type aliasing).
// Example: uint64_t d = bit_cast<uint64_t>(2.718);
template <typename Dest, typename Source>
inline Dest bit_cast(const Source& source) {
  static_assert(sizeof(Dest) == sizeof(Source), "size mismatch");
  Dest dest;
  std::memcpy(&dest, &source, sizeof(dest));
  return dest;
}

// An implementation of begin and end for pre-C++11 compilers such as gcc 4.
template <typename C>
FMT_CONSTEXPR auto begin(const C &c) -> decltype(c.begin()) {
  return c.begin();
}
template <typename T, std::size_t N>
FMT_CONSTEXPR T *begin(T (&array)[N]) FMT_NOEXCEPT { return array; }
template <typename C>
FMT_CONSTEXPR auto end(const C &c) -> decltype(c.end()) { return c.end(); }
template <typename T, std::size_t N>
FMT_CONSTEXPR T *end(T (&array)[N]) FMT_NOEXCEPT { return array + N; }

// For std::result_of in gcc 4.4.
template <typename Result>
struct function {
  template <typename T>
  struct result { typedef Result type; };
};

struct dummy_int {
  int data[2];
  operator int() const { return 0; }
};
typedef std::numeric_limits<internal::dummy_int> fputil;

// Dummy implementations of system functions such as signbit and ecvt called
// if the latter are not available.
inline dummy_int signbit(...) { return dummy_int(); }
inline dummy_int _ecvt_s(...) { return dummy_int(); }
inline dummy_int isinf(...) { return dummy_int(); }
inline dummy_int _finite(...) { return dummy_int(); }
inline dummy_int isnan(...) { return dummy_int(); }
inline dummy_int _isnan(...) { return dummy_int(); }

// A handmade floating-point number f * pow(2, e).
class fp {
 private:
  typedef uint64_t significand_type;

  // All sizes are in bits.
  static FMT_CONSTEXPR_DECL const int char_size =
	std::numeric_limits<unsigned char>::digits;
  // Subtract 1 to account for an implicit most significant bit in the
  // normalized form.
  static FMT_CONSTEXPR_DECL const int double_significand_size =
	std::numeric_limits<double>::digits - 1;
  static FMT_CONSTEXPR_DECL const uint64_t implicit_bit =
	1ull << double_significand_size;

 public:
  significand_type f;
  int e;

  static FMT_CONSTEXPR_DECL const int significand_size =
	sizeof(significand_type) * char_size;

  fp(uint64_t f, int e): f(f), e(e) {}

  // Constructs fp from an IEEE754 double. It is a template to prevent compile
  // errors on platforms where double is not IEEE754.
  template <typename Double>
  explicit fp(Double d) {
	// Assume double is in the format [sign][exponent][significand].
	typedef std::numeric_limits<Double> limits;
	const int double_size = sizeof(Double) * char_size;
	const int exponent_size =
	  double_size - double_significand_size - 1;  // -1 for sign
	const uint64_t significand_mask = implicit_bit - 1;
	const uint64_t exponent_mask = (~0ull >> 1) & ~significand_mask;
	const int exponent_bias = (1 << exponent_size) - limits::max_exponent - 1;
	auto u = bit_cast<uint64_t>(d);
	auto biased_e = (u & exponent_mask) >> double_significand_size;
	f = u & significand_mask;
	if (biased_e != 0)
	  f += implicit_bit;
	else
	  biased_e = 1;  // Subnormals use biased exponent 1 (min exponent).
	e = static_cast<int>(biased_e - exponent_bias - double_significand_size);
  }

  // Normalizes the value converted from double and multiplied by (1 << SHIFT).
  template <int SHIFT = 0>
  void normalize() {
	// Handle subnormals.
	auto shifted_implicit_bit = implicit_bit << SHIFT;
	while ((f & shifted_implicit_bit) == 0) {
	  f <<= 1;
	  --e;
	}
	// Subtract 1 to account for hidden bit.
	auto offset = significand_size - double_significand_size - SHIFT - 1;
	f <<= offset;
	e -= offset;
  }
};

// Returns an fp number representing x - y. Result may not be normalized.
inline fp operator-(fp x, fp y) {
  FMT_ASSERT(x.f >= y.f && x.e == y.e, "invalid operands");
  return fp(x.f - y.f, x.e);
}

// Computes an fp number r with r.f = x.f * y.f / pow(2, 64) rounded to nearest
// with half-up tie breaking, r.e = x.e + y.e + 64. Result may not be normalized.
fp operator*(fp x, fp y);

// Returns cached power (of 10) c_k = c_k.f * pow(2, c_k.e) such that its
// (binary) exponent satisfies min_exponent <= c_k.e <= min_exponent + 3.
fp get_cached_power(int min_exponent, int &pow10_exponent);

template <typename Allocator>
typename Allocator::value_type *allocate(Allocator& alloc, std::size_t n) {
#if __cplusplus >= 201103L || FMT_MSC_VER >= 1700
  return std::allocator_traits<Allocator>::allocate(alloc, n);
#else
  return alloc.allocate(n);
#endif
}

// A helper function to suppress bogus "conditional expression is constant"
// warnings.
template <typename T>
inline T const_check(T value) { return value; }
}  // namespace internal
FMT_END_NAMESPACE

namespace std {
// Standard permits specialization of std::numeric_limits. This specialization
// is used to resolve ambiguity between isinf and std::isinf in glibc:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=48891
// and the same for isnan and signbit.
template <>
class numeric_limits<fmt::internal::dummy_int> :
	public std::numeric_limits<int> {
 public:
  // Portable version of isinf.
  template <typename T>
  static bool isinfinity(T x) {
	using namespace fmt::internal;
	// The resolution "priority" is:
	// isinf macro > std::isinf > ::isinf > fmt::internal::isinf
	if (const_check(sizeof(isinf(x)) != sizeof(dummy_int)))
	  return isinf(x) != 0;
	return !_finite(static_cast<double>(x));
  }

  // Portable version of isnan.
  template <typename T>
  static bool isnotanumber(T x) {
	using namespace fmt::internal;
	if (const_check(sizeof(isnan(x)) != sizeof(fmt::internal::dummy_int)))
	  return isnan(x) != 0;
	return _isnan(static_cast<double>(x)) != 0;
  }

  // Portable version of signbit.
  static bool isnegative(double x) {
	using namespace fmt::internal;
	if (const_check(sizeof(signbit(x)) != sizeof(fmt::internal::dummy_int)))
	  return signbit(x) != 0;
	if (x < 0) return true;
	if (!isnotanumber(x)) return false;
	int dec = 0, sign = 0;
	char buffer[2];  // The buffer size must be >= 2 or _ecvt_s will fail.
	_ecvt_s(buffer, sizeof(buffer), x, 0, &dec, &sign);
	return sign != 0;
  }
};
}  // namespace std

FMT_BEGIN_NAMESPACE
template <typename Range>
class basic_writer;

template <typename OutputIt, typename T = typename OutputIt::value_type>
class output_range {
 private:
  OutputIt it_;

  // Unused yet.
  typedef void sentinel;
  sentinel end() const;

 public:
  typedef OutputIt iterator;
  typedef T value_type;

  explicit output_range(OutputIt it): it_(it) {}
  OutputIt begin() const { return it_; }
};

// A range where begin() returns back_insert_iterator.
template <typename Container>
class back_insert_range:
	public output_range<std::back_insert_iterator<Container>> {
  typedef output_range<std::back_insert_iterator<Container>> base;
 public:
  typedef typename Container::value_type value_type;

  back_insert_range(Container &c): base(std::back_inserter(c)) {}
  back_insert_range(typename base::iterator it): base(it) {}
};

typedef basic_writer<back_insert_range<internal::buffer>> writer;
typedef basic_writer<back_insert_range<internal::wbuffer>> wwriter;

/** A formatting error such as invalid format string. */
class format_error : public std::runtime_error {
 public:
  explicit format_error(const char *message)
  : std::runtime_error(message) {}

  explicit format_error(const std::string &message)
  : std::runtime_error(message) {}
};

namespace internal {

#if FMT_SECURE_SCL
template <typename T>
struct checked { typedef stdext::checked_array_iterator<T*> type; };

// Make a checked iterator to avoid warnings on MSVC.
template <typename T>
inline stdext::checked_array_iterator<T*> make_checked(T *p, std::size_t size) {
  return {p, size};
}
#else
template <typename T>
struct checked { typedef T *type; };
template <typename T>
inline T *make_checked(T *p, std::size_t) { return p; }
#endif

template <typename T>
template <typename U>
void basic_buffer<T>::append(const U *begin, const U *end) {
  std::size_t new_size = size_ + internal::to_unsigned(end - begin);
  reserve(new_size);
  std::uninitialized_copy(begin, end,
						  internal::make_checked(ptr_, capacity_) + size_);
  size_ = new_size;
}
}  // namespace internal

// A wrapper around std::locale used to reduce compile times since <locale>
// is very heavy.
class locale;

class locale_provider {
 public:
  virtual ~locale_provider() {}
  virtual fmt::locale locale();
};

// The number of characters to store in the basic_memory_buffer object itself
// to avoid dynamic memory allocation.
enum { inline_buffer_size = 500 };

/**
  \rst
  A dynamically growing memory buffer for trivially copyable/constructible types
  with the first ``SIZE`` elements stored in the object itself.

  You can use one of the following typedefs for common character types:

  +----------------+------------------------------+
  | Type           | Definition                   |
  +================+==============================+
  | memory_buffer  | basic_memory_buffer<char>    |
  +----------------+------------------------------+
  | wmemory_buffer | basic_memory_buffer<wchar_t> |
  +----------------+------------------------------+

  **Example**::

	 fmt::memory_buffer out;
	 format_to(out, "The answer is {}.", 42);

  This will write the following output to the ``out`` object:

  .. code-block:: none

	 The answer is 42.

  The output can be converted to an ``std::string`` with ``to_string(out)``.
  \endrst
 */
template <typename T, std::size_t SIZE = inline_buffer_size,
		  typename Allocator = std::allocator<T> >
class basic_memory_buffer: private Allocator, public internal::basic_buffer<T> {
 private:
  T store_[SIZE];

  // Deallocate memory allocated by the buffer.
  void deallocate() {
	T* data = this->data();
	if (data != store_) Allocator::deallocate(data, this->capacity());
  }

 protected:
  void grow(std::size_t size) FMT_OVERRIDE;

 public:
  explicit basic_memory_buffer(const Allocator &alloc = Allocator())
	  : Allocator(alloc) {
	this->set(store_, SIZE);
  }
  ~basic_memory_buffer() { deallocate(); }

 private:
  // Move data from other to this buffer.
  void move(basic_memory_buffer &other) {
	Allocator &this_alloc = *this, &other_alloc = other;
	this_alloc = std::move(other_alloc);
	T* data = other.data();
	std::size_t size = other.size(), capacity = other.capacity();
	if (data == other.store_) {
	  this->set(store_, capacity);
	  std::uninitialized_copy(other.store_, other.store_ + size,
							  internal::make_checked(store_, capacity));
	} else {
	  this->set(data, capacity);
	  // Set pointer to the inline array so that delete is not called
	  // when deallocating.
	  other.set(other.store_, 0);
	}
	this->resize(size);
  }

 public:
  /**
	\rst
	Constructs a :class:`fmt::basic_memory_buffer` object moving the content
	of the other object to it.
	\endrst
   */
  basic_memory_buffer(basic_memory_buffer &&other) {
	move(other);
  }

  /**
	\rst
	Moves the content of the other ``basic_memory_buffer`` object to this one.
	\endrst
   */
  basic_memory_buffer &operator=(basic_memory_buffer &&other) {
	assert(this != &other);
	deallocate();
	move(other);
	return *this;
  }

  // Returns a copy of the allocator associated with this buffer.
  Allocator get_allocator() const { return *this; }
};

template <typename T, std::size_t SIZE, typename Allocator>
void basic_memory_buffer<T, SIZE, Allocator>::grow(std::size_t size) {
  std::size_t old_capacity = this->capacity();
  std::size_t new_capacity = old_capacity + old_capacity / 2;
  if (size > new_capacity)
	  new_capacity = size;
  T *old_data = this->data();
  T *new_data = internal::allocate<Allocator>(*this, new_capacity);
  // The following code doesn't throw, so the raw pointer above doesn't leak.
  std::uninitialized_copy(old_data, old_data + this->size(),
						  internal::make_checked(new_data, new_capacity));
  this->set(new_data, new_capacity);
  // deallocate must not throw according to the standard, but even if it does,
  // the buffer already uses the new storage and will deallocate it in
  // destructor.
  if (old_data != store_)
	Allocator::deallocate(old_data, old_capacity);
}

typedef basic_memory_buffer<char> memory_buffer;
typedef basic_memory_buffer<wchar_t> wmemory_buffer;

/**
  \rst
  A fixed-size memory buffer. For a dynamically growing buffer use
  :class:`fmt::basic_memory_buffer`.

  Trying to increase the buffer size past the initial capacity will throw
  ``std::runtime_error``.
  \endrst
 */
template <typename Char>
class basic_fixed_buffer : public internal::basic_buffer<Char> {
 public:
  /**
   \rst
   Constructs a :class:`fmt::basic_fixed_buffer` object for *array* of the
   given size.
   \endrst
   */
  basic_fixed_buffer(Char *array, std::size_t size) {
	this->set(array, size);
  }

  /**
   \rst
   Constructs a :class:`fmt::basic_fixed_buffer` object for *array* of the
   size known at compile time.
   \endrst
   */
  template <std::size_t SIZE>
  explicit basic_fixed_buffer(Char (&array)[SIZE]) {
	this->set(array, SIZE);
  }

 protected:
  FMT_API void grow(std::size_t size) FMT_OVERRIDE;
};

namespace internal {

template <typename Char>
struct char_traits;

template <>
struct char_traits<char> {
  // Formats a floating-point number.
  template <typename T>
  FMT_API static int format_float(char *buffer, std::size_t size,
	  const char *format, int precision, T value);
};

template <>
struct char_traits<wchar_t> {
  template <typename T>
  FMT_API static int format_float(wchar_t *buffer, std::size_t size,
	  const wchar_t *format, int precision, T value);
};

#if FMT_USE_EXTERN_TEMPLATES
extern template int char_traits<char>::format_float<double>(
	char *buffer, std::size_t size, const char* format, int precision,
	double value);
extern template int char_traits<char>::format_float<long double>(
	char *buffer, std::size_t size, const char* format, int precision,
	long double value);

extern template int char_traits<wchar_t>::format_float<double>(
	wchar_t *buffer, std::size_t size, const wchar_t* format, int precision,
	double value);
extern template int char_traits<wchar_t>::format_float<long double>(
	wchar_t *buffer, std::size_t size, const wchar_t* format, int precision,
	long double value);
#endif

template <typename Container>
inline typename std::enable_if<
  is_contiguous<Container>::value,
  typename checked<typename Container::value_type>::type>::type
	reserve(std::back_insert_iterator<Container> &it, std::size_t n) {
  Container &c = internal::get_container(it);
  std::size_t size = c.size();
  c.resize(size + n);
  return make_checked(&c[size], n);
}

template <typename Iterator>
inline Iterator &reserve(Iterator &it, std::size_t) { return it; }

template <typename Char>
class null_terminating_iterator;

template <typename Char>
FMT_CONSTEXPR_DECL const Char *pointer_from(null_terminating_iterator<Char> it);

// An iterator that produces a null terminator on *end. This simplifies parsing
// and allows comparing the performance of processing a null-terminated string
// vs string_view.
template <typename Char>
class null_terminating_iterator {
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Char value_type;
  typedef const Char* pointer;
  typedef const Char& reference;
  typedef std::random_access_iterator_tag iterator_category;

  null_terminating_iterator() : ptr_(0), end_(0) {}

  FMT_CONSTEXPR null_terminating_iterator(const Char *ptr, const Char *end)
	: ptr_(ptr), end_(end) {}

  template <typename Range>
  FMT_CONSTEXPR explicit null_terminating_iterator(const Range &r)
	: ptr_(r.begin()), end_(r.end()) {}

  null_terminating_iterator &operator=(const Char *ptr) {
	assert(ptr <= end_);
	ptr_ = ptr;
	return *this;
  }

  FMT_CONSTEXPR Char operator*() const {
	return ptr_ != end_ ? *ptr_ : 0;
  }

  FMT_CONSTEXPR null_terminating_iterator operator++() {
	++ptr_;
	return *this;
  }

  FMT_CONSTEXPR null_terminating_iterator operator++(int) {
	null_terminating_iterator result(*this);
	++ptr_;
	return result;
  }

  FMT_CONSTEXPR null_terminating_iterator operator--() {
	--ptr_;
	return *this;
  }

  FMT_CONSTEXPR null_terminating_iterator operator+(difference_type n) {
	return null_terminating_iterator(ptr_ + n, end_);
  }

  FMT_CONSTEXPR null_terminating_iterator operator-(difference_type n) {
	return null_terminating_iterator(ptr_ - n, end_);
  }

  FMT_CONSTEXPR null_terminating_iterator operator+=(difference_type n) {
	ptr_ += n;
	return *this;
  }

  FMT_CONSTEXPR difference_type operator-(
	  null_terminating_iterator other) const {
	return ptr_ - other.ptr_;
  }

  FMT_CONSTEXPR bool operator!=(null_terminating_iterator other) const {
	return ptr_ != other.ptr_;
  }

  bool operator>=(null_terminating_iterator other) const {
	return ptr_ >= other.ptr_;
  }

  // This should be a friend specialization pointer_from<Char> but the latter
  // doesn't compile by gcc 5.1 due to a compiler bug.
  template <typename CharT>
  friend FMT_CONSTEXPR_DECL const CharT *pointer_from(
	  null_terminating_iterator<CharT> it);

 private:
  const Char *ptr_;
  const Char *end_;
};

template <typename T>
FMT_CONSTEXPR const T *pointer_from(const T *p) { return p; }

template <typename Char>
FMT_CONSTEXPR const Char *pointer_from(null_terminating_iterator<Char> it) {
  return it.ptr_;
}

// An output iterator that counts the number of objects written to it and
// discards them.
template <typename T>
class counting_iterator {
 private:
  std::size_t count_;
  mutable T blackhole_;

 public:
  typedef std::output_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T* pointer;
  typedef T& reference;
  typedef counting_iterator _Unchecked_type;  // Mark iterator as checked.

  counting_iterator(): count_(0) {}

  std::size_t count() const { return count_; }

  counting_iterator& operator++() {
	++count_;
	return *this;
  }

  counting_iterator operator++(int) {
	auto it = *this;
	++*this;
	return it;
  }

  T &operator*() const { return blackhole_; }
};

// An output iterator that truncates the output and counts the number of objects
// written to it.
template <typename OutputIt>
class truncating_iterator {
 private:
  typedef std::iterator_traits<OutputIt> traits;

  OutputIt out_;
  std::size_t limit_;
  std::size_t count_;
  mutable typename traits::value_type blackhole_;

 public:
  typedef std::output_iterator_tag iterator_category;
  typedef typename traits::value_type value_type;
  typedef typename traits::difference_type difference_type;
  typedef typename traits::pointer pointer;
  typedef typename traits::reference reference;
  typedef truncating_iterator _Unchecked_type;  // Mark iterator as checked.

  truncating_iterator(OutputIt out, std::size_t limit)
	: out_(out), limit_(limit), count_(0) {}

  OutputIt base() const { return out_; }
  std::size_t count() const { return count_; }

  truncating_iterator& operator++() {
	if (count_++ < limit_)
	  ++out_;
	return *this;
  }

  truncating_iterator operator++(int) {
	auto it = *this;
	++*this;
	return it;
  }

  reference operator*() const { return count_ < limit_ ? *out_ : blackhole_; }
};

// Returns true if value is negative, false otherwise.
// Same as (value < 0) but doesn't produce warnings if T is an unsigned type.
template <typename T>
FMT_CONSTEXPR typename std::enable_if<
	std::numeric_limits<T>::is_signed, bool>::type is_negative(T value) {
  return value < 0;
}
template <typename T>
FMT_CONSTEXPR typename std::enable_if<
	!std::numeric_limits<T>::is_signed, bool>::type is_negative(T) {
  return false;
}

template <typename T>
struct int_traits {
  // Smallest of uint32_t and uint64_t that is large enough to represent
  // all values of T.
  typedef typename std::conditional<
	std::numeric_limits<T>::digits <= 32, uint32_t, uint64_t>::type main_type;
};

// Static data is placed in this class template to allow header-only
// configuration.
template <typename T = void>
struct FMT_API basic_data {
  static const uint32_t POWERS_OF_10_32[];
  static const uint64_t POWERS_OF_10_64[];
  static const uint64_t POW10_SIGNIFICANDS[];
  static const int16_t POW10_EXPONENTS[];
  static const char DIGITS[];
  static const char RESET_COLOR[];
  static const wchar_t WRESET_COLOR[];
};

#if FMT_USE_EXTERN_TEMPLATES
extern template struct basic_data<void>;
#endif

typedef basic_data<> data;

#ifdef FMT_BUILTIN_CLZLL
// Returns the number of decimal digits in n. Leading zeros are not counted
// except for n == 0 in which case count_digits returns 1.
inline unsigned count_digits(uint64_t n) {
  // Based on http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10
  // and the benchmark https://github.com/localvoid/cxx-benchmark-count-digits.
  int t = (64 - FMT_BUILTIN_CLZLL(n | 1)) * 1233 >> 12;
  return to_unsigned(t) - (n < data::POWERS_OF_10_64[t]) + 1;
}
#else
// Fallback version of count_digits used when __builtin_clz is not available.
inline unsigned count_digits(uint64_t n) {
  unsigned count = 1;
  for (;;) {
	// Integer division is slow so do it for a group of four digits instead
	// of for every digit. The idea comes from the talk by Alexandrescu
	// "Three Optimization Tips for C++". See speed-test for a comparison.
	if (n < 10) return count;
	if (n < 100) return count + 1;
	if (n < 1000) return count + 2;
	if (n < 10000) return count + 3;
	n /= 10000u;
	count += 4;
  }
}
#endif

#if FMT_HAS_CPP_ATTRIBUTE(always_inline)
# define FMT_ALWAYS_INLINE __attribute__((always_inline))
#else
# define FMT_ALWAYS_INLINE
#endif

template <typename Handler>
inline char *lg(uint32_t n, Handler h) FMT_ALWAYS_INLINE;

// Computes g = floor(log10(n)) and calls h.on<g>(n);
template <typename Handler>
inline char *lg(uint32_t n, Handler h) {
  return n < 100 ? n < 10 ? h.template on<0>(n) : h.template on<1>(n)
				 : n < 1000000
					   ? n < 10000 ? n < 1000 ? h.template on<2>(n)
											  : h.template on<3>(n)
								   : n < 100000 ? h.template on<4>(n)
												: h.template on<5>(n)
					   : n < 100000000 ? n < 10000000 ? h.template on<6>(n)
													  : h.template on<7>(n)
									   : n < 1000000000 ? h.template on<8>(n)
														: h.template on<9>(n);
}

// An lg handler that formats a decimal number.
// Usage: lg(n, decimal_formatter(buffer));
class decimal_formatter {
 private:
  char *buffer_;

  void write_pair(unsigned N, uint32_t index) {
	std::memcpy(buffer_ + N, data::DIGITS + index * 2, 2);
  }

 public:
  explicit decimal_formatter(char *buf) : buffer_(buf) {}

  template <unsigned N> char *on(uint32_t u) {
	if (N == 0) {
	  *buffer_ = static_cast<char>(u) + '0';
	} else if (N == 1) {
	  write_pair(0, u);
	} else {
	  // The idea of using 4.32 fixed-point numbers is based on
	  // https://github.com/jeaiii/itoa
	  unsigned n = N - 1;
	  unsigned a = n / 5 * n * 53 / 16;
	  uint64_t t = ((1ULL << (32 + a)) / data::POWERS_OF_10_32[n] + 1 - n / 9);
	  t = ((t * u) >> a) + n / 5 * 4;
	  write_pair(0, t >> 32);
	  for (unsigned i = 2; i < N; i += 2) {
		t = 100ULL * static_cast<uint32_t>(t);
		write_pair(i, t >> 32);
	  }
	  if (N % 2 == 0) {
		buffer_[N] = static_cast<char>(
		  (10ULL * static_cast<uint32_t>(t)) >> 32) + '0';
	  }
	}
	return buffer_ += N + 1;
  }
};

// An lg handler that formats a decimal number with a terminating null.
class decimal_formatter_null : public decimal_formatter {
 public:
  explicit decimal_formatter_null(char *buf) : decimal_formatter(buf) {}

  template <unsigned N> char *on(uint32_t u) {
	char *buf = decimal_formatter::on<N>(u);
	*buf = '\0';
	return buf;
  }
};

#ifdef FMT_BUILTIN_CLZ
// Optional version of count_digits for better performance on 32-bit platforms.
inline unsigned count_digits(uint32_t n) {
  int t = (32 - FMT_BUILTIN_CLZ(n | 1)) * 1233 >> 12;
  return to_unsigned(t) - (n < data::POWERS_OF_10_32[t]) + 1;
}
#endif

// A functor that doesn't add a thousands separator.
struct no_thousands_sep {
  typedef char char_type;

  template <typename Char>
  void operator()(Char *) {}
};

// A functor that adds a thousands separator.
template <typename Char>
class add_thousands_sep {
 private:
  basic_string_view<Char> sep_;

  // Index of a decimal digit with the least significant digit having index 0.
  unsigned digit_index_;

 public:
  typedef Char char_type;

  explicit add_thousands_sep(basic_string_view<Char> sep)
	: sep_(sep), digit_index_(0) {}

  void operator()(Char *&buffer) {
	if (++digit_index_ % 3 != 0)
	  return;
	buffer -= sep_.size();
	std::uninitialized_copy(sep_.data(), sep_.data() + sep_.size(),
							internal::make_checked(buffer, sep_.size()));
  }
};

template <typename Char>
FMT_API Char thousands_sep(locale_provider *lp);

// Formats a decimal unsigned integer value writing into buffer.
// thousands_sep is a functor that is called after writing each char to
// add a thousands separator if necessary.
template <typename UInt, typename Char, typename ThousandsSep>
inline Char *format_decimal(Char *buffer, UInt value, unsigned num_digits,
							ThousandsSep thousands_sep) {
  buffer += num_digits;
  Char *end = buffer;
  while (value >= 100) {
	// Integer division is slow so do it for a group of two digits instead
	// of for every digit. The idea comes from the talk by Alexandrescu
	// "Three Optimization Tips for C++". See speed-test for a comparison.
	unsigned index = static_cast<unsigned>((value % 100) * 2);
	value /= 100;
	*--buffer = data::DIGITS[index + 1];
	thousands_sep(buffer);
	*--buffer = data::DIGITS[index];
	thousands_sep(buffer);
  }
  if (value < 10) {
	*--buffer = static_cast<char>('0' + value);
	return end;
  }
  unsigned index = static_cast<unsigned>(value * 2);
  *--buffer = data::DIGITS[index + 1];
  thousands_sep(buffer);
  *--buffer = data::DIGITS[index];
  return end;
}

template <typename UInt, typename Iterator, typename ThousandsSep>
inline Iterator format_decimal(
	Iterator out, UInt value, unsigned num_digits, ThousandsSep sep) {
  typedef typename ThousandsSep::char_type char_type;
  // Buffer should be large enough to hold all digits (digits10 + 1) and null.
  char_type buffer[std::numeric_limits<UInt>::digits10 + 2];
  format_decimal(buffer, value, num_digits, sep);
  return std::copy_n(buffer, num_digits, out);
}

template <typename It, typename UInt>
inline It format_decimal(It out, UInt value, unsigned num_digits) {
  return format_decimal(out, value, num_digits, no_thousands_sep());
}

template <unsigned BASE_BITS, typename Char, typename UInt>
inline Char *format_uint(Char *buffer, UInt value, unsigned num_digits,
						 bool upper = false) {
  buffer += num_digits;
  Char *end = buffer;
  do {
	const char *digits = upper ? "0123456789ABCDEF" : "0123456789abcdef";
	unsigned digit = (value & ((1 << BASE_BITS) - 1));
	*--buffer = BASE_BITS < 4 ? static_cast<char>('0' + digit) : digits[digit];
  } while ((value >>= BASE_BITS) != 0);
  return end;
}

template <unsigned BASE_BITS, typename It, typename UInt>
inline It format_uint(It out, UInt value, unsigned num_digits,
					  bool upper = false) {
  // Buffer should be large enough to hold all digits (digits / BASE_BITS + 1)
  // and null.
  char buffer[std::numeric_limits<UInt>::digits / BASE_BITS + 2];
  format_uint<BASE_BITS>(buffer, value, num_digits, upper);
  return std::copy_n(buffer, num_digits, out);
}

#ifndef _WIN32
# define FMT_USE_WINDOWS_H 0
#elif !defined(FMT_USE_WINDOWS_H)
# define FMT_USE_WINDOWS_H 1
#endif

// Define FMT_USE_WINDOWS_H to 0 to disable use of windows.h.
// All the functionality that relies on it will be disabled too.
#if FMT_USE_WINDOWS_H
// A converter from UTF-8 to UTF-16.
// It is only provided for Windows since other systems support UTF-8 natively.
class utf8_to_utf16 {
 private:
  wmemory_buffer buffer_;

 public:
  FMT_API explicit utf8_to_utf16(string_view s);
  operator wstring_view() const { return wstring_view(&buffer_[0], size()); }
  size_t size() const { return buffer_.size() - 1; }
  const wchar_t *c_str() const { return &buffer_[0]; }
  std::wstring str() const { return std::wstring(&buffer_[0], size()); }
};

// A converter from UTF-16 to UTF-8.
// It is only provided for Windows since other systems support UTF-8 natively.
class utf16_to_utf8 {
 private:
  memory_buffer buffer_;

 public:
  utf16_to_utf8() {}
  FMT_API explicit utf16_to_utf8(wstring_view s);
  operator string_view() const { return string_view(&buffer_[0], size()); }
  size_t size() const { return buffer_.size() - 1; }
  const char *c_str() const { return &buffer_[0]; }
  std::string str() const { return std::string(&buffer_[0], size()); }

  // Performs conversion returning a system error code instead of
  // throwing exception on conversion error. This method may still throw
  // in case of memory allocation error.
  FMT_API int convert(wstring_view s);
};

FMT_API void format_windows_error(fmt::internal::buffer &out, int error_code,
								  fmt::string_view message) FMT_NOEXCEPT;
#endif

template <typename T = void>
struct null {};
}  // namespace internal

struct monostate {};

/**
  \rst
  Visits an argument dispatching to the appropriate visit method based on
  the argument type. For example, if the argument type is ``double`` then
  ``vis(value)`` will be called with the value of type ``double``.
  \endrst
 */
template <typename Visitor, typename Context>
FMT_CONSTEXPR typename internal::result_of<Visitor(int)>::type
	visit(Visitor &&vis, basic_format_arg<Context> arg) {
  typedef typename Context::char_type char_type;
  switch (arg.type_) {
  case internal::none_type:
	break;
  case internal::named_arg_type:
	FMT_ASSERT(false, "invalid argument type");
	break;
  case internal::int_type:
	return vis(arg.value_.int_value);
  case internal::uint_type:
	return vis(arg.value_.uint_value);
  case internal::long_long_type:
	return vis(arg.value_.long_long_value);
  case internal::ulong_long_type:
	return vis(arg.value_.ulong_long_value);
  case internal::bool_type:
	return vis(arg.value_.int_value != 0);
  case internal::char_type:
	return vis(static_cast<char_type>(arg.value_.int_value));
  case internal::double_type:
	return vis(arg.value_.double_value);
  case internal::long_double_type:
	return vis(arg.value_.long_double_value);
  case internal::cstring_type:
	return vis(arg.value_.string.value);
  case internal::string_type:
	return vis(basic_string_view<char_type>(
				 arg.value_.string.value, arg.value_.string.size));
  case internal::pointer_type:
	return vis(arg.value_.pointer);
  case internal::custom_type:
	return vis(typename basic_format_arg<Context>::handle(arg.value_.custom));
  }
  return vis(monostate());
}

enum alignment {
  ALIGN_DEFAULT, ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER, ALIGN_NUMERIC
};

// Flags.
enum {SIGN_FLAG = 1, PLUS_FLAG = 2, MINUS_FLAG = 4, HASH_FLAG = 8};

enum format_spec_tag {fill_tag, align_tag, width_tag, type_tag};

// Format specifier.
template <typename T, format_spec_tag>
class format_spec {
 private:
  T value_;

 public:
  typedef T value_type;

  explicit format_spec(T value) : value_(value) {}

  T value() const { return value_; }
};

// template <typename Char>
// typedef format_spec<Char, fill_tag> fill_spec;
template <typename Char>
class fill_spec : public format_spec<Char, fill_tag> {
 public:
  explicit fill_spec(Char value) : format_spec<Char, fill_tag>(value) {}
};

typedef format_spec<unsigned, width_tag> width_spec;
typedef format_spec<char, type_tag> type_spec;

// An empty format specifier.
struct empty_spec {};

// An alignment specifier.
struct align_spec : empty_spec {
  unsigned width_;
  // Fill is always wchar_t and cast to char if necessary to avoid having
  // two specialization of AlignSpec and its subclasses.
  wchar_t fill_;
  alignment align_;

  FMT_CONSTEXPR align_spec(
	  unsigned width, wchar_t fill, alignment align = ALIGN_DEFAULT)
  : width_(width), fill_(fill), align_(align) {}

  FMT_CONSTEXPR unsigned width() const { return width_; }
  FMT_CONSTEXPR wchar_t fill() const { return fill_; }
  FMT_CONSTEXPR alignment align() const { return align_; }

  int precision() const { return -1; }
};

// Format specifiers.
template <typename Char>
class basic_format_specs : public align_spec {
 public:
  unsigned flags_;
  int precision_;
  Char type_;

  FMT_CONSTEXPR basic_format_specs(
	  unsigned width = 0, char type = 0, wchar_t fill = ' ')
  : align_spec(width, fill), flags_(0), precision_(-1), type_(type) {}

  FMT_CONSTEXPR bool flag(unsigned f) const { return (flags_ & f) != 0; }
  FMT_CONSTEXPR int precision() const { return precision_; }
  FMT_CONSTEXPR Char type() const { return type_; }
};

typedef basic_format_specs<char> format_specs;

template <typename Char, typename ErrorHandler>
FMT_CONSTEXPR unsigned basic_parse_context<Char, ErrorHandler>::next_arg_id() {
  if (next_arg_id_ >= 0)
	return internal::to_unsigned(next_arg_id_++);
  on_error("cannot switch from manual to automatic argument indexing");
  return 0;
}

struct format_string {};

namespace internal {

template <typename Char, typename Handler>
FMT_CONSTEXPR void handle_int_type_spec(Char spec, Handler &&handler) {
  switch (spec) {
  case 0: case 'd':
	handler.on_dec();
	break;
  case 'x': case 'X':
	handler.on_hex();
	break;
  case 'b': case 'B':
	handler.on_bin();
	break;
  case 'o':
	handler.on_oct();
	break;
  case 'n':
	handler.on_num();
	break;
  default:
	handler.on_error();
  }
}

template <typename Char, typename Handler>
FMT_CONSTEXPR void handle_float_type_spec(Char spec, Handler &&handler) {
  switch (spec) {
  case 0: case 'g': case 'G':
	handler.on_general();
	break;
  case 'e': case 'E':
	handler.on_exp();
	break;
  case 'f': case 'F':
	handler.on_fixed();
	break;
   case 'a': case 'A':
	handler.on_hex();
	break;
  default:
	handler.on_error();
	break;
  }
}

template <typename Char, typename Handler>
FMT_CONSTEXPR void handle_char_specs(
	const basic_format_specs<Char> &specs, Handler &&handler) {
  if (specs.type() && specs.type() != 'c') {
	handler.on_int();
	return;
  }
  if (specs.align() == ALIGN_NUMERIC || specs.flag(~0u) != 0)
	handler.on_error("invalid format specifier for char");
  handler.on_char();
}

template <typename Char, typename Handler>
FMT_CONSTEXPR void handle_cstring_type_spec(Char spec, Handler &&handler) {
  if (spec == 0 || spec == 's')
	handler.on_string();
  else if (spec == 'p')
	handler.on_pointer();
  else
	handler.on_error("invalid type specifier");
}

template <typename Char, typename ErrorHandler>
FMT_CONSTEXPR void check_string_type_spec(Char spec, ErrorHandler &&eh) {
  if (spec != 0 && spec != 's')
	eh.on_error("invalid type specifier");
}

template <typename Char, typename ErrorHandler>
FMT_CONSTEXPR void check_pointer_type_spec(Char spec, ErrorHandler &&eh) {
  if (spec != 0 && spec != 'p')
	eh.on_error("invalid type specifier");
}

template <typename ErrorHandler>
class int_type_checker : private ErrorHandler {
 public:
  FMT_CONSTEXPR explicit int_type_checker(ErrorHandler eh) : ErrorHandler(eh) {}

  FMT_CONSTEXPR void on_dec() {}
  FMT_CONSTEXPR void on_hex() {}
  FMT_CONSTEXPR void on_bin() {}
  FMT_CONSTEXPR void on_oct() {}
  FMT_CONSTEXPR void on_num() {}

  FMT_CONSTEXPR void on_error() {
	ErrorHandler::on_error("invalid type specifier");
  }
};

template <typename ErrorHandler>
class float_type_checker : private ErrorHandler {
 public:
  FMT_CONSTEXPR explicit float_type_checker(ErrorHandler eh)
	: ErrorHandler(eh) {}

  FMT_CONSTEXPR void on_general() {}
  FMT_CONSTEXPR void on_exp() {}
  FMT_CONSTEXPR void on_fixed() {}
  FMT_CONSTEXPR void on_hex() {}

  FMT_CONSTEXPR void on_error() {
	ErrorHandler::on_error("invalid type specifier");
  }
};

template <typename ErrorHandler, typename CharType>
class char_specs_checker : public ErrorHandler {
 private:
  CharType type_;

 public:
  FMT_CONSTEXPR char_specs_checker(CharType type, ErrorHandler eh)
	: ErrorHandler(eh), type_(type) {}

  FMT_CONSTEXPR void on_int() {
	handle_int_type_spec(type_, int_type_checker<ErrorHandler>(*this));
  }
  FMT_CONSTEXPR void on_char() {}
};

template <typename ErrorHandler>
class cstring_type_checker : public ErrorHandler {
 public:
  FMT_CONSTEXPR explicit cstring_type_checker(ErrorHandler eh)
	: ErrorHandler(eh) {}

  FMT_CONSTEXPR void on_string() {}
  FMT_CONSTEXPR void on_pointer() {}
};

template <typename Context>
void arg_map<Context>::init(const basic_format_args<Context> &args) {
  if (map_)
	return;
  map_ = new entry[args.max_size()];
  bool use_values = args.type(max_packed_args - 1) == internal::none_type;
  if (use_values) {
	for (unsigned i = 0;/*nothing*/; ++i) {
	  internal::type arg_type = args.type(i);
	  switch (arg_type) {
		case internal::none_type:
		  return;
		case internal::named_arg_type:
		  push_back(args.values_[i]);
		  break;
		default:
		  break; // Do nothing.
	  }
	}
	return;
  }
  for (unsigned i = 0; ; ++i) {
	switch (args.args_[i].type_) {
	  case internal::none_type:
		return;
	  case internal::named_arg_type:
		push_back(args.args_[i].value_);
		break;
	  default:
		break; // Do nothing.
	}
  }
}

template <typename Range>
class arg_formatter_base {
 public:
  typedef typename Range::value_type char_type;
  typedef decltype(internal::declval<Range>().begin()) iterator;
  typedef basic_format_specs<char_type> format_specs;

 private:
  typedef basic_writer<Range> writer_type;
  writer_type writer_;
  format_specs &specs_;

  FMT_DISALLOW_COPY_AND_ASSIGN(arg_formatter_base);

  struct char_writer {
	char_type value;
	template <typename It>
	void operator()(It &&it) const { *it++ = value; }
  };

  void write_char(char_type value) {
	writer_.write_padded(1, specs_, char_writer{value});
  }

  void write_pointer(const void *p) {
	format_specs specs = specs_;
	specs.flags_ = HASH_FLAG;
	specs.type_ = 'x';
	writer_.write_int(reinterpret_cast<uintptr_t>(p), specs);
  }

 protected:
  writer_type &writer() { return writer_; }
  format_specs &spec() { return specs_; }
  iterator out() { return writer_.out(); }

  void write(bool value) {
	writer_.write_str(string_view(value ? "true" : "false"), specs_);
  }

  void write(const char_type *value) {
	if (!value)
	  FMT_THROW(format_error("string pointer is null"));
	auto length = std::char_traits<char_type>::length(value);
	writer_.write_str(basic_string_view<char_type>(value, length), specs_);
  }

 public:
  arg_formatter_base(Range r, format_specs &s): writer_(r), specs_(s) {}

  iterator operator()(monostate) {
	FMT_ASSERT(false, "invalid argument type");
	return out();
  }

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, iterator>::type
	  operator()(T value) {
	// MSVC2013 fails to compile separate overloads for bool and char_type so
	// use std::is_same instead.
	if (std::is_same<T, bool>::value) {
	  if (specs_.type_)
		return (*this)(value ? 1 : 0);
	  write(value != 0);
	} else if (std::is_same<T, char_type>::value) {
	  internal::handle_char_specs(
		specs_, char_spec_handler(*this, static_cast<char_type>(value)));
	} else {
	  writer_.write_int(value, specs_);
	}
	return out();
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value, iterator>::type
	  operator()(T value) {
	writer_.write_double(value, specs_);
	return out();
  }

  struct char_spec_handler : internal::error_handler {
	arg_formatter_base &formatter;
	char_type value;

	char_spec_handler(arg_formatter_base& f, char_type val)
	  : formatter(f), value(val) {}

	void on_int() { formatter.writer_.write_int(value, formatter.specs_); }
	void on_char() { formatter.write_char(value); }
  };

  struct cstring_spec_handler : internal::error_handler {
	arg_formatter_base &formatter;
	const char_type *value;

	cstring_spec_handler(arg_formatter_base &f, const char_type *val)
	  : formatter(f), value(val) {}

	void on_string() { formatter.write(value); }
	void on_pointer() { formatter.write_pointer(value); }
  };

  iterator operator()(const char_type *value) {
	internal::handle_cstring_type_spec(
		  specs_.type_, cstring_spec_handler(*this, value));
	return out();
  }

  iterator operator()(basic_string_view<char_type> value) {
	internal::check_string_type_spec(specs_.type_, internal::error_handler());
	writer_.write_str(value, specs_);
	return out();
  }

  iterator operator()(const void *value) {
	check_pointer_type_spec(specs_.type_, internal::error_handler());
	write_pointer(value);
	return out();
  }
};

template <typename S>
struct is_format_string:
  std::integral_constant<bool, std::is_base_of<format_string, S>::value> {};

template <typename Char>
FMT_CONSTEXPR bool is_name_start(Char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || '_' == c;
}

// Parses the input as an unsigned integer. This function assumes that the
// first character is a digit and presence of a non-digit character at the end.
// it: an iterator pointing to the beginning of the input range.
template <typename Iterator, typename ErrorHandler>
FMT_CONSTEXPR unsigned parse_nonnegative_int(Iterator &it, ErrorHandler &&eh) {
  assert('0' <= *it && *it <= '9');
  unsigned value = 0;
  // Convert to unsigned to prevent a warning.
  unsigned max_int = (std::numeric_limits<int>::max)();
  unsigned big = max_int / 10;
  do {
	// Check for overflow.
	if (value > big) {
	  value = max_int + 1;
	  break;
	}
	value = value * 10 + unsigned(*it - '0');
	// Workaround for MSVC "setup_exception stack overflow" error:
	auto next = it;
	++next;
	it = next;
  } while ('0' <= *it && *it <= '9');
  if (value > max_int)
	eh.on_error("number is too big");
  return value;
}

template <typename Char, typename Context>
class custom_formatter: public function<bool> {
 private:
  Context &ctx_;

 public:
  explicit custom_formatter(Context &ctx): ctx_(ctx) {}

  bool operator()(typename basic_format_arg<Context>::handle h) const {
	h.format(ctx_);
	return true;
  }

  template <typename T>
  bool operator()(T) const { return false; }
};

template <typename T>
struct is_integer {
  enum {
	value = std::is_integral<T>::value && !std::is_same<T, bool>::value &&
			!std::is_same<T, char>::value && !std::is_same<T, wchar_t>::value
  };
};

template <typename ErrorHandler>
class width_checker: public function<unsigned long long> {
 public:
  explicit FMT_CONSTEXPR width_checker(ErrorHandler &eh) : handler_(eh) {}

  template <typename T>
  FMT_CONSTEXPR
  typename std::enable_if<
	  is_integer<T>::value, unsigned long long>::type operator()(T value) {
	if (is_negative(value))
	  handler_.on_error("negative width");
	return static_cast<unsigned long long>(value);
  }

  template <typename T>
  FMT_CONSTEXPR typename std::enable_if<
	  !is_integer<T>::value, unsigned long long>::type operator()(T) {
	handler_.on_error("width is not integer");
	return 0;
  }

 private:
  ErrorHandler &handler_;
};

template <typename ErrorHandler>
class precision_checker: public function<unsigned long long> {
 public:
  explicit FMT_CONSTEXPR precision_checker(ErrorHandler &eh) : handler_(eh) {}

  template <typename T>
  FMT_CONSTEXPR typename std::enable_if<
	  is_integer<T>::value, unsigned long long>::type operator()(T value) {
	if (is_negative(value))
	  handler_.on_error("negative precision");
	return static_cast<unsigned long long>(value);
  }

  template <typename T>
  FMT_CONSTEXPR typename std::enable_if<
	  !is_integer<T>::value, unsigned long long>::type operator()(T) {
	handler_.on_error("precision is not integer");
	return 0;
  }

 private:
  ErrorHandler &handler_;
};

// A format specifier handler that sets fields in basic_format_specs.
template <typename Char>
class specs_setter {
 public:
  explicit FMT_CONSTEXPR specs_setter(basic_format_specs<Char> &specs):
	specs_(specs) {}

  FMT_CONSTEXPR specs_setter(const specs_setter &other) : specs_(other.specs_) {}

  FMT_CONSTEXPR void on_align(alignment align) { specs_.align_ = align; }
  FMT_CONSTEXPR void on_fill(Char fill) { specs_.fill_ = fill; }
  FMT_CONSTEXPR void on_plus() { specs_.flags_ |= SIGN_FLAG | PLUS_FLAG; }
  FMT_CONSTEXPR void on_minus() { specs_.flags_ |= MINUS_FLAG; }
  FMT_CONSTEXPR void on_space() { specs_.flags_ |= SIGN_FLAG; }
  FMT_CONSTEXPR void on_hash() { specs_.flags_ |= HASH_FLAG; }

  FMT_CONSTEXPR void on_zero() {
	specs_.align_ = ALIGN_NUMERIC;
	specs_.fill_ = '0';
  }

  FMT_CONSTEXPR void on_width(unsigned width) { specs_.width_ = width; }
  FMT_CONSTEXPR void on_precision(unsigned precision) {
	specs_.precision_ = static_cast<int>(precision);
  }
  FMT_CONSTEXPR void end_precision() {}

  FMT_CONSTEXPR void on_type(Char type) { specs_.type_ = type; }

 protected:
  basic_format_specs<Char> &specs_;
};

// A format specifier handler that checks if specifiers are consistent with the
// argument type.
template <typename Handler>
class specs_checker : public Handler {
 public:
  FMT_CONSTEXPR specs_checker(const Handler& handler, internal::type arg_type)
	: Handler(handler), arg_type_(arg_type) {}

  FMT_CONSTEXPR specs_checker(const specs_checker &other)
	: Handler(other), arg_type_(other.arg_type_) {}

  FMT_CONSTEXPR void on_align(alignment align) {
	if (align == ALIGN_NUMERIC)
	  require_numeric_argument();
	Handler::on_align(align);
  }

  FMT_CONSTEXPR void on_plus() {
	check_sign();
	Handler::on_plus();
  }

  FMT_CONSTEXPR void on_minus() {
	check_sign();
	Handler::on_minus();
  }

  FMT_CONSTEXPR void on_space() {
	check_sign();
	Handler::on_space();
  }

  FMT_CONSTEXPR void on_hash() {
	require_numeric_argument();
	Handler::on_hash();
  }

  FMT_CONSTEXPR void on_zero() {
	require_numeric_argument();
	Handler::on_zero();
  }

  FMT_CONSTEXPR void end_precision() {
	if (is_integral(arg_type_) || arg_type_ == pointer_type)
	  this->on_error("precision not allowed for this argument type");
  }

 private:
  FMT_CONSTEXPR void require_numeric_argument() {
	if (!is_arithmetic(arg_type_))
	  this->on_error("format specifier requires numeric argument");
  }

  FMT_CONSTEXPR void check_sign() {
	require_numeric_argument();
	if (is_integral(arg_type_) && arg_type_ != int_type &&
		arg_type_ != long_long_type && arg_type_ != internal::char_type) {
	  this->on_error("format specifier requires signed argument");
	}
  }

  internal::type arg_type_;
};

template <template <typename> class Handler, typename T,
		  typename Context, typename ErrorHandler>
FMT_CONSTEXPR void set_dynamic_spec(
	T &value, basic_format_arg<Context> arg, ErrorHandler eh) {
  unsigned long long big_value = visit(Handler<ErrorHandler>(eh), arg);
  if (big_value > (std::numeric_limits<int>::max)())
	eh.on_error("number is too big");
  value = static_cast<T>(big_value);
}

struct auto_id {};

// The standard format specifier handler with checking.
template <typename Context>
class specs_handler: public specs_setter<typename Context::char_type> {
 public:
  typedef typename Context::char_type char_type;

  FMT_CONSTEXPR specs_handler(basic_format_specs<char_type> &specs, Context &ctx)
	: specs_setter<char_type>(specs), context_(ctx) {}

  template <typename Id>
  FMT_CONSTEXPR void on_dynamic_width(Id arg_id) {
	set_dynamic_spec<width_checker>(
		  this->specs_.width_, get_arg(arg_id), context_.error_handler());
  }

  template <typename Id>
  FMT_CONSTEXPR void on_dynamic_precision(Id arg_id) {
	set_dynamic_spec<precision_checker>(
		  this->specs_.precision_, get_arg(arg_id), context_.error_handler());
  }

  void on_error(const char *message) {
	context_.on_error(message);
  }

 private:
  FMT_CONSTEXPR basic_format_arg<Context> get_arg(auto_id) {
	return context_.next_arg();
  }

  template <typename Id>
  FMT_CONSTEXPR basic_format_arg<Context> get_arg(Id arg_id) {
	context_.parse_context().check_arg_id(arg_id);
	return context_.get_arg(arg_id);
  }

  Context &context_;
};

// An argument reference.
template <typename Char>
struct arg_ref {
  enum Kind { NONE, INDEX, NAME };

  FMT_CONSTEXPR arg_ref() : kind(NONE), index(0) {}
  FMT_CONSTEXPR explicit arg_ref(unsigned index) : kind(INDEX), index(index) {}
  explicit arg_ref(basic_string_view<Char> name) : kind(NAME), name(name) {}

  FMT_CONSTEXPR arg_ref &operator=(unsigned idx) {
	kind = INDEX;
	index = idx;
	return *this;
  }

  Kind kind;
  FMT_UNION {
	unsigned index;
	basic_string_view<Char> name;
  };
};

// Format specifiers with width and precision resolved at formatting rather
// than parsing time to allow re-using the same parsed specifiers with
// differents sets of arguments (precompilation of format strings).
template <typename Char>
struct dynamic_format_specs : basic_format_specs<Char> {
  arg_ref<Char> width_ref;
  arg_ref<Char> precision_ref;
};

// Format spec handler that saves references to arguments representing dynamic
// width and precision to be resolved at formatting time.
template <typename ParseContext>
class dynamic_specs_handler :
	public specs_setter<typename ParseContext::char_type> {
 public:
  typedef typename ParseContext::char_type char_type;

  FMT_CONSTEXPR dynamic_specs_handler(
	  dynamic_format_specs<char_type> &specs, ParseContext &ctx)
	: specs_setter<char_type>(specs), specs_(specs), context_(ctx) {}

  FMT_CONSTEXPR dynamic_specs_handler(const dynamic_specs_handler &other)
	: specs_setter<char_type>(other),
	  specs_(other.specs_), context_(other.context_) {}

  template <typename Id>
  FMT_CONSTEXPR void on_dynamic_width(Id arg_id) {
	specs_.width_ref = make_arg_ref(arg_id);
  }

  template <typename Id>
  FMT_CONSTEXPR void on_dynamic_precision(Id arg_id) {
	specs_.precision_ref = make_arg_ref(arg_id);
  }

  FMT_CONSTEXPR void on_error(const char *message) {
	context_.on_error(message);
  }

 private:
  typedef arg_ref<char_type> arg_ref_type;

  template <typename Id>
  FMT_CONSTEXPR arg_ref_type make_arg_ref(Id arg_id) {
	context_.check_arg_id(arg_id);
	return arg_ref_type(arg_id);
  }

  FMT_CONSTEXPR arg_ref_type make_arg_ref(auto_id) {
	return arg_ref_type(context_.next_arg_id());
  }

  dynamic_format_specs<char_type> &specs_;
  ParseContext &context_;
};

template <typename Iterator, typename IDHandler>
FMT_CONSTEXPR Iterator parse_arg_id(Iterator it, IDHandler &&handler) {
  typedef typename std::iterator_traits<Iterator>::value_type char_type;
  char_type c = *it;
  if (c == '}' || c == ':') {
	handler();
	return it;
  }
  if (c >= '0' && c <= '9') {
	unsigned index = parse_nonnegative_int(it, handler);
	if (*it != '}' && *it != ':') {
	  handler.on_error("invalid format string");
	  return it;
	}
	handler(index);
	return it;
  }
  if (!is_name_start(c)) {
	handler.on_error("invalid format string");
	return it;
  }
  auto start = it;
  do {
	c = *++it;
  } while (is_name_start(c) || ('0' <= c && c <= '9'));
  handler(basic_string_view<char_type>(pointer_from(start), to_unsigned(it - start)));
  return it;
}

// Adapts SpecHandler to IDHandler API for dynamic width.
template <typename SpecHandler, typename Char>
struct width_adapter {
  explicit FMT_CONSTEXPR width_adapter(SpecHandler &h) : handler(h) {}

  FMT_CONSTEXPR void operator()() { handler.on_dynamic_width(auto_id()); }
  FMT_CONSTEXPR void operator()(unsigned id) { handler.on_dynamic_width(id); }
  FMT_CONSTEXPR void operator()(basic_string_view<Char> id) {
	handler.on_dynamic_width(id);
  }

  FMT_CONSTEXPR void on_error(const char *message) {
	handler.on_error(message);
  }

  SpecHandler &handler;
};

// Adapts SpecHandler to IDHandler API for dynamic precision.
template <typename SpecHandler, typename Char>
struct precision_adapter {
  explicit FMT_CONSTEXPR precision_adapter(SpecHandler &h) : handler(h) {}

  FMT_CONSTEXPR void operator()() { handler.on_dynamic_precision(auto_id()); }
  FMT_CONSTEXPR void operator()(unsigned id) {
	handler.on_dynamic_precision(id);
  }
  FMT_CONSTEXPR void operator()(basic_string_view<Char> id) {
	handler.on_dynamic_precision(id);
  }

  FMT_CONSTEXPR void on_error(const char *message) { handler.on_error(message); }

  SpecHandler &handler;
};

// Parses standard format specifiers and sends notifications about parsed
// components to handler.
// it: an iterator pointing to the beginning of a null-terminated range of
//     characters, possibly emulated via null_terminating_iterator, representing
//     format specifiers.
template <typename Iterator, typename SpecHandler>
FMT_CONSTEXPR Iterator parse_format_specs(Iterator it, SpecHandler &&handler) {
  typedef typename std::iterator_traits<Iterator>::value_type char_type;
  char_type c = *it;
  if (c == '}' || !c)
	return it;

  // Parse fill and alignment.
  alignment align = ALIGN_DEFAULT;
  int i = 1;
  do {
	auto p = it + i;
	switch (*p) {
	  case '<':
		align = ALIGN_LEFT;
		break;
	  case '>':
		align = ALIGN_RIGHT;
		break;
	  case '=':
		align = ALIGN_NUMERIC;
		break;
	  case '^':
		align = ALIGN_CENTER;
		break;
	}
	if (align != ALIGN_DEFAULT) {
	  if (p != it) {
		if (c == '{') {
		  handler.on_error("invalid fill character '{'");
		  return it;
		}
		it += 2;
		handler.on_fill(c);
	  } else ++it;
	  handler.on_align(align);
	  break;
	}
  } while (--i >= 0);

  // Parse sign.
  switch (*it) {
	case '+':
	  handler.on_plus();
	  ++it;
	  break;
	case '-':
	  handler.on_minus();
	  ++it;
	  break;
	case ' ':
	  handler.on_space();
	  ++it;
	  break;
  }

  if (*it == '#') {
	handler.on_hash();
	++it;
  }

  // Parse zero flag.
  if (*it == '0') {
	handler.on_zero();
	++it;
  }

  // Parse width.
  if ('0' <= *it && *it <= '9') {
	handler.on_width(parse_nonnegative_int(it, handler));
  } else if (*it == '{') {
	it = parse_arg_id(it + 1, width_adapter<SpecHandler, char_type>(handler));
	if (*it++ != '}') {
	  handler.on_error("invalid format string");
	  return it;
	}
  }

  // Parse precision.
  if (*it == '.') {
	++it;
	if ('0' <= *it && *it <= '9') {
	  handler.on_precision(parse_nonnegative_int(it, handler));
	} else if (*it == '{') {
	  it = parse_arg_id(
			it + 1, precision_adapter<SpecHandler, char_type>(handler));
	  if (*it++ != '}') {
		handler.on_error("invalid format string");
		return it;
	  }
	} else {
	  handler.on_error("missing precision specifier");
	  return it;
	}
	handler.end_precision();
  }

  // Parse type.
  if (*it != '}' && *it)
	handler.on_type(*it++);
  return it;
}

template <typename Handler, typename Char>
struct id_adapter {
  FMT_CONSTEXPR explicit id_adapter(Handler &h): handler(h) {}

  FMT_CONSTEXPR void operator()() { handler.on_arg_id(); }
  FMT_CONSTEXPR void operator()(unsigned id) { handler.on_arg_id(id); }
  FMT_CONSTEXPR void operator()(basic_string_view<Char> id) {
	handler.on_arg_id(id);
  }

  FMT_CONSTEXPR void on_error(const char *message) {
	handler.on_error(message);
  }

  Handler &handler;
};

template <typename Iterator, typename Handler>
FMT_CONSTEXPR void parse_format_string(Iterator it, Handler &&handler) {
  typedef typename std::iterator_traits<Iterator>::value_type char_type;
  auto start = it;
  while (*it) {
	char_type ch = *it++;
	if (ch != '{' && ch != '}') continue;
	if (*it == ch) {
	  handler.on_text(start, it);
	  start = ++it;
	  continue;
	}
	if (ch == '}') {
	  handler.on_error("unmatched '}' in format string");
	  return;
	}
	handler.on_text(start, it - 1);

	it = parse_arg_id(it, id_adapter<Handler, char_type>(handler));
	if (*it == '}') {
	  handler.on_replacement_field(it);
	} else if (*it == ':') {
	  ++it;
	  it = handler.on_format_specs(it);
	  if (*it != '}') {
		handler.on_error("unknown format specifier");
		return;
	  }
	} else {
	  handler.on_error("missing '}' in format string");
	  return;
	}

	start = ++it;
  }
  handler.on_text(start, it);
}

template <typename T, typename ParseContext>
FMT_CONSTEXPR const typename ParseContext::char_type *
	parse_format_specs(ParseContext &ctx) {
  // GCC 7.2 requires initializer.
  formatter<T, typename ParseContext::char_type> f{};
  return f.parse(ctx);
}

template <typename Char, typename ErrorHandler, typename... Args>
class format_string_checker {
 public:
  explicit FMT_CONSTEXPR format_string_checker(
	  basic_string_view<Char> format_str, ErrorHandler eh)
	: arg_id_(-1), context_(format_str, eh),
	  parse_funcs_{&parse_format_specs<Args, parse_context_type>...} {}

  FMT_CONSTEXPR void on_text(const Char *, const Char *) {}

  FMT_CONSTEXPR void on_arg_id() {
	arg_id_ = context_.next_arg_id();
	check_arg_id();
  }
  FMT_CONSTEXPR void on_arg_id(unsigned id) {
	arg_id_ = id;
	context_.check_arg_id(id);
	check_arg_id();
  }
  FMT_CONSTEXPR void on_arg_id(basic_string_view<Char>) {}

  FMT_CONSTEXPR void on_replacement_field(const Char *) {}

  FMT_CONSTEXPR const Char *on_format_specs(const Char *s) {
	context_.advance_to(s);
	return to_unsigned(arg_id_) < NUM_ARGS ?
		  parse_funcs_[arg_id_](context_) : s;
  }

  FMT_CONSTEXPR void on_error(const char *message) {
	context_.on_error(message);
  }

 private:
  typedef basic_parse_context<Char, ErrorHandler> parse_context_type;
  enum { NUM_ARGS = sizeof...(Args) };

  FMT_CONSTEXPR void check_arg_id() {
	if (internal::to_unsigned(arg_id_) >= NUM_ARGS)
	  context_.on_error("argument index out of range");
  }

  // Format specifier parsing function.
  typedef const Char *(*parse_func)(parse_context_type &);

  int arg_id_;
  parse_context_type context_;
  parse_func parse_funcs_[NUM_ARGS > 0 ? NUM_ARGS : 1];
};

template <typename Char, typename ErrorHandler, typename... Args>
FMT_CONSTEXPR bool check_format_string(
	basic_string_view<Char> s, ErrorHandler eh = ErrorHandler()) {
  format_string_checker<Char, ErrorHandler, Args...> checker(s, eh);
  parse_format_string(s.begin(), checker);
  return true;
}

template <typename... Args, typename String>
void check_format_string(String format_str) {
  FMT_CONSTEXPR_DECL bool invalid_format =
	  internal::check_format_string<char, internal::error_handler, Args...>(
		string_view(format_str.data(), format_str.size()));
  (void)invalid_format;
}

// Specifies whether to format T using the standard formatter.
// It is not possible to use get_type in formatter specialization directly
// because of a bug in MSVC.
template <typename Context, typename T>
struct format_type :
  std::integral_constant<bool, get_type<Context, T>::value != custom_type> {};

// Specifies whether to format enums.
template <typename T, typename Enable = void>
struct format_enum : std::integral_constant<bool, std::is_enum<T>::value> {};

template <template <typename> class Handler, typename Spec, typename Context>
void handle_dynamic_spec(
	Spec &value, arg_ref<typename Context::char_type> ref, Context &ctx) {
  typedef typename Context::char_type char_type;
  switch (ref.kind) {
  case arg_ref<char_type>::NONE:
	break;
  case arg_ref<char_type>::INDEX:
	internal::set_dynamic_spec<Handler>(
		  value, ctx.get_arg(ref.index), ctx.error_handler());
	break;
  case arg_ref<char_type>::NAME:
	internal::set_dynamic_spec<Handler>(
		  value, ctx.get_arg(ref.name), ctx.error_handler());
	break;
  }
}
}  // namespace internal

/** The default argument formatter. */
template <typename Range>
class arg_formatter:
  public internal::function<
	typename internal::arg_formatter_base<Range>::iterator>,
  public internal::arg_formatter_base<Range> {
 private:
  typedef typename Range::value_type char_type;
  typedef internal::arg_formatter_base<Range> base;
  typedef basic_format_context<typename base::iterator, char_type> context_type;

  context_type &ctx_;

 public:
  typedef Range range;
  typedef typename base::iterator iterator;
  typedef typename base::format_specs format_specs;

  /**
	\rst
	Constructs an argument formatter object.
	*ctx* is a reference to the formatting context,
	*spec* contains format specifier information for standard argument types.
	\endrst
   */
  arg_formatter(context_type &ctx, format_specs &spec)
  : base(Range(ctx.out()), spec), ctx_(ctx) {}

  using base::operator();

  /** Formats an argument of a user-defined type. */
  iterator operator()(typename basic_format_arg<context_type>::handle handle) {
	handle.format(ctx_);
	return this->out();
  }
};

/**
 An error returned by an operating system or a language runtime,
 for example a file opening error.
*/
class system_error : public std::runtime_error {
 private:
  FMT_API void init(int err_code, string_view format_str, format_args args);

 protected:
  int error_code_;

  system_error() : std::runtime_error("") {}

 public:
  /**
   \rst
   Constructs a :class:`fmt::system_error` object with a description
   formatted with `fmt::format_system_error`. *message* and additional
   arguments passed into the constructor are formatted similarly to
   `fmt::format`.

   **Example**::

	 // This throws a system_error with the description
	 //   cannot open file 'madeup': No such file or directory
	 // or similar (system message may vary).
	 const char *filename = "madeup";
	 std::FILE *file = std::fopen(filename, "r");
	 if (!file)
	   throw fmt::system_error(errno, "cannot open file '{}'", filename);
   \endrst
  */
  template <typename... Args>
  system_error(int error_code, string_view message, const Args & ... args)
	: std::runtime_error("") {
	init(error_code, message, fmt::make_format_args(args...));
  }

  int error_code() const { return error_code_; }
};

/**
  \rst
  Formats an error returned by an operating system or a language runtime,
  for example a file opening error, and writes it to *out* in the following
  form:

  .. parsed-literal::
	 *<message>*: *<system-message>*

  where *<message>* is the passed message and *<system-message>* is
  the system message corresponding to the error code.
  *error_code* is a system error code as given by ``errno``.
  If *error_code* is not a valid error code such as -1, the system message
  may look like "Unknown error -1" and is platform-dependent.
  \endrst
 */
FMT_API void format_system_error(internal::buffer &out, int error_code,
								 fmt::string_view message) FMT_NOEXCEPT;

/**
  This template provides operations for formatting and writing data into a
  character range.
 */
template <typename Range>
class basic_writer {
 public:
  typedef typename Range::value_type char_type;
  typedef decltype(internal::declval<Range>().begin()) iterator;
  typedef basic_format_specs<char_type> format_specs;

 private:
  // Output iterator.
  iterator out_;

  std::unique_ptr<locale_provider> locale_;

  FMT_DISALLOW_COPY_AND_ASSIGN(basic_writer);

  iterator out() const { return out_; }

  // Attempts to reserve space for n extra characters in the output range.
  // Returns a pointer to the reserved range or a reference to out_.
  auto reserve(std::size_t n) -> decltype(internal::reserve(out_, n)) {
	return internal::reserve(out_, n);
  }

  // Writes a value in the format
  //   <left-padding><value><right-padding>
  // where <value> is written by f(it).
  template <typename F>
  void write_padded(std::size_t size, const align_spec &spec, F f);

  template <typename F>
  struct padded_int_writer {
	string_view prefix;
	char_type fill;
	std::size_t padding;
	F f;

	template <typename It>
	void operator()(It &&it) const {
	  if (prefix.size() != 0)
		it = std::copy_n(prefix.data(), prefix.size(), it);
	  it = std::fill_n(it, padding, fill);
	  f(it);
	}
  };

  // Writes an integer in the format
  //   <left-padding><prefix><numeric-padding><digits><right-padding>
  // where <digits> are written by f(it).
  template <typename Spec, typename F>
  void write_int(unsigned num_digits, string_view prefix,
				 const Spec &spec, F f) {
	std::size_t size = prefix.size() + num_digits;
	char_type fill = static_cast<char_type>(spec.fill());
	std::size_t padding = 0;
	if (spec.align() == ALIGN_NUMERIC) {
	  if (spec.width() > size) {
		padding = spec.width() - size;
		size = spec.width();
	  }
	} else if (spec.precision() > static_cast<int>(num_digits)) {
	  size = prefix.size() + static_cast<std::size_t>(spec.precision());
	  padding = static_cast<std::size_t>(spec.precision()) - num_digits;
	  fill = '0';
	}
	align_spec as = spec;
	if (spec.align() == ALIGN_DEFAULT)
	  as.align_ = ALIGN_RIGHT;
	write_padded(size, as, padded_int_writer<F>{prefix, fill, padding, f});
  }

  // Writes a decimal integer.
  template <typename Int>
  void write_decimal(Int value) {
	typedef typename internal::int_traits<Int>::main_type main_type;
	main_type abs_value = static_cast<main_type>(value);
	bool is_negative = internal::is_negative(value);
	if (is_negative)
	  abs_value = 0 - abs_value;
	unsigned num_digits = internal::count_digits(abs_value);
	auto &&it = reserve((is_negative ? 1 : 0) + num_digits);
	if (is_negative)
	  *it++ = '-';
	internal::format_decimal(it, abs_value, num_digits);
  }

  // The handle_int_type_spec handler that writes an integer.
  template <typename Int, typename Spec>
  struct int_writer {
	typedef typename internal::int_traits<Int>::main_type unsigned_type;

	basic_writer<Range> &writer;
	const Spec &spec;
	unsigned_type abs_value;
	char prefix[4];
	unsigned prefix_size;

	string_view get_prefix() const { return string_view(prefix, prefix_size); }

	// Counts the number of digits in abs_value. BITS = log2(radix).
	template <unsigned BITS>
	unsigned count_digits() const {
	  unsigned_type n = abs_value;
	  unsigned num_digits = 0;
	  do {
		++num_digits;
	  } while ((n >>= BITS) != 0);
	  return num_digits;
	}

	int_writer(basic_writer<Range> &w, Int value, const Spec &s)
	  : writer(w), spec(s), abs_value(static_cast<unsigned_type>(value)),
		prefix_size(0) {
	  if (internal::is_negative(value)) {
		prefix[0] = '-';
		++prefix_size;
		abs_value = 0 - abs_value;
	  } else if (spec.flag(SIGN_FLAG)) {
		prefix[0] = spec.flag(PLUS_FLAG) ? '+' : ' ';
		++prefix_size;
	  }
	}

	struct dec_writer {
	  unsigned_type abs_value;
	  unsigned num_digits;

	  template <typename It>
	  void operator()(It &&it) const {
		it = internal::format_decimal(it, abs_value, num_digits);
	  }
	};

	void on_dec() {
	  unsigned num_digits = internal::count_digits(abs_value);
	  writer.write_int(num_digits, get_prefix(), spec,
					   dec_writer{abs_value, num_digits});
	}

	struct hex_writer {
	  int_writer &self;
	  unsigned num_digits;

	  template <typename It>
	  void operator()(It &&it) const {
		it = internal::format_uint<4>(it, self.abs_value, num_digits,
									  self.spec.type() != 'x');
	  }
	};

	void on_hex() {
	  if (spec.flag(HASH_FLAG)) {
		prefix[prefix_size++] = '0';
		prefix[prefix_size++] = static_cast<char>(spec.type());
	  }
	  unsigned num_digits = count_digits<4>();
	  writer.write_int(num_digits, get_prefix(), spec,
					   hex_writer{*this, num_digits});
	}

	template <int BITS>
	struct bin_writer {
	  unsigned_type abs_value;
	  unsigned num_digits;

	  template <typename It>
	  void operator()(It &&it) const {
		it = internal::format_uint<BITS>(it, abs_value, num_digits);
	  }
	};

	void on_bin() {
	  if (spec.flag(HASH_FLAG)) {
		prefix[prefix_size++] = '0';
		prefix[prefix_size++] = static_cast<char>(spec.type());
	  }
	  unsigned num_digits = count_digits<1>();
	  writer.write_int(num_digits, get_prefix(), spec,
					   bin_writer<1>{abs_value, num_digits});
	}

	void on_oct() {
	  unsigned num_digits = count_digits<3>();
	  if (spec.flag(HASH_FLAG) &&
		  spec.precision() <= static_cast<int>(num_digits)) {
		// Octal prefix '0' is counted as a digit, so only add it if precision
		// is not greater than the number of digits.
		prefix[prefix_size++] = '0';
	  }
	  writer.write_int(num_digits, get_prefix(), spec,
					   bin_writer<3>{abs_value, num_digits});
	}

	enum { SEP_SIZE = 1 };

	struct num_writer {
	  unsigned_type abs_value;
	  unsigned size;
	  char_type sep;

	  template <typename It>
	  void operator()(It &&it) const {
		basic_string_view<char_type> s(&sep, SEP_SIZE);
		it = format_decimal(it, abs_value, size,
							internal::add_thousands_sep<char_type>(s));
	  }
	};

	void on_num() {
	  unsigned num_digits = internal::count_digits(abs_value);
	  char_type sep = internal::thousands_sep<char_type>(writer.locale_.get());
	  unsigned size = num_digits + SEP_SIZE * ((num_digits - 1) / 3);
	  writer.write_int(size, get_prefix(), spec,
					   num_writer{abs_value, size, sep});
	}

	void on_error() {
	  FMT_THROW(format_error("invalid type specifier"));
	}
  };

  // Writes a formatted integer.
  template <typename T, typename Spec>
  void write_int(T value, const Spec &spec) {
	internal::handle_int_type_spec(spec.type(),
								   int_writer<T, Spec>(*this, value, spec));
  }

  enum {INF_SIZE = 3}; // This is an enum to workaround a bug in MSVC.

  struct inf_or_nan_writer {
	char sign;
	const char *str;

	template <typename It>
	void operator()(It &&it) const {
	  if (sign)
		*it++ = sign;
	  it = std::copy_n(str, static_cast<std::size_t>(INF_SIZE), it);
	}
  };

  struct double_writer {
	size_t n;
	char sign;
	basic_memory_buffer<char_type> &buffer;

	template <typename It>
	void operator()(It &&it) {
	  if (sign) {
		*it++ = sign;
		--n;
	  }
	  it = std::copy_n(buffer.begin(), n, it);
	}
  };

  // Formats a floating-point number (double or long double).
  template <typename T>
  void write_double(T value, const format_specs &spec);
  template <typename T>
  void write_double_sprintf(T value, const format_specs &spec,
							internal::basic_buffer<char_type>& buffer);

  template <typename Char>
  struct str_writer {
	const Char *s;
	std::size_t size;

	template <typename It>
	void operator()(It &&it) const {
	  it = std::copy_n(s, size, it);
	}
  };

  // Writes a formatted string.
  template <typename Char>
  void write_str(const Char *s, std::size_t size, const align_spec &spec) {
	write_padded(size, spec, str_writer<Char>{s, size});
  }

  template <typename Char>
  void write_str(basic_string_view<Char> str, const format_specs &spec);

  // Appends floating-point length specifier to the format string.
  // The second argument is only used for overload resolution.
  void append_float_length(char_type *&format_ptr, long double) {
	*format_ptr++ = 'L';
  }

  template<typename T>
  void append_float_length(char_type *&, T) {}

  template <typename Char>
  friend class internal::arg_formatter_base;

 public:
  /** Constructs a ``basic_writer`` object. */
  explicit basic_writer(Range out): out_(out.begin()) {}

  void write(int value) { write_decimal(value); }
  void write(long value) { write_decimal(value); }
  void write(long long value) { write_decimal(value); }

  void write(unsigned value) { write_decimal(value); }
  void write(unsigned long value) { write_decimal(value); }
  void write(unsigned long long value) { write_decimal(value); }

  /**
	\rst
	Formats *value* and writes it to the buffer.
	\endrst
   */
  template <typename T, typename FormatSpec, typename... FormatSpecs>
  typename std::enable_if<std::is_integral<T>::value, void>::type
	  write(T value, FormatSpec spec, FormatSpecs... specs) {
	format_specs s(spec, specs...);
	s.align_ = ALIGN_RIGHT;
	write_int(value, s);
  }

  void write(double value) {
	write_double(value, format_specs());
  }

  /**
	\rst
	Formats *value* using the general format for floating-point numbers
	(``'g'``) and writes it to the buffer.
	\endrst
   */
  void write(long double value) {
	write_double(value, format_specs());
  }

  /** Writes a character to the buffer. */
  void write(char value) {
	*reserve(1) = value;
  }

  void write(wchar_t value) {
	internal::require_wchar<char_type>();
	*reserve(1) = value;
  }

  /**
	\rst
	Writes *value* to the buffer.
	\endrst
   */
  void write(string_view value) {
	auto &&it = reserve(value.size());
	it = std::copy(value.begin(), value.end(), it);
  }

  void write(wstring_view value) {
	internal::require_wchar<char_type>();
	auto &&it = reserve(value.size());
	it = std::uninitialized_copy(value.begin(), value.end(), it);
  }

  template <typename... FormatSpecs>
  void write(basic_string_view<char_type> str, FormatSpecs... specs) {
	write_str(str, format_specs(specs...));
  }

  template <typename T>
  typename std::enable_if<std::is_same<T, void>::value>::type write(const T* p) {
	format_specs specs;
	specs.flags_ = HASH_FLAG;
	specs.type_ = 'x';
	write_int(reinterpret_cast<uintptr_t>(p), specs);
  }
};

template <typename Range>
template <typename F>
void basic_writer<Range>::write_padded(
	std::size_t size, const align_spec &spec, F f) {
  unsigned width = spec.width();
  if (width <= size)
	return f(reserve(size));
  auto &&it = reserve(width);
  char_type fill = static_cast<char_type>(spec.fill());
  std::size_t padding = width - size;
  if (spec.align() == ALIGN_RIGHT) {
	it = std::fill_n(it, padding, fill);
	f(it);
  } else if (spec.align() == ALIGN_CENTER) {
	std::size_t left_padding = padding / 2;
	it = std::fill_n(it, left_padding, fill);
	f(it);
	it = std::fill_n(it, padding - left_padding, fill);
  } else {
	f(it);
	it = std::fill_n(it, padding, fill);
  }
}

template <typename Range>
template <typename Char>
void basic_writer<Range>::write_str(
	basic_string_view<Char> s, const format_specs &spec) {
  const Char *data = s.data();
  std::size_t size = s.size();
  std::size_t precision = static_cast<std::size_t>(spec.precision_);
  if (spec.precision_ >= 0 && precision < size)
	size = precision;
  write_str(data, size, spec);
}

template <typename Char>
struct float_spec_handler {
  Char type;
  bool upper;

  explicit float_spec_handler(Char t) : type(t), upper(false) {}

  void on_general() {
	if (type == 'G')
	  upper = true;
	else
	  type = 'g';
  }

  void on_exp() {
	if (type == 'E')
	  upper = true;
  }

  void on_fixed() {
	if (type == 'F') {
	  upper = true;
#if FMT_MSC_VER
	  // MSVC's printf doesn't support 'F'.
	  type = 'f';
#endif
	}
  }

  void on_hex() {
	if (type == 'A')
	  upper = true;
  }

  void on_error() {
	FMT_THROW(format_error("invalid type specifier"));
  }
};

template <typename Range>
template <typename T>
void basic_writer<Range>::write_double(T value, const format_specs &spec) {
  // Check type.
  float_spec_handler<char_type> handler(spec.type());
  internal::handle_float_type_spec(spec.type(), handler);

  char sign = 0;
  // Use isnegative instead of value < 0 because the latter is always
  // false for NaN.
  if (internal::fputil::isnegative(static_cast<double>(value))) {
	sign = '-';
	value = -value;
  } else if (spec.flag(SIGN_FLAG)) {
	sign = spec.flag(PLUS_FLAG) ? '+' : ' ';
  }

  struct write_inf_or_nan_t {
	basic_writer &writer;
	format_specs spec;
	char sign;
	void operator()(const char *str) const {
	  writer.write_padded(INF_SIZE + (sign ? 1 : 0), spec,
						  inf_or_nan_writer{sign, str});
	}
  } write_inf_or_nan = {*this, spec, sign};

  // Format NaN and ininity ourselves because sprintf's output is not consistent
  // across platforms.
  if (internal::fputil::isnotanumber(value))
	return write_inf_or_nan(handler.upper ? "NAN" : "nan");
  if (internal::fputil::isinfinity(value))
	return write_inf_or_nan(handler.upper ? "INF" : "inf");

  basic_memory_buffer<char_type> buffer;
  if (FMT_USE_GRISU && sizeof(T) <= sizeof(double) &&
	  std::numeric_limits<double>::is_iec559) {
	internal::fp fp_value(static_cast<double>(value));
	fp_value.normalize();
	// Find a cached power of 10 close to 1 / fp_value.
	int dec_exp = 0;
	const int min_exp = -60;
	auto dec_pow = internal::get_cached_power(
		min_exp - (fp_value.e + internal::fp::significand_size), dec_exp);
	internal::fp product = fp_value * dec_pow;
	// Generate output.
	internal::fp one(1ull << -product.e, product.e);
	uint64_t hi = product.f >> -one.e;
	uint64_t f = product.f & (one.f - 1);
	typedef back_insert_range<internal::basic_buffer<char_type>> range;
	basic_writer<range> w{range(buffer)};
	w.write(hi);
	size_t digits = buffer.size();
	w.write('.');
	const unsigned max_digits = 18;
	while (digits++ < max_digits) {
	  f *= 10;
	  w.write(static_cast<char>('0' + (f >> -one.e)));
	  f &= one.f - 1;
	}
	w.write('e');
	w.write(-dec_exp);
  } else {
	format_specs normalized_spec(spec);
	normalized_spec.type_ = handler.type;
	write_double_sprintf(value, normalized_spec, buffer);
  }
  size_t n = buffer.size();
  align_spec as = spec;
  if (spec.align() == ALIGN_NUMERIC) {
	if (sign) {
	  auto &&it = reserve(1);
	  *it++ = sign;
	  sign = 0;
	  if (as.width_)
		--as.width_;
	}
	as.align_ = ALIGN_RIGHT;
  } else {
	if (spec.align() == ALIGN_DEFAULT)
	  as.align_ = ALIGN_RIGHT;
	if (sign)
	  ++n;
  }
  write_padded(n, as, double_writer{n, sign, buffer});
}

template <typename Range>
template <typename T>
void basic_writer<Range>::write_double_sprintf(
	T value, const format_specs &spec,
	internal::basic_buffer<char_type>& buffer) {
  // Buffer capacity must be non-zero, otherwise MSVC's vsnprintf_s will fail.
  FMT_ASSERT(buffer.capacity() != 0, "empty buffer");

  // Build format string.
  enum { MAX_FORMAT_SIZE = 10}; // longest format: %#-*.*Lg
  char_type format[MAX_FORMAT_SIZE];
  char_type *format_ptr = format;
  *format_ptr++ = '%';
  if (spec.flag(HASH_FLAG))
	*format_ptr++ = '#';
  if (spec.precision() >= 0) {
	*format_ptr++ = '.';
	*format_ptr++ = '*';
  }

  append_float_length(format_ptr, value);
  *format_ptr++ = spec.type();
  *format_ptr = '\0';

  // Format using snprintf.
  char_type *start = FMT_NULL;
  for (;;) {
	std::size_t buffer_size = buffer.capacity();
	start = &buffer[0];
	int result = internal::char_traits<char_type>::format_float(
		start, buffer_size, format, spec.precision(), value);
	if (result >= 0) {
	  unsigned n = internal::to_unsigned(result);
	  if (n < buffer.capacity()) {
		buffer.resize(n);
		break;  // The buffer is large enough - continue with formatting.
	  }
	  buffer.reserve(n + 1);
	} else {
	  // If result is negative we ask to increase the capacity by at least 1,
	  // but as std::vector, the buffer grows exponentially.
	  buffer.reserve(buffer.capacity() + 1);
	}
  }
}

// Reports a system error without throwing an exception.
// Can be used to report errors from destructors.
FMT_API void report_system_error(int error_code,
								 string_view message) FMT_NOEXCEPT;

#if FMT_USE_WINDOWS_H

/** A Windows error. */
class windows_error : public system_error {
 private:
  FMT_API void init(int error_code, string_view format_str, format_args args);

 public:
  /**
   \rst
   Constructs a :class:`fmt::windows_error` object with the description
   of the form

   .. parsed-literal::
	 *<message>*: *<system-message>*

   where *<message>* is the formatted message and *<system-message>* is the
   system message corresponding to the error code.
   *error_code* is a Windows error code as given by ``GetLastError``.
   If *error_code* is not a valid error code such as -1, the system message
   will look like "error -1".

   **Example**::

	 // This throws a windows_error with the description
	 //   cannot open file 'madeup': The system cannot find the file specified.
	 // or similar (system message may vary).
	 const char *filename = "madeup";
	 LPOFSTRUCT of = LPOFSTRUCT();
	 HFILE file = OpenFile(filename, &of, OF_READ);
	 if (file == HFILE_ERROR) {
	   throw fmt::windows_error(GetLastError(),
								"cannot open file '{}'", filename);
	 }
   \endrst
  */
  template <typename... Args>
  windows_error(int error_code, string_view message, const Args & ... args) {
	init(error_code, message, fmt::make_format_args(args...));
  }
};

// Reports a Windows error without throwing an exception.
// Can be used to report errors from destructors.
FMT_API void report_windows_error(int error_code,
								  string_view message) FMT_NOEXCEPT;

#endif

/** Fast integer formatter. */
class format_int {
 private:
  // Buffer should be large enough to hold all digits (digits10 + 1),
  // a sign and a null character.
  enum {BUFFER_SIZE = std::numeric_limits<unsigned long long>::digits10 + 3};
  mutable char buffer_[BUFFER_SIZE];
  char *str_;

  // Formats value in reverse and returns a pointer to the beginning.
  char *format_decimal(unsigned long long value) {
	char *ptr = buffer_ + BUFFER_SIZE - 1;
	while (value >= 100) {
	  // Integer division is slow so do it for a group of two digits instead
	  // of for every digit. The idea comes from the talk by Alexandrescu
	  // "Three Optimization Tips for C++". See speed-test for a comparison.
	  unsigned index = static_cast<unsigned>((value % 100) * 2);
	  value /= 100;
	  *--ptr = internal::data::DIGITS[index + 1];
	  *--ptr = internal::data::DIGITS[index];
	}
	if (value < 10) {
	  *--ptr = static_cast<char>('0' + value);
	  return ptr;
	}
	unsigned index = static_cast<unsigned>(value * 2);
	*--ptr = internal::data::DIGITS[index + 1];
	*--ptr = internal::data::DIGITS[index];
	return ptr;
  }

  void format_signed(long long value) {
	unsigned long long abs_value = static_cast<unsigned long long>(value);
	bool negative = value < 0;
	if (negative)
	  abs_value = 0 - abs_value;
	str_ = format_decimal(abs_value);
	if (negative)
	  *--str_ = '-';
  }

 public:
  explicit format_int(int value) { format_signed(value); }
  explicit format_int(long value) { format_signed(value); }
  explicit format_int(long long value) { format_signed(value); }
  explicit format_int(unsigned value) : str_(format_decimal(value)) {}
  explicit format_int(unsigned long value) : str_(format_decimal(value)) {}
  explicit format_int(unsigned long long value) : str_(format_decimal(value)) {}

  /** Returns the number of characters written to the output buffer. */
  std::size_t size() const {
	return internal::to_unsigned(buffer_ - str_ + BUFFER_SIZE - 1);
  }

  /**
	Returns a pointer to the output buffer content. No terminating null
	character is appended.
   */
  const char *data() const { return str_; }

  /**
	Returns a pointer to the output buffer content with terminating null
	character appended.
   */
  const char *c_str() const {
	buffer_[BUFFER_SIZE - 1] = '\0';
	return str_;
  }

  /**
	\rst
	Returns the content of the output buffer as an ``std::string``.
	\endrst
   */
  std::string str() const { return std::string(str_, size()); }
};

// Formats a decimal integer value writing into buffer and returns
// a pointer to the end of the formatted string. This function doesn't
// write a terminating null character.
template <typename T>
inline void format_decimal(char *&buffer, T value) {
  typedef typename internal::int_traits<T>::main_type main_type;
  main_type abs_value = static_cast<main_type>(value);
  if (internal::is_negative(value)) {
	*buffer++ = '-';
	abs_value = 0 - abs_value;
  }
  if (abs_value < 100) {
	if (abs_value < 10) {
	  *buffer++ = static_cast<char>('0' + abs_value);
	  return;
	}
	unsigned index = static_cast<unsigned>(abs_value * 2);
	*buffer++ = internal::data::DIGITS[index];
	*buffer++ = internal::data::DIGITS[index + 1];
	return;
  }
  unsigned num_digits = internal::count_digits(abs_value);
  internal::format_decimal(buffer, abs_value, num_digits);
  buffer += num_digits;
}

// Formatter of objects of type T.
template <typename T, typename Char>
struct formatter<
	T, Char,
	typename std::enable_if<internal::format_type<
		typename buffer_context<Char>::type, T>::value>::type> {

  // Parses format specifiers stopping either at the end of the range or at the
  // terminating '}'.
  template <typename ParseContext>
  FMT_CONSTEXPR typename ParseContext::iterator parse(ParseContext &ctx) {
	auto it = internal::null_terminating_iterator<Char>(ctx);
	typedef internal::dynamic_specs_handler<ParseContext> handler_type;
	auto type = internal::get_type<
	  typename buffer_context<Char>::type, T>::value;
	internal::specs_checker<handler_type>
		handler(handler_type(specs_, ctx), type);
	it = parse_format_specs(it, handler);
	auto type_spec = specs_.type();
	auto eh = ctx.error_handler();
	switch (type) {
	case internal::none_type:
	case internal::named_arg_type:
	  FMT_ASSERT(false, "invalid argument type");
	  break;
	case internal::int_type:
	case internal::uint_type:
	case internal::long_long_type:
	case internal::ulong_long_type:
	case internal::bool_type:
	  handle_int_type_spec(
			type_spec, internal::int_type_checker<decltype(eh)>(eh));
	  break;
	case internal::char_type:
	  handle_char_specs(
		  specs_,
		  internal::char_specs_checker<decltype(eh), decltype(type_spec)>(
			  type_spec, eh));
	  break;
	case internal::double_type:
	case internal::long_double_type:
	  handle_float_type_spec(
			type_spec, internal::float_type_checker<decltype(eh)>(eh));
	  break;
	case internal::cstring_type:
	  internal::handle_cstring_type_spec(
			type_spec, internal::cstring_type_checker<decltype(eh)>(eh));
	  break;
	case internal::string_type:
	  internal::check_string_type_spec(type_spec, eh);
	  break;
	case internal::pointer_type:
	  internal::check_pointer_type_spec(type_spec, eh);
	  break;
	case internal::custom_type:
	  // Custom format specifiers should be checked in parse functions of
	  // formatter specializations.
	  break;
	}
	return pointer_from(it);
  }

  template <typename FormatContext>
  auto format(const T &val, FormatContext &ctx) -> decltype(ctx.out()) {
	internal::handle_dynamic_spec<internal::width_checker>(
	  specs_.width_, specs_.width_ref, ctx);
	internal::handle_dynamic_spec<internal::precision_checker>(
	  specs_.precision_, specs_.precision_ref, ctx);
	typedef output_range<typename FormatContext::iterator,
						 typename FormatContext::char_type> range_type;
	return visit(arg_formatter<range_type>(ctx, specs_),
				 internal::make_arg<FormatContext>(val));
  }

 private:
  internal::dynamic_format_specs<Char> specs_;
};

template <typename T, typename Char>
struct formatter<T, Char,
	typename std::enable_if<internal::format_enum<T>::value>::type>
	: public formatter<int, Char> {
  template <typename ParseContext>
  auto parse(ParseContext &ctx) -> decltype(ctx.begin()) {
	return ctx.begin();
  }
};

// A formatter for types known only at run time such as variant alternatives.
//
// Usage:
//   typedef std::variant<int, std::string> variant;
//   template <>
//   struct formatter<variant>: dynamic_formatter<> {
//     void format(buffer &buf, const variant &v, context &ctx) {
//       visit([&](const auto &val) { format(buf, val, ctx); }, v);
//     }
//   };
template <typename Char = char>
class dynamic_formatter {
 private:
  struct null_handler: internal::error_handler {
	void on_align(alignment) {}
	void on_plus() {}
	void on_minus() {}
	void on_space() {}
	void on_hash() {}
  };

 public:
  template <typename ParseContext>
  auto parse(ParseContext &ctx) -> decltype(ctx.begin()) {
	auto it = internal::null_terminating_iterator<Char>(ctx);
	// Checks are deferred to formatting time when the argument type is known.
	internal::dynamic_specs_handler<ParseContext> handler(specs_, ctx);
	it = parse_format_specs(it, handler);
	return pointer_from(it);
  }

  template <typename T, typename FormatContext>
  auto format(const T &val, FormatContext &ctx) -> decltype(ctx.out()) {
	handle_specs(ctx);
	internal::specs_checker<null_handler>
		checker(null_handler(), internal::get_type<FormatContext, T>::value);
	checker.on_align(specs_.align());
	if (specs_.flags_ == 0) {
	  // Do nothing.
	} else if (specs_.flag(SIGN_FLAG)) {
	  if (specs_.flag(PLUS_FLAG))
		checker.on_plus();
	  else
		checker.on_space();
	} else if (specs_.flag(MINUS_FLAG)) {
	  checker.on_minus();
	} else if (specs_.flag(HASH_FLAG)) {
	  checker.on_hash();
	}
	if (specs_.precision_ != -1)
	  checker.end_precision();
	typedef output_range<typename FormatContext::iterator,
						 typename FormatContext::char_type> range;
	visit(arg_formatter<range>(ctx, specs_),
		  internal::make_arg<FormatContext>(val));
	return ctx.out();
  }

 private:
  template <typename Context>
  void handle_specs(Context &ctx) {
	internal::handle_dynamic_spec<internal::width_checker>(
	  specs_.width_, specs_.width_ref, ctx);
	internal::handle_dynamic_spec<internal::precision_checker>(
	  specs_.precision_, specs_.precision_ref, ctx);
  }

  internal::dynamic_format_specs<Char> specs_;
};

template <typename Range, typename Char>
typename basic_format_context<Range, Char>::format_arg
  basic_format_context<Range, Char>::get_arg(basic_string_view<char_type> name) {
  map_.init(this->args());
  format_arg arg = map_.find(name);
  if (arg.type() == internal::none_type)
	this->on_error("argument not found");
  return arg;
}

template <typename ArgFormatter, typename Char, typename Context>
struct format_handler : internal::error_handler {
  typedef internal::null_terminating_iterator<Char> iterator;
  typedef typename ArgFormatter::range range;

  format_handler(range r, basic_string_view<Char> str,
				 basic_format_args<Context> format_args)
	: context(r.begin(), str, format_args) {}

  void on_text(iterator begin, iterator end) {
	auto size = internal::to_unsigned(end - begin);
	auto out = context.out();
	auto &&it = internal::reserve(out, size);
	it = std::copy_n(begin, size, it);
	context.advance_to(out);
  }

  void on_arg_id() { arg = context.next_arg(); }
  void on_arg_id(unsigned id) {
	context.parse_context().check_arg_id(id);
	arg = context.get_arg(id);
  }
  void on_arg_id(basic_string_view<Char> id) {
	arg = context.get_arg(id);
  }

  void on_replacement_field(iterator it) {
	context.parse_context().advance_to(pointer_from(it));
	if (visit(internal::custom_formatter<Char, Context>(context), arg))
	  return;
	basic_format_specs<Char> specs;
	context.advance_to(visit(ArgFormatter(context, specs), arg));
  }

  iterator on_format_specs(iterator it) {
	auto& parse_ctx = context.parse_context();
	parse_ctx.advance_to(pointer_from(it));
	if (visit(internal::custom_formatter<Char, Context>(context), arg))
	  return iterator(parse_ctx);
	basic_format_specs<Char> specs;
	using internal::specs_handler;
	internal::specs_checker<specs_handler<Context>>
		handler(specs_handler<Context>(specs, context), arg.type());
	it = parse_format_specs(it, handler);
	if (*it != '}')
	  on_error("missing '}' in format string");
	parse_ctx.advance_to(pointer_from(it));
	context.advance_to(visit(ArgFormatter(context, specs), arg));
	return it;
  }

  Context context;
  basic_format_arg<Context> arg;
};

/** Formats arguments and writes the output to the range. */
template <typename ArgFormatter, typename Char, typename Context>
typename Context::iterator vformat_to(typename ArgFormatter::range out,
									  basic_string_view<Char> format_str,
									  basic_format_args<Context> args) {
  typedef internal::null_terminating_iterator<Char> iterator;
  format_handler<ArgFormatter, Char, Context> h(out, format_str, args);
  parse_format_string(iterator(format_str.begin(), format_str.end()), h);
  return h.context.out();
}

// Casts ``p`` to ``const void*`` for pointer formatting.
// Example:
//   auto s = format("{}", ptr(p));
template <typename T>
inline const void *ptr(const T *p) { return p; }

template <typename It, typename Char>
struct arg_join {
  It begin;
  It end;
  basic_string_view<Char> sep;

  arg_join(It begin, It end, basic_string_view<Char> sep)
	: begin(begin), end(end), sep(sep) {}
};

template <typename It, typename Char>
struct formatter<arg_join<It, Char>, Char>:
	formatter<typename std::iterator_traits<It>::value_type, Char> {
  template <typename FormatContext>
  auto format(const arg_join<It, Char> &value, FormatContext &ctx)
	  -> decltype(ctx.out()) {
	typedef formatter<typename std::iterator_traits<It>::value_type, Char> base;
	auto it = value.begin;
	auto out = ctx.out();
	if (it != value.end) {
	  out = base::format(*it++, ctx);
	  while (it != value.end) {
		out = std::copy(value.sep.begin(), value.sep.end(), out);
		ctx.advance_to(out);
		out = base::format(*it++, ctx);
	  }
	}
	return out;
  }
};

template <typename It>
arg_join<It, char> join(It begin, It end, string_view sep) {
  return arg_join<It, char>(begin, end, sep);
}

template <typename It>
arg_join<It, wchar_t> join(It begin, It end, wstring_view sep) {
  return arg_join<It, wchar_t>(begin, end, sep);
}

// The following causes ICE in gcc 4.4.
#if FMT_USE_TRAILING_RETURN && (!FMT_GCC_VERSION || FMT_GCC_VERSION >= 405)
template <typename Range>
auto join(const Range &range, string_view sep)
	-> arg_join<decltype(internal::begin(range)), char> {
  return join(internal::begin(range), internal::end(range), sep);
}

template <typename Range>
auto join(const Range &range, wstring_view sep)
	-> arg_join<decltype(internal::begin(range)), wchar_t> {
  return join(internal::begin(range), internal::end(range), sep);
}
#endif

template <typename T = int>
inline T to_number(const std::string& strIn)
{
	return std::stoi(strIn);
}

template <>
inline int to_number(const std::string& strIn)
{
	return std::stoi(strIn);
}

template <>
inline unsigned int to_number(const std::string& strIn)
{
	return std::stoul(strIn);
}

template <>
inline long to_number(const std::string& strIn)
{
	return std::stol(strIn);
}

template <>
inline unsigned long to_number(const std::string& strIn)
{
	return std::stoul(strIn);
}

template <>
inline long long to_number(const std::string& strIn)
{
	return std::stoll(strIn);
}

template <>
inline unsigned long long to_number(const std::string& strIn)
{
	return std::stoull(strIn);
}

template <>
inline float to_number(const std::string& strIn)
{
	return std::stof(strIn);
}

template <>
inline double to_number(const std::string& strIn)
{
	return std::stod(strIn);
}

template <>
inline long double to_number(const std::string& strIn)
{
	return std::stold(strIn);
}

/**
  \rst
  Converts *value* to ``std::string`` using the default format for type *T*.

  **Example**::

	#include <dmformat.h>

	std::string answer = fmt::to_string(42);
  \endrst
 */
template <typename T>
std::string to_string(const T &value) {
  std::string str;
  internal::container_buffer<std::string> buf(str);
  writer(buf).write(value);
  return str;
}

/**
  Converts *value* to ``std::wstring`` using the default format for type *T*.
 */
template <typename T>
std::wstring to_wstring(const T &value) {
  std::wstring str;
  internal::container_buffer<std::wstring> buf(str);
  wwriter(buf).write(value);
  return str;
}

template <typename Char, std::size_t SIZE>
std::basic_string<Char> to_string(const basic_memory_buffer<Char, SIZE> &buf) {
  return std::basic_string<Char>(buf.data(), buf.size());
}

inline format_context::iterator vformat_to(
	internal::buffer &buf, string_view format_str, format_args args) {
  typedef back_insert_range<internal::buffer> range;
  return vformat_to<arg_formatter<range>>(buf, format_str, args);
}

inline wformat_context::iterator vformat_to(
	internal::wbuffer &buf, wstring_view format_str, wformat_args args) {
  typedef back_insert_range<internal::wbuffer> range;
  return vformat_to<arg_formatter<range>>(buf, format_str, args);
}

template <typename... Args, std::size_t SIZE = inline_buffer_size>
inline format_context::iterator format_to(
	basic_memory_buffer<char, SIZE> &buf, string_view format_str,
	const Args & ... args) {
  return vformat_to(buf, format_str, fmt::make_format_args(args...));
}

template <typename... Args, std::size_t SIZE = inline_buffer_size>
inline wformat_context::iterator format_to(
	basic_memory_buffer<wchar_t, SIZE> &buf, wstring_view format_str,
	const Args & ... args) {
  return vformat_to(buf, format_str, fmt::make_format_args<wformat_context>(args...));
}

template <typename OutputIt, typename Char = char>
//using format_context_t = basic_format_context<OutputIt, Char>;
struct format_context_t { typedef basic_format_context<OutputIt, Char> type; };

template <typename OutputIt, typename Char = char>
//using format_args_t = basic_format_args<format_context_t<OutputIt, Char>>;
struct format_args_t {
  typedef basic_format_args<
	typename format_context_t<OutputIt, Char>::type> type;
};

template <typename OutputIt, typename... Args>
inline OutputIt vformat_to(OutputIt out, string_view format_str,
						   typename format_args_t<OutputIt>::type args) {
  typedef output_range<OutputIt, char> range;
  return vformat_to<arg_formatter<range>>(range(out), format_str, args);
}
template <typename OutputIt, typename... Args>
inline OutputIt vformat_to(
	OutputIt out, wstring_view format_str,
	typename format_args_t<OutputIt, wchar_t>::type args) {
  typedef output_range<OutputIt, wchar_t> range;
  return vformat_to<arg_formatter<range>>(range(out), format_str, args);
}

/**
 \rst
 Formats arguments, writes the result to the output iterator ``out`` and returns
 the iterator past the end of the output range.

 **Example**::

   std::vector<char> out;
   fmt::format_to(std::back_inserter(out), "{}", 42);
 \endrst
 */
template <typename OutputIt, typename... Args>
inline OutputIt format_to(OutputIt out, string_view format_str,
						  const Args & ... args) {
  return vformat_to(out, format_str,
	  fmt::make_format_args<typename format_context_t<OutputIt>::type>(args...));
}

template <typename Container, typename... Args>
inline typename std::enable_if<
  is_contiguous<Container>::value, std::back_insert_iterator<Container>>::type
	format_to(std::back_insert_iterator<Container> out,
			  string_view format_str, const Args & ... args) {
  return vformat_to(out, format_str, fmt::make_format_args<format_context>(args...));
}

template <typename Container, typename... Args>
inline typename std::enable_if<
  is_contiguous<Container>::value, std::back_insert_iterator<Container>>::type
	format_to(std::back_insert_iterator<Container> out,
			  wstring_view format_str, const Args & ... args) {
  return vformat_to(out, format_str, fmt::make_format_args<wformat_context>(args...));
}

template <typename OutputIt>
struct format_to_n_result {
  /** Iterator past the end of the output range. */
  OutputIt out;
  /** Total (not truncated) output size. */
  std::size_t size;
};

template <typename OutputIt>
using format_to_n_context = typename fmt::format_context_t<
  fmt::internal::truncating_iterator<OutputIt>>::type;

template <typename OutputIt>
using format_to_n_args = fmt::basic_format_args<format_to_n_context<OutputIt>>;

template <typename OutputIt, typename ...Args>
inline format_arg_store<format_to_n_context<OutputIt>, Args...>
	make_format_to_n_args(const Args & ... args) {
  return format_arg_store<format_to_n_context<OutputIt>, Args...>(args...);
}

template <typename OutputIt, typename... Args>
inline format_to_n_result<OutputIt> vformat_to_n(
	OutputIt out, std::size_t n, string_view format_str,
	format_to_n_args<OutputIt> args) {
  typedef internal::truncating_iterator<OutputIt> It;
  auto it = vformat_to(It(out, n), format_str, args);
  return {it.base(), it.count()};
}

/**
 \rst
 Formats arguments, writes up to ``n`` characters of the result to the output
 iterator ``out`` and returns the total output size and the iterator past the end
 of the output range.
 \endrst
 */
template <typename OutputIt, typename... Args>
inline format_to_n_result<OutputIt> format_to_n(
	OutputIt out, std::size_t n, string_view format_str, const Args &... args) {
  return vformat_to_n<OutputIt>(
	out, n, format_str, make_format_to_n_args<OutputIt>(args...));
}
template <typename OutputIt, typename... Args>
inline format_to_n_result<OutputIt> format_to_n(
	OutputIt out, std::size_t n, wstring_view format_str, const Args &... args) {
  typedef internal::truncating_iterator<OutputIt> It;
  auto it = vformat_to(It(out, n), format_str,
	  fmt::make_format_args<typename format_context_t<It, wchar_t>::type>(args...));
  return {it.base(), it.count()};
}

inline std::string vformat(string_view format_str, format_args args) {
  memory_buffer buffer;
  vformat_to(buffer, format_str, args);
  return fmt::to_string(buffer);
}

inline std::wstring vformat(wstring_view format_str, wformat_args args) {
  wmemory_buffer buffer;
  vformat_to(buffer, format_str, args);
  return to_string(buffer);
}

template <typename String, typename... Args>
inline typename std::enable_if<
  internal::is_format_string<String>::value, std::string>::type
	format(String format_str, const Args & ... args) {
  internal::check_format_string<Args...>(format_str);
  return vformat(format_str.data(), fmt::make_format_args(args...));
}

template <typename String, typename... Args>
inline typename std::enable_if<internal::is_format_string<String>::value>::type
	print(String format_str, const Args & ... args) {
  internal::check_format_string<Args...>(format_str);
  return vprint(format_str.data(), fmt::make_format_args(args...));
}

/**
  Returns the number of characters in the output of
  ``format(format_str, args...)``.
 */
template <typename... Args>
inline std::size_t formatted_size(string_view format_str,
								  const Args & ... args) {
  auto it = format_to(internal::counting_iterator<char>(), format_str, args...);
  return it.count();
}

// Experimental color support.
#ifdef FMT_EXTENDED_COLORS
enum class color : uint32_t {
  alice_blue              = 0xF0F8FF, // rgb(240,248,255)
  antique_white           = 0xFAEBD7, // rgb(250,235,215)
  aqua                    = 0x00FFFF, // rgb(0,255,255)
  aquamarine              = 0x7FFFD4, // rgb(127,255,212)
  azure                   = 0xF0FFFF, // rgb(240,255,255)
  beige                   = 0xF5F5DC, // rgb(245,245,220)
  bisque                  = 0xFFE4C4, // rgb(255,228,196)
  black                   = 0x000000, // rgb(0,0,0)
  blanched_almond         = 0xFFEBCD, // rgb(255,235,205)
  blue                    = 0x0000FF, // rgb(0,0,255)
  blue_violet             = 0x8A2BE2, // rgb(138,43,226)
  brown                   = 0xA52A2A, // rgb(165,42,42)
  burly_wood              = 0xDEB887, // rgb(222,184,135)
  cadet_blue              = 0x5F9EA0, // rgb(95,158,160)
  chartreuse              = 0x7FFF00, // rgb(127,255,0)
  chocolate               = 0xD2691E, // rgb(210,105,30)
  coral                   = 0xFF7F50, // rgb(255,127,80)
  cornflower_blue         = 0x6495ED, // rgb(100,149,237)
  cornsilk                = 0xFFF8DC, // rgb(255,248,220)
  crimson                 = 0xDC143C, // rgb(220,20,60)
  cyan                    = 0x00FFFF, // rgb(0,255,255)
  dark_blue               = 0x00008B, // rgb(0,0,139)
  dark_cyan               = 0x008B8B, // rgb(0,139,139)
  dark_golden_rod         = 0xB8860B, // rgb(184,134,11)
  dark_gray               = 0xA9A9A9, // rgb(169,169,169)
  dark_green              = 0x006400, // rgb(0,100,0)
  dark_khaki              = 0xBDB76B, // rgb(189,183,107)
  dark_magenta            = 0x8B008B, // rgb(139,0,139)
  dark_olive_green        = 0x556B2F, // rgb(85,107,47)
  dark_orange             = 0xFF8C00, // rgb(255,140,0)
  dark_orchid             = 0x9932CC, // rgb(153,50,204)
  dark_red                = 0x8B0000, // rgb(139,0,0)
  dark_salmon             = 0xE9967A, // rgb(233,150,122)
  dark_sea_green          = 0x8FBC8F, // rgb(143,188,143)
  dark_slate_blue         = 0x483D8B, // rgb(72,61,139)
  dark_slate_gray         = 0x2F4F4F, // rgb(47,79,79)
  dark_turquoise          = 0x00CED1, // rgb(0,206,209)
  dark_violet             = 0x9400D3, // rgb(148,0,211)
  deep_pink               = 0xFF1493, // rgb(255,20,147)
  deep_sky_blue           = 0x00BFFF, // rgb(0,191,255)
  dim_gray                = 0x696969, // rgb(105,105,105)
  dodger_blue             = 0x1E90FF, // rgb(30,144,255)
  fire_brick              = 0xB22222, // rgb(178,34,34)
  floral_white            = 0xFFFAF0, // rgb(255,250,240)
  forest_green            = 0x228B22, // rgb(34,139,34)
  fuchsia                 = 0xFF00FF, // rgb(255,0,255)
  gainsboro               = 0xDCDCDC, // rgb(220,220,220)
  ghost_white             = 0xF8F8FF, // rgb(248,248,255)
  gold                    = 0xFFD700, // rgb(255,215,0)
  golden_rod              = 0xDAA520, // rgb(218,165,32)
  gray                    = 0x808080, // rgb(128,128,128)
  green                   = 0x008000, // rgb(0,128,0)
  green_yellow            = 0xADFF2F, // rgb(173,255,47)
  honey_dew               = 0xF0FFF0, // rgb(240,255,240)
  hot_pink                = 0xFF69B4, // rgb(255,105,180)
  indian_red              = 0xCD5C5C, // rgb(205,92,92)
  indigo                  = 0x4B0082, // rgb(75,0,130)
  ivory                   = 0xFFFFF0, // rgb(255,255,240)
  khaki                   = 0xF0E68C, // rgb(240,230,140)
  lavender                = 0xE6E6FA, // rgb(230,230,250)
  lavender_blush          = 0xFFF0F5, // rgb(255,240,245)
  lawn_green              = 0x7CFC00, // rgb(124,252,0)
  lemon_chiffon           = 0xFFFACD, // rgb(255,250,205)
  light_blue              = 0xADD8E6, // rgb(173,216,230)
  light_coral             = 0xF08080, // rgb(240,128,128)
  light_cyan              = 0xE0FFFF, // rgb(224,255,255)
  light_golden_rod_yellow = 0xFAFAD2, // rgb(250,250,210)
  light_gray              = 0xD3D3D3, // rgb(211,211,211)
  light_green             = 0x90EE90, // rgb(144,238,144)
  light_pink              = 0xFFB6C1, // rgb(255,182,193)
  light_salmon            = 0xFFA07A, // rgb(255,160,122)
  light_sea_green         = 0x20B2AA, // rgb(32,178,170)
  light_sky_blue          = 0x87CEFA, // rgb(135,206,250)
  light_slate_gray        = 0x778899, // rgb(119,136,153)
  light_steel_blue        = 0xB0C4DE, // rgb(176,196,222)
  light_yellow            = 0xFFFFE0, // rgb(255,255,224)
  lime                    = 0x00FF00, // rgb(0,255,0)
  lime_green              = 0x32CD32, // rgb(50,205,50)
  linen                   = 0xFAF0E6, // rgb(250,240,230)
  magenta                 = 0xFF00FF, // rgb(255,0,255)
  maroon                  = 0x800000, // rgb(128,0,0)
  medium_aquamarine       = 0x66CDAA, // rgb(102,205,170)
  medium_blue             = 0x0000CD, // rgb(0,0,205)
  medium_orchid           = 0xBA55D3, // rgb(186,85,211)
  medium_purple           = 0x9370DB, // rgb(147,112,219)
  medium_sea_green        = 0x3CB371, // rgb(60,179,113)
  medium_slate_blue       = 0x7B68EE, // rgb(123,104,238)
  medium_spring_green     = 0x00FA9A, // rgb(0,250,154)
  medium_turquoise        = 0x48D1CC, // rgb(72,209,204)
  medium_violet_red       = 0xC71585, // rgb(199,21,133)
  midnight_blue           = 0x191970, // rgb(25,25,112)
  mint_cream              = 0xF5FFFA, // rgb(245,255,250)
  misty_rose              = 0xFFE4E1, // rgb(255,228,225)
  moccasin                = 0xFFE4B5, // rgb(255,228,181)
  navajo_white            = 0xFFDEAD, // rgb(255,222,173)
  navy                    = 0x000080, // rgb(0,0,128)
  old_lace                = 0xFDF5E6, // rgb(253,245,230)
  olive                   = 0x808000, // rgb(128,128,0)
  olive_drab              = 0x6B8E23, // rgb(107,142,35)
  orange                  = 0xFFA500, // rgb(255,165,0)
  orange_red              = 0xFF4500, // rgb(255,69,0)
  orchid                  = 0xDA70D6, // rgb(218,112,214)
  pale_golden_rod         = 0xEEE8AA, // rgb(238,232,170)
  pale_green              = 0x98FB98, // rgb(152,251,152)
  pale_turquoise          = 0xAFEEEE, // rgb(175,238,238)
  pale_violet_red         = 0xDB7093, // rgb(219,112,147)
  papaya_whip             = 0xFFEFD5, // rgb(255,239,213)
  peach_puff              = 0xFFDAB9, // rgb(255,218,185)
  peru                    = 0xCD853F, // rgb(205,133,63)
  pink                    = 0xFFC0CB, // rgb(255,192,203)
  plum                    = 0xDDA0DD, // rgb(221,160,221)
  powder_blue             = 0xB0E0E6, // rgb(176,224,230)
  purple                  = 0x800080, // rgb(128,0,128)
  rebecca_purple          = 0x663399, // rgb(102,51,153)
  red                     = 0xFF0000, // rgb(255,0,0)
  rosy_brown              = 0xBC8F8F, // rgb(188,143,143)
  royal_blue              = 0x4169E1, // rgb(65,105,225)
  saddle_brown            = 0x8B4513, // rgb(139,69,19)
  salmon                  = 0xFA8072, // rgb(250,128,114)
  sandy_brown             = 0xF4A460, // rgb(244,164,96)
  sea_green               = 0x2E8B57, // rgb(46,139,87)
  sea_shell               = 0xFFF5EE, // rgb(255,245,238)
  sienna                  = 0xA0522D, // rgb(160,82,45)
  silver                  = 0xC0C0C0, // rgb(192,192,192)
  sky_blue                = 0x87CEEB, // rgb(135,206,235)
  slate_blue              = 0x6A5ACD, // rgb(106,90,205)
  slate_gray              = 0x708090, // rgb(112,128,144)
  snow                    = 0xFFFAFA, // rgb(255,250,250)
  spring_green            = 0x00FF7F, // rgb(0,255,127)
  steel_blue              = 0x4682B4, // rgb(70,130,180)
  tan                     = 0xD2B48C, // rgb(210,180,140)
  teal                    = 0x008080, // rgb(0,128,128)
  thistle                 = 0xD8BFD8, // rgb(216,191,216)
  tomato                  = 0xFF6347, // rgb(255,99,71)
  turquoise               = 0x40E0D0, // rgb(64,224,208)
  violet                  = 0xEE82EE, // rgb(238,130,238)
  wheat                   = 0xF5DEB3, // rgb(245,222,179)
  white                   = 0xFFFFFF, // rgb(255,255,255)
  white_smoke             = 0xF5F5F5, // rgb(245,245,245)
  yellow                  = 0xFFFF00, // rgb(255,255,0)
  yellow_green            = 0x9ACD32, // rgb(154,205,50)
};  // enum class color

// rgb is a struct for red, green and blue colors.
// We use rgb as name because some editors will show it as color direct in the
// editor.
struct rgb {
  FMT_CONSTEXPR_DECL rgb() : r(0), g(0), b(0) {}
  FMT_CONSTEXPR_DECL rgb(uint8_t r_, uint8_t g_, uint8_t b_)
	: r(r_), g(g_), b(b_) {}
  FMT_CONSTEXPR_DECL rgb(uint32_t hex)
	: r((hex >> 16) & 0xFF), g((hex >> 8) & 0xFF), b((hex) & 0xFF) {}
  FMT_CONSTEXPR_DECL rgb(color hex)
	: r((uint32_t(hex) >> 16) & 0xFF), g((uint32_t(hex) >> 8) & 0xFF),
	  b(uint32_t(hex) & 0xFF) {}
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

void vprint_rgb(rgb fd, string_view format, format_args args);
void vprint_rgb(rgb fd, rgb bg, string_view format, format_args args);

/**
  Formats a string and prints it to stdout using ANSI escape sequences to
  specify foreground color 'fd'.
  Example:
	fmt::print(fmt::color::red, "Elapsed time: {0:.2f} seconds", 1.23);
 */
template <typename... Args>
inline void print(rgb fd, string_view format_str, const Args & ... args) {
  vprint_rgb(fd, format_str, fmt::make_format_args(args...));
}

/**
  Formats a string and prints it to stdout using ANSI escape sequences to
  specify foreground color 'fd' and background color 'bg'.
  Example:
	fmt::print(fmt::color::red, fmt::color::black, "Elapsed time: {0:.2f} seconds", 1.23);
 */
template <typename... Args>
inline void print(rgb fd, rgb bg, string_view format_str, const Args & ... args) {
  vprint_rgb(fd, bg, format_str, fmt::make_format_args(args...));
}
#endif  // FMT_EXTENDED_COLORS

#if FMT_USE_USER_DEFINED_LITERALS
namespace internal {

# if FMT_UDL_TEMPLATE
template <typename Char, Char... CHARS>
class udl_formatter {
 public:
  template <typename... Args>
  std::basic_string<Char> operator()(const Args &... args) const {
	FMT_CONSTEXPR_DECL Char s[] = {CHARS..., '\0'};
	FMT_CONSTEXPR_DECL bool invalid_format =
		check_format_string<Char, error_handler, Args...>(
		  basic_string_view<Char>(s, sizeof...(CHARS)));
	(void)invalid_format;
	return format(s, args...);
  }
};
# else
template <typename Char>
struct udl_formatter {
  const Char *str;

  template <typename... Args>
  auto operator()(Args && ... args) const
				  -> decltype(format(str, std::forward<Args>(args)...)) {
	return format(str, std::forward<Args>(args)...);
  }
};
# endif // FMT_UDL_TEMPLATE

template <typename Char>
struct udl_arg {
  const Char *str;

  template <typename T>
  named_arg<T, Char> operator=(T &&value) const {
	return {str, std::forward<T>(value)};
  }
};

} // namespace internal

inline namespace literals {

# if FMT_UDL_TEMPLATE
template <typename Char, Char... CHARS>
FMT_CONSTEXPR internal::udl_formatter<Char, CHARS...> operator""_format() {
  return {};
}
# else
/**
  \rst
  User-defined literal equivalent of :func:`fmt::format`.

  **Example**::

	using namespace fmt::literals;
	std::string message = "The answer is {}"_format(42);
  \endrst
 */
inline internal::udl_formatter<char>
operator"" _format(const char *s, std::size_t) { return {s}; }
inline internal::udl_formatter<wchar_t>
operator"" _format(const wchar_t *s, std::size_t) { return {s}; }
# endif // FMT_UDL_TEMPLATE

/**
  \rst
  User-defined literal equivalent of :func:`fmt::arg`.

  **Example**::

	using namespace fmt::literals;
	fmt::print("Elapsed time: {s:.2f} seconds", "s"_a=1.23);
  \endrst
 */
inline internal::udl_arg<char>
operator"" _a(const char *s, std::size_t) { return {s}; }
inline internal::udl_arg<wchar_t>
operator"" _a(const wchar_t *s, std::size_t) { return {s}; }
} // inline namespace literals
#endif // FMT_USE_USER_DEFINED_LITERALS
FMT_END_NAMESPACE

#define FMT_STRING(s) [] { \
	struct S : fmt::format_string { \
	  static FMT_CONSTEXPR decltype(s) data() { return s; } \
	  static FMT_CONSTEXPR size_t size() { return sizeof(s); } \
	}; \
	return S{}; \
  }()

#ifndef FMT_NO_FMT_STRING_ALIAS
/**
  \rst
  Constructs a compile-time format string.

  **Example**::

	#include <dmformat.h>
	// A compile-time error because 'd' is an invalid specifier for strings.
	std::string s = format(fmt("{:d}"), "foo");
  \endrst
 */
# define fmt(s) FMT_STRING(s)
#endif

#ifdef FMT_HEADER_ONLY
# define FMT_FUNC inline

/*** Start of inlined file: dmformat-inl.h ***/
// Formatting library for C++
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

#ifndef __DMFORMAT_INL_H_INCLUDE__
#define __DMFORMAT_INL_H_INCLUDE__

#include <string.h>

#include <cctype>
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>  // for std::ptrdiff_t
#include <locale>

#if defined(_WIN32) && defined(__MINGW32__)
# include <cstring>
#endif

#if FMT_USE_WINDOWS_H
# if !defined(FMT_HEADER_ONLY) && !defined(WIN32_LEAN_AND_MEAN)
#  define WIN32_LEAN_AND_MEAN
# endif
# if defined(NOMINMAX) || defined(FMT_WIN_MINMAX)
#  include <windows.h>
# else
#  define NOMINMAX
#  include <windows.h>
#  undef NOMINMAX
# endif
#endif

#if FMT_EXCEPTIONS
# define FMT_TRY try
# define FMT_CATCH(x) catch (x)
#else
# define FMT_TRY if (true)
# define FMT_CATCH(x) if (false)
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127)  // conditional expression is constant
# pragma warning(disable: 4702)  // unreachable code
// Disable deprecation warning for strerror. The latter is not called but
// MSVC fails to detect it.
# pragma warning(disable: 4996)
#endif

// Dummy implementations of strerror_r and strerror_s called if corresponding
// system functions are not available.
inline fmt::internal::null<> strerror_r(int, char *, ...) {
  return fmt::internal::null<>();
}
inline fmt::internal::null<> strerror_s(char *, std::size_t, ...) {
  return fmt::internal::null<>();
}

FMT_BEGIN_NAMESPACE

namespace {

#ifndef _MSC_VER
# define FMT_SNPRINTF snprintf
#else  // _MSC_VER
inline int fmt_snprintf(char *buffer, size_t size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int result = vsnprintf_s(buffer, size, _TRUNCATE, format, args);
  va_end(args);
  return result;
}
# define FMT_SNPRINTF fmt_snprintf
#endif  // _MSC_VER

#if defined(_WIN32) && defined(__MINGW32__) && !defined(__NO_ISOCEXT)
# define FMT_SWPRINTF snwprintf
#else
# define FMT_SWPRINTF swprintf
#endif // defined(_WIN32) && defined(__MINGW32__) && !defined(__NO_ISOCEXT)

typedef void (*FormatFunc)(internal::buffer &, int, string_view);

// Portable thread-safe version of strerror.
// Sets buffer to point to a string describing the error code.
// This can be either a pointer to a string stored in buffer,
// or a pointer to some static immutable string.
// Returns one of the following values:
//   0      - success
//   ERANGE - buffer is not large enough to store the error message
//   other  - failure
// Buffer should be at least of size 1.
int safe_strerror(
	int error_code, char *&buffer, std::size_t buffer_size) FMT_NOEXCEPT {
  FMT_ASSERT(buffer != FMT_NULL && buffer_size != 0, "invalid buffer");

  class dispatcher {
   private:
	int error_code_;
	char *&buffer_;
	std::size_t buffer_size_;

	// A noop assignment operator to avoid bogus warnings.
	void operator=(const dispatcher &) {}

	// Handle the result of XSI-compliant version of strerror_r.
	int handle(int result) {
	  // glibc versions before 2.13 return result in errno.
	  return result == -1 ? errno : result;
	}

	// Handle the result of GNU-specific version of strerror_r.
	int handle(char *message) {
	  // If the buffer is full then the message is probably truncated.
	  if (message == buffer_ && strlen(buffer_) == buffer_size_ - 1)
		return ERANGE;
	  buffer_ = message;
	  return 0;
	}

	// Handle the case when strerror_r is not available.
	int handle(internal::null<>) {
	  return fallback(strerror_s(buffer_, buffer_size_, error_code_));
	}

	// Fallback to strerror_s when strerror_r is not available.
	int fallback(int result) {
	  // If the buffer is full then the message is probably truncated.
	  return result == 0 && strlen(buffer_) == buffer_size_ - 1 ?
			ERANGE : result;
	}

	// Fallback to strerror if strerror_r and strerror_s are not available.
	int fallback(internal::null<>) {
	  errno = 0;
	  buffer_ = strerror(error_code_);
	  return errno;
	}

   public:
	dispatcher(int err_code, char *&buf, std::size_t buf_size)
	  : error_code_(err_code), buffer_(buf), buffer_size_(buf_size) {}

	int run() {
	  return handle(strerror_r(error_code_, buffer_, buffer_size_));
	}
  };
  return dispatcher(error_code, buffer, buffer_size).run();
}

void format_error_code(internal::buffer &out, int error_code,
					   string_view message) FMT_NOEXCEPT {
  // Report error code making sure that the output fits into
  // inline_buffer_size to avoid dynamic memory allocation and potential
  // bad_alloc.
  out.resize(0);
  static const char SEP[] = ": ";
  static const char ERROR_STR[] = "error ";
  // Subtract 2 to account for terminating null characters in SEP and ERROR_STR.
  std::size_t error_code_size = sizeof(SEP) + sizeof(ERROR_STR) - 2;
  typedef internal::int_traits<int>::main_type main_type;
  main_type abs_value = static_cast<main_type>(error_code);
  if (internal::is_negative(error_code)) {
	abs_value = 0 - abs_value;
	++error_code_size;
  }
  error_code_size += internal::count_digits(abs_value);
  writer w(out);
  if (message.size() <= inline_buffer_size - error_code_size) {
	w.write(message);
	w.write(SEP);
  }
  w.write(ERROR_STR);
  w.write(error_code);
  assert(out.size() <= inline_buffer_size);
}

void report_error(FormatFunc func, int error_code,
				  string_view message) FMT_NOEXCEPT {
  memory_buffer full_message;
  func(full_message, error_code, message);
  // Use Writer::data instead of Writer::c_str to avoid potential memory
  // allocation.
  std::fwrite(full_message.data(), full_message.size(), 1, stderr);
  std::fputc('\n', stderr);
}
}  // namespace

class locale {
 private:
  std::locale locale_;

 public:
  explicit locale(std::locale loc = std::locale()) : locale_(loc) {}
  std::locale get() { return locale_; }
};

template <typename Char>
FMT_FUNC Char internal::thousands_sep(locale_provider *lp) {
  std::locale loc = lp ? lp->locale().get() : std::locale();
  return std::use_facet<std::numpunct<Char>>(loc).thousands_sep();
}

FMT_FUNC void system_error::init(
	int err_code, string_view format_str, format_args args) {
  error_code_ = err_code;
  memory_buffer buffer;
  format_system_error(buffer, err_code, vformat(format_str, args));
  std::runtime_error &base = *this;
  base = std::runtime_error(to_string(buffer));
}

namespace internal {
template <typename T>
int char_traits<char>::format_float(
	char *buffer, std::size_t size, const char *format, int precision, T value) {
  return precision < 0 ?
	  FMT_SNPRINTF(buffer, size, format, value) :
	  FMT_SNPRINTF(buffer, size, format, precision, value);
}

template <typename T>
int char_traits<wchar_t>::format_float(
	wchar_t *buffer, std::size_t size, const wchar_t *format, int precision,
	T value) {
  return precision < 0 ?
	  FMT_SWPRINTF(buffer, size, format, value) :
	  FMT_SWPRINTF(buffer, size, format, precision, value);
}

template <typename T>
const char basic_data<T>::DIGITS[] =
	"0001020304050607080910111213141516171819"
	"2021222324252627282930313233343536373839"
	"4041424344454647484950515253545556575859"
	"6061626364656667686970717273747576777879"
	"8081828384858687888990919293949596979899";

#define FMT_POWERS_OF_10(factor) \
  factor * 10, \
  factor * 100, \
  factor * 1000, \
  factor * 10000, \
  factor * 100000, \
  factor * 1000000, \
  factor * 10000000, \
  factor * 100000000, \
  factor * 1000000000

template <typename T>
const uint32_t basic_data<T>::POWERS_OF_10_32[] = {
  0, FMT_POWERS_OF_10(1)
};

template <typename T>
const uint64_t basic_data<T>::POWERS_OF_10_64[] = {
  0,
  FMT_POWERS_OF_10(1),
  FMT_POWERS_OF_10(1000000000ull),
  10000000000000000000ull
};

// Normalized 64-bit significands of pow(10, k), for k = -348, -340, ..., 340.
// These are generated by support/compute-powers.py.
template <typename T>
const uint64_t basic_data<T>::POW10_SIGNIFICANDS[] = {
  0xfa8fd5a0081c0288, 0xbaaee17fa23ebf76, 0x8b16fb203055ac76, 0xcf42894a5dce35ea,
  0x9a6bb0aa55653b2d, 0xe61acf033d1a45df, 0xab70fe17c79ac6ca, 0xff77b1fcbebcdc4f,
  0xbe5691ef416bd60c, 0x8dd01fad907ffc3c, 0xd3515c2831559a83, 0x9d71ac8fada6c9b5,
  0xea9c227723ee8bcb, 0xaecc49914078536d, 0x823c12795db6ce57, 0xc21094364dfb5637,
  0x9096ea6f3848984f, 0xd77485cb25823ac7, 0xa086cfcd97bf97f4, 0xef340a98172aace5,
  0xb23867fb2a35b28e, 0x84c8d4dfd2c63f3b, 0xc5dd44271ad3cdba, 0x936b9fcebb25c996,
  0xdbac6c247d62a584, 0xa3ab66580d5fdaf6, 0xf3e2f893dec3f126, 0xb5b5ada8aaff80b8,
  0x87625f056c7c4a8b, 0xc9bcff6034c13053, 0x964e858c91ba2655, 0xdff9772470297ebd,
  0xa6dfbd9fb8e5b88f, 0xf8a95fcf88747d94, 0xb94470938fa89bcf, 0x8a08f0f8bf0f156b,
  0xcdb02555653131b6, 0x993fe2c6d07b7fac, 0xe45c10c42a2b3b06, 0xaa242499697392d3,
  0xfd87b5f28300ca0e, 0xbce5086492111aeb, 0x8cbccc096f5088cc, 0xd1b71758e219652c,
  0x9c40000000000000, 0xe8d4a51000000000, 0xad78ebc5ac620000, 0x813f3978f8940984,
  0xc097ce7bc90715b3, 0x8f7e32ce7bea5c70, 0xd5d238a4abe98068, 0x9f4f2726179a2245,
  0xed63a231d4c4fb27, 0xb0de65388cc8ada8, 0x83c7088e1aab65db, 0xc45d1df942711d9a,
  0x924d692ca61be758, 0xda01ee641a708dea, 0xa26da3999aef774a, 0xf209787bb47d6b85,
  0xb454e4a179dd1877, 0x865b86925b9bc5c2, 0xc83553c5c8965d3d, 0x952ab45cfa97a0b3,
  0xde469fbd99a05fe3, 0xa59bc234db398c25, 0xf6c69a72a3989f5c, 0xb7dcbf5354e9bece,
  0x88fcf317f22241e2, 0xcc20ce9bd35c78a5, 0x98165af37b2153df, 0xe2a0b5dc971f303a,
  0xa8d9d1535ce3b396, 0xfb9b7cd9a4a7443c, 0xbb764c4ca7a44410, 0x8bab8eefb6409c1a,
  0xd01fef10a657842c, 0x9b10a4e5e9913129, 0xe7109bfba19c0c9d, 0xac2820d9623bf429,
  0x80444b5e7aa7cf85, 0xbf21e44003acdd2d, 0x8e679c2f5e44ff8f, 0xd433179d9c8cb841,
  0x9e19db92b4e31ba9, 0xeb96bf6ebadf77d9, 0xaf87023b9bf0ee6b
};

// Binary exponents of pow(10, k), for k = -348, -340, ..., 340, corresponding
// to significands above.
template <typename T>
const int16_t basic_data<T>::POW10_EXPONENTS[] = {
  -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007,  -980,  -954,
   -927,  -901,  -874,  -847,  -821,  -794,  -768,  -741,  -715,  -688,  -661,
   -635,  -608,  -582,  -555,  -529,  -502,  -475,  -449,  -422,  -396,  -369,
   -343,  -316,  -289,  -263,  -236,  -210,  -183,  -157,  -130,  -103,   -77,
	-50,   -24,     3,    30,    56,    83,   109,   136,   162,   189,   216,
	242,   269,   295,   322,   348,   375,   402,   428,   455,   481,   508,
	534,   561,   588,   614,   641,   667,   694,   720,   747,   774,   800,
	827,   853,   880,   907,   933,   960,   986,  1013,  1039,  1066
};

template <typename T> const char basic_data<T>::RESET_COLOR[] = "\x1b[0m";
template <typename T> const wchar_t basic_data<T>::WRESET_COLOR[] = L"\x1b[0m";

FMT_FUNC fp operator*(fp x, fp y) {
  // Multiply 32-bit parts of significands.
  uint64_t mask = (1ULL << 32) - 1;
  uint64_t a = x.f >> 32, b = x.f & mask;
  uint64_t c = y.f >> 32, d = y.f & mask;
  uint64_t ac = a * c, bc = b * c, ad = a * d, bd = b * d;
  // Compute mid 64-bit of result and round.
  uint64_t mid = (bd >> 32) + (ad & mask) + (bc & mask) + (1U << 31);
  return fp(ac + (ad >> 32) + (bc >> 32) + (mid >> 32), x.e + y.e + 64);
}

FMT_FUNC fp get_cached_power(int min_exponent, int &pow10_exponent) {
  const double one_over_log2_10 = 0.30102999566398114;  // 1 / log2(10)
  int index = static_cast<int>(std::ceil(
		(min_exponent + fp::significand_size - 1) * one_over_log2_10));
  // Decimal exponent of the first (smallest) cached power of 10.
  const int first_dec_exp = -348;
  // Difference between two consecutive decimal exponents in cached powers of 10.
  const int dec_exp_step = 8;
  index = (index - first_dec_exp - 1) / dec_exp_step + 1;
  pow10_exponent = first_dec_exp + index * dec_exp_step;
  return fp(data::POW10_SIGNIFICANDS[index], data::POW10_EXPONENTS[index]);
}
}  // namespace internal

#if FMT_USE_WINDOWS_H

FMT_FUNC internal::utf8_to_utf16::utf8_to_utf16(string_view s) {
  static const char ERROR_MSG[] = "cannot convert string from UTF-8 to UTF-16";
  if (s.size() > INT_MAX)
	FMT_THROW(windows_error(ERROR_INVALID_PARAMETER, ERROR_MSG));
  int s_size = static_cast<int>(s.size());
  if (s_size == 0) {
	// MultiByteToWideChar does not support zero length, handle separately.
	buffer_.resize(1);
	buffer_[0] = 0;
	return;
  }

  int length = MultiByteToWideChar(
	  CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), s_size, FMT_NULL, 0);
  if (length == 0)
	FMT_THROW(windows_error(GetLastError(), ERROR_MSG));
  buffer_.resize(length + 1);
  length = MultiByteToWideChar(
	CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), s_size, &buffer_[0], length);
  if (length == 0)
	FMT_THROW(windows_error(GetLastError(), ERROR_MSG));
  buffer_[length] = 0;
}

FMT_FUNC internal::utf16_to_utf8::utf16_to_utf8(wstring_view s) {
  if (int error_code = convert(s)) {
	FMT_THROW(windows_error(error_code,
		"cannot convert string from UTF-16 to UTF-8"));
  }
}

FMT_FUNC int internal::utf16_to_utf8::convert(wstring_view s) {
  if (s.size() > INT_MAX)
	return ERROR_INVALID_PARAMETER;
  int s_size = static_cast<int>(s.size());
  if (s_size == 0) {
	// WideCharToMultiByte does not support zero length, handle separately.
	buffer_.resize(1);
	buffer_[0] = 0;
	return 0;
  }

  int length = WideCharToMultiByte(
		CP_UTF8, 0, s.data(), s_size, FMT_NULL, 0, FMT_NULL, FMT_NULL);
  if (length == 0)
	return GetLastError();
  buffer_.resize(length + 1);
  length = WideCharToMultiByte(
	CP_UTF8, 0, s.data(), s_size, &buffer_[0], length, FMT_NULL, FMT_NULL);
  if (length == 0)
	return GetLastError();
  buffer_[length] = 0;
  return 0;
}

FMT_FUNC void windows_error::init(
	int err_code, string_view format_str, format_args args) {
  error_code_ = err_code;
  memory_buffer buffer;
  internal::format_windows_error(buffer, err_code, vformat(format_str, args));
  std::runtime_error &base = *this;
  base = std::runtime_error(to_string(buffer));
}

FMT_FUNC void internal::format_windows_error(
	internal::buffer &out, int error_code, string_view message) FMT_NOEXCEPT {
  FMT_TRY {
	wmemory_buffer buf;
	buf.resize(inline_buffer_size);
	for (;;) {
	  wchar_t *system_message = &buf[0];
	  int result = FormatMessageW(
		  FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		  FMT_NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		  system_message, static_cast<uint32_t>(buf.size()), FMT_NULL);
	  if (result != 0) {
		utf16_to_utf8 utf8_message;
		if (utf8_message.convert(system_message) == ERROR_SUCCESS) {
		  writer w(out);
		  w.write(message);
		  w.write(": ");
		  w.write(utf8_message);
		  return;
		}
		break;
	  }
	  if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		break;  // Can't get error message, report error code instead.
	  buf.resize(buf.size() * 2);
	}
  } FMT_CATCH(...) {}
  format_error_code(out, error_code, message);
}

#endif  // FMT_USE_WINDOWS_H

FMT_FUNC void format_system_error(
	internal::buffer &out, int error_code, string_view message) FMT_NOEXCEPT {
  FMT_TRY {
	memory_buffer buf;
	buf.resize(inline_buffer_size);
	for (;;) {
	  char *system_message = &buf[0];
	  int result = safe_strerror(error_code, system_message, buf.size());
	  if (result == 0) {
		writer w(out);
		w.write(message);
		w.write(": ");
		w.write(system_message);
		return;
	  }
	  if (result != ERANGE)
		break;  // Can't get error message, report error code instead.
	  buf.resize(buf.size() * 2);
	}
  } FMT_CATCH(...) {}
  format_error_code(out, error_code, message);
}

template <typename Char>
void basic_fixed_buffer<Char>::grow(std::size_t) {
  FMT_THROW(std::runtime_error("buffer overflow"));
}

FMT_FUNC void internal::error_handler::on_error(const char *message) {
  FMT_THROW(format_error(message));
}

FMT_FUNC void report_system_error(
	int error_code, fmt::string_view message) FMT_NOEXCEPT {
  report_error(format_system_error, error_code, message);
}

#if FMT_USE_WINDOWS_H
FMT_FUNC void report_windows_error(
	int error_code, fmt::string_view message) FMT_NOEXCEPT {
  report_error(internal::format_windows_error, error_code, message);
}
#endif

FMT_FUNC void vprint(std::FILE *f, string_view format_str, format_args args) {
  memory_buffer buffer;
  vformat_to(buffer, format_str, args);
  std::fwrite(buffer.data(), 1, buffer.size(), f);
}

FMT_FUNC void vprint(std::FILE *f, wstring_view format_str, wformat_args args) {
  wmemory_buffer buffer;
  vformat_to(buffer, format_str, args);
  std::fwrite(buffer.data(), sizeof(wchar_t), buffer.size(), f);
}

FMT_FUNC void vprint(string_view format_str, format_args args) {
  vprint(stdout, format_str, args);
}

FMT_FUNC void vprint(wstring_view format_str, wformat_args args) {
  vprint(stdout, format_str, args);
}

#ifndef FMT_EXTENDED_COLORS
FMT_FUNC void vprint_colored(color c, string_view format, format_args args) {
  char escape[] = "\x1b[30m";
  escape[3] = static_cast<char>('0' + c);
  std::fputs(escape, stdout);
  vprint(format, args);
  std::fputs(internal::data::RESET_COLOR, stdout);
}

FMT_FUNC void vprint_colored(color c, wstring_view format, wformat_args args) {
  wchar_t escape[] = L"\x1b[30m";
  escape[3] = static_cast<wchar_t>('0' + c);
  std::fputws(escape, stdout);
  vprint(format, args);
  std::fputws(internal::data::WRESET_COLOR, stdout);
}
#else
namespace internal {
FMT_CONSTEXPR void to_esc(uint8_t c, char out[], int offset) {
  out[offset + 0] = static_cast<char>('0' + c / 100);
  out[offset + 1] = static_cast<char>('0' + c / 10 % 10);
  out[offset + 2] = static_cast<char>('0' + c % 10);
}
} // namespace internal

FMT_FUNC void vprint_rgb(rgb fd, string_view format, format_args args) {
  char escape_fd[] = "\x1b[38;2;000;000;000m";
  internal::to_esc(fd.r, escape_fd, 7);
  internal::to_esc(fd.g, escape_fd, 11);
  internal::to_esc(fd.b, escape_fd, 15);

  std::fputs(escape_fd, stdout);
  vprint(format, args);
  std::fputs(internal::data::RESET_COLOR, stdout);
}

FMT_FUNC void vprint_rgb(rgb fd, rgb bg, string_view format, format_args args) {
  char escape_fd[] = "\x1b[38;2;000;000;000m"; // foreground color
  char escape_bg[] = "\x1b[48;2;000;000;000m"; // background color
  internal::to_esc(fd.r, escape_fd, 7);
  internal::to_esc(fd.g, escape_fd, 11);
  internal::to_esc(fd.b, escape_fd, 15);

  internal::to_esc(bg.r, escape_bg, 7);
  internal::to_esc(bg.g, escape_bg, 11);
  internal::to_esc(bg.b, escape_bg, 15);

  std::fputs(escape_fd, stdout);
  std::fputs(escape_bg, stdout);
  vprint(format, args);
  std::fputs(internal::data::RESET_COLOR, stdout);
}
#endif

FMT_FUNC locale locale_provider::locale() { return fmt::locale(); }

FMT_END_NAMESPACE

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif // __DMFORMAT_INL_H_INCLUDE__

/*** End of inlined file: dmformat-inl.h ***/


#else
# define FMT_FUNC
#endif

// Restore warnings.
#if FMT_GCC_VERSION >= 406 || FMT_CLANG_VERSION
# pragma GCC diagnostic pop
#endif


/*** Start of inlined file: dmprintf.h ***/
// Formatting library for C++
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

#ifndef __DMPRINTF_H_INCLUDE__
#define __DMPRINTF_H_INCLUDE__

#include <algorithm>  // std::fill_n
#include <limits>     // std::numeric_limits


/*** Start of inlined file: dmostream.h ***/
// Formatting library for C++ - std::ostream support
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

#ifndef __DMOSTREAM_H_INCLUDE__
#define __DMOSTREAM_H_INCLUDE__

#include <ostream>

FMT_BEGIN_NAMESPACE
namespace internal {

template <class Char>
class formatbuf : public std::basic_streambuf<Char> {
 private:
  typedef typename std::basic_streambuf<Char>::int_type int_type;
  typedef typename std::basic_streambuf<Char>::traits_type traits_type;

  basic_buffer<Char> &buffer_;

 public:
  formatbuf(basic_buffer<Char> &buffer) : buffer_(buffer) {}

 protected:
  // The put-area is actually always empty. This makes the implementation
  // simpler and has the advantage that the streambuf and the buffer are always
  // in sync and sputc never writes into uninitialized memory. The obvious
  // disadvantage is that each call to sputc always results in a (virtual) call
  // to overflow. There is no disadvantage here for sputn since this always
  // results in a call to xsputn.

  int_type overflow(int_type ch = traits_type::eof()) FMT_OVERRIDE {
	if (!traits_type::eq_int_type(ch, traits_type::eof()))
	  buffer_.push_back(static_cast<Char>(ch));
	return ch;
  }

  std::streamsize xsputn(const Char *s, std::streamsize count) FMT_OVERRIDE {
	buffer_.append(s, s + count);
	return count;
  }
};

template <typename Char>
struct test_stream : std::basic_ostream<Char> {
 private:
  struct null;
  // Hide all operator<< from std::basic_ostream<Char>.
  void operator<<(null);
};

// Checks if T has a user-defined operator<< (e.g. not a member of std::ostream).
template <typename T, typename Char>
class is_streamable {
 private:
  template <typename U>
  static decltype(
	internal::declval<test_stream<Char>&>()
	  << internal::declval<U>(), std::true_type()) test(int);

  template <typename>
  static std::false_type test(...);

  typedef decltype(test<T>(0)) result;

 public:
  // std::string operator<< is not considered user-defined because we handle strings
  // specially.
  static const bool value = result::value && !std::is_same<T, std::string>::value;
};

// Disable conversion to int if T has an overloaded operator<< which is a free
// function (not a member of std::ostream).
template <typename T, typename Char>
class convert_to_int<T, Char, true> {
 public:
  static const bool value =
	convert_to_int<T, Char, false>::value && !is_streamable<T, Char>::value;
};

// Write the content of buf to os.
template <typename Char>
void write(std::basic_ostream<Char> &os, basic_buffer<Char> &buf) {
  const Char *data = buf.data();
  typedef std::make_unsigned<std::streamsize>::type UnsignedStreamSize;
  UnsignedStreamSize size = buf.size();
  UnsignedStreamSize max_size =
	  internal::to_unsigned((std::numeric_limits<std::streamsize>::max)());
  do {
	UnsignedStreamSize n = size <= max_size ? size : max_size;
	os.write(data, static_cast<std::streamsize>(n));
	data += n;
	size -= n;
  } while (size != 0);
}

template <typename Char, typename T>
void format_value(basic_buffer<Char> &buffer, const T &value) {
  internal::formatbuf<Char> format_buf(buffer);
  std::basic_ostream<Char> output(&format_buf);
  output.exceptions(std::ios_base::failbit | std::ios_base::badbit);
  output << value;
  buffer.resize(buffer.size());
}

// Disable builtin formatting of enums and use operator<< instead.
template <typename T>
struct format_enum<T,
	typename std::enable_if<std::is_enum<T>::value>::type> : std::false_type {};
}  // namespace internal

// Formats an object of type T that has an overloaded ostream operator<<.
template <typename T, typename Char>
struct formatter<T, Char,
	typename std::enable_if<internal::is_streamable<T, Char>::value>::type>
	: formatter<basic_string_view<Char>, Char> {

  template <typename Context>
  auto format(const T &value, Context &ctx) -> decltype(ctx.out()) {
	basic_memory_buffer<Char> buffer;
	internal::format_value(buffer, value);
	basic_string_view<Char> str(buffer.data(), buffer.size());
	formatter<basic_string_view<Char>, Char>::format(str, ctx);
	return ctx.out();
  }
};

template <typename Char>
inline void vprint(std::basic_ostream<Char> &os,
				   basic_string_view<Char> format_str,
				   basic_format_args<typename buffer_context<Char>::type> args) {
  basic_memory_buffer<Char> buffer;
  vformat_to(buffer, format_str, args);
  internal::write(os, buffer);
}
/**
  \rst
  Prints formatted data to the stream *os*.

  **Example**::

	fmt::print(cerr, "Don't {}!", "panic");
  \endrst
 */
template <typename... Args>
inline void print(std::ostream &os, string_view format_str,
				  const Args & ... args) {
  vprint<char>(os, format_str, fmt::make_format_args<format_context>(args...));
}

template <typename... Args>
inline void print(std::wostream &os, wstring_view format_str,
				  const Args & ... args) {
  vprint<wchar_t>(os, format_str, fmt::make_format_args<wformat_context>(args...));
}
FMT_END_NAMESPACE

#endif // __DMOSTREAM_H_INCLUDE__

/*** End of inlined file: dmostream.h ***/

FMT_BEGIN_NAMESPACE
namespace internal {

// Checks if a value fits in int - used to avoid warnings about comparing
// signed and unsigned integers.
template <bool IsSigned>
struct int_checker {
  template <typename T>
  static bool fits_in_int(T value) {
	unsigned max = std::numeric_limits<int>::max();
	return value <= max;
  }
  static bool fits_in_int(bool) { return true; }
};

template <>
struct int_checker<true> {
  template <typename T>
  static bool fits_in_int(T value) {
	return value >= std::numeric_limits<int>::min() &&
		   value <= std::numeric_limits<int>::max();
  }
  static bool fits_in_int(int) { return true; }
};

class printf_precision_handler: public function<int> {
 public:
  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, int>::type
	  operator()(T value) {
	if (!int_checker<std::numeric_limits<T>::is_signed>::fits_in_int(value))
	  FMT_THROW(format_error("number is too big"));
	return static_cast<int>(value);
  }

  template <typename T>
  typename std::enable_if<!std::is_integral<T>::value, int>::type operator()(T) {
	FMT_THROW(format_error("precision is not integer"));
	return 0;
  }
};

// An argument visitor that returns true iff arg is a zero integer.
class is_zero_int: public function<bool> {
 public:
  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, bool>::type
	  operator()(T value) { return value == 0; }

  template <typename T>
  typename std::enable_if<!std::is_integral<T>::value, bool>::type
	  operator()(T) { return false; }
};

template <typename T>
struct make_unsigned_or_bool : std::make_unsigned<T> {};

template <>
struct make_unsigned_or_bool<bool> {
  typedef bool type;
};

template <typename T, typename Context>
class arg_converter: public function<void> {
 private:
  typedef typename Context::char_type Char;

  basic_format_arg<Context> &arg_;
  typename Context::char_type type_;

 public:
  arg_converter(basic_format_arg<Context> &arg, Char type)
	: arg_(arg), type_(type) {}

  void operator()(bool value) {
	if (type_ != 's')
	  operator()<bool>(value);
  }

  template <typename U>
  typename std::enable_if<std::is_integral<U>::value>::type
	  operator()(U value) {
	bool is_signed = type_ == 'd' || type_ == 'i';
	typedef typename std::conditional<
		std::is_same<T, void>::value, U, T>::type TargetType;
	if (const_check(sizeof(TargetType) <= sizeof(int))) {
	  // Extra casts are used to silence warnings.
	  if (is_signed) {
		arg_ = internal::make_arg<Context>(
		  static_cast<int>(static_cast<TargetType>(value)));
	  } else {
		typedef typename make_unsigned_or_bool<TargetType>::type Unsigned;
		arg_ = internal::make_arg<Context>(
		  static_cast<unsigned>(static_cast<Unsigned>(value)));
	  }
	} else {
	  if (is_signed) {
		// glibc's printf doesn't sign extend arguments of smaller types:
		//   std::printf("%lld", -42);  // prints "4294967254"
		// but we don't have to do the same because it's a UB.
		arg_ = internal::make_arg<Context>(static_cast<long long>(value));
	  } else {
		arg_ = internal::make_arg<Context>(
		  static_cast<typename make_unsigned_or_bool<U>::type>(value));
	  }
	}
  }

  template <typename U>
  typename std::enable_if<!std::is_integral<U>::value>::type operator()(U) {
	// No coversion needed for non-integral types.
  }
};

// Converts an integer argument to T for printf, if T is an integral type.
// If T is void, the argument is converted to corresponding signed or unsigned
// type depending on the type specifier: 'd' and 'i' - signed, other -
// unsigned).
template <typename T, typename Context, typename Char>
void convert_arg(basic_format_arg<Context> &arg, Char type) {
  visit(arg_converter<T, Context>(arg, type), arg);
}

// Converts an integer argument to char for printf.
template <typename Context>
class char_converter: public function<void> {
 private:
  basic_format_arg<Context> &arg_;

  FMT_DISALLOW_COPY_AND_ASSIGN(char_converter);

 public:
  explicit char_converter(basic_format_arg<Context> &arg) : arg_(arg) {}

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value>::type
	  operator()(T value) {
	typedef typename Context::char_type Char;
	arg_ = internal::make_arg<Context>(static_cast<Char>(value));
  }

  template <typename T>
  typename std::enable_if<!std::is_integral<T>::value>::type operator()(T) {
	// No coversion needed for non-integral types.
  }
};

// Checks if an argument is a valid printf width specifier and sets
// left alignment if it is negative.
template <typename Char>
class printf_width_handler: public function<unsigned> {
 private:
  typedef basic_format_specs<Char> format_specs;

  format_specs &spec_;

  FMT_DISALLOW_COPY_AND_ASSIGN(printf_width_handler);

 public:
  explicit printf_width_handler(format_specs &spec) : spec_(spec) {}

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, unsigned>::type
	  operator()(T value) {
	typedef typename internal::int_traits<T>::main_type UnsignedType;
	UnsignedType width = static_cast<UnsignedType>(value);
	if (internal::is_negative(value)) {
	  spec_.align_ = ALIGN_LEFT;
	  width = 0 - width;
	}
	unsigned int_max = std::numeric_limits<int>::max();
	if (width > int_max)
	  FMT_THROW(format_error("number is too big"));
	return static_cast<unsigned>(width);
  }

  template <typename T>
  typename std::enable_if<!std::is_integral<T>::value, unsigned>::type
	  operator()(T) {
	FMT_THROW(format_error("width is not integer"));
	return 0;
  }
};
}  // namespace internal

template <typename Range>
class printf_arg_formatter;

template <
	typename OutputIt, typename Char,
	typename ArgFormatter =
	  printf_arg_formatter<back_insert_range<internal::basic_buffer<Char>>>>
class basic_printf_context;

/**
  \rst
  The ``printf`` argument formatter.
  \endrst
 */
template <typename Range>
class printf_arg_formatter:
  public internal::function<
	typename internal::arg_formatter_base<Range>::iterator>,
  public internal::arg_formatter_base<Range> {
 private:
  typedef typename Range::value_type char_type;
  typedef decltype(internal::declval<Range>().begin()) iterator;
  typedef internal::arg_formatter_base<Range> base;
  typedef basic_printf_context<iterator, char_type> context_type;

  context_type &context_;

  void write_null_pointer(char) {
	this->spec().type_ = 0;
	this->write("(nil)");
  }

  void write_null_pointer(wchar_t) {
	this->spec().type_ = 0;
	this->write(L"(nil)");
  }

 public:
  typedef typename base::format_specs format_specs;

  /**
	\rst
	Constructs an argument formatter object.
	*buffer* is a reference to the output buffer and *spec* contains format
	specifier information for standard argument types.
	\endrst
   */
  printf_arg_formatter(internal::basic_buffer<char_type> &buffer,
					   format_specs &spec, context_type &ctx)
	: base(back_insert_range<internal::basic_buffer<char_type>>(buffer), spec),
	  context_(ctx) {}

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value, iterator>::type
	  operator()(T value) {
	// MSVC2013 fails to compile separate overloads for bool and char_type so
	// use std::is_same instead.
	if (std::is_same<T, bool>::value) {
	  format_specs &fmt_spec = this->spec();
	  if (fmt_spec.type_ != 's')
		return base::operator()(value ? 1 : 0);
	  fmt_spec.type_ = 0;
	  this->write(value != 0);
	} else if (std::is_same<T, char_type>::value) {
	  format_specs &fmt_spec = this->spec();
	  if (fmt_spec.type_ && fmt_spec.type_ != 'c')
		return (*this)(static_cast<int>(value));
	  fmt_spec.flags_ = 0;
	  fmt_spec.align_ = ALIGN_RIGHT;
	  return base::operator()(value);
	} else {
	  return base::operator()(value);
	}
	return this->out();
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value, iterator>::type
	  operator()(T value) {
	return base::operator()(value);
  }

  /** Formats a null-terminated C string. */
  iterator operator()(const char *value) {
	if (value)
	  base::operator()(value);
	else if (this->spec().type_ == 'p')
	  write_null_pointer(char_type());
	else
	  this->write("(null)");
	return this->out();
  }

  /** Formats a null-terminated wide C string. */
  iterator operator()(const wchar_t *value) {
	if (value)
	  base::operator()(value);
	else if (this->spec().type_ == 'p')
	  write_null_pointer(char_type());
	else
	  this->write(L"(null)");
	return this->out();
  }

  iterator operator()(basic_string_view<char_type> value) {
	return base::operator()(value);
  }

  iterator operator()(monostate value) {
	return base::operator()(value);
  }

  /** Formats a pointer. */
  iterator operator()(const void *value) {
	if (value)
	  return base::operator()(value);
	this->spec().type_ = 0;
	write_null_pointer(char_type());
	return this->out();
  }

  /** Formats an argument of a custom (user-defined) type. */
  iterator operator()(typename basic_format_arg<context_type>::handle handle) {
	handle.format(context_);
	return this->out();
  }
};

template <typename T>
struct printf_formatter {
  template <typename ParseContext>
  auto parse(ParseContext &ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const T &value, FormatContext &ctx) -> decltype(ctx.out()) {
	internal::format_value(internal::get_container(ctx.out()), value);
	return ctx.out();
  }
};

/** This template formats data and writes the output to a writer. */
template <typename OutputIt, typename Char, typename ArgFormatter>
class basic_printf_context :
  private internal::context_base<
	OutputIt, basic_printf_context<OutputIt, Char, ArgFormatter>, Char> {
 public:
  /** The character type for the output. */
  typedef Char char_type;

  template <typename T>
  struct formatter_type { typedef printf_formatter<T> type; };

 private:
  typedef internal::context_base<OutputIt, basic_printf_context, Char> base;
  typedef typename base::format_arg format_arg;
  typedef basic_format_specs<char_type> format_specs;
  typedef internal::null_terminating_iterator<char_type> iterator;

  void parse_flags(format_specs &spec, iterator &it);

  // Returns the argument with specified index or, if arg_index is equal
  // to the maximum unsigned value, the next argument.
  format_arg get_arg(
	  iterator it,
	  unsigned arg_index = (std::numeric_limits<unsigned>::max)());

  // Parses argument index, flags and width and returns the argument index.
  unsigned parse_header(iterator &it, format_specs &spec);

 public:
  /**
   \rst
   Constructs a ``printf_context`` object. References to the arguments and
   the writer are stored in the context object so make sure they have
   appropriate lifetimes.
   \endrst
   */
  basic_printf_context(OutputIt out, basic_string_view<char_type> format_str,
					   basic_format_args<basic_printf_context> args)
	: base(out, format_str, args) {}

  using base::parse_context;
  using base::out;
  using base::advance_to;

  /** Formats stored arguments and writes the output to the range. */
  void format();
};

template <typename OutputIt, typename Char, typename AF>
void basic_printf_context<OutputIt, Char, AF>::parse_flags(
	format_specs &spec, iterator &it) {
  for (;;) {
	switch (*it++) {
	  case '-':
		spec.align_ = ALIGN_LEFT;
		break;
	  case '+':
		spec.flags_ |= SIGN_FLAG | PLUS_FLAG;
		break;
	  case '0':
		spec.fill_ = '0';
		break;
	  case ' ':
		spec.flags_ |= SIGN_FLAG;
		break;
	  case '#':
		spec.flags_ |= HASH_FLAG;
		break;
	  default:
		--it;
		return;
	}
  }
}

template <typename OutputIt, typename Char, typename AF>
typename basic_printf_context<OutputIt, Char, AF>::format_arg
  basic_printf_context<OutputIt, Char, AF>::get_arg(
	iterator it, unsigned arg_index) {
  (void)it;
  if (arg_index == std::numeric_limits<unsigned>::max())
	return this->do_get_arg(this->parse_context().next_arg_id());
  return base::get_arg(arg_index - 1);
}

template <typename OutputIt, typename Char, typename AF>
unsigned basic_printf_context<OutputIt, Char, AF>::parse_header(
  iterator &it, format_specs &spec) {
  unsigned arg_index = std::numeric_limits<unsigned>::max();
  char_type c = *it;
  if (c >= '0' && c <= '9') {
	// Parse an argument index (if followed by '$') or a width possibly
	// preceded with '0' flag(s).
	internal::error_handler eh;
	unsigned value = parse_nonnegative_int(it, eh);
	if (*it == '$') {  // value is an argument index
	  ++it;
	  arg_index = value;
	} else {
	  if (c == '0')
		spec.fill_ = '0';
	  if (value != 0) {
		// Nonzero value means that we parsed width and don't need to
		// parse it or flags again, so return now.
		spec.width_ = value;
		return arg_index;
	  }
	}
  }
  parse_flags(spec, it);
  // Parse width.
  if (*it >= '0' && *it <= '9') {
	internal::error_handler eh;
	spec.width_ = parse_nonnegative_int(it, eh);
  } else if (*it == '*') {
	++it;
	spec.width_ =
		visit(internal::printf_width_handler<char_type>(spec), get_arg(it));
  }
  return arg_index;
}

template <typename OutputIt, typename Char, typename AF>
void basic_printf_context<OutputIt, Char, AF>::format() {
  auto &buffer = internal::get_container(this->out());
  auto start = iterator(this->parse_context());
  auto it = start;
  using internal::pointer_from;
  while (*it) {
	char_type c = *it++;
	if (c != '%') continue;
	if (*it == c) {
	  buffer.append(pointer_from(start), pointer_from(it));
	  start = ++it;
	  continue;
	}
	buffer.append(pointer_from(start), pointer_from(it) - 1);

	format_specs spec;
	spec.align_ = ALIGN_RIGHT;

	// Parse argument index, flags and width.
	unsigned arg_index = parse_header(it, spec);

	// Parse precision.
	if (*it == '.') {
	  ++it;
	  if ('0' <= *it && *it <= '9') {
		internal::error_handler eh;
		spec.precision_ = static_cast<int>(parse_nonnegative_int(it, eh));
	  } else if (*it == '*') {
		++it;
		spec.precision_ =
			visit(internal::printf_precision_handler(), get_arg(it));
	  } else {
		spec.precision_ = 0;
	  }
	}

	format_arg arg = get_arg(it, arg_index);
	if (spec.flag(HASH_FLAG) && visit(internal::is_zero_int(), arg))
	  spec.flags_ &= ~internal::to_unsigned<int>(HASH_FLAG);
	if (spec.fill_ == '0') {
	  if (arg.is_arithmetic())
		spec.align_ = ALIGN_NUMERIC;
	  else
		spec.fill_ = ' ';  // Ignore '0' flag for non-numeric types.
	}

	// Parse length and convert the argument to the required type.
	using internal::convert_arg;
	switch (*it++) {
	case 'h':
	  if (*it == 'h')
		convert_arg<signed char>(arg, *++it);
	  else
		convert_arg<short>(arg, *it);
	  break;
	case 'l':
	  if (*it == 'l')
		convert_arg<long long>(arg, *++it);
	  else
		convert_arg<long>(arg, *it);
	  break;
	case 'j':
	  convert_arg<intmax_t>(arg, *it);
	  break;
	case 'z':
	  convert_arg<std::size_t>(arg, *it);
	  break;
	case 't':
	  convert_arg<std::ptrdiff_t>(arg, *it);
	  break;
	case 'L':
	  // printf produces garbage when 'L' is omitted for long double, no
	  // need to do the same.
	  break;
	default:
	  --it;
	  convert_arg<void>(arg, *it);
	}

	// Parse type.
	if (!*it)
	  FMT_THROW(format_error("invalid format string"));
	spec.type_ = static_cast<char>(*it++);
	if (arg.is_integral()) {
	  // Normalize type.
	  switch (spec.type_) {
	  case 'i': case 'u':
		spec.type_ = 'd';
		break;
	  case 'c':
		// TODO: handle wchar_t better?
		visit(internal::char_converter<basic_printf_context>(arg), arg);
		break;
	  }
	}

	start = it;

	// Format argument.
	visit(AF(buffer, spec, *this), arg);
  }
  buffer.append(pointer_from(start), pointer_from(it));
}

template <typename Char, typename Context>
void printf(internal::basic_buffer<Char> &buf, basic_string_view<Char> format,
			basic_format_args<Context> args) {
  Context(std::back_inserter(buf), format, args).format();
}

template <typename Buffer>
struct printf_context {
  typedef basic_printf_context<
	std::back_insert_iterator<Buffer>, typename Buffer::value_type> type;
};

template <typename ...Args>
inline format_arg_store<printf_context<internal::buffer>::type, Args...>
	make_printf_args(const Args & ... args) {
  return format_arg_store<printf_context<internal::buffer>::type, Args...>(
	  args...);
}
typedef basic_format_args<printf_context<internal::buffer>::type> printf_args;
typedef basic_format_args<printf_context<internal::wbuffer>::type> wprintf_args;

inline std::string vsprintf(string_view format, printf_args args) {
  memory_buffer buffer;
  printf(buffer, format, args);
  return to_string(buffer);
}

/**
  \rst
  Formats arguments and returns the result as a string.

  **Example**::

	std::string message = fmt::sprintf("The answer is %d", 42);
  \endrst
*/
template <typename... Args>
inline std::string sprintf(string_view format_str, const Args & ... args) {
  return vsprintf(format_str,
	fmt::make_format_args<typename printf_context<internal::buffer>::type>(args...));
}

inline std::wstring vsprintf(wstring_view format, wprintf_args args) {
  wmemory_buffer buffer;
  printf(buffer, format, args);
  return to_string(buffer);
}

template <typename... Args>
inline std::wstring sprintf(wstring_view format_str, const Args & ... args) {
  return vsprintf(format_str,
	fmt::make_format_args<typename printf_context<internal::wbuffer>::type>(args...));
}

template <typename Char>
inline int vfprintf(std::FILE *f, basic_string_view<Char> format,
					basic_format_args<typename printf_context<
					  internal::basic_buffer<Char>>::type> args) {
  basic_memory_buffer<Char> buffer;
  printf(buffer, format, args);
  std::size_t size = buffer.size();
  return std::fwrite(
	buffer.data(), sizeof(Char), size, f) < size ? -1 : static_cast<int>(size);
}

/**
  \rst
  Prints formatted data to the file *f*.

  **Example**::

	fmt::fprintf(stderr, "Don't %s!", "panic");
  \endrst
 */
template <typename... Args>
inline int fprintf(std::FILE *f, string_view format_str, const Args & ... args) {
  auto vargs = fmt::make_format_args<
	typename printf_context<internal::buffer>::type>(args...);
  return vfprintf<char>(f, format_str, vargs);
}

template <typename... Args>
inline int fprintf(std::FILE *f, wstring_view format_str,
				   const Args & ... args) {
  return vfprintf(f, format_str,
	fmt::make_format_args<typename printf_context<internal::wbuffer>::type>(args...));
}

inline int vprintf(string_view format, printf_args args) {
  return vfprintf(stdout, format, args);
}

inline int vprintf(wstring_view format, wprintf_args args) {
  return vfprintf(stdout, format, args);
}

/**
  \rst
  Prints formatted data to ``stdout``.

  **Example**::

	fmt::printf("Elapsed time: %.2f seconds", 1.23);
  \endrst
 */
template <typename... Args>
inline int printf(string_view format_str, const Args & ... args) {
  return vprintf(format_str,
	fmt::make_format_args<typename printf_context<internal::buffer>::type>(args...));
}

template <typename... Args>
inline int printf(wstring_view format_str, const Args & ... args) {
  return vprintf(format_str,
	fmt::make_format_args<typename printf_context<internal::wbuffer>::type>(args...));
}

inline int vfprintf(std::ostream &os, string_view format_str,
					printf_args args) {
  memory_buffer buffer;
  printf(buffer, format_str, args);
  internal::write(os, buffer);
  return static_cast<int>(buffer.size());
}

inline int vfprintf(std::wostream &os, wstring_view format_str,
					wprintf_args args) {
  wmemory_buffer buffer;
  printf(buffer, format_str, args);
  internal::write(os, buffer);
  return static_cast<int>(buffer.size());
}

/**
  \rst
  Prints formatted data to the stream *os*.

  **Example**::

	fmt::fprintf(cerr, "Don't %s!", "panic");
  \endrst
 */
template <typename... Args>
inline int fprintf(std::ostream &os, string_view format_str,
				   const Args & ... args) {
  auto vargs = fmt::make_format_args<
	typename printf_context<internal::buffer>::type>(args...);
  return vfprintf(os, format_str, vargs);
}

template <typename... Args>
inline int fprintf(std::wostream &os, wstring_view format_str,
				   const Args & ... args) {
  auto vargs = fmt::make_format_args<
	typename printf_context<internal::buffer>::type>(args...);
  return vfprintf(os, format_str, vargs);
}
FMT_END_NAMESPACE

#endif  // __DMPRINTF_H_INCLUDE__

/*** End of inlined file: dmprintf.h ***/

#endif // __DMFORMAT_H_INCLUDE__

/*** End of inlined file: dmformat.h ***/


/*** Start of inlined file: dmtime.h ***/
// Formatting library for C++ - time formatting
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

#ifndef __DMTIME_H_INCLUDE__
#define __DMTIME_H_INCLUDE__

#include <ctime>

FMT_BEGIN_NAMESPACE

namespace internal{
inline null<> localtime_r(...) { return null<>(); }
inline null<> localtime_s(...) { return null<>(); }
inline null<> gmtime_r(...) { return null<>(); }
inline null<> gmtime_s(...) { return null<>(); }
}

// Thread-safe replacement for std::localtime
inline std::tm localtime(std::time_t time) {
  struct dispatcher {
	std::time_t time_;
	std::tm tm_;

	dispatcher(std::time_t t): time_(t) {}

	bool run() {
	  using namespace fmt::internal;
	  return handle(localtime_r(&time_, &tm_));
	}

	bool handle(std::tm *tm) { return tm != FMT_NULL; }

	bool handle(internal::null<>) {
	  using namespace fmt::internal;
	  return fallback(localtime_s(&tm_, &time_));
	}

	bool fallback(int res) { return res == 0; }

	bool fallback(internal::null<>) {
	  using namespace fmt::internal;
	  std::tm *tm = std::localtime(&time_);
	  if (tm) tm_ = *tm;
	  return tm != FMT_NULL;
	}
  };
  dispatcher lt(time);
  if (lt.run())
	return lt.tm_;
  // Too big time values may be unsupported.
  FMT_THROW(format_error("time_t value out of range"));
  return std::tm();
}

// Thread-safe replacement for std::gmtime
inline std::tm gmtime(std::time_t time) {
  struct dispatcher {
	std::time_t time_;
	std::tm tm_;

	dispatcher(std::time_t t): time_(t) {}

	bool run() {
	  using namespace fmt::internal;
	  return handle(gmtime_r(&time_, &tm_));
	}

	bool handle(std::tm *tm) { return tm != FMT_NULL; }

	bool handle(internal::null<>) {
	  using namespace fmt::internal;
	  return fallback(gmtime_s(&tm_, &time_));
	}

	bool fallback(int res) { return res == 0; }

	bool fallback(internal::null<>) {
	  std::tm *tm = std::gmtime(&time_);
	  if (tm) tm_ = *tm;
	  return tm != FMT_NULL;
	}
  };
  dispatcher gt(time);
  if (gt.run())
	return gt.tm_;
  // Too big time values may be unsupported.
  FMT_THROW(format_error("time_t value out of range"));
}

namespace internal {
inline std::size_t strftime(char *str, std::size_t count, const char *format,
							const std::tm *time) {
  return std::strftime(str, count, format, time);
}

inline std::size_t strftime(wchar_t *str, std::size_t count,
							const wchar_t *format, const std::tm *time) {
  return std::wcsftime(str, count, format, time);
}
}

template <typename Char>
struct formatter<std::tm, Char> {
  template <typename ParseContext>
  auto parse(ParseContext &ctx) -> decltype(ctx.begin()) {
	auto it = internal::null_terminating_iterator<Char>(ctx);
	if (*it == ':')
	  ++it;
	auto end = it;
	while (*end && *end != '}')
	  ++end;
	tm_format.reserve(end - it + 1);
	using internal::pointer_from;
	tm_format.append(pointer_from(it), pointer_from(end));
	tm_format.push_back('\0');
	return pointer_from(end);
  }

  template <typename FormatContext>
  auto format(const std::tm &tm, FormatContext &ctx) -> decltype(ctx.out()) {
	internal::basic_buffer<Char> &buf = internal::get_container(ctx.out());
	std::size_t start = buf.size();
	for (;;) {
	  std::size_t size = buf.capacity() - start;
	  std::size_t count =
		internal::strftime(&buf[start], size, &tm_format[0], &tm);
	  if (count != 0) {
		buf.resize(start + count);
		break;
	  }
	  if (size >= tm_format.size() * 256) {
		// If the buffer is 256 times larger than the format string, assume
		// that `strftime` gives an empty result. There doesn't seem to be a
		// better way to distinguish the two cases:
		// https://github.com/fmtlib/fmt/issues/367
		break;
	  }
	  const std::size_t MIN_GROWTH = 10;
	  buf.reserve(buf.capacity() + (size > MIN_GROWTH ? size : MIN_GROWTH));
	}
	return ctx.out();
  }

  basic_memory_buffer<Char> tm_format;
};
FMT_END_NAMESPACE

#endif  // __DMTIME_H_INCLUDE__

/*** End of inlined file: dmtime.h ***/

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

/*** Start of inlined file: console_globals.h ***/
#ifndef __CONSOLE_GLOBALS_H__
#define __CONSOLE_GLOBALS_H__

#pragma once
//
// Copyright(c) 2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//


/*** Start of inlined file: null_mutex.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __NULL_MUTEX_H__
#define __NULL_MUTEX_H__

#pragma once

#include <atomic>
// null, no cost dummy "mutex" and dummy "atomic" int

namespace spdlog {
	namespace details {
		struct null_mutex
		{
			void lock() {}
			void unlock() {}
			bool try_lock()
			{
				return true;
			}
		};

		struct null_atomic_int
		{
			int value;
			null_atomic_int() = default;

			explicit null_atomic_int(int val)
				: value(val)
			{
			}

			int load(std::memory_order) const
			{
				return value;
			}

			void store(int val)
			{
				value = val;
			}
		};

	} // namespace details
} // namespace spdlog

#endif // __NULL_MUTEX_H__

/*** End of inlined file: null_mutex.h ***/

#include <cstdio>
#include <mutex>

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX // prevent windows redefining min/max
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#endif

namespace spdlog {
	namespace details {
		struct console_stdout
		{
			static std::FILE* stream()
			{
				return stdout;
			}
#ifdef _WIN32
			static HANDLE handle()
			{
				return ::GetStdHandle(STD_OUTPUT_HANDLE);
			}
#endif
		};

		struct console_stderr
		{
			static std::FILE* stream()
			{
				return stderr;
			}
#ifdef _WIN32
			static HANDLE handle()
			{
				return ::GetStdHandle(STD_ERROR_HANDLE);
			}
#endif
		};

		struct console_mutex
		{
			using mutex_t = std::mutex;
			static mutex_t& mutex()
			{
				static mutex_t s_mutex;
				return s_mutex;
			}
		};

		struct console_nullmutex
		{
			using mutex_t = null_mutex;
			static mutex_t& mutex()
			{
				static mutex_t s_mutex;
				return s_mutex;
			}
		};
	} // namespace details
} // namespace spdlog

#endif // __CONSOLE_GLOBALS_H__

/*** End of inlined file: console_globals.h ***/



/*** Start of inlined file: spdlog.h ***/
//
// Copyright(c) 2015-2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// spdlog main header file.
// see example.cpp for usage example

#ifndef SPDLOG_H
#define SPDLOG_H
#pragma once


/*** Start of inlined file: common.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __COMMON_H__
#define __COMMON_H__

#pragma once


/*** Start of inlined file: tweakme.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __TWEAKME_H__
#define __TWEAKME_H__

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Edit this file to squeeze more performance, and to customize supported
// features
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Under Linux, the much faster CLOCK_REALTIME_COARSE clock can be used.
// This clock is less accurate - can be off by dozens of millis - depending on
// the kernel HZ.
// Uncomment to use it instead of the regular clock.
//
// #define SPDLOG_CLOCK_COARSE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment if date/time logging is not needed and never appear in the log
// pattern.
// This will prevent spdlog from querying the clock on each log call.
//
// WARNING: If the log pattern contains any date/time while this flag is on, the
// result is undefined.
//          You must set new pattern(spdlog::set_pattern(..") without any
//          date/time in it
//
// #define SPDLOG_NO_DATETIME
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment if thread id logging is not needed (i.e. no %t in the log pattern).
// This will prevent spdlog from querying the thread id on each log call.
//
// WARNING: If the log pattern contains thread id (i.e, %t) while this flag is
// on, the result is undefined.
//
// #define SPDLOG_NO_THREAD_ID
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to prevent spdlog from using thread local storage.
//
// WARNING: if your program forks, UNCOMMENT this flag to prevent undefined
// thread ids in the children logs.
//
// #define SPDLOG_NO_TLS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment if logger name logging is not needed.
// This will prevent spdlog from copying the logger name on each log call.
//
// #define SPDLOG_NO_NAME
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to enable the SPDLOG_DEBUG/SPDLOG_TRACE macros.
//
// #define SPDLOG_DEBUG_ON
// #define SPDLOG_TRACE_ON
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to avoid spdlog's usage of atomic log levels
// Use only if your code never modifies a logger's log levels concurrently by
// different threads.
//
// #define SPDLOG_NO_ATOMIC_LEVELS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to enable usage of wchar_t for file names on Windows.
//
// #define SPDLOG_WCHAR_FILENAMES
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to override default eol ("\n" or "\r\n" under Linux/Windows)
//
// #define SPDLOG_EOL ";-)\n"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to use your own copy of the fmt library instead of spdlog's copy.
// In this case spdlog will try to include <fmt/format.h> so set your -I flag
// accordingly.
//
// #define SPDLOG_FMT_EXTERNAL
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to enable wchar_t support (convert to utf8)
//
// #define SPDLOG_WCHAR_TO_UTF8_SUPPORT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to prevent child processes from inheriting log file descriptors
//
// #define SPDLOG_PREVENT_CHILD_FD
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to enable message counting feature.
// Use the %i in the logger pattern to display log message sequence id.
//
// #define SPDLOG_ENABLE_MESSAGE_COUNTER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to customize level names (e.g. "MT TRACE")
//
// #define SPDLOG_LEVEL_NAMES { "MY TRACE", "MY DEBUG", "MY INFO", "MY WARNING",
// "MY ERROR", "MY CRITICAL", "OFF" }
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment to disable default logger creation.
// This might save some (very) small initialization time if no default logger is needed.
//
// #define SPDLOG_DISABLE_DEFAULT_LOGGER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment and set to compile time level with zero cost (default is INFO).
// Macros like SPDLOG_DEBUG(..), SPDLOG_INFO(..)  will expand to empty statements if not enabled
//
// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Uncomment (and change if desired) macro to use for function names.
// This is compiler dependent.
// __PRETTY_FUNCTION__ might be nicer in clang/gcc, and __FUNCTION__ in msvc.
// Defaults to __FUNCTION__ (should work on all compilers) if not defined.
//
// #define SPDLOG_FUNCTION __PRETTY_FUNCTION__
///////////////////////////////////////////////////////////////////////////////
#endif // __TWEAKME_H__

/*** End of inlined file: tweakme.h ***/

#include <atomic>
#include <chrono>
#include <functional>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <cstring>
#include <type_traits>
#include <unordered_map>

#if defined(SPDLOG_WCHAR_FILENAMES) || defined(SPDLOG_WCHAR_TO_UTF8_SUPPORT)
#include <codecvt>
#include <locale>
#endif

// visual studio upto 2013 does not support noexcept nor constexpr
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define SPDLOG_NOEXCEPT throw()
#define SPDLOG_CONSTEXPR
#else
#define SPDLOG_NOEXCEPT noexcept
#define SPDLOG_CONSTEXPR constexpr
#endif

#if defined(__GNUC__) || defined(__clang__)
#define SPDLOG_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define SPDLOG_DEPRECATED __declspec(deprecated)
#else
#define SPDLOG_DEPRECATED
#endif

// disable thread local on msvc 2013
#ifndef SPDLOG_NO_TLS
#if (defined(_MSC_VER) && (_MSC_VER < 1900)) || defined(__cplusplus_winrt)
#define SPDLOG_NO_TLS 1
#endif
#endif

// Get the basename of __FILE__ (at compile time if possible)
#if FMT_HAS_FEATURE(__builtin_strrchr)
#define SPDLOG_STRRCHR(str, sep) __builtin_strrchr(str, sep)
#else
#define SPDLOG_STRRCHR(str, sep) strrchr(str, sep)
#endif //__builtin_strrchr not defined

#ifdef _WIN32
#define SPDLOG_FILE_BASENAME(file) SPDLOG_STRRCHR("\\" file, '\\') + 1
#else
#define SPDLOG_FILE_BASENAME(file) SPDLOG_STRRCHR("/" file, '/') + 1
#endif

#ifndef SPDLOG_FUNCTION
#define SPDLOG_FUNCTION __FUNCTION__
#endif

namespace spdlog {

class formatter;

namespace sinks {
class sink;
}

using log_clock = std::chrono::system_clock;
using sink_ptr = std::shared_ptr<sinks::sink>;
using sinks_init_list = std::initializer_list<sink_ptr>;
using log_err_handler = std::function<void(const std::string &err_msg)>;

// string_view type - either std::string_view or fmt::string_view (pre c++17)
#if defined(FMT_USE_STD_STRING_VIEW)
using string_view_t = std::string_view;
#else
using string_view_t = fmt::string_view;
#endif

#if defined(SPDLOG_NO_ATOMIC_LEVELS)
using level_t = details::null_atomic_int;
#else
using level_t = std::atomic<int>;
#endif

#define SPDLOG_LEVEL_TRACE 0
#define SPDLOG_LEVEL_DEBUG 1
#define SPDLOG_LEVEL_INFO 2
#define SPDLOG_LEVEL_WARN 3
#define SPDLOG_LEVEL_ERROR 4
#define SPDLOG_LEVEL_CRITICAL 5
#define SPDLOG_LEVEL_OFF 6

#if !defined(SPDLOG_ACTIVE_LEVEL)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif

// Log level enum
namespace level {
enum level_enum
{
	trace = SPDLOG_LEVEL_TRACE,
	debug = SPDLOG_LEVEL_DEBUG,
	info = SPDLOG_LEVEL_INFO,
	warn = SPDLOG_LEVEL_WARN,
	err = SPDLOG_LEVEL_ERROR,
	critical = SPDLOG_LEVEL_CRITICAL,
	off = SPDLOG_LEVEL_OFF,
};

#if !defined(SPDLOG_LEVEL_NAMES)
#define SPDLOG_LEVEL_NAMES                                                                                                                 \
	{                                                                                                                                      \
		"trace", "debug", "info", "warning", "error", "critical", "off"                                                                    \
	}
#endif

static string_view_t level_string_views[] SPDLOG_LEVEL_NAMES;
static const char *short_level_names[]{"T", "D", "I", "W", "E", "C", "O"};

inline string_view_t &to_string_view(spdlog::level::level_enum l) SPDLOG_NOEXCEPT
{
	return level_string_views[l];
}

inline const char *to_short_c_str(spdlog::level::level_enum l) SPDLOG_NOEXCEPT
{
	return short_level_names[l];
}

inline spdlog::level::level_enum from_str(const std::string &name) SPDLOG_NOEXCEPT
{
	int level = 0;
	for (const auto &level_str : level_string_views)
	{
		if (level_str == name)
		{
			return static_cast<level::level_enum>(level);
		}
		level++;
	}
	return level::off;
}

using level_hasher = std::hash<int>;
} // namespace level

//
// Pattern time - specific time getting to use for pattern_formatter.
// local time by default
//
enum class pattern_time_type
{
	local, // log localtime
	utc    // log utc
};

//
// Log exception
//
class spdlog_ex : public std::exception
{
public:
	explicit spdlog_ex(std::string msg)
		: msg_(std::move(msg))
	{
	}

	spdlog_ex(const std::string &msg, int last_errno)
	{
		fmt::memory_buffer outbuf;
		fmt::format_system_error(outbuf, last_errno, msg);
		msg_ = fmt::to_string(outbuf);
	}

	const char *what() const SPDLOG_NOEXCEPT override
	{
		return msg_.c_str();
	}

private:
	std::string msg_;
};

//
// wchar support for windows file names (SPDLOG_WCHAR_FILENAMES must be defined)
//
#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
using filename_t = std::wstring;
#else
using filename_t = std::string;
#endif

struct source_loc
{
	SPDLOG_CONSTEXPR source_loc()
		: filename{""}
		, line{0}
		, funcname{""}
	{
	}
	SPDLOG_CONSTEXPR source_loc(const char *filename, int line, const char *funcname)
		: filename{filename}
		, line{static_cast<uint32_t>(line)}
		, funcname{funcname}
	{
	}

	SPDLOG_CONSTEXPR bool empty() const SPDLOG_NOEXCEPT
	{
		return line == 0;
	}
	const char *filename;
	uint32_t line;
	const char *funcname;
};

namespace details {
// make_unique support for pre c++14

#if __cplusplus >= 201402L // C++14 and beyond
using std::make_unique;
#else
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args)
{
	static_assert(!std::is_array<T>::value, "arrays not supported");
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif
} // namespace details
} // namespace spdlog

#endif // __COMMON_H__

/*** End of inlined file: common.h ***/


/*** Start of inlined file: registry.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#pragma once

// Loggers registy of unique name->logger pointer
// An attempt to create a logger with an already existing name will be ignored
// If user requests a non existing logger, nullptr will be returned
// This class is thread safe


/*** Start of inlined file: periodic_worker.h ***/
//
// Copyright(c) 2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __PERIODIC_WORKER_H__
#define __PERIODIC_WORKER_H__

#pragma once

// periodic worker thread - periodically executes the given callback function.
//
// RAII over the owned thread:
//    creates the thread on construction.
//    stops and joins the thread on destruction (if the thread is executing a callback, wait for it to finish first).

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
namespace spdlog {
	namespace details {

		class periodic_worker
		{
		public:
			periodic_worker(const std::function<void()>& callback_fun, std::chrono::seconds interval)
			{
				active_ = (interval > std::chrono::seconds::zero());
				if (!active_)
				{
					return;
				}

				worker_thread_ = std::thread([this, callback_fun, interval]() {
					for (;;)
					{
						std::unique_lock<std::mutex> lock(this->mutex_);
						if (this->cv_.wait_for(lock, interval, [this] { return !this->active_; }))
						{
							return; // active_ == false, so exit this thread
						}
						callback_fun();
					}
				});
			}

			periodic_worker(const periodic_worker&) = delete;
			periodic_worker& operator=(const periodic_worker&) = delete;

			// stop the worker thread and join it
			~periodic_worker()
			{
				if (worker_thread_.joinable())
				{
					{
						std::lock_guard<std::mutex> lock(mutex_);
						active_ = false;
					}
					cv_.notify_one();
					worker_thread_.join();
				}
			}

		private:
			bool active_;
			std::thread worker_thread_;
			std::mutex mutex_;
			std::condition_variable cv_;
		};
	} // namespace details
} // namespace spdlog

#endif // __PERIODIC_WORKER_H__

/*** End of inlined file: periodic_worker.h ***/


/*** Start of inlined file: logger.h ***/
//
// Copyright(c) 2015-2108 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __LOGGER_H__
#define __LOGGER_H__

#pragma once

// Thread safe logger (except for set_pattern(..), set_formatter(..) and
// set_error_handler())
// Has name, log level, vector of std::shared sink pointers and formatter
// Upon each log write the logger:
// 1. Checks if its log level is enough to log the message and if yes:
// 2. Call the underlying sinks to do the job.
// 3. Each sink use its own private copy of a formatter to format the message
// and send to its destination.
//
// The use of private formatter per sink provides the opportunity to cache some
// formatted data,
// and support customize format per each sink.


/*** Start of inlined file: formatter.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __FORMATTER_H__
#define __FORMATTER_H__

#pragma once


/*** Start of inlined file: log_msg.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __LOG_MSG_H__
#define __LOG_MSG_H__

#pragma once


/*** Start of inlined file: os.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __OS_H__
#define __OS_H__

#pragma once

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX // prevent windows redefining min/max
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <io.h>      // _get_osfhandle and _isatty support
#include <process.h> //  _get_pid support
#include <windows.h>

#ifdef __MINGW32__
#include <share.h>
#endif

#else // unix

#include <fcntl.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/syscall.h> //Use gettid() syscall under linux to get thread id

#elif __FreeBSD__
#include <sys/thr.h> //Use thr_self() syscall under FreeBSD to get thread id
#endif

#endif // unix

#ifndef __has_feature      // Clang - feature checking macros.
#define __has_feature(x) 0 // Compatibility with non-clang compilers.
#endif

namespace spdlog {
	namespace details {
		namespace os {

			inline spdlog::log_clock::time_point now() SPDLOG_NOEXCEPT
			{

#if defined __linux__ && defined SPDLOG_CLOCK_COARSE
				timespec ts;
				::clock_gettime(CLOCK_REALTIME_COARSE, &ts);
				return std::chrono::time_point<log_clock, typename log_clock::duration>(
					std::chrono::duration_cast<typename log_clock::duration>(std::chrono::seconds(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec)));

#else
				return log_clock::now();
#endif
			}
			inline std::tm localtime(const std::time_t& time_tt) SPDLOG_NOEXCEPT
			{

#ifdef _WIN32
				std::tm tm;
				localtime_s(&tm, &time_tt);
#else
				std::tm tm;
				localtime_r(&time_tt, &tm);
#endif
				return tm;
			}

			inline std::tm localtime() SPDLOG_NOEXCEPT
			{
				std::time_t now_t = time(nullptr);
				return localtime(now_t);
			}

			inline std::tm gmtime(const std::time_t& time_tt) SPDLOG_NOEXCEPT
			{

#ifdef _WIN32
				std::tm tm;
				gmtime_s(&tm, &time_tt);
#else
				std::tm tm;
				gmtime_r(&time_tt, &tm);
#endif
				return tm;
			}

			inline std::tm gmtime() SPDLOG_NOEXCEPT
			{
				std::time_t now_t = time(nullptr);
				return gmtime(now_t);
			}

			// eol definition
#if !defined(SPDLOG_EOL)
#ifdef _WIN32
#define SPDLOG_EOL "\r\n"
#else
#define SPDLOG_EOL "\n"
#endif
#endif

			SPDLOG_CONSTEXPR static const char* default_eol = SPDLOG_EOL;

			// folder separator
#ifdef _WIN32
			SPDLOG_CONSTEXPR static const char folder_sep = '\\';
#else
			SPDLOG_CONSTEXPR static const char folder_sep = '/';
#endif

			inline void prevent_child_fd(FILE* f)
			{

#ifdef _WIN32
#if !defined(__cplusplus_winrt)
				auto file_handle = (HANDLE)_get_osfhandle(_fileno(f));
				if (!::SetHandleInformation(file_handle, HANDLE_FLAG_INHERIT, 0))
					throw spdlog_ex("SetHandleInformation failed", errno);
#endif
#else
				auto fd = fileno(f);
				if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
				{
					throw spdlog_ex("fcntl with FD_CLOEXEC failed", errno);
				}
#endif
			}

			// fopen_s on non windows for writing
			inline bool fopen_s(FILE** fp, const filename_t& filename, const filename_t& mode)
			{
#ifdef _WIN32
#ifdef SPDLOG_WCHAR_FILENAMES
				* fp = _wfsopen((filename.c_str()), mode.c_str(), _SH_DENYNO);
#else
				* fp = _fsopen((filename.c_str()), mode.c_str(), _SH_DENYNO);
#endif
#else // unix
				* fp = fopen((filename.c_str()), mode.c_str());
#endif

#ifdef SPDLOG_PREVENT_CHILD_FD
				if (*fp != nullptr)
				{
					prevent_child_fd(*fp);
				}
#endif
				return *fp == nullptr;
			}

			inline int remove(const filename_t& filename) SPDLOG_NOEXCEPT
			{
#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
				return _wremove(filename.c_str());
#else
				return std::remove(filename.c_str());
#endif
			}

			inline int rename(const filename_t& filename1, const filename_t& filename2) SPDLOG_NOEXCEPT
			{
#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
				return _wrename(filename1.c_str(), filename2.c_str());
#else
				return std::rename(filename1.c_str(), filename2.c_str());
#endif
			}

			// Return if file exists
			inline bool file_exists(const filename_t& filename) SPDLOG_NOEXCEPT
			{
#ifdef _WIN32
#ifdef SPDLOG_WCHAR_FILENAMES
				auto attribs = GetFileAttributesW(filename.c_str());
#else
				auto attribs = GetFileAttributesA(filename.c_str());
#endif
				return (attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY));
#else // common linux/unix all have the stat system call
				struct stat buffer;
				return (stat(filename.c_str(), &buffer) == 0);
#endif
			}

			// Return file size according to open FILE* object
			inline size_t filesize(FILE* f)
			{
				if (f == nullptr)
				{
					throw spdlog_ex("Failed getting file size. fd is null");
				}
#if defined(_WIN32) && !defined(__CYGWIN__)
				int fd = _fileno(f);
#if _WIN64 // 64 bits
				__int64 ret = _filelengthi64(fd);
				if (ret >= 0)
				{
					return static_cast<size_t>(ret);
				}

#else // windows 32 bits
				long ret = _filelength(fd);
				if (ret >= 0)
				{
					return static_cast<size_t>(ret);
				}
#endif

#else // unix
				int fd = fileno(f);
				// 64 bits(but not in osx or cygwin, where fstat64 is deprecated)
#if !defined(__FreeBSD__) && !defined(__APPLE__) && (defined(__x86_64__) || defined(__ppc64__)) && !defined(__CYGWIN__)
				struct stat64 st;
				if (fstat64(fd, &st) == 0)
				{
					return static_cast<size_t>(st.st_size);
				}
#else // unix 32 bits or cygwin
				struct stat st;

				if (fstat(fd, &st) == 0)
				{
					return static_cast<size_t>(st.st_size);
				}
#endif
#endif
				throw spdlog_ex("Failed getting file size from fd", errno);
			}

			// Return utc offset in minutes or throw spdlog_ex on failure
			inline int utc_minutes_offset(const std::tm& tm = details::os::localtime())
			{

#ifdef _WIN32
#if _WIN32_WINNT < _WIN32_WINNT_WS08
				TIME_ZONE_INFORMATION tzinfo;
				auto rv = GetTimeZoneInformation(&tzinfo);
#else
				DYNAMIC_TIME_ZONE_INFORMATION tzinfo;
				auto rv = GetDynamicTimeZoneInformation(&tzinfo);
#endif
				if (rv == TIME_ZONE_ID_INVALID)
					throw spdlog::spdlog_ex("Failed getting timezone info. ", errno);

				int offset = -tzinfo.Bias;
				if (tm.tm_isdst)
				{
					offset -= tzinfo.DaylightBias;
				}
				else
				{
					offset -= tzinfo.StandardBias;
				}
				return offset;
#else

#if defined(sun) || defined(__sun) || defined(_AIX)
				// 'tm_gmtoff' field is BSD extension and it's missing on SunOS/Solaris
				struct helper
				{
					static long int calculate_gmt_offset(const std::tm& localtm = details::os::localtime(), const std::tm& gmtm = details::os::gmtime())
					{
						int local_year = localtm.tm_year + (1900 - 1);
						int gmt_year = gmtm.tm_year + (1900 - 1);

						long int days = (
							// difference in day of year
							localtm.tm_yday -
							gmtm.tm_yday

							// + intervening leap days
							+ ((local_year >> 2) - (gmt_year >> 2)) - (local_year / 100 - gmt_year / 100) +
							((local_year / 100 >> 2) - (gmt_year / 100 >> 2))

							// + difference in years * 365 */
							+ (long int)(local_year - gmt_year) * 365);

						long int hours = (24 * days) + (localtm.tm_hour - gmtm.tm_hour);
						long int mins = (60 * hours) + (localtm.tm_min - gmtm.tm_min);
						long int secs = (60 * mins) + (localtm.tm_sec - gmtm.tm_sec);

						return secs;
					}
				};

				auto offset_seconds = helper::calculate_gmt_offset(tm);
#else
				auto offset_seconds = tm.tm_gmtoff;
#endif

				return static_cast<int>(offset_seconds / 60);
#endif
			}

			// Return current thread id as size_t
			// It exists because the std::this_thread::get_id() is much slower(especially
			// under VS 2013)
			inline size_t _thread_id() SPDLOG_NOEXCEPT
			{
#ifdef _WIN32
				return static_cast<size_t>(::GetCurrentThreadId());
#elif __linux__
#if defined(__ANDROID__) && defined(__ANDROID_API__) && (__ANDROID_API__ < 21)
#define SYS_gettid __NR_gettid
#endif
				return static_cast<size_t>(syscall(SYS_gettid));
#elif __FreeBSD__
				long tid;
				thr_self(&tid);
				return static_cast<size_t>(tid);
#elif __APPLE__
				uint64_t tid;
				pthread_threadid_np(nullptr, &tid);
				return static_cast<size_t>(tid);
#else // Default to standard C++11 (other Unix)
				return static_cast<size_t>(std::hash<std::thread::id>()(std::this_thread::get_id()));
#endif
			}

			// Return current thread id as size_t (from thread local storage)
			inline size_t thread_id() SPDLOG_NOEXCEPT
			{
#if defined(SPDLOG_NO_TLS)
				return _thread_id();
#else // cache thread id in tls
				static thread_local const size_t tid = _thread_id();
				return tid;
#endif
			}

			// This is avoid msvc issue in sleep_for that happens if the clock changes.
			// See https://github.com/gabime/spdlog/issues/609
			inline void sleep_for_millis(int milliseconds) SPDLOG_NOEXCEPT
			{
#if defined(_WIN32)
				::Sleep(milliseconds);
#else
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
			}

			// wchar support for windows file names (SPDLOG_WCHAR_FILENAMES must be defined)
#if defined(_WIN32) && defined(SPDLOG_WCHAR_FILENAMES)
#define SPDLOG_FILENAME_T(s) L##s
			inline std::string filename_to_str(const filename_t& filename)
			{
				std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> c;
				return c.to_bytes(filename);
			}
#else
#define SPDLOG_FILENAME_T(s) s
			inline std::string filename_to_str(const filename_t& filename)
			{
				return filename;
			}
#endif

			inline int pid()
			{

#ifdef _WIN32
				return static_cast<int>(::GetCurrentProcessId());
#else
				return static_cast<int>(::getpid());
#endif
			}

			// Determine if the terminal supports colors
			// Source: https://github.com/agauniyal/rang/
			inline bool is_color_terminal() SPDLOG_NOEXCEPT
			{
#ifdef _WIN32
				return true;
#else
				static constexpr const char* Terms[] = {
					"ansi", "color", "console", "cygwin", "gnome", "konsole", "kterm", "linux", "msys", "putty", "rxvt", "screen", "vt100", "xterm" };

				const char* env_p = std::getenv("TERM");
				if (env_p == nullptr)
				{
					return false;
				}

				static const bool result =
					std::any_of(std::begin(Terms), std::end(Terms), [&](const char* term) { return std::strstr(env_p, term) != nullptr; });
				return result;
#endif
			}

			// Detrmine if the terminal attached
			// Source: https://github.com/agauniyal/rang/
			inline bool in_terminal(FILE* file) SPDLOG_NOEXCEPT
			{

#ifdef _WIN32
				return _isatty(_fileno(file)) != 0;
#else
				return isatty(fileno(file)) != 0;
#endif
			}
			} // namespace os
				} // namespace details
			} // namespace spdlog

#endif // __OS_H__

/*** End of inlined file: os.h ***/

#include <string>
#include <utility>

namespace spdlog {
	namespace details {
		struct log_msg
		{

			log_msg(source_loc loc, const std::string* loggers_name, level::level_enum lvl, string_view_t view)
				: logger_name(loggers_name)
				, level(lvl)
#ifndef SPDLOG_NO_DATETIME
				, time(os::now())
#endif

#ifndef SPDLOG_NO_THREAD_ID
				, thread_id(os::thread_id())
#endif
				, source(loc)
				, payload(view)
			{
			}

			log_msg(const std::string* loggers_name, level::level_enum lvl, string_view_t view)
				: log_msg(source_loc{}, loggers_name, lvl, view)
			{
			}

			log_msg(const log_msg& other) = default;

			const std::string* logger_name{ nullptr };
			level::level_enum level{ level::off };
			log_clock::time_point time;
			size_t thread_id{ 0 };
			size_t msg_id{ 0 };

			// wrapping the formatted text with color (updated by pattern_formatter).
			mutable size_t color_range_start{ 0 };
			mutable size_t color_range_end{ 0 };

			source_loc source;
			const string_view_t payload;
		};
	} // namespace details
} // namespace spdlog

#endif // __LOG_MSG_H__

/*** End of inlined file: log_msg.h ***/

namespace spdlog {

	class formatter
	{
	public:
		virtual ~formatter() = default;
		virtual void format(const details::log_msg& msg, fmt::memory_buffer& dest) = 0;
		virtual std::unique_ptr<formatter> clone() const = 0;
	};
} // namespace spdlog

#endif // __FORMATTER_H__

/*** End of inlined file: formatter.h ***/


/*** Start of inlined file: sink.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __SINK_H__
#define __SINK_H__

#pragma once


/*** Start of inlined file: pattern_formatter.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __PATTERN_FORMATTER_H__
#define __PATTERN_FORMATTER_H__

#pragma once


/*** Start of inlined file: fmt_helper.h ***/
//
// Created by gabi on 6/15/18.
//
#ifndef __FMT_HELPER_H__
#define __FMT_HELPER_H__

#pragma once

#include <chrono>
#include <type_traits>

// Some fmt helpers to efficiently format and pad ints and strings
namespace spdlog {
	namespace details {
		namespace fmt_helper {

			template<size_t Buffer_Size>
			inline spdlog::string_view_t to_string_view(const fmt::basic_memory_buffer<char, Buffer_Size>& buf) SPDLOG_NOEXCEPT
			{
				return spdlog::string_view_t(buf.data(), buf.size());
			}

			template<size_t Buffer_Size1, size_t Buffer_Size2>
			inline void append_buf(const fmt::basic_memory_buffer<char, Buffer_Size1>& buf, fmt::basic_memory_buffer<char, Buffer_Size2>& dest)
			{
				auto* buf_ptr = buf.data();
				dest.append(buf_ptr, buf_ptr + buf.size());
			}

			template<size_t Buffer_Size>
			inline void append_string_view(spdlog::string_view_t view, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				auto* buf_ptr = view.data();
				if (buf_ptr != nullptr)
				{
					dest.append(buf_ptr, buf_ptr + view.size());
				}
			}

			template<typename T, size_t Buffer_Size>
			inline void append_int(T n, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				fmt::format_int i(n);
				dest.append(i.data(), i.data() + i.size());
			}

			template<typename T>
			inline unsigned count_digits(T n)
			{
				using count_type = typename std::conditional<(sizeof(T) > sizeof(uint32_t)), uint64_t, uint32_t>::type;
				return static_cast<unsigned>(fmt::internal::count_digits(static_cast<count_type>(n)));
			}

			template<size_t Buffer_Size>
			inline void pad2(int n, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				if (n > 99)
				{
					append_int(n, dest);
				}
				else if (n > 9) // 10-99
				{
					dest.push_back(static_cast<char>('0' + n / 10));
					dest.push_back(static_cast<char>('0' + n % 10));
				}
				else if (n >= 0) // 0-9
				{
					dest.push_back('0');
					dest.push_back(static_cast<char>('0' + n));
				}
				else // negatives (unlikely, but just in case, let fmt deal with it)
				{
					fmt::format_to(dest, "{:02}", n);
				}
			}

			template<typename T, size_t Buffer_Size>
			inline void pad_uint(T n, unsigned int width, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				static_assert(std::is_unsigned<T>::value, "pad_uint must get unsigned T");
				auto digits = count_digits(n);
				if (width > digits)
				{
					const char* zeroes = "0000000000000000000";
					dest.append(zeroes, zeroes + width - digits);
				}
				append_int(n, dest);
			}

			template<typename T, size_t Buffer_Size>
			inline void pad3(T n, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				pad_uint(n, 3, dest);
			}

			template<typename T, size_t Buffer_Size>
			inline void pad6(T n, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				pad_uint(n, 6, dest);
			}

			template<typename T, size_t Buffer_Size>
			inline void pad9(T n, fmt::basic_memory_buffer<char, Buffer_Size>& dest)
			{
				pad_uint(n, 9, dest);
			}

			// return fraction of a second of the given time_point.
			// e.g.
			// fraction<std::milliseconds>(tp) -> will return the millis part of the second
			template<typename ToDuration>
			inline ToDuration time_fraction(const log_clock::time_point& tp)
			{
				using std::chrono::duration_cast;
				using std::chrono::seconds;
				auto duration = tp.time_since_epoch();
				auto secs = duration_cast<seconds>(duration);
				return duration_cast<ToDuration>(duration) - duration_cast<ToDuration>(secs);
			}

		} // namespace fmt_helper
	} // namespace details
} // namespace spdlog

#endif // __FMT_HELPER_H__

/*** End of inlined file: fmt_helper.h ***/

#include <array>
#include <chrono>
#include <ctime>
#include <cctype>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace spdlog {
	namespace details {

		// padding information.
		struct padding_info
		{
			enum pad_side
			{
				left,
				right,
				center
			};

			padding_info() = default;
			padding_info(size_t width, padding_info::pad_side side)
				: width_(width)
				, side_(side)
			{
			}

			bool enabled() const
			{
				return width_ != 0;
			}
			const size_t width_ = 0;
			const pad_side side_ = left;
		};

		class scoped_pad
		{
		public:
			scoped_pad(size_t wrapped_size, padding_info& padinfo, fmt::memory_buffer& dest)
				: padinfo_(padinfo)
				, dest_(dest)
			{

				if (padinfo_.width_ <= wrapped_size)
				{
					total_pad_ = 0;
					return;
				}

				total_pad_ = padinfo.width_ - wrapped_size;
				if (padinfo_.side_ == padding_info::left)
				{
					pad_it(total_pad_);
					total_pad_ = 0;
				}
				else if (padinfo_.side_ == padding_info::center)
				{
					auto half_pad = total_pad_ / 2;
					auto reminder = total_pad_ & 1;
					pad_it(half_pad);
					total_pad_ = half_pad + reminder; // for the right side
				}
			}

			scoped_pad(spdlog::string_view_t txt, padding_info& padinfo, fmt::memory_buffer& dest)
				: scoped_pad(txt.size(), padinfo, dest)
			{
			}

			~scoped_pad()
			{
				if (total_pad_)
				{
					pad_it(total_pad_);
				}
			}

		private:
			void pad_it(size_t count)
			{
				// count = std::min(count, spaces_.size());
				assert(count <= spaces_.size());
				fmt_helper::append_string_view(string_view_t(spaces_.data(), count), dest_);
			}

			const padding_info& padinfo_;
			fmt::memory_buffer& dest_;
			size_t total_pad_;
			string_view_t spaces_{ "                                                                "
								  "                                                                ",
				128 };
		};

		class flag_formatter
		{
		public:
			explicit flag_formatter(padding_info padinfo)
				: padinfo_(padinfo)
			{
			}
			flag_formatter() = default;
			virtual ~flag_formatter() = default;
			virtual void format(const details::log_msg& msg, const std::tm& tm_time, fmt::memory_buffer& dest) = 0;

		protected:
			padding_info padinfo_;
		};

		///////////////////////////////////////////////////////////////////////
		// name & level pattern appender
		///////////////////////////////////////////////////////////////////////
		class name_formatter : public flag_formatter
		{
		public:
			explicit name_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (padinfo_.enabled())
				{
					scoped_pad p(*msg.logger_name, padinfo_, dest);
					fmt_helper::append_string_view(*msg.logger_name, dest);
				}
				else
				{
					fmt_helper::append_string_view(*msg.logger_name, dest);
				}
			}
		};

		// log level appender
		class level_formatter : public flag_formatter
		{
		public:
			explicit level_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				string_view_t& level_name = level::to_string_view(msg.level);
				if (padinfo_.enabled())
				{
					scoped_pad p(level_name, padinfo_, dest);
					fmt_helper::append_string_view(level_name, dest);
				}
				else
				{
					fmt_helper::append_string_view(level_name, dest);
				}
			}
		};

		// short log level appender
		class short_level_formatter : public flag_formatter
		{
		public:
			explicit short_level_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				string_view_t level_name{ level::to_short_c_str(msg.level) };
				scoped_pad p(level_name, padinfo_, dest);
				fmt_helper::append_string_view(level_name, dest);
			}
		};

		///////////////////////////////////////////////////////////////////////
		// Date time pattern appenders
		///////////////////////////////////////////////////////////////////////

		static const char* ampm(const tm& t)
		{
			return t.tm_hour >= 12 ? "PM" : "AM";
		}

		static int to12h(const tm& t)
		{
			return t.tm_hour > 12 ? t.tm_hour - 12 : t.tm_hour;
		}

		// Abbreviated weekday name
		static const char* days[]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		class a_formatter : public flag_formatter
		{
		public:
			explicit a_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				string_view_t field_value{ days[tm_time.tm_wday] };
				scoped_pad p(field_value, padinfo_, dest);
				fmt_helper::append_string_view(field_value, dest);
			}
		};

		// Full weekday name
		static const char* full_days[]{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		class A_formatter : public flag_formatter
		{
		public:
			explicit A_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				string_view_t field_value{ full_days[tm_time.tm_wday] };
				scoped_pad p(field_value, padinfo_, dest);
				fmt_helper::append_string_view(field_value, dest);
			}
		};

		// Abbreviated month
		static const char* months[]{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };
		class b_formatter : public flag_formatter
		{
		public:
			explicit b_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				string_view_t field_value{ months[tm_time.tm_mon] };
				scoped_pad p(field_value, padinfo_, dest);
				fmt_helper::append_string_view(field_value, dest);
			}
		};

		// Full month name
		static const char* full_months[]{
			"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		class B_formatter : public flag_formatter
		{
		public:
			explicit B_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				string_view_t field_value{ full_months[tm_time.tm_mon] };
				scoped_pad p(field_value, padinfo_, dest);
				fmt_helper::append_string_view(field_value, dest);
			}
		};

		// Date and time representation (Thu Aug 23 15:35:46 2014)
		class c_formatter final : public flag_formatter
		{
		public:
			explicit c_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 24;
				scoped_pad p(field_size, padinfo_, dest);

				fmt_helper::append_string_view(days[tm_time.tm_wday], dest);
				dest.push_back(' ');
				fmt_helper::append_string_view(months[tm_time.tm_mon], dest);
				dest.push_back(' ');
				fmt_helper::append_int(tm_time.tm_mday, dest);
				dest.push_back(' ');
				// time

				fmt_helper::pad2(tm_time.tm_hour, dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_min, dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_sec, dest);
				dest.push_back(' ');
				fmt_helper::append_int(tm_time.tm_year + 1900, dest);
			}
		};

		// year - 2 digit
		class C_formatter final : public flag_formatter
		{
		public:
			explicit C_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(tm_time.tm_year % 100, dest);
			}
		};

		// Short MM/DD/YY date, equivalent to %m/%d/%y 08/23/01
		class D_formatter final : public flag_formatter
		{
		public:
			explicit D_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 10;
				scoped_pad p(field_size, padinfo_, dest);

				fmt_helper::pad2(tm_time.tm_mon + 1, dest);
				dest.push_back('/');
				fmt_helper::pad2(tm_time.tm_mday, dest);
				dest.push_back('/');
				fmt_helper::pad2(tm_time.tm_year % 100, dest);
			}
		};

		// year - 4 digit
		class Y_formatter final : public flag_formatter
		{
		public:
			explicit Y_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 4;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::append_int(tm_time.tm_year + 1900, dest);
			}
		};

		// month 1-12
		class m_formatter final : public flag_formatter
		{
		public:
			explicit m_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(tm_time.tm_mon + 1, dest);
			}
		};

		// day of month 1-31
		class d_formatter final : public flag_formatter
		{
		public:
			explicit d_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(tm_time.tm_mday, dest);
			}
		};

		// hours in 24 format 0-23
		class H_formatter final : public flag_formatter
		{
		public:
			explicit H_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(tm_time.tm_hour, dest);
			}
		};

		// hours in 12 format 1-12
		class I_formatter final : public flag_formatter
		{
		public:
			explicit I_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(to12h(tm_time), dest);
			}
		};

		// minutes 0-59
		class M_formatter final : public flag_formatter
		{
		public:
			explicit M_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(tm_time.tm_min, dest);
			}
		};

		// seconds 0-59
		class S_formatter final : public flag_formatter
		{
		public:
			explicit S_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad2(tm_time.tm_sec, dest);
			}
		};

		// milliseconds
		class e_formatter final : public flag_formatter
		{
		public:
			explicit e_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				auto millis = fmt_helper::time_fraction<std::chrono::milliseconds>(msg.time);
				if (padinfo_.enabled())
				{
					const size_t field_size = 3;
					scoped_pad p(field_size, padinfo_, dest);
					fmt_helper::pad3(static_cast<uint32_t>(millis.count()), dest);
				}
				else
				{
					fmt_helper::pad3(static_cast<uint32_t>(millis.count()), dest);
				}
			}
		};

		// microseconds
		class f_formatter final : public flag_formatter
		{
		public:
			explicit f_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				auto micros = fmt_helper::time_fraction<std::chrono::microseconds>(msg.time);
				if (padinfo_.enabled())
				{
					const size_t field_size = 6;
					scoped_pad p(field_size, padinfo_, dest);
					fmt_helper::pad6(static_cast<size_t>(micros.count()), dest);
				}
				else
				{
					fmt_helper::pad6(static_cast<size_t>(micros.count()), dest);
				}
			}
		};

		// nanoseconds
		class F_formatter final : public flag_formatter
		{
		public:
			explicit F_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				auto ns = fmt_helper::time_fraction<std::chrono::nanoseconds>(msg.time);
				if (padinfo_.enabled())
				{
					const size_t field_size = 9;
					scoped_pad p(field_size, padinfo_, dest);
					fmt_helper::pad9(static_cast<size_t>(ns.count()), dest);
				}
				else
				{
					fmt_helper::pad9(static_cast<size_t>(ns.count()), dest);
				}
			}
		};

		// seconds since epoch
		class E_formatter final : public flag_formatter
		{
		public:
			explicit E_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 10;
				scoped_pad p(field_size, padinfo_, dest);
				auto duration = msg.time.time_since_epoch();
				auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
				fmt_helper::append_int(seconds, dest);
			}
		};

		// AM/PM
		class p_formatter final : public flag_formatter
		{
		public:
			explicit p_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 2;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::append_string_view(ampm(tm_time), dest);
			}
		};

		// 12 hour clock 02:55:02 pm
		class r_formatter final : public flag_formatter
		{
		public:
			explicit r_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 11;
				scoped_pad p(field_size, padinfo_, dest);

				fmt_helper::pad2(to12h(tm_time), dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_min, dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_sec, dest);
				dest.push_back(' ');
				fmt_helper::append_string_view(ampm(tm_time), dest);
			}
		};

		// 24-hour HH:MM time, equivalent to %H:%M
		class R_formatter final : public flag_formatter
		{
		public:
			explicit R_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 5;
				scoped_pad p(field_size, padinfo_, dest);

				fmt_helper::pad2(tm_time.tm_hour, dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_min, dest);
			}
		};

		// ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S
		class T_formatter final : public flag_formatter
		{
		public:
			explicit T_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 8;
				scoped_pad p(field_size, padinfo_, dest);

				fmt_helper::pad2(tm_time.tm_hour, dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_min, dest);
				dest.push_back(':');
				fmt_helper::pad2(tm_time.tm_sec, dest);
			}
		};

		// ISO 8601 offset from UTC in timezone (+-HH:MM)
		class z_formatter final : public flag_formatter
		{
		public:
			explicit z_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			const std::chrono::seconds cache_refresh = std::chrono::seconds(5);

			z_formatter() = default;
			z_formatter(const z_formatter&) = delete;
			z_formatter& operator=(const z_formatter&) = delete;

			void format(const details::log_msg& msg, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 6;
				scoped_pad p(field_size, padinfo_, dest);

#ifdef _WIN32
				int total_minutes = get_cached_offset(msg, tm_time);
#else
				// No need to chache under gcc,
				// it is very fast (already stored in tm.tm_gmtoff)
				(void)(msg);
				int total_minutes = os::utc_minutes_offset(tm_time);
#endif
				bool is_negative = total_minutes < 0;
				if (is_negative)
				{
					total_minutes = -total_minutes;
					dest.push_back('-');
				}
				else
				{
					dest.push_back('+');
				}

				fmt_helper::pad2(total_minutes / 60, dest); // hours
				dest.push_back(':');
				fmt_helper::pad2(total_minutes % 60, dest); // minutes
			}

		private:
			log_clock::time_point last_update_{ std::chrono::seconds(0) };
#ifdef _WIN32
			int offset_minutes_{ 0 };

			int get_cached_offset(const log_msg& msg, const std::tm& tm_time)
			{
				if (msg.time - last_update_ >= cache_refresh)
				{
					offset_minutes_ = os::utc_minutes_offset(tm_time);
					last_update_ = msg.time;
				}
				return offset_minutes_;
			}
#endif
		};

		// Thread id
		class t_formatter final : public flag_formatter
		{
		public:
			explicit t_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (padinfo_.enabled())
				{
					const auto field_size = fmt_helper::count_digits(msg.thread_id);
					scoped_pad p(field_size, padinfo_, dest);
					fmt_helper::append_int(msg.thread_id, dest);
				}
				else
				{
					fmt_helper::append_int(msg.thread_id, dest);
				}
			}
		};

		// Current pid
		class pid_formatter final : public flag_formatter
		{
		public:
			explicit pid_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg&, const std::tm&, fmt::memory_buffer& dest) override
			{
				const auto pid = static_cast<uint32_t>(details::os::pid());
				if (padinfo_.enabled())
				{
					auto field_size = fmt_helper::count_digits(pid);
					scoped_pad p(field_size, padinfo_, dest);
					fmt_helper::append_int(pid, dest);
				}
				else
				{
					fmt_helper::append_int(pid, dest);
				}
			}
		};

		// message counter formatter
		class i_formatter final : public flag_formatter
		{
		public:
			explicit i_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 6;
				scoped_pad p(field_size, padinfo_, dest);
				fmt_helper::pad6(msg.msg_id, dest);
			}
		};

		class v_formatter final : public flag_formatter
		{
		public:
			explicit v_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (padinfo_.enabled())
				{
					scoped_pad p(msg.payload, padinfo_, dest);
					fmt_helper::append_string_view(msg.payload, dest);
				}
				else
				{
					fmt_helper::append_string_view(msg.payload, dest);
				}
			}
		};

		class ch_formatter final : public flag_formatter
		{
		public:
			explicit ch_formatter(char ch)
				: ch_(ch)
			{
			}

			void format(const details::log_msg&, const std::tm&, fmt::memory_buffer& dest) override
			{
				const size_t field_size = 1;
				scoped_pad p(field_size, padinfo_, dest);
				dest.push_back(ch_);
			}

		private:
			char ch_;
		};

		// aggregate user chars to display as is
		class aggregate_formatter final : public flag_formatter
		{
		public:
			aggregate_formatter() = default;

			void add_ch(char ch)
			{
				str_ += ch;
			}
			void format(const details::log_msg&, const std::tm&, fmt::memory_buffer& dest) override
			{
				fmt_helper::append_string_view(str_, dest);
			}

		private:
			std::string str_;
		};

		// mark the color range. expect it to be in the form of "%^colored text%$"
		class color_start_formatter final : public flag_formatter
		{
		public:
			explicit color_start_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				msg.color_range_start = dest.size();
			}
		};
		class color_stop_formatter final : public flag_formatter
		{
		public:
			explicit color_stop_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				msg.color_range_end = dest.size();
			}
		};

		// print source location
		class source_location_formatter final : public flag_formatter
		{
		public:
			explicit source_location_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (msg.source.empty())
				{
					return;
				}
				if (padinfo_.enabled())
				{
					const auto text_size = std::char_traits<char>::length(msg.source.filename) + fmt_helper::count_digits(msg.source.line) + 1;
					scoped_pad p(text_size, padinfo_, dest);
					fmt_helper::append_string_view(msg.source.filename, dest);
					dest.push_back(':');
					fmt_helper::append_int(msg.source.line, dest);
				}
				else
				{
					fmt_helper::append_string_view(msg.source.filename, dest);
					dest.push_back(':');
					fmt_helper::append_int(msg.source.line, dest);
				}
			}
		};
		// print source filename
		class source_filename_formatter final : public flag_formatter
		{
		public:
			explicit source_filename_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (msg.source.empty())
				{
					return;
				}
				scoped_pad p(msg.source.filename, padinfo_, dest);
				fmt_helper::append_string_view(msg.source.filename, dest);
			}
		};

		class source_linenum_formatter final : public flag_formatter
		{
		public:
			explicit source_linenum_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (msg.source.empty())
				{
					return;
				}
				if (padinfo_.enabled())
				{
					auto field_size = fmt_helper::count_digits(msg.source.line);
					scoped_pad p(field_size, padinfo_, dest);
					fmt_helper::append_int(msg.source.line, dest);
				}
				else
				{
					fmt_helper::append_int(msg.source.line, dest);
				}
			}
		};
		// print source funcname
		class source_funcname_formatter final : public flag_formatter
		{
		public:
			explicit source_funcname_formatter(padding_info padinfo)
				: flag_formatter(padinfo){};

			void format(const details::log_msg& msg, const std::tm&, fmt::memory_buffer& dest) override
			{
				if (msg.source.empty())
				{
					return;
				}
				scoped_pad p(msg.source.funcname, padinfo_, dest);
				fmt_helper::append_string_view(msg.source.funcname, dest);
			}
		};

		// Full info formatter
		// pattern: [%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v
		class full_formatter final : public flag_formatter
		{
		public:
			explicit full_formatter(padding_info padinfo)
				: flag_formatter(padinfo)
			{
			}

			void format(const details::log_msg& msg, const std::tm& tm_time, fmt::memory_buffer& dest) override
			{
				using std::chrono::duration_cast;
				using std::chrono::milliseconds;
				using std::chrono::seconds;

#ifndef SPDLOG_NO_DATETIME

				// cache the date/time part for the next second.
				auto duration = msg.time.time_since_epoch();
				auto secs = duration_cast<seconds>(duration);

				if (cache_timestamp_ != secs || cached_datetime_.size() == 0)
				{
					cached_datetime_.clear();
					cached_datetime_.push_back('[');
					fmt_helper::append_int(tm_time.tm_year + 1900, cached_datetime_);
					cached_datetime_.push_back('-');

					fmt_helper::pad2(tm_time.tm_mon + 1, cached_datetime_);
					cached_datetime_.push_back('-');

					fmt_helper::pad2(tm_time.tm_mday, cached_datetime_);
					cached_datetime_.push_back(' ');

					fmt_helper::pad2(tm_time.tm_hour, cached_datetime_);
					cached_datetime_.push_back(':');

					fmt_helper::pad2(tm_time.tm_min, cached_datetime_);
					cached_datetime_.push_back(':');

					fmt_helper::pad2(tm_time.tm_sec, cached_datetime_);
					cached_datetime_.push_back('.');

					cache_timestamp_ = secs;
				}
				fmt_helper::append_buf(cached_datetime_, dest);

				auto millis = fmt_helper::time_fraction<milliseconds>(msg.time);
				fmt_helper::pad3(static_cast<uint32_t>(millis.count()), dest);
				dest.push_back(']');
				dest.push_back(' ');

#else // no datetime needed
				(void)tm_time;
#endif

#ifndef SPDLOG_NO_NAME
				if (!msg.logger_name->empty())
				{
					dest.push_back('[');
					// fmt_helper::append_str(*msg.logger_name, dest);
					fmt_helper::append_string_view(*msg.logger_name, dest);
					dest.push_back(']');
					dest.push_back(' ');
				}
#endif

				dest.push_back('[');
				// wrap the level name with color
				msg.color_range_start = dest.size();
				// fmt_helper::append_string_view(level::to_c_str(msg.level), dest);
				fmt_helper::append_string_view(level::to_string_view(msg.level), dest);
				msg.color_range_end = dest.size();
				dest.push_back(']');
				dest.push_back(' ');

				// add source location if present
				if (!msg.source.empty())
				{
					dest.push_back('[');
					fmt_helper::append_string_view(msg.source.filename, dest);
					dest.push_back(':');
					fmt_helper::append_int(msg.source.line, dest);
					dest.push_back(']');
					dest.push_back(' ');
				}
				// fmt_helper::append_string_view(msg.msg(), dest);
				fmt_helper::append_string_view(msg.payload, dest);
			}

		private:
			std::chrono::seconds cache_timestamp_{ 0 };
			fmt::basic_memory_buffer<char, 128> cached_datetime_;
		};

	} // namespace details

	class pattern_formatter final : public formatter
	{
	public:
		explicit pattern_formatter(
			std::string pattern, pattern_time_type time_type = pattern_time_type::local, std::string eol = spdlog::details::os::default_eol)
			: pattern_(std::move(pattern))
			, eol_(std::move(eol))
			, pattern_time_type_(time_type)
			, last_log_secs_(0)
		{
			std::memset(&cached_tm_, 0, sizeof(cached_tm_));
			compile_pattern_(pattern_);
		}

		// use by default full formatter for if pattern is not given
		explicit pattern_formatter(pattern_time_type time_type = pattern_time_type::local, std::string eol = spdlog::details::os::default_eol)
			: pattern_("%+")
			, eol_(std::move(eol))
			, pattern_time_type_(time_type)
			, last_log_secs_(0)
		{
			std::memset(&cached_tm_, 0, sizeof(cached_tm_));
			formatters_.push_back(details::make_unique<details::full_formatter>(details::padding_info{}));
		}

		pattern_formatter(const pattern_formatter& other) = delete;
		pattern_formatter& operator=(const pattern_formatter& other) = delete;

		std::unique_ptr<formatter> clone() const override
		{
			return details::make_unique<pattern_formatter>(pattern_, pattern_time_type_, eol_);
		}

		void format(const details::log_msg& msg, fmt::memory_buffer& dest) override
		{
#ifndef SPDLOG_NO_DATETIME
			auto secs = std::chrono::duration_cast<std::chrono::seconds>(msg.time.time_since_epoch());
			if (secs != last_log_secs_)
			{
				cached_tm_ = get_time_(msg);
				last_log_secs_ = secs;
			}
#endif
			for (auto& f : formatters_)
			{
				f->format(msg, cached_tm_, dest);
			}
			// write eol
			details::fmt_helper::append_string_view(eol_, dest);
		}

	private:
		std::string pattern_;
		std::string eol_;
		pattern_time_type pattern_time_type_;
		std::tm cached_tm_;
		std::chrono::seconds last_log_secs_;

		std::vector<std::unique_ptr<details::flag_formatter>> formatters_;

		std::tm get_time_(const details::log_msg& msg)
		{
			if (pattern_time_type_ == pattern_time_type::local)
			{
				return details::os::localtime(log_clock::to_time_t(msg.time));
			}
			return details::os::gmtime(log_clock::to_time_t(msg.time));
		}

		void handle_flag_(char flag, details::padding_info padding)
		{
			switch (flag)
			{

			case ('+'): // default formatter
				formatters_.push_back(details::make_unique<details::full_formatter>(padding));
				break;

			case 'n': // logger name
				formatters_.push_back(details::make_unique<details::name_formatter>(padding));
				break;

			case 'l': // level
				formatters_.push_back(details::make_unique<details::level_formatter>(padding));
				break;

			case 'L': // short level
				formatters_.push_back(details::make_unique<details::short_level_formatter>(padding));
				break;

			case ('t'): // thread id
				formatters_.push_back(details::make_unique<details::t_formatter>(padding));
				break;

			case ('v'): // the message text
				formatters_.push_back(details::make_unique<details::v_formatter>(padding));
				break;

			case ('a'): // weekday
				formatters_.push_back(details::make_unique<details::a_formatter>(padding));
				break;

			case ('A'): // short weekday
				formatters_.push_back(details::make_unique<details::A_formatter>(padding));
				break;

			case ('b'):
			case ('h'): // month
				formatters_.push_back(details::make_unique<details::b_formatter>(padding));
				break;

			case ('B'): // short month
				formatters_.push_back(details::make_unique<details::B_formatter>(padding));
				break;

			case ('c'): // datetime
				formatters_.push_back(details::make_unique<details::c_formatter>(padding));
				break;

			case ('C'): // year 2 digits
				formatters_.push_back(details::make_unique<details::C_formatter>(padding));
				break;

			case ('Y'): // year 4 digits
				formatters_.push_back(details::make_unique<details::Y_formatter>(padding));
				break;

			case ('D'):
			case ('x'): // datetime MM/DD/YY
				formatters_.push_back(details::make_unique<details::D_formatter>(padding));
				break;

			case ('m'): // month 1-12
				formatters_.push_back(details::make_unique<details::m_formatter>(padding));
				break;

			case ('d'): // day of month 1-31
				formatters_.push_back(details::make_unique<details::d_formatter>(padding));
				break;

			case ('H'): // hours 24
				formatters_.push_back(details::make_unique<details::H_formatter>(padding));
				break;

			case ('I'): // hours 12
				formatters_.push_back(details::make_unique<details::I_formatter>(padding));
				break;

			case ('M'): // minutes
				formatters_.push_back(details::make_unique<details::M_formatter>(padding));
				break;

			case ('S'): // seconds
				formatters_.push_back(details::make_unique<details::S_formatter>(padding));
				break;

			case ('e'): // milliseconds
				formatters_.push_back(details::make_unique<details::e_formatter>(padding));
				break;

			case ('f'): // microseconds
				formatters_.push_back(details::make_unique<details::f_formatter>(padding));
				break;

			case ('F'): // nanoseconds
				formatters_.push_back(details::make_unique<details::F_formatter>(padding));
				break;

			case ('E'): // seconds since epoch
				formatters_.push_back(details::make_unique<details::E_formatter>(padding));
				break;

			case ('p'): // am/pm
				formatters_.push_back(details::make_unique<details::p_formatter>(padding));
				break;

			case ('r'): // 12 hour clock 02:55:02 pm
				formatters_.push_back(details::make_unique<details::r_formatter>(padding));
				break;

			case ('R'): // 24-hour HH:MM time
				formatters_.push_back(details::make_unique<details::R_formatter>(padding));
				break;

			case ('T'):
			case ('X'): // ISO 8601 time format (HH:MM:SS)
				formatters_.push_back(details::make_unique<details::T_formatter>(padding));
				break;

			case ('z'): // timezone
				formatters_.push_back(details::make_unique<details::z_formatter>(padding));
				break;

			case ('P'): // pid
				formatters_.push_back(details::make_unique<details::pid_formatter>(padding));
				break;

#ifdef SPDLOG_ENABLE_MESSAGE_COUNTER
			case ('i'):
				formatters_.push_back(details::make_unique<details::i_formatter>(padding));
				break;
#endif
			case ('^'): // color range start
				formatters_.push_back(details::make_unique<details::color_start_formatter>(padding));
				break;

			case ('$'): // color range end
				formatters_.push_back(details::make_unique<details::color_stop_formatter>(padding));
				break;

			case ('@'): // source location (filename:filenumber)
				formatters_.push_back(details::make_unique<details::source_location_formatter>(padding));
				break;

			case ('s'): // source filename
				formatters_.push_back(details::make_unique<details::source_filename_formatter>(padding));
				break;

			case ('#'): // source line number
				formatters_.push_back(details::make_unique<details::source_linenum_formatter>(padding));
				break;

			case ('!'): // source funcname
				formatters_.push_back(details::make_unique<details::source_funcname_formatter>(padding));
				break;

			case ('%'): // % char
				formatters_.push_back(details::make_unique<details::ch_formatter>('%'));
				break;

			default: // Unknown flag appears as is
				auto unknown_flag = details::make_unique<details::aggregate_formatter>();
				unknown_flag->add_ch('%');
				unknown_flag->add_ch(flag);
				formatters_.push_back((std::move(unknown_flag)));
				break;
			}
		}

		// Extract given pad spec (e.g. %8X)
		// Advance the given it pass the end of the padding spec found (if any)
		// Return padding.
		details::padding_info handle_padspec_(std::string::const_iterator& it, std::string::const_iterator end)
		{
			using details::padding_info;
			using details::scoped_pad;
			const size_t max_width = 128;
			if (it == end)
			{
				return padding_info{};
			}

			padding_info::pad_side side;
			switch (*it)
			{
			case '-':
				side = padding_info::right;
				++it;
				break;
			case '=':
				side = padding_info::center;
				++it;
				break;
			default:
				side = details::padding_info::left;
				break;
			}

			if (it == end || !std::isdigit(static_cast<unsigned char>(*it)))
			{
				return padding_info{ 0, side };
			}

			auto width = static_cast<size_t>(*it - '0');
			for (++it; it != end && std::isdigit(static_cast<unsigned char>(*it)); ++it)
			{
				auto digit = static_cast<size_t>(*it - '0');
				width = width * 10 + digit;
			}
			return details::padding_info{ std::min<size_t>(width, max_width), side };
		}

		void compile_pattern_(const std::string& pattern)
		{
			auto end = pattern.end();
			std::unique_ptr<details::aggregate_formatter> user_chars;
			formatters_.clear();
			for (auto it = pattern.begin(); it != end; ++it)
			{
				if (*it == '%')
				{
					if (user_chars) // append user chars found so far
					{
						formatters_.push_back(std::move(user_chars));
					}

					auto padding = handle_padspec_(++it, end);

					if (it != end)
					{
						handle_flag_(*it, padding);
					}
					else
					{
						break;
					}
				}
				else // chars not following the % sign should be displayed as is
				{
					if (!user_chars)
					{
						user_chars = details::make_unique<details::aggregate_formatter>();
					}
					user_chars->add_ch(*it);
				}
			}
			if (user_chars) // append raw chars found so far
			{
				formatters_.push_back(std::move(user_chars));
			}
		}
	};
} // namespace spdlog

#endif // __PATTERN_FORMATTER_H__

/*** End of inlined file: pattern_formatter.h ***/

namespace spdlog {
	namespace sinks {
		class sink
		{
		public:
			sink()
				: level_(level::trace)
				, formatter_(new pattern_formatter())
			{
			}

			explicit sink(std::unique_ptr<spdlog::pattern_formatter> formatter)
				: level_(level::trace)
				, formatter_(std::move(formatter))
			{
			}

			virtual ~sink() = default;
			virtual void log(const details::log_msg& msg) = 0;
			virtual void flush() = 0;
			virtual void set_pattern(const std::string& pattern) = 0;
			virtual void set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) = 0;

			bool should_log(level::level_enum msg_level) const
			{
				return msg_level >= level_.load(std::memory_order_relaxed);
			}

			void set_level(level::level_enum log_level)
			{
				level_.store(log_level);
			}

			level::level_enum level() const
			{
				return static_cast<spdlog::level::level_enum>(level_.load(std::memory_order_relaxed));
			}

		protected:
			// sink log level - default is all
			level_t level_;

			// sink formatter - default is full format
			std::unique_ptr<spdlog::formatter> formatter_;
		};

	} // namespace sinks
} // namespace spdlog

#endif // __SINK_H__

/*** End of inlined file: sink.h ***/

#include <memory>
#include <string>
#include <vector>

namespace spdlog {

	class logger
	{
	public:
		logger(std::string name, sink_ptr single_sink);
		logger(std::string name, sinks_init_list sinks);

		template<typename It>
		logger(std::string name, It begin, It end);

		virtual ~logger();

		logger(const logger&) = delete;
		logger& operator=(const logger&) = delete;

		template<typename... Args>
		void log(level::level_enum lvl, const char* fmt, const Args &... args);

		template<typename... Args>
		void log(source_loc loc, level::level_enum lvl, const char* fmt, const Args &... args);

		void log(level::level_enum lvl, const char* msg);

		void log(source_loc loc, level::level_enum lvl, const char* msg);

		template<typename... Args>
		void trace(const char* fmt, const Args &... args);

		template<typename... Args>
		void debug(const char* fmt, const Args &... args);

		template<typename... Args>
		void info(const char* fmt, const Args &... args);

		template<typename... Args>
		void warn(const char* fmt, const Args &... args);

		template<typename... Args>
		void error(const char* fmt, const Args &... args);

		template<typename... Args>
		void critical(const char* fmt, const Args &... args);

#ifdef SPDLOG_WCHAR_TO_UTF8_SUPPORT
#ifndef _WIN32
#error SPDLOG_WCHAR_TO_UTF8_SUPPORT only supported on windows
#else
		template<typename... Args>
		void log(level::level_enum lvl, const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void log(source_loc source, level::level_enum lvl, const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void trace(const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void debug(const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void info(const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void warn(const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void error(const wchar_t* fmt, const Args &... args);

		template<typename... Args>
		void critical(const wchar_t* fmt, const Args &... args);
#endif // _WIN32
#endif // SPDLOG_WCHAR_TO_UTF8_SUPPORT

		// T can be statically converted to string_view
		template<class T, typename std::enable_if<std::is_convertible<T, spdlog::string_view_t>::value, T>::type* = nullptr>
		void log(level::level_enum lvl, const T&);

		// T can be statically converted to string_view
		template<class T, typename std::enable_if<std::is_convertible<T, spdlog::string_view_t>::value, T>::type* = nullptr>
		void log(source_loc loc, level::level_enum lvl, const T&);

		// T cannot be statically converted to string_view
		template<class T, typename std::enable_if<!std::is_convertible<T, spdlog::string_view_t>::value, T>::type* = nullptr>
		void log(level::level_enum lvl, const T&);

		// T cannot be statically converted to string_view
		template<class T, typename std::enable_if<!std::is_convertible<T, spdlog::string_view_t>::value, T>::type* = nullptr>
		void log(source_loc loc, level::level_enum lvl, const T&);

		template<typename T>
		void trace(const T& msg);

		template<typename T>
		void debug(const T& msg);

		template<typename T>
		void info(const T& msg);

		template<typename T>
		void warn(const T& msg);

		template<typename T>
		void error(const T& msg);

		template<typename T>
		void critical(const T& msg);

		bool should_log(level::level_enum msg_level) const;
		void set_level(level::level_enum log_level);

		static level::level_enum default_level();
		level::level_enum level() const;
		const std::string& name() const;

		// set formatting for the sinks in this logger.
		// each sink will get a seperate instance of the formatter object.
		void set_formatter(std::unique_ptr<formatter> formatter);
		void set_pattern(std::string pattern, pattern_time_type time_type = pattern_time_type::local);

		// flush functions
		void flush();
		void flush_on(level::level_enum log_level);
		level::level_enum flush_level() const;

		// sinks
		const std::vector<sink_ptr>& sinks() const;
		std::vector<sink_ptr>& sinks();

		// error handler
		void set_error_handler(log_err_handler err_handler);
		log_err_handler error_handler() const;

		// create new logger with same sinks and configuration.
		virtual std::shared_ptr<logger> clone(std::string logger_name);

	protected:
		virtual void sink_it_(details::log_msg& msg);
		virtual void flush_();

		bool should_flush_(const details::log_msg& msg);

		// default error handler.
		// print the error to stderr with the max rate of 1 message/minute.
		void default_err_handler_(const std::string& msg);

		// increment the message count (only if defined(SPDLOG_ENABLE_MESSAGE_COUNTER))
		void incr_msg_counter_(details::log_msg& msg);

		const std::string name_;
		std::vector<sink_ptr> sinks_;
		spdlog::level_t level_{ spdlog::logger::default_level() };
		spdlog::level_t flush_level_{ level::off };
		log_err_handler err_handler_{ [this](const std::string& msg) { this->default_err_handler_(msg); } };
		std::atomic<time_t> last_err_time_{ 0 };
		std::atomic<size_t> msg_counter_{ 1 };
	};
} // namespace spdlog


/*** Start of inlined file: logger_impl.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __LOGGER_IMPL_H__
#define __LOGGER_IMPL_H__

#pragma once

#include <memory>
#include <string>

#define SPDLOG_CATCH_AND_HANDLE                                                                                                            \
	catch (const std::exception &ex)                                                                                                       \
	{                                                                                                                                      \
		err_handler_(ex.what());                                                                                                           \
	}                                                                                                                                      \
	catch (...)                                                                                                                            \
	{                                                                                                                                      \
		err_handler_("Unknown exception in logger");                                                                                       \
	}

// create logger with given name, sinks and the default pattern formatter
// all other ctors will call this one
template<typename It>
inline spdlog::logger::logger(std::string logger_name, It begin, It end)
	: name_(std::move(logger_name))
	, sinks_(begin, end)
{
}

// ctor with sinks as init list
inline spdlog::logger::logger(std::string logger_name, sinks_init_list sinks_list)
	: logger(std::move(logger_name), sinks_list.begin(), sinks_list.end())
{
}

// ctor with single sink
inline spdlog::logger::logger(std::string logger_name, spdlog::sink_ptr single_sink)
	: logger(std::move(logger_name), { std::move(single_sink) })
{
}

inline spdlog::logger::~logger() = default;

inline void spdlog::logger::set_formatter(std::unique_ptr<spdlog::formatter> f)
{
	for (auto& sink : sinks_)
	{
		sink->set_formatter(f->clone());
	}
}

inline void spdlog::logger::set_pattern(std::string pattern, pattern_time_type time_type)
{
	auto new_formatter = details::make_unique<spdlog::pattern_formatter>(std::move(pattern), time_type);
	set_formatter(std::move(new_formatter));
}

template<typename... Args>
inline void spdlog::logger::log(source_loc source, level::level_enum lvl, const char* fmt, const Args &... args)
{
	if (!should_log(lvl))
	{
		return;
	}

	try
	{
		using details::fmt_helper::to_string_view;
		fmt::memory_buffer buf;
		fmt::format_to(buf, fmt, args...);
		details::log_msg log_msg(source, &name_, lvl, to_string_view(buf));
		sink_it_(log_msg);
	}
	SPDLOG_CATCH_AND_HANDLE
}

template<typename... Args>
inline void spdlog::logger::log(level::level_enum lvl, const char* fmt, const Args &... args)
{
	log(source_loc{}, lvl, fmt, args...);
}

inline void spdlog::logger::log(source_loc source, level::level_enum lvl, const char* msg)
{
	if (!should_log(lvl))
	{
		return;
	}

	try
	{
		details::log_msg log_msg(source, &name_, lvl, spdlog::string_view_t(msg));
		sink_it_(log_msg);
	}
	SPDLOG_CATCH_AND_HANDLE
}

inline void spdlog::logger::log(level::level_enum lvl, const char* msg)
{
	log(source_loc{}, lvl, msg);
}

template<class T, typename std::enable_if<std::is_convertible<T, spdlog::string_view_t>::value, T>::type*>
inline void spdlog::logger::log(source_loc source, level::level_enum lvl, const T & msg)
{
	if (!should_log(lvl))
	{
		return;
	}
	try
	{
		details::log_msg log_msg(source, &name_, lvl, msg);
		sink_it_(log_msg);
	}
	SPDLOG_CATCH_AND_HANDLE
}

template<class T, typename std::enable_if<std::is_convertible<T, spdlog::string_view_t>::value, T>::type*>
inline void spdlog::logger::log(level::level_enum lvl, const T & msg)
{
	log(source_loc{}, lvl, msg);
}

template<class T, typename std::enable_if<!std::is_convertible<T, spdlog::string_view_t>::value, T>::type*>
inline void spdlog::logger::log(source_loc source, level::level_enum lvl, const T & msg)
{
	if (!should_log(lvl))
	{
		return;
	}
	try
	{
		using details::fmt_helper::to_string_view;
		fmt::memory_buffer buf;
		fmt::format_to(buf, "{}", msg);
		details::log_msg log_msg(source, &name_, lvl, to_string_view(buf));
		sink_it_(log_msg);
	}
	SPDLOG_CATCH_AND_HANDLE
}

template<class T, typename std::enable_if<!std::is_convertible<T, spdlog::string_view_t>::value, T>::type*>
inline void spdlog::logger::log(level::level_enum lvl, const T & msg)
{
	log(source_loc{}, lvl, msg);
}

template<typename... Args>
inline void spdlog::logger::trace(const char* fmt, const Args &... args)
{
	log(level::trace, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::debug(const char* fmt, const Args &... args)
{
	log(level::debug, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::info(const char* fmt, const Args &... args)
{
	log(level::info, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::warn(const char* fmt, const Args &... args)
{
	log(level::warn, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::error(const char* fmt, const Args &... args)
{
	log(level::err, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::critical(const char* fmt, const Args &... args)
{
	log(level::critical, fmt, args...);
}

template<typename T>
inline void spdlog::logger::trace(const T & msg)
{
	log(level::trace, msg);
}

template<typename T>
inline void spdlog::logger::debug(const T & msg)
{
	log(level::debug, msg);
}

template<typename T>
inline void spdlog::logger::info(const T & msg)
{
	log(level::info, msg);
}

template<typename T>
inline void spdlog::logger::warn(const T & msg)
{
	log(level::warn, msg);
}

template<typename T>
inline void spdlog::logger::error(const T & msg)
{
	log(level::err, msg);
}

template<typename T>
inline void spdlog::logger::critical(const T & msg)
{
	log(level::critical, msg);
}

#ifdef SPDLOG_WCHAR_TO_UTF8_SUPPORT

inline void wbuf_to_utf8buf(const fmt::wmemory_buffer & wbuf, fmt::memory_buffer & target)
{
	int wbuf_size = static_cast<int>(wbuf.size());
	if (wbuf_size == 0)
	{
		return;
	}

	auto result_size = ::WideCharToMultiByte(CP_UTF8, 0, wbuf.data(), wbuf_size, NULL, 0, NULL, NULL);

	if (result_size > 0)
	{
		target.resize(result_size);
		::WideCharToMultiByte(CP_UTF8, 0, wbuf.data(), wbuf_size, &target.data()[0], result_size, NULL, NULL);
	}
	else
	{
		throw spdlog::spdlog_ex(fmt::format("WideCharToMultiByte failed. Last error: {}", ::GetLastError()));
	}
}

template<typename... Args>
inline void spdlog::logger::log(source_loc source, level::level_enum lvl, const wchar_t* fmt, const Args &... args)
{
	if (!should_log(lvl))
	{
		return;
	}

	try
	{
		// format to wmemory_buffer and convert to utf8
		using details::fmt_helper::to_string_view;
		fmt::wmemory_buffer wbuf;
		fmt::format_to(wbuf, fmt, args...);
		fmt::memory_buffer buf;
		wbuf_to_utf8buf(wbuf, buf);
		details::log_msg log_msg(source, &name_, lvl, to_string_view(buf));
		sink_it_(log_msg);
	}
	SPDLOG_CATCH_AND_HANDLE
}

template<typename... Args>
inline void spdlog::logger::log(level::level_enum lvl, const wchar_t* fmt, const Args &... args)
{
	log(source_loc{}, lvl, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::trace(const wchar_t* fmt, const Args &... args)
{
	log(level::trace, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::debug(const wchar_t* fmt, const Args &... args)
{
	log(level::debug, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::info(const wchar_t* fmt, const Args &... args)
{
	log(level::info, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::warn(const wchar_t* fmt, const Args &... args)
{
	log(level::warn, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::error(const wchar_t* fmt, const Args &... args)
{
	log(level::err, fmt, args...);
}

template<typename... Args>
inline void spdlog::logger::critical(const wchar_t* fmt, const Args &... args)
{
	log(level::critical, fmt, args...);
}

#endif // SPDLOG_WCHAR_TO_UTF8_SUPPORT

//
// name and level
//
inline const std::string& spdlog::logger::name() const
{
	return name_;
}

inline void spdlog::logger::set_level(spdlog::level::level_enum log_level)
{
	level_.store(log_level);
}

inline void spdlog::logger::set_error_handler(spdlog::log_err_handler err_handler)
{
	err_handler_ = std::move(err_handler);
}

inline spdlog::log_err_handler spdlog::logger::error_handler() const
{
	return err_handler_;
}

inline void spdlog::logger::flush()
{
	try
	{
		flush_();
	}
	SPDLOG_CATCH_AND_HANDLE
}

inline void spdlog::logger::flush_on(level::level_enum log_level)
{
	flush_level_.store(log_level);
}

inline spdlog::level::level_enum spdlog::logger::flush_level() const
{
	return static_cast<spdlog::level::level_enum>(flush_level_.load(std::memory_order_relaxed));
}

inline bool spdlog::logger::should_flush_(const details::log_msg & msg)
{
	auto flush_level = flush_level_.load(std::memory_order_relaxed);
	return (msg.level >= flush_level) && (msg.level != level::off);
}

inline spdlog::level::level_enum spdlog::logger::default_level()
{
	return static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL);
}

inline spdlog::level::level_enum spdlog::logger::level() const
{
	return static_cast<spdlog::level::level_enum>(level_.load(std::memory_order_relaxed));
}

inline bool spdlog::logger::should_log(spdlog::level::level_enum msg_level) const
{
	return msg_level >= level_.load(std::memory_order_relaxed);
}

//
// protected virtual called at end of each user log call (if enabled) by the
// line_logger
//
inline void spdlog::logger::sink_it_(details::log_msg & msg)
{
#if defined(SPDLOG_ENABLE_MESSAGE_COUNTER)
	incr_msg_counter_(msg);
#endif
	for (auto& sink : sinks_)
	{
		if (sink->should_log(msg.level))
		{
			sink->log(msg);
		}
	}

	if (should_flush_(msg))
	{
		flush_();
	}
}

inline void spdlog::logger::flush_()
{
	for (auto& sink : sinks_)
	{
		sink->flush();
	}
}

inline void spdlog::logger::default_err_handler_(const std::string & msg)
{
	auto now = time(nullptr);
	if (now - last_err_time_ < 60)
	{
		return;
	}
	last_err_time_ = now;
	auto tm_time = details::os::localtime(now);
	char date_buf[100];
	std::strftime(date_buf, sizeof(date_buf), "%Y-%m-%d %H:%M:%S", &tm_time);
	fmt::print(stderr, "[*** LOG ERROR ***] [{}] [{}] {}\n", date_buf, name(), msg);
}

inline void spdlog::logger::incr_msg_counter_(details::log_msg & msg)
{
	msg.msg_id = msg_counter_.fetch_add(1, std::memory_order_relaxed);
}

inline const std::vector<spdlog::sink_ptr>& spdlog::logger::sinks() const
{
	return sinks_;
}

inline std::vector<spdlog::sink_ptr>& spdlog::logger::sinks()
{
	return sinks_;
}

inline std::shared_ptr<spdlog::logger> spdlog::logger::clone(std::string logger_name)
{
	auto cloned = std::make_shared<spdlog::logger>(std::move(logger_name), sinks_.begin(), sinks_.end());
	cloned->set_level(this->level());
	cloned->flush_on(this->flush_level());
	cloned->set_error_handler(this->error_handler());
	return cloned;
}

#endif // __LOGGER_IMPL_H__

/*** End of inlined file: logger_impl.h ***/

#endif // __LOGGER_H__

/*** End of inlined file: logger.h ***/

#ifndef SPDLOG_DISABLE_DEFAULT_LOGGER
// support for the default stdout color logger
#ifdef _WIN32

/*** Start of inlined file: wincolor_sink.h ***/
//
// Copyright(c) 2016 spdlog
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __WINCOLOR_SINK_H__
#define __WINCOLOR_SINK_H__

#pragma once

#ifndef SPDLOG_H

#endif

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <wincon.h>

namespace spdlog {
	namespace sinks {
		/*
		 * Windows color console sink. Uses WriteConsoleA to write to the console with
		 * colors
		 */
		template<typename OutHandle, typename ConsoleMutex>
		class wincolor_sink : public sink
		{
		public:
			const WORD BOLD = FOREGROUND_INTENSITY;
			const WORD RED = FOREGROUND_RED;
			const WORD GREEN = FOREGROUND_GREEN;
			const WORD CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;
			const WORD WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			const WORD YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;

			wincolor_sink()
				: out_handle_(OutHandle::handle())
				, mutex_(ConsoleMutex::mutex())
			{
				colors_[level::trace] = WHITE;
				colors_[level::debug] = CYAN;
				colors_[level::info] = GREEN;
				colors_[level::warn] = YELLOW | BOLD;
				colors_[level::err] = RED | BOLD;                         // red bold
				colors_[level::critical] = BACKGROUND_RED | WHITE | BOLD; // white bold on red background
				colors_[level::off] = 0;
			}

			~wincolor_sink() override
			{
				this->flush();
			}

			wincolor_sink(const wincolor_sink& other) = delete;
			wincolor_sink& operator=(const wincolor_sink& other) = delete;

			// change the color for the given level
			void set_color(level::level_enum level, WORD color)
			{
				std::lock_guard<mutex_t> lock(mutex_);
				colors_[level] = color;
			}

			void log(const details::log_msg& msg) final override
			{
				std::lock_guard<mutex_t> lock(mutex_);
				fmt::memory_buffer formatted;
				formatter_->format(msg, formatted);
				if (msg.color_range_end > msg.color_range_start)
				{
					// before color range
					print_range_(formatted, 0, msg.color_range_start);

					// in color range
					auto orig_attribs = set_console_attribs(colors_[msg.level]);
					print_range_(formatted, msg.color_range_start, msg.color_range_end);
					::SetConsoleTextAttribute(out_handle_,
						orig_attribs); // reset to orig colors
									   // after color range
					print_range_(formatted, msg.color_range_end, formatted.size());
				}
				else // print without colors if color range is invalid
				{
					print_range_(formatted, 0, formatted.size());
				}
			}

			void flush() final override
			{
				// windows console always flushed?
			}

			void set_pattern(const std::string& pattern) override final
			{
				std::lock_guard<mutex_t> lock(mutex_);
				formatter_ = std::unique_ptr<spdlog::formatter>(new pattern_formatter(pattern));
			}

			void set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) override final
			{
				std::lock_guard<mutex_t> lock(mutex_);
				formatter_ = std::move(sink_formatter);
			}

		private:
			using mutex_t = typename ConsoleMutex::mutex_t;
			// set color and return the orig console attributes (for resetting later)
			WORD set_console_attribs(WORD attribs)
			{
				CONSOLE_SCREEN_BUFFER_INFO orig_buffer_info;
				::GetConsoleScreenBufferInfo(out_handle_, &orig_buffer_info);
				WORD back_color = orig_buffer_info.wAttributes;
				// retrieve the current background color
				back_color &= static_cast<WORD>(~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY));
				// keep the background color unchanged
				::SetConsoleTextAttribute(out_handle_, attribs | back_color);
				return orig_buffer_info.wAttributes; // return orig attribs
			}

			// print a range of formatted message to console
			void print_range_(const fmt::memory_buffer& formatted, size_t start, size_t end)
			{
				auto size = static_cast<DWORD>(end - start);
				::WriteConsoleA(out_handle_, formatted.data() + start, size, nullptr, nullptr);
			}

			HANDLE out_handle_;
			mutex_t& mutex_;
			std::unordered_map<level::level_enum, WORD, level::level_hasher> colors_;
		};

		using wincolor_stdout_sink_mt = wincolor_sink<details::console_stdout, details::console_mutex>;
		using wincolor_stdout_sink_st = wincolor_sink<details::console_stdout, details::console_nullmutex>;

		using wincolor_stderr_sink_mt = wincolor_sink<details::console_stderr, details::console_mutex>;
		using wincolor_stderr_sink_st = wincolor_sink<details::console_stderr, details::console_nullmutex>;

	} // namespace sinks
} // namespace spdlog

#endif // __WINCOLOR_SINK_H__

/*** End of inlined file: wincolor_sink.h ***/


#else

/*** Start of inlined file: ansicolor_sink.h ***/
//
// Copyright(c) 2017 spdlog authors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __ANSICOLOR_SINK_H__
#define __ANSICOLOR_SINK_H__

#pragma once

#ifndef SPDLOG_H

#endif

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace spdlog {
	namespace sinks {

		/**
		 * This sink prefixes the output with an ANSI escape sequence color code
		 * depending on the severity
		 * of the message.
		 * If no color terminal detected, omit the escape codes.
		 */
		template<typename TargetStream, class ConsoleMutex>
		class ansicolor_sink final : public sink
		{
		public:
			using mutex_t = typename ConsoleMutex::mutex_t;
			ansicolor_sink()
				: target_file_(TargetStream::stream())
				, mutex_(ConsoleMutex::mutex())

			{
				should_do_colors_ = details::os::in_terminal(target_file_) && details::os::is_color_terminal();
				colors_[level::trace] = white;
				colors_[level::debug] = cyan;
				colors_[level::info] = green;
				colors_[level::warn] = yellow + bold;
				colors_[level::err] = red + bold;
				colors_[level::critical] = bold + on_red;
				colors_[level::off] = reset;
			}

			~ansicolor_sink() override = default;

			ansicolor_sink(const ansicolor_sink& other) = delete;
			ansicolor_sink& operator=(const ansicolor_sink& other) = delete;

			void set_color(level::level_enum color_level, const std::string& color)
			{
				std::lock_guard<mutex_t> lock(mutex_);
				colors_[color_level] = color;
			}

			/// Formatting codes
			const std::string reset = "\033[m";
			const std::string bold = "\033[1m";
			const std::string dark = "\033[2m";
			const std::string underline = "\033[4m";
			const std::string blink = "\033[5m";
			const std::string reverse = "\033[7m";
			const std::string concealed = "\033[8m";
			const std::string clear_line = "\033[K";

			// Foreground colors
			const std::string black = "\033[30m";
			const std::string red = "\033[31m";
			const std::string green = "\033[32m";
			const std::string yellow = "\033[33m";
			const std::string blue = "\033[34m";
			const std::string magenta = "\033[35m";
			const std::string cyan = "\033[36m";
			const std::string white = "\033[37m";

			/// Background colors
			const std::string on_black = "\033[40m";
			const std::string on_red = "\033[41m";
			const std::string on_green = "\033[42m";
			const std::string on_yellow = "\033[43m";
			const std::string on_blue = "\033[44m";
			const std::string on_magenta = "\033[45m";
			const std::string on_cyan = "\033[46m";
			const std::string on_white = "\033[47m";

			void log(const details::log_msg& msg) override
			{
				// Wrap the originally formatted message in color codes.
				// If color is not supported in the terminal, log as is instead.
				std::lock_guard<mutex_t> lock(mutex_);

				fmt::memory_buffer formatted;
				formatter_->format(msg, formatted);
				if (should_do_colors_ && msg.color_range_end > msg.color_range_start)
				{
					// before color range
					print_range_(formatted, 0, msg.color_range_start);
					// in color range
					print_ccode_(colors_[msg.level]);
					print_range_(formatted, msg.color_range_start, msg.color_range_end);
					print_ccode_(reset);
					// after color range
					print_range_(formatted, msg.color_range_end, formatted.size());
				}
				else // no color
				{
					print_range_(formatted, 0, formatted.size());
				}
				fflush(target_file_);
			}

			void flush() override
			{
				std::lock_guard<mutex_t> lock(mutex_);
				fflush(target_file_);
			}

			void set_pattern(const std::string& pattern) final
			{
				std::lock_guard<mutex_t> lock(mutex_);
				formatter_ = std::unique_ptr<spdlog::formatter>(new pattern_formatter(pattern));
			}

			void set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) override
			{
				std::lock_guard<mutex_t> lock(mutex_);
				formatter_ = std::move(sink_formatter);
			}

		private:
			void print_ccode_(const std::string& color_code)
			{
				fwrite(color_code.data(), sizeof(char), color_code.size(), target_file_);
			}
			void print_range_(const fmt::memory_buffer& formatted, size_t start, size_t end)
			{
				fwrite(formatted.data() + start, sizeof(char), end - start, target_file_);
			}

			FILE* target_file_;
			mutex_t& mutex_;

			bool should_do_colors_;
			std::unordered_map<level::level_enum, std::string, level::level_hasher> colors_;
		};

		using ansicolor_stdout_sink_mt = ansicolor_sink<details::console_stdout, details::console_mutex>;
		using ansicolor_stdout_sink_st = ansicolor_sink<details::console_stdout, details::console_nullmutex>;

		using ansicolor_stderr_sink_mt = ansicolor_sink<details::console_stderr, details::console_mutex>;
		using ansicolor_stderr_sink_st = ansicolor_sink<details::console_stderr, details::console_nullmutex>;

	} // namespace sinks

} // namespace spdlog

#endif // __ANSICOLOR_SINK_H__

/*** End of inlined file: ansicolor_sink.h ***/


#endif
#endif // SPDLOG_DISABLE_DEFAULT_LOGGER

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace spdlog {
	namespace details {
		class thread_pool;

		class registry
		{
		public:
			registry(const registry&) = delete;
			registry& operator=(const registry&) = delete;

			void register_logger(std::shared_ptr<logger> new_logger)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				register_logger_(std::move(new_logger));
			}

			void initialize_logger(std::shared_ptr<logger> new_logger)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				new_logger->set_formatter(formatter_->clone());

				if (err_handler_)
				{
					new_logger->set_error_handler(err_handler_);
				}

				new_logger->set_level(level_);
				new_logger->flush_on(flush_level_);

				if (automatic_registration_)
				{
					register_logger_(std::move(new_logger));
				}
			}

			std::shared_ptr<logger> get(const std::string& logger_name)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				auto found = loggers_.find(logger_name);
				return found == loggers_.end() ? nullptr : found->second;
			}

			std::shared_ptr<logger> default_logger()
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				return default_logger_;
			}

			// Return raw ptr to the default logger.
			// To be used directly by the spdlog default api (e.g. spdlog::info)
			// This make the default API faster, but cannot be used concurrently with set_default_logger().
			// e.g do not call set_default_logger() from one thread while calling spdlog::info() from another.
			logger* get_default_raw()
			{
				return default_logger_.get();
			}

			// set default logger.
			// default logger is stored in default_logger_ (for faster retrieval) and in the loggers_ map.
			void set_default_logger(std::shared_ptr<logger> new_default_logger)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				// remove previous default logger from the map
				if (default_logger_ != nullptr)
				{
					loggers_.erase(default_logger_->name());
				}
				if (new_default_logger != nullptr)
				{
					loggers_[new_default_logger->name()] = new_default_logger;
				}
				default_logger_ = std::move(new_default_logger);
			}

			void set_tp(std::shared_ptr<thread_pool> tp)
			{
				std::lock_guard<std::recursive_mutex> lock(tp_mutex_);
				tp_ = std::move(tp);
			}

			std::shared_ptr<thread_pool> get_tp()
			{
				std::lock_guard<std::recursive_mutex> lock(tp_mutex_);
				return tp_;
			}

			// Set global formatter. Each sink in each logger will get a clone of this object
			void set_formatter(std::unique_ptr<formatter> formatter)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				formatter_ = std::move(formatter);
				for (auto& l : loggers_)
				{
					l.second->set_formatter(formatter_->clone());
				}
			}

			void set_level(level::level_enum log_level)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				for (auto& l : loggers_)
				{
					l.second->set_level(log_level);
				}
				level_ = log_level;
			}

			void flush_on(level::level_enum log_level)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				for (auto& l : loggers_)
				{
					l.second->flush_on(log_level);
				}
				flush_level_ = log_level;
			}

			void flush_every(std::chrono::seconds interval)
			{
				std::lock_guard<std::mutex> lock(flusher_mutex_);
				std::function<void()> clbk = std::bind(&registry::flush_all, this);
				periodic_flusher_ = details::make_unique<periodic_worker>(clbk, interval);
			}

			void set_error_handler(log_err_handler handler)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				for (auto& l : loggers_)
				{
					l.second->set_error_handler(handler);
				}
				err_handler_ = handler;
			}

			void apply_all(const std::function<void(const std::shared_ptr<logger>)>& fun)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				for (auto& l : loggers_)
				{
					fun(l.second);
				}
			}

			void flush_all()
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				for (auto& l : loggers_)
				{
					l.second->flush();
				}
			}

			void drop(const std::string& logger_name)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				loggers_.erase(logger_name);
				if (default_logger_ && default_logger_->name() == logger_name)
				{
					default_logger_.reset();
				}
			}

			void drop_all()
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				loggers_.clear();
				default_logger_.reset();
			}

			// clean all resources and threads started by the registry
			void shutdown()
			{
				{
					std::lock_guard<std::mutex> lock(flusher_mutex_);
					periodic_flusher_.reset();
				}

				drop_all();

				{
					std::lock_guard<std::recursive_mutex> lock(tp_mutex_);
					tp_.reset();
				}
			}

			std::recursive_mutex& tp_mutex()
			{
				return tp_mutex_;
			}

			void set_automatic_registration(bool automatic_regsistration)
			{
				std::lock_guard<std::mutex> lock(logger_map_mutex_);
				automatic_registration_ = automatic_regsistration;
			}

			static registry& instance()
			{
				static registry s_instance;
				return s_instance;
			}

		private:
			registry()
				: formatter_(new pattern_formatter())
			{

#ifndef SPDLOG_DISABLE_DEFAULT_LOGGER
				// create default logger (ansicolor_stdout_sink_mt or wincolor_stdout_sink_mt in windows).
#ifdef _WIN32
				auto color_sink = std::make_shared<sinks::wincolor_stdout_sink_mt>();
#else
				auto color_sink = std::make_shared<sinks::ansicolor_stdout_sink_mt>();
#endif

				const char* default_logger_name = "";
				default_logger_ = std::make_shared<spdlog::logger>(default_logger_name, std::move(color_sink));
				loggers_[default_logger_name] = default_logger_;

#endif // SPDLOG_DISABLE_DEFAULT_LOGGER
			}

			~registry() = default;

			void throw_if_exists_(const std::string& logger_name)
			{
				if (loggers_.find(logger_name) != loggers_.end())
				{
					throw spdlog_ex("logger with name '" + logger_name + "' already exists");
				}
			}

			void register_logger_(std::shared_ptr<logger> new_logger)
			{
				auto logger_name = new_logger->name();
				throw_if_exists_(logger_name);
				loggers_[logger_name] = std::move(new_logger);
			}

			std::mutex logger_map_mutex_, flusher_mutex_;
			std::recursive_mutex tp_mutex_;
			std::unordered_map<std::string, std::shared_ptr<logger>> loggers_;
			std::unique_ptr<formatter> formatter_;
			level::level_enum level_ = spdlog::logger::default_level();
			level::level_enum flush_level_ = level::off;
			log_err_handler err_handler_;
			std::shared_ptr<thread_pool> tp_;
			std::unique_ptr<periodic_worker> periodic_flusher_;
			std::shared_ptr<logger> default_logger_;
			bool automatic_registration_ = true;
		};

	} // namespace details
} // namespace spdlog

#endif // __REGISTRY_H__

/*** End of inlined file: registry.h ***/


/*** Start of inlined file: version.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __VERSION_H__
#define __VERSION_H__

#pragma once

#define SPDLOG_VER_MAJOR 1
#define SPDLOG_VER_MINOR 3
#define SPDLOG_VER_PATCH 1

#define SPDLOG_VERSION (SPDLOG_VER_MAJOR * 10000 + SPDLOG_VER_MINOR * 100 + SPDLOG_VER_PATCH)

#endif // __VERSION_H__

/*** End of inlined file: version.h ***/

#include <chrono>
#include <functional>
#include <memory>
#include <string>

namespace spdlog {

// Default logger factory-  creates synchronous loggers
struct synchronous_factory
{
	template<typename Sink, typename... SinkArgs>
	static std::shared_ptr<spdlog::logger> create(std::string logger_name, SinkArgs &&... args)
	{
		auto sink = std::make_shared<Sink>(std::forward<SinkArgs>(args)...);
		auto new_logger = std::make_shared<logger>(std::move(logger_name), std::move(sink));
		details::registry::instance().initialize_logger(new_logger);
		return new_logger;
	}
};

using default_factory = synchronous_factory;

// Create and register a logger with a templated sink type
// The logger's level, formatter and flush level will be set according the
// global settings.
// Example:
// spdlog::create<daily_file_sink_st>("logger_name", "dailylog_filename", 11, 59);
template<typename Sink, typename... SinkArgs>
inline std::shared_ptr<spdlog::logger> create(std::string logger_name, SinkArgs &&... sink_args)
{
	return default_factory::create<Sink>(std::move(logger_name), std::forward<SinkArgs>(sink_args)...);
}

// Return an existing logger or nullptr if a logger with such name doesn't
// exist.
// example: spdlog::get("my_logger")->info("hello {}", "world");
inline std::shared_ptr<logger> get(const std::string &name)
{
	return details::registry::instance().get(name);
}

// Set global formatter. Each sink in each logger will get a clone of this object
inline void set_formatter(std::unique_ptr<spdlog::formatter> formatter)
{
	details::registry::instance().set_formatter(std::move(formatter));
}

// Set global format string.
// example: spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %l : %v");
inline void set_pattern(std::string pattern, pattern_time_type time_type = pattern_time_type::local)
{
	set_formatter(std::unique_ptr<spdlog::formatter>(new pattern_formatter(std::move(pattern), time_type)));
}

// Set global logging level
inline void set_level(level::level_enum log_level)
{
	details::registry::instance().set_level(log_level);
}

// Set global flush level
inline void flush_on(level::level_enum log_level)
{
	details::registry::instance().flush_on(log_level);
}

// Start/Restart a periodic flusher thread
// Warning: Use only if all your loggers are thread safe!
inline void flush_every(std::chrono::seconds interval)
{
	details::registry::instance().flush_every(interval);
}

// Set global error handler
inline void set_error_handler(log_err_handler handler)
{
	details::registry::instance().set_error_handler(std::move(handler));
}

// Register the given logger with the given name
inline void register_logger(std::shared_ptr<logger> logger)
{
	details::registry::instance().register_logger(std::move(logger));
}

// Apply a user defined function on all registered loggers
// Example:
// spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) {l->flush();});
inline void apply_all(const std::function<void(std::shared_ptr<logger>)> &fun)
{
	details::registry::instance().apply_all(fun);
}

// Drop the reference to the given logger
inline void drop(const std::string &name)
{
	details::registry::instance().drop(name);
}

// Drop all references from the registry
inline void drop_all()
{
	details::registry::instance().drop_all();
}

// stop any running threads started by spdlog and clean registry loggers
inline void shutdown()
{
	details::registry::instance().shutdown();
}

// Automatic registration of loggers when using spdlog::create() or spdlog::create_async
inline void set_automatic_registration(bool automatic_registation)
{
	details::registry::instance().set_automatic_registration(automatic_registation);
}

// API for using default logger (stdout_color_mt),
// e.g: spdlog::info("Message {}", 1);
//
// The default logger object can be accessed using the spdlog::default_logger():
// For example, to add another sink to it:
// spdlog::default_logger()->sinks()->push_back(some_sink);
//
// The default logger can replaced using spdlog::set_default_logger(new_logger).
// For example, to replace it with a file logger.
//
// IMPORTANT:
// The default API is thread safe (for _mt loggers), but:
// set_default_logger() *should not* be used concurrently with the default API.
// e.g do not call set_default_logger() from one thread while calling spdlog::info() from another.

inline std::shared_ptr<spdlog::logger> default_logger()
{
	return details::registry::instance().default_logger();
}

inline spdlog::logger *default_logger_raw()
{
	return details::registry::instance().get_default_raw();
}

inline void set_default_logger(std::shared_ptr<spdlog::logger> default_logger)
{
	details::registry::instance().set_default_logger(std::move(default_logger));
}

template<typename... Args>
inline void log(source_loc source, level::level_enum lvl, const char *fmt, const Args &... args)
{
	default_logger_raw()->log(source, lvl, fmt, args...);
}

template<typename... Args>
inline void log(level::level_enum lvl, const char *fmt, const Args &... args)
{
	default_logger_raw()->log(source_loc{}, lvl, fmt, args...);
}

template<typename... Args>
inline void trace(const char *fmt, const Args &... args)
{
	default_logger_raw()->trace(fmt, args...);
}

template<typename... Args>
inline void debug(const char *fmt, const Args &... args)
{
	default_logger_raw()->debug(fmt, args...);
}

template<typename... Args>
inline void info(const char *fmt, const Args &... args)
{
	default_logger_raw()->info(fmt, args...);
}

template<typename... Args>
inline void warn(const char *fmt, const Args &... args)
{
	default_logger_raw()->warn(fmt, args...);
}

template<typename... Args>
inline void error(const char *fmt, const Args &... args)
{
	default_logger_raw()->error(fmt, args...);
}

template<typename... Args>
inline void critical(const char *fmt, const Args &... args)
{
	default_logger_raw()->critical(fmt, args...);
}

template<typename T>
inline void log(level::level_enum lvl, const T &msg)
{
	default_logger_raw()->log(lvl, msg);
}

template<typename T>
inline void trace(const T &msg)
{
	default_logger_raw()->trace(msg);
}

template<typename T>
inline void debug(const T &msg)
{
	default_logger_raw()->debug(msg);
}

template<typename T>
inline void info(const T &msg)
{
	default_logger_raw()->info(msg);
}

template<typename T>
inline void warn(const T &msg)
{
	default_logger_raw()->warn(msg);
}

template<typename T>
inline void error(const T &msg)
{
	default_logger_raw()->error(msg);
}

template<typename T>
inline void critical(const T &msg)
{
	default_logger_raw()->critical(msg);
}

#ifdef SPDLOG_WCHAR_TO_UTF8_SUPPORT
template<typename... Args>
inline void log(level::level_enum lvl, const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->log(lvl, fmt, args...);
}

template<typename... Args>
inline void trace(const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->trace(fmt, args...);
}

template<typename... Args>
inline void debug(const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->debug(fmt, args...);
}

template<typename... Args>
inline void info(const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->info(fmt, args...);
}

template<typename... Args>
inline void warn(const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->warn(fmt, args...);
}

template<typename... Args>
inline void error(const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->error(fmt, args...);
}

template<typename... Args>
inline void critical(const wchar_t *fmt, const Args &... args)
{
	default_logger_raw()->critical(fmt, args...);
}

#endif // SPDLOG_WCHAR_TO_UTF8_SUPPORT

} // namespace spdlog

//
// enable/disable log calls at compile time according to global level.
//
// define SPDLOG_ACTIVE_LEVEL to one of those (before including spdlog.h):
// SPDLOG_LEVEL_TRACE,
// SPDLOG_LEVEL_DEBUG,
// SPDLOG_LEVEL_INFO,
// SPDLOG_LEVEL_WARN,
// SPDLOG_LEVEL_ERROR,
// SPDLOG_LEVEL_CRITICAL,
// SPDLOG_LEVEL_OFF
//

#define SPDLOG_LOGGER_CALL(logger, level, ...)                                                                                             \
	if (logger->should_log(level))                                                                                                         \
	logger->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#define SPDLOG_LOGGER_TRACE(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#define SPDLOG_TRACE(...) SPDLOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define SPDLOG_LOGGER_TRACE(logger, ...) (void)0
#define SPDLOG_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#define SPDLOG_LOGGER_DEBUG(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#define SPDLOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define SPDLOG_LOGGER_DEBUG(logger, ...) (void)0
#define SPDLOG_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#define SPDLOG_LOGGER_INFO(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::info, __VA_ARGS__)
#define SPDLOG_INFO(...) SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define SPDLOG_LOGGER_INFO(logger, ...) (void)0
#define SPDLOG_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#define SPDLOG_LOGGER_WARN(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#define SPDLOG_WARN(...) SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define SPDLOG_LOGGER_WARN(logger, ...) (void)0
#define SPDLOG_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#define SPDLOG_LOGGER_ERROR(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::err, __VA_ARGS__)
#define SPDLOG_ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define SPDLOG_LOGGER_ERROR(logger, ...) (void)0
#define SPDLOG_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#define SPDLOG_LOGGER_CRITICAL(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)
#define SPDLOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define SPDLOG_LOGGER_CRITICAL(logger, ...) (void)0
#define SPDLOG_CRITICAL(...) (void)0
#endif

#endif // SPDLOG_H

/*** End of inlined file: spdlog.h ***/


/*** Start of inlined file: daily_file_sink.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __DAILY_FILE_SINK_H__
#define __DAILY_FILE_SINK_H__

#pragma once

#ifndef SPDLOG_H

#endif


/*** Start of inlined file: file_helper.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __FILE_HELPER_H__
#define __FILE_HELPER_H__

#pragma once

// Helper class for file sinks.
// When failing to open a file, retry several times(5) with a delay interval(10 ms).
// Throw spdlog_ex exception on errors.

#include <cerrno>
#include <chrono>
#include <cstdio>
#include <string>
#include <thread>
#include <tuple>

namespace spdlog {
	namespace details {

		class file_helper
		{

		public:
			const int open_tries = 5;
			const int open_interval = 10;

			explicit file_helper() = default;

			file_helper(const file_helper&) = delete;
			file_helper& operator=(const file_helper&) = delete;

			~file_helper()
			{
				close();
			}

			void open(const filename_t& fname, bool truncate = false)
			{
				close();
				auto* mode = truncate ? SPDLOG_FILENAME_T("wb") : SPDLOG_FILENAME_T("ab");
				_filename = fname;
				for (int tries = 0; tries < open_tries; ++tries)
				{
					if (!os::fopen_s(&fd_, fname, mode))
					{
						return;
					}

					details::os::sleep_for_millis(open_interval);
				}

				throw spdlog_ex("Failed opening file " + os::filename_to_str(_filename) + " for writing", errno);
			}

			void reopen(bool truncate)
			{
				if (_filename.empty())
				{
					throw spdlog_ex("Failed re opening file - was not opened before");
				}
				open(_filename, truncate);
			}

			void flush()
			{
				std::fflush(fd_);
			}

			void close()
			{
				if (fd_ != nullptr)
				{
					std::fclose(fd_);
					fd_ = nullptr;
				}
			}

			void write(const fmt::memory_buffer& buf)
			{
				size_t msg_size = buf.size();
				auto data = buf.data();
				if (std::fwrite(data, 1, msg_size, fd_) != msg_size)
				{
					throw spdlog_ex("Failed writing to file " + os::filename_to_str(_filename), errno);
				}
			}

			size_t size() const
			{
				if (fd_ == nullptr)
				{
					throw spdlog_ex("Cannot use size() on closed file " + os::filename_to_str(_filename));
				}
				return os::filesize(fd_);
			}

			const filename_t& filename() const
			{
				return _filename;
			}

			static bool file_exists(const filename_t& fname)
			{
				return os::file_exists(fname);
			}

			//
			// return file path and its extension:
			//
			// "mylog.txt" => ("mylog", ".txt")
			// "mylog" => ("mylog", "")
			// "mylog." => ("mylog.", "")
			// "/dir1/dir2/mylog.txt" => ("/dir1/dir2/mylog", ".txt")
			//
			// the starting dot in filenames is ignored (hidden files):
			//
			// ".mylog" => (".mylog". "")
			// "my_folder/.mylog" => ("my_folder/.mylog", "")
			// "my_folder/.mylog.txt" => ("my_folder/.mylog", ".txt")
			static std::tuple<filename_t, filename_t> split_by_extension(const spdlog::filename_t& fname)
			{
				auto ext_index = fname.rfind('.');

				// no valid extension found - return whole path and empty string as
				// extension
				if (ext_index == filename_t::npos || ext_index == 0 || ext_index == fname.size() - 1)
				{
					return std::make_tuple(fname, spdlog::filename_t());
				}

				// treat casese like "/etc/rc.d/somelogfile or "/abc/.hiddenfile"
				auto folder_index = fname.rfind(details::os::folder_sep);
				if (folder_index != filename_t::npos && folder_index >= ext_index - 1)
				{
					return std::make_tuple(fname, spdlog::filename_t());
				}

				// finally - return a valid base and extension tuple
				return std::make_tuple(fname.substr(0, ext_index), fname.substr(ext_index));
			}

		private:
			std::FILE* fd_{ nullptr };
			filename_t _filename;
		};
	} // namespace details
} // namespace spdlog

#endif // __FILE_HELPER_H__

/*** End of inlined file: file_helper.h ***/


/*** Start of inlined file: base_sink.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __BASE_SINK_H__
#define __BASE_SINK_H__

#pragma once
//
// base sink templated over a mutex (either dummy or real)
// concrete implementation should override the sink_it_() and flush_()  methods.
// locking is taken care of in this class - no locking needed by the
// implementers..
//

namespace spdlog {
	namespace sinks {
		template<typename Mutex>
		class base_sink : public sink
		{
		public:
			base_sink() = default;
			base_sink(const base_sink&) = delete;
			base_sink& operator=(const base_sink&) = delete;

			void log(const details::log_msg& msg) final
			{
				std::lock_guard<Mutex> lock(mutex_);
				sink_it_(msg);
			}

			void flush() final
			{
				std::lock_guard<Mutex> lock(mutex_);
				flush_();
			}

			void set_pattern(const std::string& pattern) final
			{
				std::lock_guard<Mutex> lock(mutex_);
				set_pattern_(pattern);
			}

			void set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) final
			{
				std::lock_guard<Mutex> lock(mutex_);
				set_formatter_(std::move(sink_formatter));
			}

		protected:
			virtual void sink_it_(const details::log_msg& msg) = 0;
			virtual void flush_() = 0;

			virtual void set_pattern_(const std::string& pattern)
			{
				set_formatter_(details::make_unique<spdlog::pattern_formatter>(pattern));
			}

			virtual void set_formatter_(std::unique_ptr<spdlog::formatter> sink_formatter)
			{
				formatter_ = std::move(sink_formatter);
			}
			Mutex mutex_;
		};
	} // namespace sinks
} // namespace spdlog

#endif // __BASE_SINK_H__

/*** End of inlined file: base_sink.h ***/

#include <chrono>
#include <cstdio>
#include <ctime>
#include <mutex>
#include <string>

namespace spdlog {
	namespace sinks {

		/*
		 * Generator of daily log file names in format basename.YYYY-MM-DD.ext
		 */
		struct daily_filename_calculator
		{
			// Create filename for the form basename.YYYY-MM-DD
			static filename_t calc_filename(const filename_t& filename, const tm& now_tm)
			{
				filename_t basename, ext;
				std::tie(basename, ext) = details::file_helper::split_by_extension(filename);
				std::conditional<std::is_same<filename_t::value_type, char>::value, fmt::memory_buffer, fmt::wmemory_buffer>::type w;
				fmt::format_to(
					w, SPDLOG_FILENAME_T("{}_{:04d}-{:02d}-{:02d}{}"), basename, now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday, ext);
				return fmt::to_string(w);
			}
		};

		/*
		 * Rotating file sink based on date. rotates at midnight
		 */
		template<typename Mutex, typename FileNameCalc = daily_filename_calculator>
		class daily_file_sink final : public base_sink<Mutex>
		{
		public:
			// create daily file sink which rotates on given time
			daily_file_sink(filename_t base_filename, int rotation_hour, int rotation_minute, bool truncate = false)
				: base_filename_(std::move(base_filename))
				, rotation_h_(rotation_hour)
				, rotation_m_(rotation_minute)
				, truncate_(truncate)
			{
				if (rotation_hour < 0 || rotation_hour > 23 || rotation_minute < 0 || rotation_minute > 59)
				{
					throw spdlog_ex("daily_file_sink: Invalid rotation time in ctor");
				}
				auto now = log_clock::now();
				file_helper_.open(FileNameCalc::calc_filename(base_filename_, now_tm(now)), truncate_);
				rotation_tp_ = next_rotation_tp_();
			}

		protected:
			void sink_it_(const details::log_msg& msg) override
			{

				if (msg.time >= rotation_tp_)
				{
					file_helper_.open(FileNameCalc::calc_filename(base_filename_, now_tm(msg.time)), truncate_);
					rotation_tp_ = next_rotation_tp_();
				}
				fmt::memory_buffer formatted;
				sink::formatter_->format(msg, formatted);
				file_helper_.write(formatted);
			}

			void flush_() override
			{
				file_helper_.flush();
			}

		private:
			tm now_tm(log_clock::time_point tp)
			{
				time_t tnow = log_clock::to_time_t(tp);
				return spdlog::details::os::localtime(tnow);
			}

			log_clock::time_point next_rotation_tp_()
			{
				auto now = log_clock::now();
				tm date = now_tm(now);
				date.tm_hour = rotation_h_;
				date.tm_min = rotation_m_;
				date.tm_sec = 0;
				auto rotation_time = log_clock::from_time_t(std::mktime(&date));
				if (rotation_time > now)
				{
					return rotation_time;
				}
				return { rotation_time + std::chrono::hours(24) };
			}

			filename_t base_filename_;
			int rotation_h_;
			int rotation_m_;
			log_clock::time_point rotation_tp_;
			details::file_helper file_helper_;
			bool truncate_;
		};

		using daily_file_sink_mt = daily_file_sink<std::mutex>;
		using daily_file_sink_st = daily_file_sink<details::null_mutex>;

	} // namespace sinks

	//
	// factory functions
	//
	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> daily_logger_mt(
		const std::string& logger_name, const filename_t& filename, int hour = 0, int minute = 0, bool truncate = false)
	{
		return Factory::template create<sinks::daily_file_sink_mt>(logger_name, filename, hour, minute, truncate);
	}

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> daily_logger_st(
		const std::string& logger_name, const filename_t& filename, int hour = 0, int minute = 0, bool truncate = false)
	{
		return Factory::template create<sinks::daily_file_sink_st>(logger_name, filename, hour, minute, truncate);
	}
} // namespace spdlog

#endif // __DAILY_FILE_SINK_H__

/*** End of inlined file: daily_file_sink.h ***/


/*** Start of inlined file: stdout_color_sinks.h ***/
//
// Copyright(c) 2018 spdlog
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __STDOUT_COLOR_SINKS_H__
#define __STDOUT_COLOR_SINKS_H__

#pragma once

#ifndef SPDLOG_H

#endif

#ifdef _WIN32

#else

#endif

namespace spdlog {
	namespace sinks {
#ifdef _WIN32
		using stdout_color_sink_mt = wincolor_stdout_sink_mt;
		using stdout_color_sink_st = wincolor_stdout_sink_st;
		using stderr_color_sink_mt = wincolor_stderr_sink_mt;
		using stderr_color_sink_st = wincolor_stderr_sink_st;
#else
		using stdout_color_sink_mt = ansicolor_stdout_sink_mt;
		using stdout_color_sink_st = ansicolor_stdout_sink_st;
		using stderr_color_sink_mt = ansicolor_stderr_sink_mt;
		using stderr_color_sink_st = ansicolor_stderr_sink_st;
#endif
	} // namespace sinks

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> stdout_color_mt(const std::string& logger_name)
	{
		return Factory::template create<sinks::stdout_color_sink_mt>(logger_name);
	}

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> stdout_color_st(const std::string& logger_name)
	{
		return Factory::template create<sinks::stdout_color_sink_st>(logger_name);
	}

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> stderr_color_mt(const std::string& logger_name)
	{
		return Factory::template create<sinks::stderr_color_sink_mt>(logger_name);
	}

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> stderr_color_st(const std::string& logger_name)
	{
		return Factory::template create<sinks::stderr_color_sink_mt>(logger_name);
	}
} // namespace spdlog

#endif // __STDOUT_COLOR_SINKS_H__

/*** End of inlined file: stdout_color_sinks.h ***/


/*** Start of inlined file: rotating_file_sink.h ***/
//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
#ifndef __ROTATING_FILE_SINK_H__
#define __ROTATING_FILE_SINK_H__

#pragma once

#ifndef SPDLOG_H

#endif

#include <cerrno>
#include <chrono>
#include <ctime>
#include <mutex>
#include <string>
#include <tuple>

namespace spdlog {
	namespace sinks {

		//
		// Rotating file sink based on size
		//
		template<typename Mutex>
		class rotating_file_sink final : public base_sink<Mutex>
		{
		public:
			rotating_file_sink(filename_t base_filename, std::size_t max_size, std::size_t max_files)
				: base_filename_(std::move(base_filename))
				, max_size_(max_size)
				, max_files_(max_files)
			{
				file_helper_.open(calc_filename(base_filename_, 0));
				current_size_ = file_helper_.size(); // expensive. called only once
			}

			// calc filename according to index and file extension if exists.
			// e.g. calc_filename("logs/mylog.txt, 3) => "logs/mylog.3.txt".
			static filename_t calc_filename(const filename_t& filename, std::size_t index)
			{
				typename std::conditional<std::is_same<filename_t::value_type, char>::value, fmt::memory_buffer, fmt::wmemory_buffer>::type w;
				if (index != 0u)
				{
					filename_t basename, ext;
					std::tie(basename, ext) = details::file_helper::split_by_extension(filename);
					fmt::format_to(w, SPDLOG_FILENAME_T("{}.{}{}"), basename, index, ext);
				}
				else
				{
					fmt::format_to(w, SPDLOG_FILENAME_T("{}"), filename);
				}
				return fmt::to_string(w);
			}

		protected:
			void sink_it_(const details::log_msg& msg) override
			{
				fmt::memory_buffer formatted;
				sink::formatter_->format(msg, formatted);
				current_size_ += formatted.size();
				if (current_size_ > max_size_)
				{
					rotate_();
					current_size_ = formatted.size();
				}
				file_helper_.write(formatted);
			}

			void flush_() override
			{
				file_helper_.flush();
			}

		private:
			// Rotate files:
			// log.txt -> log.1.txt
			// log.1.txt -> log.2.txt
			// log.2.txt -> log.3.txt
			// log.3.txt -> delete
			void rotate_()
			{
				using details::os::filename_to_str;
				file_helper_.close();
				for (auto i = max_files_; i > 0; --i)
				{
					filename_t src = calc_filename(base_filename_, i - 1);
					if (!details::file_helper::file_exists(src))
					{
						continue;
					}
					filename_t target = calc_filename(base_filename_, i);

					if (!rename_file(src, target))
					{
						// if failed try again after a small delay.
						// this is a workaround to a windows issue, where very high rotation
						// rates can cause the rename to fail with permission denied (because of antivirus?).
						details::os::sleep_for_millis(100);
						if (!rename_file(src, target))
						{
							file_helper_.reopen(true); // truncate the log file anyway to prevent it to grow beyond its limit!
							current_size_ = 0;
							throw spdlog_ex(
								"rotating_file_sink: failed renaming " + filename_to_str(src) + " to " + filename_to_str(target), errno);
						}
					}
				}
				file_helper_.reopen(true);
			}

			// delete the target if exists, and rename the src file  to target
			// return true on success, false otherwise.
			bool rename_file(const filename_t& src_filename, const filename_t& target_filename)
			{
				// try to delete the target file in case it already exists.
				(void)details::os::remove(target_filename);
				return details::os::rename(src_filename, target_filename) == 0;
			}

			filename_t base_filename_;
			std::size_t max_size_;
			std::size_t max_files_;
			std::size_t current_size_;
			details::file_helper file_helper_;
		};

		using rotating_file_sink_mt = rotating_file_sink<std::mutex>;
		using rotating_file_sink_st = rotating_file_sink<details::null_mutex>;

	} // namespace sinks

	//
	// factory functions
	//

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> rotating_logger_mt(
		const std::string& logger_name, const filename_t& filename, size_t max_file_size, size_t max_files)
	{
		return Factory::template create<sinks::rotating_file_sink_mt>(logger_name, filename, max_file_size, max_files);
	}

	template<typename Factory = default_factory>
	inline std::shared_ptr<logger> rotating_logger_st(
		const std::string& logger_name, const filename_t& filename, size_t max_file_size, size_t max_files)
	{
		return Factory::template create<sinks::rotating_file_sink_st>(logger_name, filename, max_file_size, max_files);
	}
} // namespace spdlog

#endif // __ROTATING_FILE_SINK_H__

/*** End of inlined file: rotating_file_sink.h ***/

#define LOG_CRITICAL(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::critical, __VA_ARGS__)
#define LOG_ERROR(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::err, __VA_ARGS__)
#define LOG_WARN(...)  CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::warn, __VA_ARGS__)
#define LOG_INFO(...)  CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::info, __VA_ARGS__)
#define LOG_DEBUG(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::debug, __VA_ARGS__)
#define LOG_TRACE(...) CDMLog::Instance()->GetLogger()->log(spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, SPDLOG_FUNCTION}, spdlog::level::level_enum::trace, __VA_ARGS__)

class CDMLog
{
public:
	CDMLog()
	{
		std::string strPath = DMGetRootPath() + "/logs";
		std::string strFile = DMGetRootPath() + "/logs/" + DMGetExeName() + ".log";
		DMCreateDirectories((DMGetRootPath() + "/logs").c_str());

		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::warn);
		console_sink->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%@][%t][%l] %v");

		auto daily_logger = std::make_shared<spdlog::sinks::daily_file_sink_mt>(strFile,
			2, 30);
		daily_logger->set_level(spdlog::level::trace);
		daily_logger->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%@][%t][%l] %v");

		//auto rotating_logger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(strFile, 5 * 1024 * 1024, 7);
		//rotating_logger->set_level(spdlog::level::trace);
		//rotating_logger->set_pattern("[%Y-%m-%d %H:%M:%S %f] [%@][%t][%l] %v");

		//spdlog::logger logger(DMGetExeName(), {console_sink, daily_logger , rotating_logger});
		spdlog::logger logger(DMGetExeName(), { console_sink, daily_logger});

		my_logger = logger.clone(DMGetExeName());

		my_logger->flush_on(spdlog::level::warn);

		spdlog::flush_every(std::chrono::seconds(0));
	}
	~CDMLog()
	{
		spdlog::drop_all();
	}

	static CDMLog* Instance()
	{
		static CDMLog s_oT;
		return &s_oT;
	}

	inline std::shared_ptr<spdlog::logger> GetLogger()
	{
		return my_logger;
	}

private:
	std::shared_ptr<spdlog::logger> my_logger;
};

#define DMLOG_INIT() CDMLog::Instance()

struct DMLogTimer
{
	DMLogTimer() : tp(std::chrono::system_clock::now()) {}
	virtual ~DMLogTimer()
	{
		auto dur = std::chrono::system_clock::now() - tp;
		LOG_DEBUG("Cost {} ms", std::chrono::duration_cast<std::chrono::milliseconds>
			(dur).count());
	}
	std::chrono::system_clock::time_point tp;
};

struct DMBench : public DMLogTimer
{
	DMBench() : val(0) {}
	virtual ~DMBench()
	{
		stop();
	}
	inline void stop()
	{
		auto dur = std::chrono::system_clock::now() - tp;
		LOG_DEBUG("Per op: {} ns",
			std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() / std::max(
				val, (uint64_t)1));
		auto perf = (double)val / std::chrono::duration_cast<std::chrono::milliseconds>
			(dur).count() / 10;

		if (perf < 1)
		{
			LOG_DEBUG("Performance: {:03.2f}  w/s", perf);
		}
		else
		{
			LOG_DEBUG("Performance: {} w/s", perf);
		}
	}
	DMBench& operator++()
	{
		++val;
		return *this;
	}
	DMBench& operator++(int)
	{
		++val;
		return *this;
	}
	DMBench& operator+=(uint64_t v)
	{
		val += v;
		return *this;
	}
	DMBench& add(uint64_t v)
	{
		val += v;
		return *this;
	}
	uint64_t val;
};

#endif // __DMLOG_H__

