#include <cstdlib>
#include <unistd.h>
#include "Vector.h"
#include "Grounded.h"
#include "GrandPotential.h"

void printUsage(PsimagLite::String prog)
{
	std::cerr<<"USAGE: "<<prog<<" -b begin -t total -s step -m mu -U U\n";

}

typedef double RealType;

int main(int argc, char** argv)
{
	int opt = 0;
	SizeType meshKtotal = 1000;
	SizeType meshLambdaTotal = 10000;
	SizeType tt = 0;
	RealType tb;
	RealType ts;
	RealType mu;
	RealType U;
	while ((opt = getopt(argc, argv,"b:t:s:m:U:K:L:")) != -1) {
		switch (opt) {
		case 'b':
			tb = atof(optarg);
			break;
		case 't':
			tt = atoi(optarg);
			break;
		case 's':
			ts = atof(optarg);
			break;
		case 'm':
			mu = atof(optarg);
			break;
		case 'U':
			U = atof(optarg);
			break;
		case 'K':
			meshKtotal = atoi(optarg);
			break;
		case 'L':
			meshLambdaTotal = atoi(optarg);
			break;
		default:
			printUsage(argv[0]);
			return 1;
		}
	}

	if (tt == 0 or ts <= 0) {
		printUsage(argv[0]);
		return 2;
	}

	BetheAnsatz::Grounded<RealType> grounded(U,meshKtotal);

	for (SizeType i = 0; i < tt; ++i) {
		RealType t = tb + i*ts;
		BetheAnsatz::GrandPotential<RealType> grandPotential(grounded,
		                                                     mu,
		                                                     t,
		                                                     meshLambdaTotal);
		RealType omegaValue = grandPotential();
		std::cout<<t<<" "<<omegaValue<<"\n";
	}
}

