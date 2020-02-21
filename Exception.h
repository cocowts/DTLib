#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
public:
    Exception(const char *message);
    Exception(const char *file, int line);
    Exception(const char *message, const char *file, int line);

    Exception(const Exception &e);
    Exception &operator= (const Exception &e);

    virtual const char *message() const;
    virtual const char *location() const;

    virtual ~Exception() = 0;

protected:
    char *m_message = nullptr;
    char *m_location = nullptr;
};

class ArithmeticExcption : public Exception
{
public:
    ArithmeticExcption() : Exception(nullptr) { }
    ArithmeticExcption(const char *message) : Exception(message) { }
    ArithmeticExcption(const char *file, int line) : Exception(file, line) { }
    ArithmeticExcption(const char *message, const char *file, int line) : Exception(message, file, line) { }

    ArithmeticExcption(const ArithmeticExcption &e) : Exception(e) { }

    ArithmeticExcption &operator= (const ArithmeticExcption &e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~ArithmeticExcption() override { }
};

class NullPointerException : public Exception
{
public:
    NullPointerException() : Exception(nullptr) { }
    NullPointerException(const char *message) : Exception(message) { }
    NullPointerException(const char *file, int line) : Exception(file, line) { }
    NullPointerException(const char *message, const char *file, int line) : Exception(message, file, line) { }

    NullPointerException(const NullPointerException &e) : Exception(e) { }

    NullPointerException &operator= (const NullPointerException &e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~NullPointerException() override { }
};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() : Exception(nullptr) { }
    IndexOutOfBoundsException(const char *message) : Exception(message) { }
    IndexOutOfBoundsException(const char *file, int line) : Exception(file, line) { }
    IndexOutOfBoundsException(const char *message, const char *file, int line) : Exception(message, file, line) { }

    IndexOutOfBoundsException(const IndexOutOfBoundsException &e) : Exception(e) { }

    IndexOutOfBoundsException &operator= (const IndexOutOfBoundsException &e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~IndexOutOfBoundsException() override { }
};

class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() : Exception(nullptr) { }
    NoEnoughMemoryException(const char *message) : Exception(message) { }
    NoEnoughMemoryException(const char *file, int line) : Exception(file, line) { }
    NoEnoughMemoryException(const char *message, const char *file, int line) : Exception(message, file, line) { }

    NoEnoughMemoryException(const NoEnoughMemoryException &e) : Exception(e) { }

    NoEnoughMemoryException &operator= (const NoEnoughMemoryException &e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~NoEnoughMemoryException() override { }
};

class InvalidParameterExcetion : public Exception
{
public:
    InvalidParameterExcetion() : Exception(nullptr) { }
    InvalidParameterExcetion(const char *message) : Exception(message) { }
    InvalidParameterExcetion(const char *file, int line) : Exception(file, line) { }
    InvalidParameterExcetion(const char *message, const char *file, int line) : Exception(message, file, line) { }

    InvalidParameterExcetion(const InvalidParameterExcetion &e) : Exception(e) { }

    InvalidParameterExcetion &operator= (const InvalidParameterExcetion &e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~InvalidParameterExcetion() override { }
};

class InvalidOpertionExcetion : public Exception
{
public:
    InvalidOpertionExcetion() : Exception(nullptr) { }
    InvalidOpertionExcetion(const char *message) : Exception(message) { }
    InvalidOpertionExcetion(const char *file, int line) : Exception(file, line) { }
    InvalidOpertionExcetion(const char *message, const char *file, int line) : Exception(message, file, line) { }

    InvalidOpertionExcetion(const InvalidOpertionExcetion &e) : Exception(e) { }

    InvalidOpertionExcetion &operator= (const InvalidOpertionExcetion &e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~InvalidOpertionExcetion() override { }
};

}

#endif // EXCEPTION_H
