#include "Substructure.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace DNest3;
using namespace std;

Substructure::Substructure(int M, int N)
:M(M), N(N)
,hidden(M, vector<double>(N))
,kernel(5, vector<double>(5))
,pixels(M, vector<double>(N))
{

}

void Substructure::fromPrior()
{
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			hidden[i][j] = randomU();

	K = 1. - exp(log(1E-6) + log(1E6)*randomU());
	mu = exp(log(1E-3) + log(1E6)*randomU());
	width = 5.*randomU();
	calculate_kernel();
	calculate_pixels();
}

double Substructure::perturb()
{
	double chance = pow(10., 0.5 - 4.*randomU());
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			if(randomU() <= chance)
				hidden[i][j] = randomU();

	int which = randInt(3);
	if(which == 0)
	{
		K = 1. - K;
		K = log(K);
		K += log(1E6)*pow(10., 1.5 - 6.*randomU())*randn();
		K = mod(K - log(1E-6), log(1E6)) + log(1E-6);
		K = exp(K);
		K = 1. - K;
	}
	else if(which == 1)
	{
		mu = log(mu);
		mu += log(1E6)*pow(10., 1.5 - 6.*randomU())*randn();
		mu = mod(mu - log(1E-3), log(1E6)) + log(1E-3);
		mu = exp(mu);
	}
	else
	{
		width += 5.*pow(10., 1.5 - 6.*randomU())*randn();
		width = mod(width, 5.);
		calculate_kernel();
	}

	calculate_pixels();
	return 0.;
}

void Substructure::calculate_kernel()
{
	double rsq;
	double tot = 0.;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			rsq = pow(i - 2, 2) + pow(j - 2, 2);
			kernel[i][j] = exp(-0.5*rsq/pow(width, 2));
			tot += kernel[i][j];
		}
	}
	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			kernel[i][j] /= tot;
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

	blur();
}

void Substructure::blur()
{
	vector< vector<double> > blurred(M, vector<double>(N, 0.));
	int m, n;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(pixels[i][j] > 0.)
			{
				for(int ii=0; ii<5; ii++)
					for(int jj=0; jj<5; jj++)
					{
						m = i + ii - 2;
						n = j + jj - 2;
						if(m >= 0 && m < M && n >= 0 && n < N)
							blurred[m][n] += pixels[i][j]*kernel[ii][jj];
					}
			}
		}
	}
	pixels = blurred;
}

void Substructure::print(ostream& out) const
{
	out<<K<<' '<<mu<<' ';
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			out<<pixels[i][j]<<' ';
}

