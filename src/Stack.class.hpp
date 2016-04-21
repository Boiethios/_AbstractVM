#pragma once

#include <deque>

#include "IOperand.interface.hpp"

class Stack : private std::deque<IOperand const *>
{
	public:
		Stack(void);

		~Stack(void) = default;
		Stack(Stack const &) = delete;
		Stack & operator=(Stack const &) = delete;

		void
		push(IOperand const *operand);

		IOperand const *
		pop(void);

		void
		dump(void) const;

		void
		assert(IOperand const *operand) const;

		void
		print(void) const;


		void
		add(void);

		void
		sub(void);

		void
		mul(void);

		void
		div(void);

		void
		mod(void);
};
