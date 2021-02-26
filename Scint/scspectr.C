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
	FillHist(string c, string nameroot)
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
			
			printf("Integral %g\n",h1->Integral());
			
			printf("int NaI30 Compton %g\n",h1->Integral(0,308));//NaI10 308 NaI30 321
			printf("int NaI30 Photo %g\n",h1->Integral(360,512));
			
		}
				
	};
	
	/* Functions : fitFunction2 - gaussian with linear
	 * 				fitf - gaussian 
	 * 				fitf1 - linear
	*/
	
	
Double_t fitFunction2(Double_t *x, Double_t *par) {
Double_t arg = 0;
if (par[4] != 0) arg = (x[0] - par[3])/par[4];
	return -par[1]*x[0]+par[0] + par[2]*TMath::Exp(-0.5*arg*arg);
}

Double_t fitf(Double_t *x,Double_t *par)
{
Double_t arg = 0;
if (par[2] != 0) arg = (x[0] - par[1])/par[2];
Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);	

	return fitval;
}

Double_t fitf1(Double_t *x,Double_t *par)
{
Double_t fitval1 = -par[1]*x[0]+par[0];
 	return fitval1;
}
	
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

// Main body
	
void scspectr()
{
	//NaI(30x30)
TCanvas *c1 = new TCanvas("c1","Cs/NaI(30x30)",60,40,1200,800);
FillHist A("SpektrCsNaI30.dat","SpektrCsNaI30.root");
	//fitting
TF1 *fitFcn1 = new TF1("fitFcn1",fitFunction2,60,180,5);
	fitFcn1->SetParameters(750,0.9,300,120,15);
	fitFcn1->Draw("same");
TF1* backFcn1 = new TF1("backFcn",fitf1,70,170,2);
	backFcn1->SetLineColor(2);
TF1* signalFcn1 = new TF1("signalFcn",fitf,60,180,3);
	signalFcn1->SetLineColor(2);
Double_t par1[5];
// writes the fit results into the par array
	fitFcn1->GetParameters(par1);
	backFcn1->SetParameters(par1);
	backFcn1->Draw("same");
	signalFcn1->SetParameters(&par1[2]);
	signalFcn1->Draw("same");
	printf("backwards1 %g\n",signalFcn1->Integral(0,1024));

	//NaI(10x30)
TCanvas *c2 = new TCanvas("c2","Cs/NaI(10x30)",100,70,1200,800);
FillHist B("SpektrCsNaI10.dat","SpektrCsNaI10.root");
	//fitting
TF1* fitFcn2 = new TF1("fitFcn2",fitFunction2,60,180,5);
	fitFcn2->SetParameters(620,1,280,130,15);
	fitFcn2->Draw("same");
TF1 *backFcn2 = new TF1("backFcn",fitf1,70,170,2);
	backFcn2->SetLineColor(2);
TF1 *signalFcn2 = new TF1("signalFcn",fitf,60,180,3);
	signalFcn2->SetLineColor(2);
Double_t par2[5];
// writes the fit results into the par array
	fitFcn2->GetParameters(par2);
	backFcn2->SetParameters(par2);
	backFcn2->Draw("same");
	signalFcn2->SetParameters(&par2[2]);
	signalFcn2->Draw("same");
	printf("backwards2 %g\n",signalFcn2->Integral(0,1024));
	
	
	//Antracene
TCanvas *c3 = new TCanvas("c3","Cs/Antracene",120,100,1200,800);
FillHist C("SpektrCsAntr.dat","SpektrCsAntr.root");
	//Toroot Ta("SpektrCsAntr");
	
	}
