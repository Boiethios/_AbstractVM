#include "Operand.template.hpp"

template<>
eOperandType Operand<int8_t>::getType(void) const
{return Int8;}

template<>
eOperandType Operand<int16_t>::getType(void) const
{return Int16;}

template<>
eOperandType Operand<int32_t>::getType(void) const
{return Int32;}

template<>
eOperandType Operand<float>::getType(void) const
{return Float;}

template<>
eOperandType Operand<double>::getType(void) const
{return Double;}
