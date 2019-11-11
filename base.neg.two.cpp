
#include <iostream>
#include <string>
#include <vector>
#include <array>

/*
100111 represents -23
001011 represents -12
10011  represents 9
001    represents 4,
because:

| 1 | -2 | 4 | -8 | 16 | -32 | ... |
|---|----|---|----|----|-----|-----|
| 1 | 0  | 0 | 1  | 1  | 1   |     | = 1 + 0 + 0 + (-8) + 16 + (-32) = -23
| 0 | 0  | 1 | 0  | 1  | 1   |     | = 0 + 0 + 4 + 0    + 16 + (-32) = -12
| 1 | 0  | 0 | 1  | 1  |     |     | = 1 + 0 + 0 + (-8) + 16         = 9
| 0 | 0  | 1 |    |    |     |     | = 0 + 0 + 4                     = 4
*/

// pre-calculated and stored things
constexpr std::array<int,20> powers{ 1, -2, 4, -8, 16, -32, 64, -128, 256, -512, 1'024, -2'048, 4'096, -8'192, 16'384, -32'768, 65'536, -131'072, 262'144, -524'288 };
//                                     0  1  2   3  4   5    6    7   8     9   10    11    12     13    14      15     16      17     18       19
constexpr std::array<int,20> sum_left{ 0, 0, 1, -2, 5, -10, 21, -42, 85, -170, 341, -682, 1365, -2730, 5461, -10922, 21845, -43690, 87381, -174762 };

constexpr int ENCODE_MAX = powers[18];
constexpr int ENCODE_MIN = powers[19];


int to_int( const std::vector<int>& bits )
{
	int result{ 0 };
	int pow{ 0 };

	for( auto i : bits )
	{
		result += i * powers[pow++];
	}
	
	return result;
}


std::vector<int> to_bin( int target )
{
	if( (target > ENCODE_MAX) || (target < ENCODE_MIN) ) {
		std::cout << target << " exceeds encode limits" << std::endl;
		return {};
	}

	//std::cout << "encoding " << target << std::endl;
	std::vector<int> result( powers.size() );
	int wrk = 0;
	int dist = target - wrk;

	auto Encode = [&]( int x ) {
		//std::cout << "\t + encoded " << x << " (" << powers[x] << ")" << std::endl;
		result[x] = 1;
		wrk += powers[x];
	};
	
	auto EncodeClosestLargest = [&]() {
		for( int x = powers.size()-2; x >= 0; x-=2 )
		{
			// if dist > the sum of the lesser (same sign-ed) factors, choose this one
			if( dist > sum_left[x] ) {
				Encode( x );
				break;
			}
		}
	};

	auto EncodeClosestSmallest = [&]() {
		for( int x = powers.size()-1; x >= 0; x-=2 )
		{
			// if dist < the sum of the lesser (same sign-ed) factors, choose this one
			if( dist < sum_left[x] ) {
				Encode( x );
				break;
			}
		}
	};


	while( true ) {
		dist = target - wrk;
		//std::cout << "wrk: " << wrk << " dist: " << dist << std::endl;
		if( dist == 0 )
			break; // yay, finished

		if( dist > 0 ) {
			EncodeClosestLargest();
		}
		else // dist < 0
		{
			EncodeClosestSmallest();
		}
	}

	return result;
}


void multiply_tests()
{
	std::cout << "Running multiply tests..." << std::endl;
	bool pass = true;

	for( int x = -300; x <= 300; ++x )
	{
		auto A = to_bin(x);

		for( int y = -300; y <= 300; ++y )
		{
			auto B = to_bin( y );
			auto expected_int = x * y;
			auto bin = to_bin( to_int(A) * to_int(B) );
			auto result = to_int( bin );
			if( result != expected_int )
			{
				pass = false;
				std::cout << "FAILED multiplying " << x << " * " << y << std::endl
						<< " got " << result;
				return;
			}
		}
	}

	if( pass )
		std::cout << "All tests passed." << std::endl;
}


// round-trip encodings between -100'000 and 100'000
void exhaustive_roundtrip_test()
{
	std::cout << "Running exhaustive tests..." << std::endl;
	bool pass = true;

	for( int x = -100'000; x <= 100'000; ++x )
	{
		auto bin = to_bin( x );
		auto i = to_int( bin );
		if( i != x ) {
			pass = false;
			std::cout << "FAILED round trip encoding of " << x << std::endl
					<< "i = " << i << " bin: ";
			for( auto p: bin )
			{
				std::cout << p << " ";
			}
			std::cout << std::endl;
			break;
		}
	}

	int max = ENCODE_MAX + 1;
	auto q = to_int( to_bin( max ) );
	if( q != 0 ) {
		pass = false;
		std::cout << "Failed atempting ot encode more then the max." << std::endl;
	}

	int min = ENCODE_MIN - 1;
	auto r = to_int( to_bin( min ) );
	if( r != 0 ) {
		pass = false;
		std::cout << "Failed atempting ot encode less then the min." << std::endl;
	}

	if( pass )
		std::cout << "All tests passed." << std::endl;
}

// a few select test cases
void minimal_test()
{
	const std::vector<int> cases{ -23, -12, 123 };
	for( auto i : cases )
	{
		auto bin = to_bin( i );
		auto result = to_int( bin );
		if( i != result ) {
			std::cout << "FAILED round trip encoding of " << i << std::endl
					<< "result = " << result << " bin: ";
			for( auto p: bin )
			{
				std::cout << p << " ";
			}
			std::cout << std::endl;
			break;
		}
	}	
}

std::vector<int> base_neg_two( std::vector<int> &A, std::vector<int> &B )
{
	return to_bin( to_int(A) * to_int(B) );
}

std::int32_t base_neg_two_tests()
{
	minimal_test();
	exhaustive_roundtrip_test();
	multiply_tests();

	return 0;
}
