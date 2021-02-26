/* to use: convert(rename) spectrum file from .txt to .dat*/
#include "Riostream.h"

void toroot(){
	
const char fn[]="SpektrCsNaI10";//spectrum filename SpektrCsNaI30 SpektrCsNaI10 SpektrCsAntr

	Double_t x,y;    // coordinates
	TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
	//sets path to current dir
	dir.ReplaceAll("toroot.C",fn);
	
	TFile *file = new TFile(Form("%s.root",dir.Data()),"RECREATE");
	TTree *tree = new TTree("tree","data");

	Long64_t nlines = tree->ReadFile(Form("%s.dat",dir.Data()),"x:y");
	//reading from file:
	
	//Create branches
	//setting the first leaf as x
	TBranch *branch = tree->Branch("x",&x,"x/D");
	  for(Int_t i=0;i<nlines;i++){
		branch->Fill();
	  }
	  tree->Write();
	tree->Print();
	
	printf("   -->  found %lld lines\n",nlines);
	printf("   -->  create root file: %s.root\n",fn);

//
	TCanvas *c1 = new TCanvas("c1","y of x",50,50,800,600);
	
	
	tree->Draw("y:x");

}
