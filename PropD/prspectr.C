#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <TCanvas.h>
#include <TGraph.h>
#include <math.h>

using namespace std;

class FillHist{
	private: ifstream fin;
	public: 
	FillHist(string c)//, string nameroot)
		{
			const Int_t n=1024;
			Int_t i;
			Double_t all[2*n],x[n],y[n],er[n];
				for(Int_t i=0;i<n;i++){
					x[i]=0, y[i]=0, er[i]=0;
				}
		
			fin.open(c);
			if(!fin) cout<<"error"<<endl;
			for(i=0;i<2*n;i++){	fin>>all[i];}
			//for(i=0;i<100;i++){	fin>>all[i]; cout<<"i="<<i<<" all[i]="<<all[i]<<endl;}
			fin.close();
			
			TH1F *h1 = new TH1F("h1","Spectrum",1024,0,1024);
			for(i=0;i<n;i++)
			
			{	
				x[i]=all[2*i];
				y[i]=all[2*i+1];
				er[i]=TMath::Sqrt(y[i]); 
					//cout<<"x[i]="<<x[i]<<" ;y[i]="<<y[i]<<"; err="<<er[i]<<endl;
				h1->Fill(x[i],y[i]);
				h1->SetBinError(i,er[i]);
				
				}

			h1->Draw();
		//	TFile f(nameroot,"update");
			//h1->Draw("E1");
			//h1->Write();
			h1->SetLineColor(1);
			
			
			//printf("Integral %g\n",h1->Integral());
		}
		
		
		
	};
	
class Toroot{
	private: Double_t x,y;
	public: 
		Toroot(Char_t *c){
			TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
			dir.ReplaceAll("scspectr.C",c);
	TFile *file = new TFile(Form("%s.root",dir.Data()),"RECREATE");
	TTree *tree = new TTree("tree","data");

	Long64_t nlines = tree->ReadFile(Form("%s.dat",dir.Data()),"x:y");
	TBranch *branch = tree->Branch("x",&x,"x/D");
	  for(Int_t i=0;i<nlines;i++){
		branch->Fill();
	  }
	tree->Write();
	tree->Print();
	TCanvas *c1 = new TCanvas("c1","y of x",50,50,800,600);
	tree->Draw("y:x");
			}
	
	};
	
void prspectr()
{
	
	TCanvas *c1 = new TCanvas("c1","100VMult1024",60,40,1200,800);
	FillHist A("100VMult1024.dat");//,"100VMult1024.root");
	
	TCanvas *c2 = new TCanvas("c2","1400VMult",100,70,1200,800);
	FillHist B("1400VMult.dat");//,"1400VMult.root");
	

	
	}
