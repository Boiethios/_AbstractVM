#include "OperandFactory.class.hpp"
#include "Operand.template.hpp"

#include <boost/lexical_cast.hpp>

OperandFactory const &
OperandFactory::Get(void)
{
	static OperandFactory _instance;

	return _instance;
}


OperandFactory::OperandFactory(void) :
	_funcs{
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	}
{
}


IOperand const *
OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	try
	{
		return (this->*_funcs[type])(value);
	}
	catch (std::exception const &e)
	{
		throw Exception(e.what());
	}
}


IOperand const *
OperandFactory::createInt8(std::string const &value) const
{
	int8_t	nbr(boost::numeric_cast<int8_t>(boost::lexical_cast<int>(value)));

	return new Operand<int8_t>(nbr);
}

IOperand const *
OperandFactory::createInt16(std::string const &value) const
{
	int16_t	nbr(boost::numeric_cast<int16_t>(boost::lexical_cast<int>(value)));

	return new Operand<int16_t>(nbr);
}

IOperand const *
OperandFactory::createInt32(std::string const &value) const
{
	int32_t	nbr(boost::numeric_cast<int32_t>(boost::lexical_cast<int>(value)));

	return new Operand<int32_t>(nbr);
}

IOperand const *
OperandFactory::createFloat(std::string const &value) const
{
	return new Operand<float>(boost::lexical_cast<float>(value));
}

IOperand const *
OperandFactory::createDouble(std::string const &value) const
{
	return new Operand<double>(boost::lexical_cast<double>(value));
}
