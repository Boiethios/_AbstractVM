#include "Operand.template.hpp"

template<>
eOperandType Operand<int8_t>::getType(void) const
{return INT8;}

template<>
eOperandType Operand<int16_t>::getType(void) const
{return INT16;}

template<>
eOperandType Operand<int32_t>::getType(void) const
{return INT32;}

template<>
eOperandType Operand<float>::getType(void) const
{return FLOAT;}

template<>
eOperandType Operand<double>::getType(void) const
{return DOUBLE;}
