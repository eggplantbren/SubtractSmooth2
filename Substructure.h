#ifndef _Substructure_
#define _Substructure_

#include <vector>
#include <ostream>

class Substructure
{
	private:
		// Array size
		int M, N;

		// Hidden variables with iid U(0, 1) prior
		std::vector< std::vector<double> > hidden;

		// Fraction of nonzero pixels
		double K;

		// Mean of nonzero pixels
		double mu;

		// Width of blurring kernel in pixels
		double width;

		// Blurring kernel
		std::vector< std::vector<double> > kernel;

		// Pixel values
		std::vector< std::vector<double> > pixels;

		// Calculate the kernel
		void calculate_kernel();

		// Calculate the pixel values from the parameters
		void calculate_pixels();

		// Blur with the kernel
		void blur();

	public:
		/*
		* (M, N) are the dimensions of the array of pixels
		*/
		Substructure(int M, int N);

		void fromPrior();
		double perturb();

		void print(std::ostream& out) const;

};

#endif

