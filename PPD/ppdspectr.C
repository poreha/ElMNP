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
			const Int_t n=4096;
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
			
			TH1F *h1 = new TH1F("h1","Spectrum",n,0,n);
			for(i=0;i<n;i++)
			//for(i=1240;i<1280;i++)
			{	
				x[i]=all[2*i];
				y[i]=all[2*i+1];
				er[i]=TMath::Sqrt(y[i]); 
					//cout<<"x[i]="<<x[i]<<" ;y[i]="<<y[i]<<"; err="<<er[i]<<endl;
				h1->Fill(x[i],y[i]);
				h1->SetBinError(i,er[i]);
				
				}
			h1->SetLineColor(1);
			h1->Draw("E");
			
			/*TFile f(nameroot,"update");
			
			h1->Write();
			*/
			
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
	
void ppdspectr()
{
	/*
	TCanvas *c1 = new TCanvas("c1","Source 3/4V",60,40,800,600);
	FillHist A("SpektrSource3-4V.dat");//,"SpektrCsNaI30.root");
	
	TCanvas *c2 = new TCanvas("c2","Source 3/5V",100,70,800,600);
	FillHist B("SpektrSource3-5V.dat");//"SpektrCsNaI10.root");
	
	TCanvas *c3 = new TCanvas("c3","Source 3/15V",120,100,800,600);
	FillHist C("SpektrSource3-15V.dat");//"SpektrCsAntr.root");
	//Toroot Ta("SpektrCsAntr");
	
	TCanvas *c4 = new TCanvas("c4","Source 3/30V",140,130,800,600);
	FillHist D("SpektrSource3-30V.dat");
	*/
	TCanvas *c5 = new TCanvas("c5","Source 3/50V",180,160,800,600);
	FillHist E("SpektrSource3-50V.dat");
	
	
	//delta E from U
	
	Double_t dE[5]={80.2,72.6,67.3,63.5,64.8};
	Double_t edE[5]={0.8,0.8,0.5,0.5,0.3};
	Double_t U[5]={4,5,15,30,50};
	Double_t eU[5]={0.1,0.1,0.1,0.1,0.1};
	TCanvas *c7 = new TCanvas("c7","delta E of U",180,160,800,600);
	c7->SetGrid();
	TGraph *eofu = new TGraphErrors(5,U,dE,eU,edE);
	eofu->Draw();
	
	//TCanvas *c6 = new TCanvas("c6","Source 3/48.6V",200,190,800,600);
	//FillHist F("SpektrSource3-48.6V.dat");
	TCanvas *c6 = new TCanvas("c6","Source 2/50V",200,190,800,600);
	FillHist H("SpektrSrc2-50V.dat");
	TCanvas *c61 = new TCanvas("c61","Source 3/50V(task 5)",200,190,800,600);
	FillHist H1("SpektrSrc3(task 5)-50V.dat");
	
	//calibration f/ task 5
	
	//with generator
	
	
	TCanvas *c11 = new TCanvas("c11","Source Generator/50V",60,40,800,600);
	FillHist A1("SpektrSrcGen3-50V(after).dat");
	//FillHist A1("SpektrSrcGen3-50V.dat");
	TCanvas *c15 = new TCanvas("c15","Source 3/50V",180,160,800,600);
	FillHist E1("SpektrSrc3(task 5)-50V.dat");
	TCanvas *c12 = new TCanvas("c12","Source Generator/50V",60,40,800,600);
	FillHist A12("SpektrSourceGen-0V(5min).dat");
	
	
	
	//C(U)
	
	
	//Double_t U[5]={4,5,15,30,50};
	Double_t C[5]={161.0,155.5,97.3,76.3,64.3};
	Double_t lnU[5]={1.386,1.609,2.708,3.401,3.912};
	Double_t lnC[5]={5.081,5.047,4.578,4.335,4.164};
	Double_t lnU1[5];
	TCanvas *c72 = new TCanvas("c72","ln(C)/ln(U)",180,160,800,600);
	c7->SetGrid();
	for(Int_t i=0;i<5;i++){
	lnU1[i]=(-0.5)*lnU[i]+6;
	}
	
	TGraph *calibr = new TGraph(5,lnU,lnC);//,eU,eC);
	
	calibr->Draw("A*");
	calibr->Fit("pol1");
	TGraph *calibr1 = new TGraph(5,lnU,lnU1);
	calibr1->Draw("SAME");
	calibr->GetXaxis()->SetTitle("U,V");
	calibr->GetXaxis()->CenterTitle();
	calibr->GetYaxis()->SetTitle("C, e-12 F");
	calibr->GetYaxis()->CenterTitle();
	
	}

