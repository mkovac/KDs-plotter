#ifndef Plotter_h
#define Plotter_h

// C++
#include <iostream>
#include <fstream>
#include <sstream>

// ROOT
#include "TApplication.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "THStack.h"

#include "Utilities.hpp"


using namespace std;

class Plotter
{

public:
	Plotter( TString, bool );
	~Plotter();

	void Plot();
	void PlotKD( Utilities::hypothesis, Utilities::production );
	void read8TeV_MC();
	void read7TeV_MC();
	void read8TeV_Data();
	void read7TeV_Data();
	void makeHistos8TeV_MC( TString );
	void makeHistos7TeV_MC( TString );
	
	
	
private:

	double ZXnorm;
	
	bool applySuperKDcut, _unblind;
	TString cutString, cutStringR, drawString, drawStringR, binWidth, plotsDir, inputDir, _energy;
	TH1F *datahisto, *qqZZ_7histo, *qqZZ_8histo, *ggZZ_7histo, *ggZZ_8histo, *POWHEG_7histo, *POWHEG_8histo, *SM_7histo, *SM_8histo, *PS_7histo, *PS_8histo, *qqZZhisto, *ggZZhisto, *ZXhisto, *SMhisto, *PShisto;
	TLatex *SupeKDCut;
	TCanvas *can;
	Utilities::hypothesis _myModel;
	Utilities::production _myProd;
	TPaveText *pt;
	TText *text;
	
	TChain *data, *qqZZ_8, *qqZZ_7, *ggZZ_8, *ggZZ_7, *SM_8, *SM_7, *POWHEG_8, *POWHEG_7, *PS_8, *PS_7;
	
	
	TString sampleNameGG[14] =
   {
      "powheg15jhuGenV3-0MH125.6",
      "powheg15jhuGenV3-0PHH125.6",
      "jhuGenV3Vec1MH125.6", // for PID
      "jhuGenV3Vec1PH125.6", // for PID
      "jhuGenV3Grav2PMH126",
      "jhuGenV3Grav2PH2H125.6",
      "jhuGenV3Grav2PH3H125.6",
      "jhuGenV3Grav2PHH126",
      "jhuGenV3Grav2PBH126",
      "jhuGenV3Grav2PH6H125.6",
      "jhuGenV3Grav2PH7H125.6",
      "jhuGenV3Grav2MHH126",
      "jhuGenV3Grav2MH9H125.6",
      "jhuGenV3Grav2MH10H125.6"
   };

	TString sampleNameQQB[14] =
	{
		"dummy",
      "dummy",
      "jhuGenV3Vec1MH125.6",
      "jhuGenV3Vec1PH125.6",
      "jhuGenV3Grav2PMqqbH126",
      "jhuGenV3Grav2PH2qqbH125.6",
      "jhuGenV3Grav2PH3qqbH125.6",
      "jhuGenV3Grav2PHqqbH125.6",
      "jhuGenV3Grav2PBqqbH125.6",
      "jhuGenV3Grav2PH6qqbH125.6",
      "jhuGenV3Grav2PH7qqbH125.6",
      "jhuGenV3Grav2MHqqbH125.6",
      "jhuGenV3Grav2MH9qqbH125.6",
      "jhuGenV3Grav2MH10qqbH125.6"
	};
	
	TString variableString[9] =
	{
		"Z1Mass",
		"Z2Mass",
		"costhetastar",
		"helcosthetaZ1",
		"helcosthetaZ2",
		"helphi",
		"phistarZ1",
		"p0plus_VAJHU*p0plus_m4l/(p0plus_VAJHU*p0plus_m4l+",
		"p0plus_VAJHU/(p0plus_VAJHU+"
	};
	
//	TString variableStringR[9] =
//	{
//		"Z1Mass",
//		"Z2Mass",
//		"costhetastar",
//		"helcosthetaZ1",
//		"helcosthetaZ2",
//		"helphi",
//		"phistarZ1",
//		"p0plus_VAJHU*p0plus_m4l_125p65/(p0plus_VAJHU*p0plus_m4l_125p65+",
//		"p0plus_VAJHU/(p0plus_VAJHU+"
//	};

	TString modelGG[14] =
	{
		"p0minus",
		"p0hplus",
		"dummy",
		"dummy",
		"p2",
		"p2h2plus_gg",
		"p2h3plus_gg",
		"p2hplus",
		"p2bplus",
		"5*p2h6plus_gg",
		"p2h7plus_gg",
      "p2hminus",
		"p2h9minus_gg",
		"p2h10minus_gg"
	};

	TString modelQQB[14] =
	{
		"dummy",
		"dummy",
		"p1",
		"p1plus",
		"p2qqb",
		"p2h2plus_qqbar",
		"p2h3plus_qqbar",
		"p2hplus_qqb",
		"p2bplus_qqb",
		"5*p2h6plus_qqbar",
		"p2h7plus_qqbar",
      "p2hminus_qqb",
		"p2h9minus_qqbar",
		"p2h10minus_qqbar"
	};
	
	TString modelPID[14] =
	{
		"dummy",
		"dummy",
		"p1_prodIndep",
		"p1plus_prodIndep",
		"p2_prodIndep",
		"p2h2plus_prodIndep",
		"p2h3plus_prodIndep",
      "p2hplus_prodIndep",
		"p2bplus_prodIndep",
		"5*p2h6plus_prodIndep",
		"p2h7plus_prodIndep",
      "p2hminus_prodIndep",
		"p2h9minus_prodIndep",
		"p2h10minus_prodIndep"
	};
	
	TString binsString[9] =
	{
		"(20,40,100)",
		"(20,12,72)",
		"(10,-1,1)",
		"(10,-1,1)",
		"(10,-1,1)",
		"(10,-3,3)",
		"(10,-3,3)",
		"(20,0,1)",
		"(20,0,1)"
	};
	
	TString legendTagGG[14] =
	{
		"J^{P} = 0^{-}",
		"J^{P} = 0^{+}_{h}",
      "dummy",
		"dummy",
		"J^{P} = 2^{+}_{m} (gg)",
		"J^{P} = 2^{+}_{h2} (gg)",
		"J^{P} = 2^{+}_{h3} (gg)",
      "J^{P} = 2^{+}_{h} (gg)",
		"J^{P} = 2^{+}_{b} (gg)",
      "J^{P} = 2^{+}_{h6} (gg)",
		"J^{P} = 2^{+}_{h7} (gg)",
		"J^{P} = 2^{-}_{h} (gg)",
		"J^{P} = 2^{-}_{h9} (gg)",
		"J^{P} = 2^{-}_{h10} (gg)"
	};

	TString legendTagQQB[14] =
	{
		"dummy",
		"dummy",
      "J^{P} = 1^{-}",
		"J^{P} = 1^{+}",
		"J^{P} = 2^{+}_{m} (q#bar{q})",
		"J^{P} = 2^{+}_{h2} (q#bar{q})",
		"J^{P} = 2^{+}_{h3} (q#bar{q})",
      "J^{P} = 2^{+}_{h} (q#bar{q})",
		"J^{P} = 2^{+}_{b} (q#bar{q})",
      "J^{P} = 2^{+}_{h6} (q#bar{q})",
		"J^{P} = 2^{+}_{h7} (q#bar{q})",
		"J^{P} = 2^{-}_{h} (q#bar{q})",
		"J^{P} = 2^{-}_{h9} (q#bar{q})",
		"J^{P} = 2^{-}_{h10} (q#bar{q})"
	};
	
	TString legendTagPID[14] =
	{
		"dummy",
		"dummy",
		"J^{P} = 1^{-} (dec)",
		"J^{P} = 1^{+} (dec)",
		"J^{P} = 2^{+}_{m} (dec)",
		"J^{P} = 2^{+}_{h2} (dec)",
		"J^{P} = 2^{+}_{h3} (dec)",
      "J^{P} = 2^{+}_{h} (dec)",
		"J^{P} = 2^{+}_{b} (dec)",
      "J^{P} = 2^{+}_{h6} (dec)",
		"J^{P} = 2^{+}_{h7} (dec)",
		"J^{P} = 2^{-}_{h} (dec)",
		"J^{P} = 2^{-}_{h9} (dec)",
		"J^{P} = 2^{-}_{h10} (dec)"
	};
	
	TString KDlabelGG[14] =
	{
		"#it{D}_{0^{-}}",
		"#it{D}_{0^{+}_{h}}",
      "dummy",
		"dummy",
		"#it{D}^{gg}_{2^{+}_{m}}",
		"#it{D}^{gg}_{2^{+}_{h2}}",
		"#it{D}^{gg}_{2^{+}_{h3}}",
      "#it{D}^{gg}_{2^{+}_{h}}",
		"#it{D}^{gg}_{2^{+}_{b}}",
      "#it{D}^{gg}_{2^{+}_{h6}}",
		"#it{D}^{gg}_{2^{+}_{h7}}",
		"#it{D}^{gg}_{2^{-}_{h}}",
		"#it{D}^{gg}_{2^{-}_{h9}}",
		"#it{D}^{gg}_{2^{-}_{h10}}"
	};

	TString KDlabelQQB[14] =
	{
		"dummy",
		"dummy",
		"#it{D}_{1^{-}}",
		"#it{D}_{1^{+}}",
		"#it{D}^{q#bar{q}}_{2^{+}_{m}}",
		"#it{D}^{q#bar{q}}_{2^{+}_{h2}}",
		"#it{D}^{q#bar{q}}_{2^{+}_{h3}}",
      "#it{D}^{q#bar{q}}_{2^{+}_{h}}",
		"#it{D}^{q#bar{q}}_{2^{+}_{b}}",
      "#it{D}^{q#bar{q}}_{2^{+}_{h6}}",
		"#it{D}^{q#bar{q}}_{2^{+}_{h7}}",
      "#it{D}^{q#bar{q}}_{2^{-}_{h}}",
		"#it{D}^{q#bar{q}}_{2^{-}_{h9}}",
		"#it{D}^{q#bar{q}}_{2^{-}_{h10}}"
	};
	
	TString KDlabelPID[14] =
	{
		"dummy",
		"dummy",
      "#it{D}^{dec}_{1^{-}}",
		"#it{D}^{dec}_{1^{+}}",
		"#it{D}^{dec}_{2^{+}_{m}}",
		"#it{D}^{dec}_{2^{+}_{h2}}",
		"#it{D}^{dec}_{2^{+}_{h3}}",
      "#it{D}^{dec}_{2^{+}_{h}}",
		"#it{D}^{dec}_{2^{+}_{b}}",
      "#it{D}^{dec}_{2^{+}_{h6}}",
		"#it{D}^{dec}_{2^{+}_{h7}}",
		"#it{D}^{dec}_{2^{-}_{h}}",
		"#it{D}^{dec}_{2^{-}_{h9}}",
		"#it{D}^{dec}_{2^{-}_{h10}}"
	};
	
	TString axisLabel[9] =
	{
		"M_{Z_{1}} (GeV)",
		"M_{Z_{2}} (GeV)",
		"cos#theta*",
		"cos#theta_{1}",
		"cos#theta_{2}",
		"#Phi",
		"#Phi_{1}",
		"#it{D}_{bkg}",
		""
	};
	
	TString saveTag[14] =
	{
		"0minus",
		"0hplus",
		"1minus",
		"1plus",
		"2mplus",
		"2h2plus",
		"2h3plus",
      "2hplus",
		"2bplus",
      "2h6plus",
		"2h7plus",
		"2hminus",
		"2h9minus",
		"2h10minus"
	};
	
	TString saveProductionTag[3] =
	{
		"_gg_",
		"_qqb_",
		"_pid_"
	};
	
	TString saveString[9] =
	{
		"Z1Mass",
		"Z2Mass",
		"costhetastar",
		"helcosthetaZ1",
		"helcosthetaZ2",
		"helphi",
		"phistarZ1",
		"SuperKD",
		"KD"
	};

};
#endif