#ifndef _Substructure_
#define _Substructure_

#include <vector>

class Substructure
{
	private:


		// Pixel values
		std::vector< std::vector<double> > pixels;


	public:
		/*
		* (M, N) are the dimensions of the array of pixels
		*/
		Substructure(int M, int N);

};

#endif

