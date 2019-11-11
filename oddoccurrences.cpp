/*
Odd Occurrences

A non-empty array A consisting of N integers is given. The array contains an odd number of elements, and each element of
the array can be paired with another element that has the same value, except for one element that is left unpaired.

For example, in array A such that:
A[0] = 9  A[1] = 3  A[2] = 9
A[3] = 3  A[4] = 9  A[5] = 7
A[6] = 9

	the elements at indexes 0 and 2 have value 9,
	the elements at indexes 1 and 3 have value 3,
	the elements at indexes 4 and 6 have value 9,
	the element at index 5 has value 7 and is unpaired.

Write a function:

int solution(vector<int> &A);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

Write an efficient algorithm for the following assumptions:

	N is an odd integer within the range [1..1,000,000];
	each element of array A is an integer within the range [1..1,000,000,000];
	all but one of the values in A occur an even number of times.
*/

#include "./common.h"

#include <vector>
#include <algorithm>

std::int64_t oddoccurrences( std::vector< std::int64_t >& A )
{
	const auto a_size = A.size();

	if( a_size % 2 == 0 ) {
		COUT( "Bad array size, must be odd: " << A.size() << std::endl );
		return -1;
	}

	// degenerate case
	if( a_size == 1 )
		return A[0];

	std::sort( A.begin(), A.end() );
	std::int64_t lastval{ A[0] };

	for( size_t x = 0; x < a_size; ++x )
	{
		auto thisval = A[x];

		if( x % 2 == 0 ) // even
		{
			if( thisval != lastval )
				return thisval;
		}
		else // odd
		{
			lastval = thisval;
		}
	}

	return -1;
}

void oddoccurrences_tests()
{
	std::vector< std::int64_t > v{ 9, 3, 9, 3, 9, 7, 9 };
	auto result = oddoccurrences( v );
	if( result != 7 )
		COUT( "FAIL OddOccurrences test 1: " << result << std::endl );

	v = { 7, 9, 3, 9, 3, 9, 9 };
	result = oddoccurrences( v );
	if( result != 7 )
		COUT( "FAIL OddOccurrences test 2: " << result << std::endl );

	v = { 9, 3, 9, 3, 9, 9, 7 };
	result = oddoccurrences( v );
	if( result != 7 )
		COUT( "FAIL OddOccurrences test 3: " << result << std::endl );

	v = { 7 };
	result = oddoccurrences( v );
	if( result != 7 )
		COUT( "FAIL OddOccurrences test 4: " << result << std::endl );
}

