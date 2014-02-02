#pragma once

#include <exception>

class DivideByZeroException: public virtual std::exception
{

};

class InvalidPostfixException: public virtual std::exception
{

};

class InvalidCellContentException: public virtual std::exception
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


