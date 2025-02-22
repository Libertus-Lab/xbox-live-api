/***
* Copyright (C) Microsoft. All rights reserved.
* Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
*
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* Various common utilities.
*
* For the latest on this and related APIs, please see: https://github.com/Microsoft/cpprestsdk
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <system_error>
#include <random>
#include <locale.h>

#include "HookedUri/details/basic_types.h"

#if !defined(_WIN32) || (_MSC_VER >= 1700)
#include <chrono>
#endif

#ifndef _WIN32
#include <sys/time.h>
#endif

#if HC_PLATFORM_IS_MICROSOFT
#pragma warning( push )
#pragma warning( disable : 26444 ) // ignore various unnamed objects
#endif

namespace xbox { namespace services { namespace cppresturi {

/// Various utilities for string conversions and date and time manipulation.
namespace utility
{

// Left over from VS2010 support, remains to avoid breaking.
typedef std::chrono::seconds seconds;

/// Functions for converting to/from std::chrono::seconds to xml string.
namespace timespan
{
    /// <summary>
    /// Converts a timespan/interval in seconds to xml duration string as specified by
    /// http://www.w3.org/TR/xmlschema-2/#duration
    /// </summary>
    utility::string_t seconds_to_xml_duration(utility::seconds numSecs);

    /// <summary>
    /// Converts an xml duration to timespan/interval in seconds
    /// http://www.w3.org/TR/xmlschema-2/#duration
    /// </summary>
    utility::seconds xml_duration_to_seconds(const utility::string_t &timespanString);
}

/// Functions for Unicode string conversions.
namespace conversions
{
    /// <summary>
    /// Converts a UTF-16 string to a UTF-8 string.
    /// </summary>
    /// <param name="w">A two byte character UTF-16 string.</param>
    /// <returns>A single byte character UTF-8 string.</returns>
    xsapi_internal_string utf16_to_utf8_internal(const xsapi_internal_wstring &w);
    std::string utf16_to_utf8(const utf16string&w);

    /// <summary>
    /// Converts a UTF-8 string to a UTF-16
    /// </summary>
    /// <param name="s">A single byte character UTF-8 string.</param>
    /// <returns>A two byte character UTF-16 string.</returns>
    utf16string utf8_to_utf16(const std::string &s);

    /// <summary>
    /// Converts a ASCII (us-ascii) string to a UTF-16 string.
    /// </summary>
    /// <param name="s">A single byte character us-ascii string.</param>
    /// <returns>A two byte character UTF-16 string.</returns>
    utf16string usascii_to_utf16(const std::string &s);

    /// <summary>
    /// Converts a Latin1 (iso-8859-1) string to a UTF-8 string.
    /// </summary>
    /// <param name="s">A single byte character UTF-8 string.</param>
    /// <returns>A single byte character UTF-8 string.</returns>
    utf8string latin1_to_utf8(const std::string &s);

    /// <summary>
    /// Converts to a platform dependent Unicode string type.
    /// </summary>
    /// <param name="s">A single byte character UTF-8 string.</param>
    /// <returns>A platform dependent string type.</returns>
    utility::string_t to_string_t(std::string &&s);

    /// <summary>
    /// Converts to a platform dependent Unicode string type.
    /// </summary>
    /// <param name="s">A two byte character UTF-16 string.</param>
    /// <returns>A platform dependent string type.</returns>
    utility::string_t to_string_t(utf16string &&s);

    /// <summary>
    /// Converts to a platform dependent Unicode string type.
    /// </summary>
    /// <param name="s">A single byte character UTF-8 string.</param>
    /// <returns>A platform dependent string type.</returns>
    utility::string_t to_string_t(const std::string &s);

    /// <summary>
    /// Converts to a platform dependent Unicode string type.
    /// </summary>
    /// <param name="s">A two byte character UTF-16 string.</param>
    /// <returns>A platform dependent string type.</returns>
    utility::string_t to_string_t(const utf16string &s);

    /// <summary>
    /// Converts to a UTF-16 from string.
    /// </summary>
    /// <param name="value">A single byte character UTF-8 string.</param>
    /// <returns>A two byte character UTF-16 string.</returns>
    utf16string to_utf16string(const std::string &value);

    /// <summary>
    /// Converts to a UTF-16 from string.
    /// </summary>
    /// <param name="value">A two byte character UTF-16 string.</param>
    /// <returns>A two byte character UTF-16 string.</returns>
    utf16string to_utf16string(utf16string value);

    /// <summary>
    /// Converts to a UTF-8 string.
    /// </summary>
    /// <param name="value">A single byte character UTF-8 string.</param>
    /// <returns>A single byte character UTF-8 string.</returns>
    xsapi_internal_string to_utf8string_internal(xsapi_internal_string value);

    /// <summary>
    /// Converts to a UTF-8 string.
    /// </summary>
    /// <param name="value">A two byte character UTF-16 string.</param>
    /// <returns>A single byte character UTF-8 string.</returns>
    xsapi_internal_string to_utf8string_internal(const xsapi_internal_wstring &value);

    xsapi_internal_string latin1_to_utf8_internal(const xsapi_internal_string &s);
    xsapi_internal_wstring latin1_to_utf16_internal(const xsapi_internal_string &s);

    /// <summary>
    /// Encode the given byte array into a base64 string
    /// </summary>
    utility::string_t to_base64(const unsigned char* data, size_t dataSize);

    /// <summary>
    /// Encode the given byte array into a base64 string
    /// </summary>
    utility::string_t to_base64(const std::vector<unsigned char>& data);

    /// <summary>
    /// Encode the given 8-byte integer into a base64 string
    /// </summary>
    utility::string_t to_base64(uint64_t data);

    /// <summary>
    /// Decode the given base64 string to a byte array
    /// </summary>
    std::vector<unsigned char> from_base64(const utility::string_t& str);

    template <typename Source>
    utility::string_t print_string(const Source &val, const std::locale &loc)
    {
        utility::ostringstream_t oss;
        oss.imbue(loc);
        oss << val;
        if (oss.bad())
        {
            throw std::bad_cast();
        }
        return oss.str();
    }

    template <typename Source>
    utility::string_t print_string(const Source &val)
    {
        return print_string(val, std::locale());
    }

    inline utility::string_t print_string(const utility::string_t &val)
    {
        return val;
    }

    template <typename Target>
    Target scan_string(const utility::string_t &str, const std::locale &loc)
    {
        Target t;
        utility::istringstream_t iss(str);
        iss.imbue(loc);
        iss >> t;
        if (iss.bad())
        {
            throw std::bad_cast();
        }
        return t;
    }

    template <typename Target>
    Target scan_string(const utility::string_t &str)
    {
        return scan_string<Target>(str, std::locale());
    }

    inline utility::string_t scan_string(const utility::string_t &str)
    {
        return str;
    }
}

namespace details
{
    /// <summary>
    /// Cross platform RAII container for setting thread local locale.
    /// </summary>
    class scoped_c_thread_locale
    {
    public:
        _ASYNCRTIMP scoped_c_thread_locale();
        _ASYNCRTIMP ~scoped_c_thread_locale();

#if !defined(ANDROID) && !defined(__ANDROID__) && !defined(__ORBIS__) && !defined(__PROSPERO__) // CodePlex 269
#ifdef _WIN32
        typedef _locale_t xplat_locale;
#else
        typedef locale_t xplat_locale;
#endif

        static _ASYNCRTIMP xplat_locale c_locale();
#endif
    private:
#ifdef _WIN32
        std::string m_prevLocale;
        int m_prevThreadSetting;
#elif !(defined(ANDROID) || defined(__ANDROID__) || defined(__ORBIS__) || defined(__PROSPERO__))
        locale_t m_prevLocale;
#endif
        scoped_c_thread_locale(const scoped_c_thread_locale &);
        scoped_c_thread_locale & operator=(const scoped_c_thread_locale &);
    };

    /// <summary>
    /// Our own implementation of alpha numeric instead of std::isalnum to avoid
    /// taking global lock for performance reasons.
    /// </summary>
    inline bool __cdecl is_alnum(char ch)
    {
        return (ch >= '0' && ch <= '9')
            || (ch >= 'A' && ch <= 'Z')
            || (ch >= 'a' && ch <= 'z');
    }

    /// <summary>
    /// Simplistic implementation of make_unique. A better implementation would be based on variadic templates
    /// and therefore not be compatible with Dev10.
    /// </summary>
    template <typename _Type>
    std::unique_ptr<_Type> make_unique() {
        return std::unique_ptr<_Type>(new _Type());
    }

    template <typename _Type, typename _Arg1>
    std::unique_ptr<_Type> make_unique(_Arg1&& arg1) {
        return std::unique_ptr<_Type>(new _Type(std::forward<_Arg1>(arg1)));
    }

    template <typename _Type, typename _Arg1, typename _Arg2>
    std::unique_ptr<_Type> make_unique(_Arg1&& arg1, _Arg2&& arg2) {
        return std::unique_ptr<_Type>(new _Type(std::forward<_Arg1>(arg1), std::forward<_Arg2>(arg2)));
    }

    template <typename _Type, typename _Arg1, typename _Arg2, typename _Arg3>
    std::unique_ptr<_Type> make_unique(_Arg1&& arg1, _Arg2&& arg2, _Arg3&& arg3) {
        return std::unique_ptr<_Type>(new _Type(std::forward<_Arg1>(arg1), std::forward<_Arg2>(arg2), std::forward<_Arg3>(arg3)));
    }

    template <typename _Type, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
    std::unique_ptr<_Type> make_unique(_Arg1&& arg1, _Arg2&& arg2, _Arg3&& arg3, _Arg4&& arg4) {
        return std::unique_ptr<_Type>(new _Type(std::forward<_Arg1>(arg1), std::forward<_Arg2>(arg2), std::forward<_Arg3>(arg3), std::forward<_Arg4>(arg4)));
    }

    /// <summary>
    /// Cross platform utility function for performing case insensitive string comparision.
    /// </summary>
    /// <param name="left">First string to compare.</param>
    /// <param name="right">Second strong to compare.</param>
    /// <returns>true if the strings are equivalent, false otherwise</returns>
    inline bool str_icmp(const utility::string_t &left, const utility::string_t &right)
    {
#ifdef _WIN32
        return _wcsicmp(left.c_str(), right.c_str()) == 0;
#else
        return strcasecmp(left.c_str(), right.c_str());
#endif
    }

#ifdef _WIN32

/// <summary>
/// Category error type for Windows OS errors.
/// </summary>
class windows_category_impl : public std::error_category
{
public:
    virtual const char *name() const CPPREST_NOEXCEPT { return "windows"; }

    _ASYNCRTIMP virtual std::string message(int errorCode) const CPPREST_NOEXCEPT;

    _ASYNCRTIMP virtual std::error_condition default_error_condition(int errorCode) const CPPREST_NOEXCEPT;
};

/// <summary>
/// Gets the one global instance of the windows error category.
/// </summary>
/// <returns>An error category instance.</returns>
_ASYNCRTIMP const std::error_category & __cdecl windows_category();

#else

/// <summary>
/// Gets the one global instance of the linux error category.
/// </summary>
/// </returns>An error category instance.</returns>
_ASYNCRTIMP const std::error_category & __cdecl linux_category();

#endif

/// <summary>
/// Gets the one global instance of the current platform's error category.
/// </summary>
_ASYNCRTIMP const std::error_category & __cdecl platform_category();

/// <summary>
/// Creates an instance of std::system_error from a OS error code.
/// </summary>
inline std::system_error __cdecl create_system_error(unsigned long errorCode)
{
    std::error_code code((int)errorCode, platform_category());
    return std::system_error(code, code.message());
}

/// <summary>
/// Creates a std::error_code from a OS error code.
/// </summary>
inline std::error_code __cdecl create_error_code(unsigned long errorCode)
{
    return std::error_code((int)errorCode, platform_category());
}

/// <summary>
/// Creates the corresponding error message from a OS error code.
/// </summary>
inline utility::string_t __cdecl create_error_message(unsigned long errorCode)
{
    return utility::conversions::to_string_t(create_error_code(errorCode).message());
}

}

class datetime
{
public:
    typedef uint64_t interval_type;

    /// <summary>
    /// Defines the supported date and time string formats.
    /// </summary>
    enum date_format { RFC_1123, ISO_8601 };

    /// <summary>
    /// Returns the current UTC time.
    /// </summary>
    static _ASYNCRTIMP datetime __cdecl utc_now();

    /// <summary>
    /// An invalid UTC timestamp value.
    /// </summary>
    enum:interval_type { utc_timestamp_invalid = static_cast<interval_type>(-1) };

    /// <summary>
    /// Returns seconds since Unix/POSIX time epoch at 01-01-1970 00:00:00.
    /// If time is before epoch, utc_timestamp_invalid is returned.
    /// </summary>
    static interval_type utc_timestamp()
    {
        const auto seconds = utc_now().to_interval() / _secondTicks;
        if (seconds >= 11644473600LL)
        {
            return seconds - 11644473600LL;
        }
        else
        {
            return utc_timestamp_invalid;
        }
    }

    datetime() : m_interval(0)
    {
    }

    /// <summary>
    /// Creates <c>datetime</c> from a string representing time in UTC in RFC 1123 format.
    /// </summary>
    /// <returns>Returns a <c>datetime</c> of zero if not successful.</returns>
    static _ASYNCRTIMP datetime __cdecl from_string(const utility::string_t& timestring, date_format format = RFC_1123);

    /// <summary>
    /// Returns a string representation of the <c>datetime</c>.
    /// </summary>
    _ASYNCRTIMP xsapi_internal_string to_string_internal(date_format format = RFC_1123) const;

    /// <summary>
    /// Returns the integral time value.
    /// </summary>
    interval_type to_interval() const
    {
        return m_interval;
    }

    datetime operator- (interval_type value) const
    {
        return datetime(m_interval - value);
    }

    datetime operator+ (interval_type value) const
    {
        return datetime(m_interval + value);
    }

    bool operator== (datetime dt) const
    {
        return m_interval == dt.m_interval;
    }

    bool operator!= (const datetime& dt) const
    {
        return !(*this == dt);
    }

    static interval_type from_milliseconds(unsigned int milliseconds)
    {
        return milliseconds*_msTicks;
    }

    static interval_type from_seconds(unsigned int seconds)
    {
        return seconds*_secondTicks;
    }

    static interval_type from_minutes(unsigned int minutes)
    {
        return minutes*_minuteTicks;
    }

    static interval_type from_hours(unsigned int hours)
    {
        return hours*_hourTicks;
    }

    static interval_type from_days(unsigned int days)
    {
        return days*_dayTicks;
    }

    bool is_initialized() const
    {
        return m_interval != 0;
    }

private:

    friend int operator- (datetime t1, datetime t2);

    static const interval_type _msTicks = static_cast<interval_type>(10000);
    static const interval_type _secondTicks = 1000*_msTicks;
    static const interval_type _minuteTicks = 60*_secondTicks;
    static const interval_type _hourTicks   = 60*60*_secondTicks;
    static const interval_type _dayTicks    = 24*60*60*_secondTicks;


#ifdef _WIN32
    // void* to avoid pulling in windows.h
    static _ASYNCRTIMP bool __cdecl system_type_to_datetime(/*SYSTEMTIME*/ void* psysTime, uint64_t seconds, datetime * pdt);
#else
    static datetime timeval_to_datetime(const timeval &time);
#endif

    // Private constructor. Use static methods to create an instance.
    datetime(interval_type interval) : m_interval(interval)
    {
    }

    // Storing as hundreds of nanoseconds 10e-7, i.e. 1 here equals 100ns.
    interval_type m_interval;
};

#ifndef _WIN32

// temporary workaround for the fact that
// utf16char is not fully supported in GCC
class cmp
{
public:

    static int icmp(std::string left, std::string right)
    {
        size_t i;
        for (i = 0; i < left.size(); ++i)
        {
            if (i == right.size()) return 1;

            auto l = cmp::tolower(left[i]);
            auto r = cmp::tolower(right[i]);
            if (l > r) return 1;
            if (l < r) return -1;
        }
        if (i < right.size()) return -1;
        return 0;
    }

private:
    static char tolower(char c)
    {
        if (c >= 'A' && c <= 'Z')
            return static_cast<char>(c - 'A' + 'a');
        return c;
    }
};

#endif

inline int operator- (datetime t1, datetime t2)
{
    auto diff = (t1.m_interval - t2.m_interval);

    // Round it down to seconds
    diff /= 10 * 1000 * 1000;

    return static_cast<int>(diff);
}

/// <summary>
/// Nonce string generator class.
/// </summary>
class nonce_generator
{
public:

    /// <summary>
    /// Define default nonce length.
    /// </summary>
    enum { default_length = 32 };

    /// <summary>
    /// Nonce generator constructor.
    /// </summary>
    /// <param name="length">Length of the generated nonce string.</param>
    nonce_generator(int length=default_length) :
        m_random(static_cast<unsigned int>(utility::datetime::utc_timestamp())),
        m_length(length)
    {}

    /// <summary>
    /// Generate a nonce string containing random alphanumeric characters (A-Za-z0-9).
    /// Length of the generated string is set by length().
    /// </summary>
    /// <returns>The generated nonce string.</returns>
    _ASYNCRTIMP utility::string_t generate();

    /// <summary>
    /// Get length of generated nonce string.
    /// </summary>
    /// <returns>Nonce string length.</returns>
    int length() const { return m_length; }

    /// <summary>
    /// Set length of the generated nonce string.
    /// </summary>
    /// <param name="length">Lenght of nonce string.</param>
    void set_length(int length) { m_length = length; }

private:
    static const utility::char_t* c_allowed_chars;
    std::mt19937 m_random;
    int m_length;
};

} // namespace utility;

} } }

#if HC_PLATFORM_IS_MICROSOFT
#pragma warning( pop )
#endif
