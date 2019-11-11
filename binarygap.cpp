/*
A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is
surrounded by ones at both ends in the binary representation of N.

For example, number 9 has binary representation 1001 and contains a binary gap of length 2.
The number 529 has binary representation 1000010001 and contains two binary gaps: one of
length 4 and one of length 3. The number 20 has binary representation 10100 and contains one
binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps.
The number 32 has binary representation 100000 and has no binary gaps.

Write a function:

    class Solution { public int solution(int N); }

that, given a positive integer N, returns the length of its longest binary gap. The function
should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary representation
10000010001 and so its longest binary gap is of length 5. Given N = 32 the function should
return 0, because N has binary representation '100000' and thus no binary gaps.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..2,147,483,647].

*/
#include "common.h"

#include <cstdint>
#include <iostream>


std::int64_t binarygap( std::int64_t number )
{
	// COUT( number << "'s bits are:" << std::endl );
	constexpr std::int64_t mask = 0x00000001;
	std::int64_t maxgap{ 0 };
	std::int64_t curgap{ 0 };
	bool start{ false };

	// test each bit
	while( number )
	{
		const bool bit = number & mask;
		if( bit )
		{
			// maybe start of a new gap
			start = true;
			maxgap = std::max( maxgap, curgap );
			curgap = 0;
		}
		else
		{
			// in a gap
			if( start )
				++curgap;
		}

		// COUT( bit << " " );
		number >>= 1;
	}
	// COUT( std::endl );

	return maxgap;
}

void binarygap_tests()
{
	// 9 = 2
	// 529 = 4
	// 20 = 1
	// 15 = 0
	// 32 = 0
	std::int64_t r = binarygap( 9 );
	if( r != 2 )
		std::cout << "FAILED: 9 = " << r << std::endl;

	r = binarygap( 529 );
	if( r != 4 )
		std::cout << "FAILED: 529 = " << r << std::endl;

	r = binarygap( 20 );
	if( r != 1 )
		std::cout << "FAILED: 20 = " << r << std::endl;

	r = binarygap( 15 );
	if( r != 0 )
		std::cout << "FAILED: 15 = " << r << std::endl;

	r = binarygap( 32 );
	if( r != 0 )
		std::cout << "FAILED: 32 = " << r << std::endl;
}
