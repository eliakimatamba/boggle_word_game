#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

				unsigned long long w[5];
				for(int i = 0; i < 5; i++) {
					w[i] = 0;
				}

				int index = signed(k.size());
				std::string holder = k;
				int count = 0;

				for(int i = 4; i >= 0; i--) { //Index through each w[i]
					std::string substring = holder.substr(std::max(0,index-6), index); //Create a substring from holder to get every set of 6 letters
					holder = holder.substr(0, std::max(0,index-6)); //Adjust holder to get rid of the previous 6 letters
					for(int y = substring.size()-1; y >= 0; y--) { //Iterate through the new substring
						w[i] += pow(36, count) * letterDigitToNumber(substring[y]); //Add to w[i]
						count++; //Increment count to adjust exponent
					}
					count = 0;
					index = signed(holder.size());
				}

				HASH_INDEX_T result = 0;
				for(int i = 0; i < 5; i++){ //Sum rValues & w[i]
					result += rValues[i] * w[i];
				}

				return result;
		}

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				HASH_INDEX_T convert = int(std::tolower(letter));
				if(convert >= 48 && convert <= 57) {
					convert -= 22;
				}
				else if(convert >= 97 && convert <= 122) {
					convert -= 97;
				}

				return convert;	

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif