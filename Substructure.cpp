#include "Substructure.h"
#include "RandomNumberGenerator.h"
#include <cmath>

using namespace DNest3;
using namespace std;

Substructure::Substructure(int M, int N)
:M(M), N(N)
,hidden(M, vector<double>(N))
,pixels(M, vector<double>(N))
{

}

void Substructure::fromPrior()
{
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			hidden[i][j] = randomU();

	K = randomU();
	mu = exp(log(1E-3) + log(1E6)*randomU());
	calculate_pixels();
}

void Substructure::calculate_pixels()
{
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(hidden[i][j] >= K)
			{
				pixels[i][j] = -mu*log(1. -
						(hidden[i][j] - K)/(1. - K));
			}
			else
				pixels[i][j] = 0.;
		}
	}
}

void Substructure::print(ostream& out) const
{
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			out<<pixels[i][j]<<' ';
}

