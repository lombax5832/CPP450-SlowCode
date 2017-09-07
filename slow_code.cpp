// compiles with:
// g++ slow_code.cpp -o slow_code


#include <time.h>
#include <math.h>
#include <stdint.h>
#include <iostream>
#include <fstream>

using namespace std;

// complex algorithm for evaluation
void myfunc(double** v_s, double** v_mat, int* i_v, int size)
{
	// this assumes that the two dimensional vector is square 

	uint8_t i_val;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			i_val = i_v[i] % 256; // this should return an integer
			v_mat[i][j] = v_s[i][j] * (-cos(2.0*i_val));
		}
	}
}

int main(int argc, char *argv[])
{

	// this should be called as> ./slow_code <i_R> <i_N>

	int i_R = 1000;
	int i_N = 100;

	clock_t d_S, d_E;

	// parse input parameters 
	if (argc >= 2)
	{
		i_R = atoi(argv[1]);
	}

	if (argc >= 3)
	{
		i_N = atoi(argv[2]);
	}

	// some declarations

	double **vd_s = new double*[i_N];
	double **vd_mat = new double*[i_N];
	for (int i = 0; i < i_N; i++) {
		vd_s[i] = new double[i_N];
		vd_mat[i] = new double[i_N];
	}
	int *vi_v = new int[i_N];

	// populate memory with some random data
	for (int i = 0; i < i_N; i++)
	{
		vi_v[i] = i * i;
		for (int j = 0; j < i_N; j++)
			vd_s[i][j] = j + i;
	}

	// start benchmark
	d_S = clock();

	// iterative test loop
	for (int i = 0; i < i_R; i++)
	{
		myfunc(vd_s, vd_mat, vi_v, i_N);
	}

	// end benchmark
	d_E = clock();

	ofstream outfile = ofstream("output.txt");

	for (int i = 0; i < i_N; i++)
	{
		for (int j = 0; j < i_N; j++)
		{
			outfile << vd_mat[i][j] << ' ';
		}
		outfile << "\n\n";
	}

	outfile.close();

	// delete dynamically allocated stuff
	for (int i = 0; i < i_N; i++) {
		delete[] vd_mat[i];
		delete[] vd_s[i];
	}
	delete[] vd_s;
	delete[] vd_mat;
	delete[] vi_v;

	// report results
	printf("Elapsed time: %f\n", (float)(d_E - d_S)/CLOCKS_PER_SEC);

	return 0;
}
