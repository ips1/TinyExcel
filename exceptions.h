#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

// Exceptions used throughout the entire project

class DivideByZeroException: public virtual std::exception
{

};

class InvalidPostfixException: public virtual std::exception
{

};

class InvalidCellContentException: public virtual std::exception
{

};

class InvalidCoordinatesException: public virtual std::exception
{

};

class CoordinatesOverflowException: public virtual std::exception
{

};

class InvalidInfixException: public virtual std::exception
{

};

class InvalidOperatorException: public virtual std::exception
{

};

class CycleException: public virtual std::exception
{

};

class DependencyException: public virtual std::exception
{

};

class EvaluationException: public virtual std::exception
{

};

class CellNotSetException: public virtual std::exception
{

};

class FileOpenException: public virtual std::exception
{

};

class InvalidCommandException: public virtual std::exception
{

};

class NotEnoughArgumentsException: public virtual std::exception
{

};

#endif // EXCEPTIONS_H
