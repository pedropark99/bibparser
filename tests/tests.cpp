#include <catch2/catch_test_macros.hpp>

#include "parser.hpp"

int number( int n ) {
    return n;
}

TEST_CASE( "Teste", "[test]" ) {
    REQUIRE( number(1) == 1 );
    REQUIRE( number(2) == 2 );
}