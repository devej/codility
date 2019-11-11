
#include "./common.h"

#include <cstdint>
#include <iostream>
#include <vector>

std::vector<int> base_neg_two( std::vector<int> &A, std::vector<int> &B );
std::int32_t base_neg_two_tests();

std::int64_t binarygap(std::int64_t number);
void binarygap_tests();

std::int64_t oddoccurrences( std::vector< std::int64_t >& A );
void oddoccurrences_tests();

std::vector<std::int64_t> cyclicrotation( std::vector<std::int64_t> &A, int K );
void cyclicrotation_tests();

std::int32_t main(std::int32_t /*argc*/, char ** /*argv*/)
{
	base_neg_two_tests();
	binarygap_tests();
	oddoccurrences_tests();
	cyclicrotation_tests();

	return 0;
}
