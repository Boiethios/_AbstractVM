project(_AbstractVM)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11 -Werror -Wall -Wextra -Wconversion)

aux_source_directory(src SRC_LIST)
set(INC_LIST

	src/Main.class.hpp
	src/Exception.class.hpp
	src/IOperand.interface.hpp
	src/Operand.template.hpp
	src/eOperandType.enum.hpp
	src/OperandFactory.class.hpp
	src/Stack.class.hpp
	src/Lexer.class.hpp
	src/Parser.class.hpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})
