#ifndef Utilities_h
#define Utilities_h

using namespace std;

class Utilities
{

public:
	
	enum hypothesis
	{
		H0minus = 0,
		H0hplus = 1,
		H1minus = 2,
		H1plus  = 3,
		H2_g1g5 = 4,  // 2m+,  replacing 2m+
		H2_g2	  = 5,  // 2h2+
		H2_g3	  = 6,  // 2h3+
		H2_g4   = 7,  // 2h4+, replacing 2h+
		H2_g5   = 8,  // 2h5+, replacing 2b+
		H2_g6	  = 9,  // 2h6+
		H2_g7	  = 10, // 2h7+
		H2_g8   = 11, // 2h8-, replacing 2h-
		H2_g9	  = 12, // 2h9-
		H2_g10  = 13  // 2h10-
	};
	
	enum production
	{
		GG  = 0,
		QQB = 1,
		PID = 2
	};
	
	enum variable
	{
		Z1Mass = 0,
		Z2Mass = 1,
		costhetastar  = 2,
		helcosthetaZ1 = 3,
		helcosthetaZ2 = 4,
		helphi    = 5,
		phistarZ1 = 6,
		SuperKD   = 7,
		KD = 8,
		numOfVariables = 9
	};

};
#endif