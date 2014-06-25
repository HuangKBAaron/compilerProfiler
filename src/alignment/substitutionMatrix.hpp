#pragma once
/*
 * 
 *

 *  Created on: Jun 25, 2014
 *      Author: nickhathaway <nickjhathaway@gmail.com>
 */
#include "common.h"

class substituteMatrix {
public:
	//constructor
	/*
	 * Simple 1 for match -1 for mismatch
	 */
	substituteMatrix(){
		setWithSimple(1,-1);
	}
	//constructor
	/*
	 * Given match and mismatch values
	 */
	substituteMatrix(int32_t match, int32_t mismatch){
		setWithSimple(match, mismatch);
	}

	//members
	std::array<std::array<int32_t, 127>, 127> mat_;

	//functions

	void setWithZeros();

	void setWithSimple(int32_t match, int32_t mismatch);

	void setWithCaseInsensitive(int32_t match, int32_t mismatch);
};
