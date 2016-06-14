cmake_minimum_required(VERSION 3.2)

project(Kulay CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -ggdb3")

find_package(BISON)
find_package(FLEX)

bison_target(Kulay grammar.yy ${Kulay_SOURCE_DIR}/parser.cpp)
flex_target(Kulay lexer.ll ${Kulay_SOURCE_DIR}/lexer.cpp)

set(ast_srcs
    ast/add.cpp
    ast/add.h
    ast/ast.h
    ast/binop.h
    ast/block.h
    ast/decls.cpp
    ast/decls.h
    ast/defaultvisitor.h
    ast/expr.h
    ast/exprinstr.h
    ast/identifier.h
    ast/instrbody.h
    ast/instr.cpp
    ast/instr.h
    ast/interpretervisitor.h
    ast/intlit.h
    ast/mul.cpp
    ast/mul.h
    ast/print.h
    ast/sub.cpp
    ast/sub.h
    ast/varget.h
    ast/varset.cpp
    ast/varset.h
    )

include_directories(.)

add_executable(kulc
    ${ast_srcs}
    ${BISON_Kulay_OUTPUTS}
    ${FLEX_Kulay_OUTPUTS}
    )
