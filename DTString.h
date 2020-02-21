#ifndef STRING_H
#define STRING_H

#include "Exception.h"
#include "Object.h"

#include <cstdint>

namespace DTLib
{

class String
{
public:
    String();
    String(const String &s);
    String(const char* s);

    size_t length() const;
    const char *str() const;

    bool startWith(const char *s) const;
    bool startWith(const String &s) const;
    bool endOf(const char *s) const;
    bool endOf(const String &s) const;

    String &insert(size_t i, const char *s);
    String &insert(size_t i, const String &s);
    String &trim();
    int indexOf(const char *s) const;
    int indexOf(const String &s) const;
    String &remove(size_t i, size_t len);
    String &remove(const char *s);
    String &remove(const String &s);
    String &replace(const char *t, const char* s);
    String &replace(const String &t, const char *s);
    String &replace(const char *t, const String &s);
    String &replace(const String &t, const String &s);
    String sub(size_t i, size_t len) const;

    bool operator == (const char *s) const;
    bool operator == (const String &s) const;
    bool operator != (const char *s) const;
    bool operator != (const String &s) const;
    bool operator > (const char *s) const;
    bool operator > (const String &s) const;
    bool operator < (const char *s) const;
    bool operator < (const String &s) const;
    bool operator >= (const char *s) const;
    bool operator >= (const String &s) const;
    bool operator <= (const char *s) const;
    bool operator <= (const String &s) const;

    String operator + (const char *s) const;
    String operator + (const String &s) const;
    String &operator += (const char *s);
    String &operator += (const String &s);

    String operator - (const char *s) const;
    String operator - (const String &s) const;
    String &operator -= (const char *s);
    String &operator -= (const String &s);

    String &operator = (const char c);
    String &operator = (const char *s);
    String &operator = (const String &s);

    char &operator[] (size_t i);
    char operator[] (size_t i) const;

    ~String();

protected:
    char *m_str = nullptr;
    size_t m_length = 0;

    static int *make_pmt(const char *p);
    static int kmp(const char *s, const char *p);
};

}

#endif // STRING_H
