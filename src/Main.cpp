// C++
#include <iostream>
#include <fstream>
#include <string>

// ROOT
#include "TApplication.h"
#include <TROOT.h>
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TStyle.h"

// My own files
#include "Plotter.hpp"
#include "Utilities.hpp"

using namespace std;

int main( int argc, char *argv[] )
{

	gROOT->ProcessLine(".L ./src/tdrstyle.C+");
	gROOT->ProcessLine("setTDRStyle();");
	
	Plotter *p = new Plotter( "all", true );

   p->PlotKD( Utilities::H0minus, Utilities::GG );

   p->PlotKD( Utilities::H0hplus, Utilities::GG );

   p->PlotKD( Utilities::H1minus, Utilities::QQB );
   p->PlotKD( Utilities::H1minus, Utilities::PID );

   p->PlotKD( Utilities::H1plus, Utilities::QQB );
   p->PlotKD( Utilities::H1plus, Utilities::PID );

//   p->PlotKD( Utilities::H2_g1g5, Utilities::GG );
//   p->PlotKD( Utilities::H2_g1g5, Utilities::QQB );
//   p->PlotKD( Utilities::H2_g1g5, Utilities::PID );

   p->PlotKD( Utilities::H2_g2, Utilities::GG );
   p->PlotKD( Utilities::H2_g2, Utilities::QQB );
   p->PlotKD( Utilities::H2_g2, Utilities::PID );

   p->PlotKD( Utilities::H2_g3, Utilities::GG );
   p->PlotKD( Utilities::H2_g3, Utilities::QQB );
   p->PlotKD( Utilities::H2_g3, Utilities::PID );
	
   p->PlotKD( Utilities::H2_g4, Utilities::GG );
   p->PlotKD( Utilities::H2_g4, Utilities::QQB );
   p->PlotKD( Utilities::H2_g4, Utilities::PID );

   p->PlotKD( Utilities::H2_g5, Utilities::GG );
   p->PlotKD( Utilities::H2_g5, Utilities::QQB );
   p->PlotKD( Utilities::H2_g5, Utilities::PID );
   
   p->PlotKD( Utilities::H2_g6, Utilities::GG );
   p->PlotKD( Utilities::H2_g6, Utilities::QQB );
   p->PlotKD( Utilities::H2_g6, Utilities::PID );

   p->PlotKD( Utilities::H2_g7, Utilities::GG );
   p->PlotKD( Utilities::H2_g7, Utilities::QQB );
   p->PlotKD( Utilities::H2_g7, Utilities::PID );
	
   p->PlotKD( Utilities::H2_g8, Utilities::GG );
   p->PlotKD( Utilities::H2_g8, Utilities::QQB );
   p->PlotKD( Utilities::H2_g8, Utilities::PID );
   
   p->PlotKD( Utilities::H2_g9, Utilities::GG );
   p->PlotKD( Utilities::H2_g9, Utilities::QQB );
   p->PlotKD( Utilities::H2_g9, Utilities::PID );
   
   p->PlotKD( Utilities::H2_g10, Utilities::GG );
   p->PlotKD( Utilities::H2_g10, Utilities::QQB );
   p->PlotKD( Utilities::H2_g10, Utilities::PID );
}