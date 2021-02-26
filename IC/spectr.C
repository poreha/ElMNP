#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <TCanvas.h>
#include <TGraph.h>

using namespace std;

class FillHist{
	private: ifstream fin;
	public: 
	FillHist(const char *c, char *nameroot)
		{
			const Int_t n=1024;
			Int_t i,j,k;
			Double_t all[2*n],x[n],y[n];
		
			fin.open(c);
			if(!fin) cout<<"error"<<endl;
			for(i=0;i<2*n;i++)	fin>>all[i];
			j=1; k=0;
			
			TH1D *h1 = new TH1D("h1","Spectrum",1024,0,400);
			for(i=0;i<n;i++)
			{	
				x[i]=all[k];
				y[i]=all[j];
				h1->Fill(x[i],y[i]);
				j+=2; k+=2;
				}
			
			TFile f(nameroot,"update");
			//h1->Draw("e1");
			h1->Draw();
			h1->Write();
			h1->SetLineColor(1);
			fin.close();
			
			printf("Integral %g\n",h1->Integral());
		}
		
		
		
	};
	
void spectr()
{
	
	TCanvas *c1 = new TCanvas("c1","Imp/channel",60,40,1200,800);
	FillHist A("Spectr2nonet.txt","NoNet.root");
	
	TCanvas *c2 = new TCanvas("c2","Imp/channel",100,70,1200,800);
	FillHist B("Speksetk1.txt","NetIC.root");
	
	
	}
