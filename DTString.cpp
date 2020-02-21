#include "DTString.h"

#include <cstring>
#include <cstdlib>

namespace DTLib
{

int *String::make_pmt(const char *p)  // O(m)
{
    size_t len = strlen(p);
    int *ret = static_cast<int*>(malloc(sizeof(int) * len));

    if (ret != nullptr)
    {
        int ll = 0;

        ret[0] = 0;

        for (size_t i=1; i<len; ++i)
        {
            while ((ll > 0) && (p[i] != p[ll]))
            {
                ll = ret[ll - 1];
            }

            if (p[i] == p[ll])
            {
                ++ll;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int String::kmp(const char *s, const char *p)  // O(m + n)
{
   int ret = -1;
   int sl = strlen(s);
   int pl = strlen(p);
   int *pmt = make_pmt(p);  // O(m)

   if ((pmt != nullptr) && (0 < pl) &&(pl <= sl))
   {
       for (int i=0, j = 0; i < sl; ++i)  // O(n)
       {
           while ((j > 0) && (s[i] != p[j]))
           {
               j = pmt[j - 1];
           }

           if (s[i] == p[j])
           {
               ++j;
           }

           if (j == pl)
           {
               ret = i + 1 - pl;
               break;
           }
       }
   }

   free(pmt);

   return ret;
}

String::String() : String("")
{
}

String::String(const String &s) : String(s.m_str)
{
}

String::String(const char* s)
{
    char* str = strdup(s);

    if (str != nullptr)
    {
        m_str = str;

        m_length = strlen(str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enogh memory to create str object ...");
    }
}

size_t String::length() const
{
    return m_length;
}

const char *String::str() const
{
    return m_str;
}

bool String::startWith(const char *s) const
{
    bool ret = (s != nullptr);

    if (ret)
    {
        size_t len = strlen(s);

        ret = (m_length > len) && (strncmp(m_str, s, len) == 0);
    }

    return ret;
}

bool String::startWith(const String &s) const
{
    return startWith(s.str());
}

bool String::endOf(const char *s) const
{
    bool ret = (s != nullptr);

    if (ret)
    {
        size_t len = strlen(s);
        char *str = m_str + (m_length - len);

        ret = (m_length > len) && (strncmp(str, s, len) == 0);
    }

    return ret;
}

bool String::endOf(const String &s) const
{
    return endOf(s.str());
}

String &String::insert(size_t i, const char *s)
{
    if (i <= m_length)
    {
        if ((s != nullptr) || s[0] != '\0')
        {
            size_t len = strlen(s);
            char *str = reinterpret_cast<char*>(malloc(m_length + len + 1));

            if (str != nullptr)
            {
               strncpy(str, m_str, i);
               strncpy(str + i, s, len);
               strncpy(str + i + len, m_str + i, m_length - i);
               str[len + m_length] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert str object ...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid");
    }

    return *this;
}

String &String::insert(size_t i, const String &s)
{
    return insert(i, s.str());
}

String &String::trim()
{
    size_t b = 0;
    size_t e = m_length - 1;

    while (m_str[b] == ' ') b++;
    while (m_str[e] == ' ') e--;

    if (b == 0)
    {
        m_str[e + 1] = '\0';
        m_length = e + 1;
    }
    else
    {
        for (size_t i=0, j = b; j<=e; ++i, ++j)
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}

int String::indexOf(const char *s) const
{
    return kmp(m_str, s);
}

int String::indexOf(const String &s) const
{
    return kmp(m_str, s.m_str);
}

String &String::remove(size_t i, size_t len)
{
    if (i < m_length)
    {
        size_t n = i;
        size_t m = i + len;

        while ((n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

String &String::remove(const char *s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

String &String::remove(const String &s)
{
    return remove(indexOf(s), s.length());
}

String &String::replace(const char *t, const char* s)
{
    int index = indexOf(t);

    if (index >= 0)
    {
        remove(t);
        insert(index, s);
    }

    return *this;
}

String &String::replace(const String &t, const char *s)
{
    return replace(t.str(), s);
}

String &String::replace(const char *t, const String &s)
{
    return replace(t, s.str());
}

String &String::replace(const String &t, const String &s)
{
    return replace(t.str(), s.str());
}

String String::sub(size_t i, size_t len) const
{
    String ret;

    if (i < m_length)
    {
        if (len + i > m_length) len = m_length - i;

        char *str = reinterpret_cast<char*>(malloc(len + 1));

        if (str != nullptr)
        {
            strncpy(str, m_str + i, len);

            str[len] = '\0';
            ret = str;
        }

        free(str);
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is Invalid ...");
    }

    return ret;
}

bool String::operator == (const char *s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator == (const String &s) const
{
    return (strcmp(m_str, s.str()) == 0);
}

bool String::operator != (const char *s) const
{
    return (strcmp(m_str, s ? s : "") != 0);
}

bool String::operator != (const String &s) const
{
    return (strcmp(m_str, s.str()) != 0);
}

bool String::operator > (const char *s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator > (const String &s) const
{
    return (strcmp(m_str, s.str()) > 0);
}

bool String::operator < (const char *s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator < (const String &s) const
{
    return (strcmp(m_str, s.str()) < 0);
}

bool String::operator >= (const char *s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator >= (const String &s) const
{
    return (strcmp(m_str, s.str()) >= 0);
}

bool String::operator <= (const char *s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

bool String::operator <= (const String &s) const
{
    return (strcmp(m_str, s.str()) <= 0);
}

String String::operator + (const char *s) const
{
    String ret;

    size_t len = m_length + strlen(s ? s : "");

    char *str = reinterpret_cast<char*>(malloc(len + 1));

    if (str != nullptr)
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create str object ...");
    }

    return ret;
}

String String::operator + (const String &s) const
{
    return (*this + s.str());
}

String &String::operator += (const char *s)
{
    return (*this = *this + s);
}

String &String::operator += (const String &s)
{
    return (*this = *this + s.str());
}

String String::operator - (const char *s) const
{
    return String(*this).remove(s);
}

String String::operator - (const String &s) const
{
    return String(*this).remove(s);
}

String &String::operator -= (const char *s)
{
    return remove(s);
}

String &String::operator -= (const String &s)
{
    return remove(s);
}

String &String::operator = (const char *s)
{
    if (m_str != s)
    {
        char *str = strdup(s ? s : "");

        if (str != nullptr)
        {
            free(m_str);

            m_str = str;
            m_length = strlen(str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create str object ...");
        }
    }

    return *this;
}

String &String::operator = (const char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

String &String::operator = (const String &s)
{
    return (*this = s.str());
}

char &String::operator[] (size_t i)
{
    if (i < m_length)
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterExcetion, "Parameter i invalid...");
    }
}

char String::operator[] (size_t i) const
{
    return const_cast<String&>(*this)[i];
}

String::~String()
{
    free(m_str);
}

}


