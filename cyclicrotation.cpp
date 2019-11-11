/*
Cyclic Rotation

An array A consisting of N integers is given. Rotation of the array means that each element is shifted right by one
index, and the last element of the array is moved to the first place. For example, the rotation of array
A = [3, 8, 9, 7, 6] is [6, 3, 8, 9, 7] (elements are shifted right by one index and 6 is moved to the first place).

The goal is to rotate array A K times; that is, each element of A will be shifted to the right K times.

Write a function:

    vector<int> solution(vector<int> &A, int K);

that, given an array A consisting of N integers and an integer K, returns the array A rotated K times.

For example, given
    A = [3, 8, 9, 7, 6]
    K = 3

the function should return [9, 7, 6, 3, 8]. Three rotations were made:
    [3, 8, 9, 7, 6] -> [6, 3, 8, 9, 7]
    [6, 3, 8, 9, 7] -> [7, 6, 3, 8, 9]
    [7, 6, 3, 8, 9] -> [9, 7, 6, 3, 8]

For another example, given
    A = [0, 0, 0]
    K = 1

the function should return [0, 0, 0]

Given
    A = [1, 2, 3, 4]
    K = 4

the function should return [1, 2, 3, 4]

Assume that:

        N and K are integers within the range [0..100];
        each element of array A is an integer within the range [−1,000..1,000].

In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.
*/

#include "./common.h"
#include <vector>
#include <algorithm>

using IntVec = std::vector< std::int64_t >;

IntVec cyclicrotation( IntVec& A, std::int64_t K )
{
	for( int64_t x = 0; x < K; ++x )
		std::rotate(A.begin(), A.end() - 1, A.end());

	return A;
}

void cyclicrotation_tests()
{
	IntVec vec{ 1, 2, 3, 4 };
	IntVec expected{ 4, 1, 2, 3 };
	auto r = cyclicrotation( vec, 1 );
	if( r != expected ) {
		COUT( "FAILED Cyclicrotation test 1" << std::endl );
	}

	vec = { 1, 2, 3, 4, 5, 6 };
	expected = { 1, 2, 3, 4, 5, 6 };
	r = cyclicrotation(vec, 6);
	if (r != expected)
	{
		COUT("FAILED Cyclicrotation test 2" << std::endl);
	}
}
