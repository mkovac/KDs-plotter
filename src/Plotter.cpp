#include "Plotter.hpp"

// Constructor
//==============================================
Plotter::Plotter( TString energy, bool unblind )
{

//	ZXnorm = 1.0086 + 0.3826 + 0.4505 + 1.3097 + 0.8967 + 1.9897;
	ZXnorm = 0.462495 + 1.86816 + 0.297662 + 1.32318 + 0.211827 + 1.12853;
	
//	_applySuperKDcut = applySuperKDcut;
	_unblind = unblind;
	_energy = energy;
	
	plotsDir = "plots/properties_v3/";
	inputDir = "/data_CMS/cms/mkovac/StatTrees/140519/";
	
	can = new TCanvas( "can", "can", 550, 550 );
	pt = new TPaveText( 0.14, 0.94, 0.89, 0.99, "brNDC" );

	
	// Chains
	data     = new TChain("SelectedTree");
	qqZZ_8   = new TChain("SelectedTree");
	qqZZ_7   = new TChain("SelectedTree");
	ggZZ_8   = new TChain("SelectedTree");
	ggZZ_7   = new TChain("SelectedTree");
	SM_8     = new TChain("SelectedTree");
	SM_7     = new TChain("SelectedTree");
//	POWHEG_8 = new TChain("SelectedTree");
//	POWHEG_7 = new TChain("SelectedTree");
	PS_8     = new TChain("SelectedTree");
	PS_7     = new TChain("SelectedTree");
}
//==============================================



// Destructor
//=================
Plotter::~Plotter()
{
	delete can;
}
//=================



//==================
void Plotter::Plot()
{

	if( applySuperKDcut )
	{
		if ( _myProd == Utilities::GG || _myProd == Utilities::QQB )
		{
			cutString  = "ZZMass > 105.6 && ZZMass < 140.6 && p0plus_VAJHU*p0plus_m4l/(p0plus_VAJHU*p0plus_m4l+bkg_VAMCFM*bkg_m4l) > .5"; // SuperKD
//			cutStringR = "ZZMass > 105.6 && ZZMass < 140.6 && p0plus_VAJHU*p0plus_m4l_125p65/(p0plus_VAJHU*p0plus_m4l_125p65+bkg_VAMCFM*bkg_m4l_125p65) > .5"; // SuperKD
		}
		else
		{
			cutString  = "ZZMass > 105.6 && ZZMass < 140.6 && p0plus_VAJHU*p0plus_m4l/(p0plus_VAJHU*p0plus_m4l+bkg_prodIndep_VAMCFM*bkg_m4l) > .5"; // Production indepedent SuperKD
//			cutStringR = "ZZMass > 105.6 && ZZMass < 140.6 && p0plus_VAJHU*p0plus_m4l_125p65/(p0plus_VAJHU*p0plus_m4l_125p65+bkg_prodIndep_VAMCFM*bkg_m4l_125p65) > .5"; // production indepedent SuperKD
		}
	}
	else
	{
		cutString = "ZZMass > 121.5 && ZZMass < 130.5";
//		cutStringR = "ZZMass > 121.5 && ZZMass < 130.5";
//		cutString = "ZZMass > 105.6 && ZZMass < 140.6";
	}
		
	// Read the Trees
	if ( _energy == "7TeV" )
	{
		data->Reset();
		qqZZ_7->Reset();
		ggZZ_7->Reset();
		SM_7->Reset();
//		POWHEG_7->Reset();
		PS_7->Reset();
		
		read7TeV_Data();
		read7TeV_MC();
	}
	else if ( _energy == "8TeV" )
	{
		data->Reset();
		qqZZ_8->Reset();
		ggZZ_8->Reset();
		SM_8->Reset();
//		POWHEG_8->Reset();
		PS_8->Reset();
		
		read8TeV_Data();
		read8TeV_MC();
	}
	else
	{
		data->Reset();
		qqZZ_7->Reset();
		ggZZ_7->Reset();
		SM_7->Reset();
//		POWHEG_7->Reset();
		PS_7->Reset();
		qqZZ_8->Reset();
		ggZZ_8->Reset();
		SM_8->Reset();
//		POWHEG_8->Reset();
		PS_8->Reset();
		
		read7TeV_Data();
		read7TeV_MC();
		read8TeV_Data();
		read8TeV_MC();
	}
		

	// Loop over the variables
	for ( int iVar = 0; iVar < Utilities::numOfVariables; iVar++ )
	{
		
		// Set correct draw strings
		if ( iVar == Utilities::SuperKD && (_myProd == Utilities::GG || _myProd == Utilities::QQB) )
		{
			drawString = variableString[7] + "bkg_VAMCFM*bkg_m4l)";
//			drawStringR = variableStringR[7] + "bkg_VAMCFM*bkg_m4l_125p65)";
		}
		else if ( iVar == Utilities::SuperKD && _myProd == Utilities::PID )
		{
			drawString = variableString[7] + "bkg_prodIndep_VAMCFM*bkg_m4l)";
//			drawStringR = variableStringR[7] + "bkg_prodIndep_VAMCFM*bkg_m4l_125p65)";
		}
		else if ( iVar == Utilities::KD )
		{
			if ( _myProd == Utilities::GG )
			{
				drawString = variableString[8] + modelGG[_myModel] + "_VAJHU)";
//				drawStringR = variableStringR[8] + model[myModel] + "_VAJHU)";
			}
			else if ( _myProd == Utilities::QQB )
			{
				drawString = variableString[8] + modelQQB[_myModel] + "_VAJHU)";
			}
			else if ( _myProd == Utilities::PID )
			{
				drawString = variableString[8] + modelPID[_myModel] + "_VAJHU)";
			}
		}
		else
		{
			drawString = variableString[iVar];
//			drawStringR = variableStringR[iVar];
		}
		
		// Set correct cuts for KD and SuperKD
		if ( iVar >= 7 && !applySuperKDcut )
		{
			cutString = "ZZMass > 105.6 && ZZMass < 140.6";
//			cutStringR = "ZZMass > 105.6 && ZZMass < 140.6";
		}
		
		// Set binning
		if ( iVar == Utilities::Z1Mass && !applySuperKDcut )
			binsString[0] = "(40,40,120)";
			

		// Make data histograms
		if ( _unblind )
		{
			data->Draw( drawString + ">>datahisto" + binsString[iVar], cutString );
			datahisto = (TH1F*) gDirectory->Get("datahisto");
			datahisto->SetBinErrorOption(TH1::kPoisson);
			datahisto->SetMarkerStyle(20);
			datahisto->SetMarkerSize(.7);
		}
		
		// Make histograms
		if ( _energy == "7TeV" )
		{
			makeHistos7TeV_MC( binsString[iVar] );
			
			qqZZhisto = new TH1F(*qqZZ_7histo);
			ggZZhisto = new TH1F(*ggZZ_7histo);
			SMhisto   = new TH1F(*SM_7histo);
			PShisto   = new TH1F(*PS_7histo);
		}
		else if ( _energy == "8TeV" )
		{
			makeHistos8TeV_MC( binsString[iVar] );
			
			qqZZhisto = new TH1F(*qqZZ_8histo);
			ggZZhisto = new TH1F(*ggZZ_8histo);
			SMhisto   = new TH1F(*SM_8histo);
			PShisto   = new TH1F(*PS_8histo);
		}
		else
		{
			makeHistos8TeV_MC( binsString[iVar] );
			makeHistos7TeV_MC( binsString[iVar] );
		
			qqZZhisto = new TH1F(*qqZZ_7histo);
			qqZZhisto->Add(qqZZ_8histo);
			ggZZhisto = new TH1F(*ggZZ_7histo);
			ggZZhisto->Add(ggZZ_8histo);
			SMhisto = new TH1F(*SM_7histo);
			SMhisto->Add(SM_8histo);
			PShisto = new TH1F(*PS_7histo);
			PShisto->Add(PS_8histo);
		}
		
//		if ( !qqZZ_7histo || !qqZZ_8histo ) assert(0);

		qqZZhisto->SetLineColor(kAzure-9);
		qqZZhisto->SetLineWidth(2);
		qqZZhisto->SetFillColor(kAzure-9);

		ggZZhisto->SetLineColor(kAzure-9);
		ggZZhisto->SetLineWidth(0);
		ggZZhisto->SetFillColor(kAzure-9);
		
		SMhisto->SetLineColor(kOrange+10);
		SMhisto->SetLineWidth(2);
		SMhisto->SetFillColor(0);

		PShisto->SetLineColor(kRed);
		PShisto->SetLineWidth(2);
		PShisto->SetLineStyle(2);
		PShisto->SetFillColor(0);
		PShisto->Scale( SMhisto->Integral()/PShisto->Integral() );

		
		double with = (double)qqZZ_8->Draw( "ZZMass", cutString );
		double without = (double)qqZZ_8->Draw( "ZZMass", "ZZMass > 105.6 && ZZMass < 140.6" );
//		double with = (double)qqZZhisto->Draw( "ZZMass", cutString );
//		double without = (double)qqZZhisto->Draw( "ZZMass", "ZZMass > 105.6 && ZZMass < 140.6" );
		
		ZXhisto = new TH1F(*qqZZhisto);
		ZXhisto->Scale( (ZXnorm*with/without)/ZXhisto->Integral() );
		ZXhisto->SetLineColor(kGreen-5);
		ZXhisto->SetLineWidth(2);
		ZXhisto->SetFillColor(kGreen-5);

		stringstream ss;
		ss << SMhisto->GetBinWidth(5);
		ss >> binWidth;

		if ( _unblind )
		{
			datahisto->GetXaxis()->SetTitle( axisLabel[iVar] );
			datahisto->GetYaxis()->SetTitle( "Events / " + binWidth );
			
			if ( iVar == Utilities::KD)
			{
				if ( _myProd == Utilities::GG )
					datahisto->GetXaxis()->SetTitle(KDlabelGG[_myModel]);
				else if ( _myProd == Utilities::QQB )
					datahisto->GetXaxis()->SetTitle(KDlabelQQB[_myModel]);
				else
					datahisto->GetXaxis()->SetTitle(KDlabelPID[_myModel]);
			}
			
			if( _myProd == Utilities::PID && iVar == Utilities::SuperKD )
				datahisto->GetXaxis()->SetTitle( axisLabel[iVar] + "^{dec}" );
		}

		THStack* stackSM = new THStack( "stackSM", "stackSM" );
		stackSM->Add(ZXhisto);
		stackSM->Add(ggZZhisto);
		stackSM->Add(qqZZhisto);
		stackSM->Add(SMhisto);

		THStack* stackPS = new THStack( "stackPS", "stackPS" );
		stackPS->Add(ZXhisto);
		stackPS->Add(ggZZhisto);
		stackPS->Add(qqZZhisto);
		stackPS->Add(PShisto);


//////////
//	Draw //
//////////
		
		if ( _unblind )
		{
			datahisto->GetYaxis()->SetRangeUser(0,max(stackSM->GetMaximum(),datahisto->GetBinContent(datahisto->GetMaximumBin())+datahisto->GetBinError(datahisto->GetMaximumBin()))*1.5);
			datahisto->Draw("E1");
		}
		else
      {
         stackSM->Draw("");
			stackSM->GetXaxis()->SetTitle( axisLabel[iVar] );
			stackSM->GetYaxis()->SetTitle( "Events / " + binWidth );
			stackSM->SetMaximum( stackSM->GetMaximum()*2 );

			if ( iVar == Utilities::KD)
			{
				if ( _myProd == Utilities::GG )
					stackSM->GetXaxis()->SetTitle(KDlabelGG[_myModel]);
				else if ( _myProd == Utilities::QQB )
					stackSM->GetXaxis()->SetTitle(KDlabelQQB[_myModel]);
				else
					stackSM->GetXaxis()->SetTitle(KDlabelPID[_myModel]);
			}

			if( _myProd == Utilities::PID && iVar == Utilities::SuperKD )
				stackSM->GetXaxis()->SetTitle( axisLabel[iVar] + "^{dec}" );
		}

		
		stackSM->Draw("SAME");
//		if(myModel!=0) stackPS->Draw("SAME");
		stackPS->Draw("SAME");
		
		if ( _unblind )
		{
			datahisto->Draw("E1same");
			datahisto->Draw("SAMEp");
		}
		
//
// Legend
//
		TLegend *leg = new TLegend( .2, .68, .6, .9 );
		leg->SetFillColor(0);
		leg->SetBorderSize(0);

		if ( _unblind )
		{
			leg->AddEntry( datahisto, "Data", "p" );
		}
		leg->AddEntry(SMhisto,"0^{+}","l"); //, m_{H}=126 GeV
		
		if ( _myProd == Utilities::GG )
			leg->AddEntry( PShisto, legendTagGG[_myModel], "l" );
		else if ( _myProd == Utilities::QQB )
			leg->AddEntry( PShisto, legendTagQQB[_myModel], "l" );
		else
			leg->AddEntry( PShisto, legendTagPID[_myModel], "l" );
		
		leg->AddEntry( qqZZhisto, "ZZ/Z#gamma*", "f" );
		leg->AddEntry( ZXhisto, "Z+X", "f" );

		leg->Draw();

//		datahisto->Draw( "E1same" );
		gPad->RedrawAxis();

//
//	Plot header
//
		pt->SetBorderSize(0);
		pt->SetTextAlign(12);
		pt->SetFillStyle(0);
		pt->SetTextFont(42);
		pt->SetTextSize(0.03);
		text = pt->AddText( 0.01, 0.3, "CMS (preliminary)" );
		text = pt->AddText( 0.53, 0.3, "19.7 fb^{-1} (8 TeV) + 5.1 fb^{-1} (7 TeV)");
		pt->Draw();
    
        
		if ( _myProd == Utilities::PID && applySuperKDcut )
		{
			SupeKDCut = new TLatex(0.7, 0.85, "D^{dec}_{bkg} > 0.5");
			SupeKDCut->SetNDC(kTRUE);
			SupeKDCut->SetTextFont(42);
			SupeKDCut->Draw("same");
		}
		else if ( (_myProd == Utilities::GG || _myProd == Utilities::QQB) && applySuperKDcut )
		{
			SupeKDCut = new TLatex(0.7, 0.85, "D_{bkg} > 0.5");
			SupeKDCut->SetNDC(kTRUE);
			SupeKDCut->SetTextFont(42);
			SupeKDCut->Draw("same");
		}
      
//
//	Save
//
		if ( applySuperKDcut )
		{
			can->SaveAs(plotsDir + saveTag[_myModel] + saveProductionTag[_myProd] + saveString[iVar] + "_superKDcut.png");
			can->SaveAs(plotsDir + saveTag[_myModel] + saveProductionTag[_myProd] + saveString[iVar] + "_superKDcut.pdf");
//			can->SaveAs(plotsDir + saveTag[_myModel] + "_" + saveString[iVar] + "_superKDcut.eps");
//			can->SaveAs(plotsDir + saveTag[_myModel] + "_" + saveString[iVar] + "_superKDcut.root");
//			can->SaveAs(plotsDir + saveTag[_myModel] + "_" + saveString[iVar] + "_superKDcut.C");
		}
		else
		{
			can->SaveAs(plotsDir + saveTag[_myModel] + saveProductionTag[_myProd] + saveString[iVar] + ".png");
			can->SaveAs(plotsDir + saveTag[_myModel] + saveProductionTag[_myProd] + saveString[iVar] + ".pdf");
//			can->SaveAs(plotsDir + saveTag[_myModel] + "_" + saveString[iVar] + ".eps");
//			can->SaveAs(plotsDir + saveTag[_myModel] + "_" + saveString[iVar] + ".root");
//			can->SaveAs(plotsDir + saveTag[_myModel] + "_" + saveString[iVar] + ".C");
		}
		
		
		// Cleaning
		cout << "[INFO]: Cleaning..." << endl;
		
		pt->Clear();
		delete qqZZ_7histo;
		delete qqZZ_8histo;
		delete ggZZ_7histo;
		delete ggZZ_8histo;
//		delete POWHEG_7histo;
//		delete POWHEG_8histo;
		delete SM_7histo;
		delete SM_8histo;
		delete PS_7histo;
		delete PS_8histo;
		delete datahisto;
		delete qqZZhisto;
		delete ZXhisto;
		delete SMhisto;
		delete PShisto;
	} // End for var
}
// End plot function
//==================



//=========================
void Plotter::read8TeV_MC()
{

	cout << "[INFO]: Reading 8TeV MC..." << endl;
	
	qqZZ_8->Add(inputDir + "PRODFSR_8TeV/4mu/HZZ4lTree_ZZTo*.root");
	qqZZ_8->Add(inputDir + "PRODFSR_8TeV/4e/HZZ4lTree_ZZTo*.root");
	qqZZ_8->Add(inputDir + "PRODFSR_8TeV/2mu2e/HZZ4lTree_ZZTo*.root");
	
	ggZZ_8->Add(inputDir + "PRODFSR_8TeV/4mu/HZZ4lTree_ggZZ*.root");
	ggZZ_8->Add(inputDir + "PRODFSR_8TeV/4e/HZZ4lTree_ggZZ*.root");
	ggZZ_8->Add(inputDir + "PRODFSR_8TeV/2mu2e/HZZ4lTree_ggZZ*.root");
	
	SM_8->Add(inputDir + "PRODFSR_8TeV/4mu/HZZ4lTree_powheg15jhuGenV3-0PMH125.6.root");
	SM_8->Add(inputDir + "PRODFSR_8TeV/4e/HZZ4lTree_powheg15jhuGenV3-0PMH125.6.root");
	SM_8->Add(inputDir + "PRODFSR_8TeV/2mu2e/HZZ4lTree_powheg15jhuGenV3-0PMH125.6.root");
	
//	POWHEG_8->Add(inputDir + "PRODFSR_8TeV/4mu/HZZ4lTree_powheg15jhuGenV3H126.root");   // Was HZZ4lTree_H126
//	POWHEG_8->Add(inputDir + "PRODFSR_8TeV/4e/HZZ4lTree_powheg15jhuGenV3H126.root");    // Was HZZ4lTree_H126
//	POWHEG_8->Add(inputDir + "PRODFSR_8TeV/2mu2e/HZZ4lTree_powheg15jhuGenV3H126.root"); // Was HZZ4lTree_H126

	if ( _myProd == Utilities::QQB )
	{
		PS_8->Add(inputDir + "PRODFSR_8TeV/4mu/HZZ4lTree_"   + sampleNameQQB[_myModel] + ".root");
		PS_8->Add(inputDir + "PRODFSR_8TeV/4e/HZZ4lTree_"    + sampleNameQQB[_myModel] + ".root");
		PS_8->Add(inputDir + "PRODFSR_8TeV/2mu2e/HZZ4lTree_" + sampleNameQQB[_myModel] + ".root");
      cout << "[INFO] 8TeV ALT model tree is " << sampleNameQQB[_myModel] << endl;
	}
	else
	{
		PS_8->Add(inputDir + "PRODFSR_8TeV/4mu/HZZ4lTree_"   + sampleNameGG[_myModel] + ".root");
		PS_8->Add(inputDir + "PRODFSR_8TeV/4e/HZZ4lTree_"    + sampleNameGG[_myModel] + ".root");
		PS_8->Add(inputDir + "PRODFSR_8TeV/2mu2e/HZZ4lTree_" + sampleNameGG[_myModel] + ".root");
      cout << "[INFO] 8TeV ALT model tree is " << sampleNameGG[_myModel] << endl;
	} // End if _myProd


} // End read8TeV_MC()
//=========================



//=========================
void Plotter::read7TeV_MC()
{
	
	cout << "[INFO]: Reading 7TeV MC..." << endl;
	
	qqZZ_7->Add(inputDir + "PRODFSR/4mu/HZZ4lTree_ZZTo*.root");
	qqZZ_7->Add(inputDir + "PRODFSR/4e/HZZ4lTree_ZZTo*.root");
	qqZZ_7->Add(inputDir + "PRODFSR/2mu2e/HZZ4lTree_ZZTo*.root");
	
	ggZZ_7->Add(inputDir + "PRODFSR/4mu/HZZ4lTree_ggZZ*.root");
	ggZZ_7->Add(inputDir + "PRODFSR/4e/HZZ4lTree_ggZZ*.root");
	ggZZ_7->Add(inputDir + "PRODFSR/2mu2e/HZZ4lTree_ggZZ*.root");
	
	SM_7->Add(inputDir + "PRODFSR/4mu/HZZ4lTree_powheg15jhuGenV3-0PMH125.6.root");
	SM_7->Add(inputDir + "PRODFSR/4e/HZZ4lTree_powheg15jhuGenV3-0PMH125.6.root");
	SM_7->Add(inputDir + "PRODFSR/2mu2e/HZZ4lTree_powheg15jhuGenV3-0PMH125.6.root");
	
//	POWHEG_7->Add(inputDir + "PRODFSR/4mu/HZZ4lTree_powheg15jhuGenV3H126.root");   // Was HZZ4lTree_H126
//	POWHEG_7->Add(inputDir + "PRODFSR/4e/HZZ4lTree_powheg15jhuGenV3H126.root");    // Was HZZ4lTree_H126
//	POWHEG_7->Add(inputDir + "PRODFSR/2mu2e/HZZ4lTree_powheg15jhuGenV3H126.root"); // Was HZZ4lTree_H126

	if ( _myProd == Utilities::QQB )
	{
		PS_7->Add(inputDir + "PRODFSR/4mu/HZZ4lTree_"   + sampleNameQQB[_myModel] + ".root");
		PS_7->Add(inputDir + "PRODFSR/4e/HZZ4lTree_"    + sampleNameQQB[_myModel] + ".root");
		PS_7->Add(inputDir + "PRODFSR/2mu2e/HZZ4lTree_" + sampleNameQQB[_myModel] + ".root");
      cout << "[INFO] 7TeV ALT model tree is " << sampleNameQQB[_myModel] << endl;
	}
	else
	{
		PS_7->Add(inputDir + "PRODFSR/4mu/HZZ4lTree_"   + sampleNameGG[_myModel] + ".root");
		PS_7->Add(inputDir + "PRODFSR/4e/HZZ4lTree_"    + sampleNameGG[_myModel] + ".root");
		PS_7->Add(inputDir + "PRODFSR/2mu2e/HZZ4lTree_" + sampleNameGG[_myModel] + ".root");
      cout << "[INFO] 7TeV ALT model tree is " << sampleNameGG[_myModel] << endl;
	} // End if _myProd
	
	
} // End read7TeV_MC()
//=========================



//===========================
void Plotter::read8TeV_Data()
{
	cout << "[INFO]: Reading 8TeV Data..." << endl;
	
	data->Add(inputDir + "PRODFSR_8TeV/data/HZZ4lTree_DoubleMu.root");
	data->Add(inputDir + "PRODFSR_8TeV/data/HZZ4lTree_DoubleOr.root");
	data->Add(inputDir + "PRODFSR_8TeV/data/HZZ4lTree_DoubleEle.root");
}
//===========================



//===========================
void Plotter::read7TeV_Data()
{
	cout << "[INFO]: Reading 7TeV Data..." << endl;
	
	data->Add(inputDir + "PRODFSR/data/HZZ4lTree_DoubleMu.root");
	data->Add(inputDir + "PRODFSR/data/HZZ4lTree_DoubleOr.root");
	data->Add(inputDir + "PRODFSR/data/HZZ4lTree_DoubleEle.root");
}
//===========================



//================================================
void Plotter::makeHistos8TeV_MC( TString binning )
{

	cout << "[INFO]: Making 8TeV histos..." << endl;
	
	qqZZ_8->Draw( drawString + ">>qqZZ_8histo" + binning, "19.712*MC_weight*("+cutString+")" );
	qqZZ_8histo = (TH1F*) gDirectory->Get("qqZZ_8histo");
		
	ggZZ_8->Draw( drawString + ">>ggZZ_8histo" + binning, "19.712*MC_weight*("+cutString+")" );
	ggZZ_8histo = (TH1F*) gDirectory->Get("ggZZ_8histo");
	
//	POWHEG_8->Draw( drawString + ">>POWHEG_8histo" + binning, "19.712*MC_weight*("+cutString+")" );
//	POWHEG_8histo = (TH1F*) gDirectory->Get("POWHEG_8histo");

	SM_8->Draw( drawString + ">>SM_8histo" + binning, "19.712*MC_weight*("+cutString+")" );
	SM_8histo = (TH1F*) gDirectory->Get("SM_8histo");
//	SM_8histo->Scale(POWHEG_8histo->Integral()/SM_8histo->Integral());

	PS_8->Draw( drawString + ">>PS_8histo" + binning, "19.712*MC_weight*("+cutString+")" );
	PS_8histo = (TH1F*) gDirectory->Get("PS_8histo");
//	PS_8histo->Scale(POWHEG_8histo->Integral()/PS_8histo->Integral());

}
//================================================



//================================================
void Plotter::makeHistos7TeV_MC( TString binning )
{
	
	cout << "[INFO]: Making 7TeV histos..." << endl;

	
	qqZZ_7->Draw( drawString + ">>qqZZ_7histo" + binning, "5.051*MC_weight*("+cutString+")" );
	qqZZ_7histo = (TH1F*) gDirectory->Get("qqZZ_7histo");
   
	ggZZ_7->Draw( drawString + ">>ggZZ_7histo" + binning, "5.051*MC_weight*("+cutString+")" );
	ggZZ_7histo = (TH1F*) gDirectory->Get("ggZZ_7histo");
	
//	POWHEG_7->Draw( drawString + ">>POWHEG_7histo" + binning, "5.051*MC_weight*("+cutString+")" );
//	POWHEG_7histo = (TH1F*) gDirectory->Get("POWHEG_7histo");

	SM_7->Draw( drawString + ">>SM_7histo" + binning, "5.051*MC_weight*("+cutString+")" );
	SM_7histo = (TH1F*) gDirectory->Get("SM_7histo");
//	SM_7histo->Scale(POWHEG_7histo->Integral()/SM_7histo->Integral());

	PS_7->Draw( drawString + ">>PS_7histo" + binning, "5.051*MC_weight*("+cutString+")" );
	PS_7histo = (TH1F*) gDirectory->Get("PS_7histo");
//	PS_7histo->Scale(POWHEG_7histo->Integral()/PS_7histo->Integral());

}
//================================================



//======================================================
void Plotter::PlotKD( Utilities::hypothesis myModel, Utilities::production myProd )
{
	
	_myModel = myModel;
	_myProd  = myProd;
	
	applySuperKDcut = true;
	Plot();

	applySuperKDcut = false;
	Plot();
}
//======================================================
