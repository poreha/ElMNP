#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <TCanvas.h>
#include <TGraph.h>

using namespace std;
/* класс при создании заполняет гистограмму значениями из текстового файла,
 * рисует ее (канва создается отдельно или подключается внутри) и сохраняет
 * рут-файлом в той же директории,
 * метод ReadFit считывает рут-файл, фитирует два пика на указанных интервалах 
 * гауссом */
class FillHist{
	private: ifstream fin;
	public: 
	FillHist(char *c, char *nameroot)
		{
			const Int_t n=1024;
			Int_t i,j,k;
			Double_t all[2*n],x[n],y[n],er[n];
		
			fin.open(c);
			if(!fin) cout<<"error"<<endl;
			for(i=0;i<2*n;i++)	fin>>all[i];
			j=1; k=0;
			
			TH1D *h1 = new TH1D("h1",c,1024,0,1024);
			for(i=0;i<n;i++)
			{	
				x[i]=all[k];
				y[i]=all[j];
				er[i]=sqrt(y[i]);
				h1->Fill(x[i],y[i]);
				h1->SetBinError(x[i],er[i]);
				j+=2; k+=2;
				}
			//TCanvas *c1 = new TCanvas("c1","Imp/channel",60,40,1200,800);
			TFile f(nameroot,"update");//запись в рут-файл
			h1->Draw();
			h1->Write();
			fin.close();
			
		}
		
void ReadFit(Char_t *name, Double_t x11, Double_t x12, Double_t x21, Double_t x22){
			TFile f(name,"read");		 
			TH1D *h1 = (TH1D*)f.Get("h1");
			TF1 *g1 = new TF1("m1","gaus",x11,x12);
			TF1 *g2 = new TF1("m2","gaus",x21,x22);
			h1->Draw("same");
			h1->Fit(g1,"R");
			h1->Fit(g2,"R+");
			g1->Draw("same");
			g2->Draw("same");
			}
	
	};//eof class


void calibr()
{	
	
	TCanvas *c1 = new TCanvas("c1","Imp/channel",60,40,800,600);
	FillHist A("calibr2mV.txt","calibr2mV.root");
	A.ReadFit("calibr2mV.root",55,104,170,230);
			
	TCanvas *c2 = new TCanvas("c2","Imp/channel",100,50,800,600);		
	FillHist B("calibr4mV.txt","calibr4mV.root");
	B.ReadFit("calibr4mV.root",112,160,322,378);
			
	TCanvas *c3 = new TCanvas("c3","Imp/channel",150,60,800,600);		
	FillHist C("calibr6mV.txt","calibr6mV.root");
	C.ReadFit("calibr6mV.root",170,224,460,530);
	
	TCanvas *c4 = new TCanvas("c4","Imp/channel",200,70,800,600);		
	FillHist D("calibr8mV.txt","calibr8mV.root");
	D.ReadFit("calibr8mV.root",210,258,562,625);	
	
	TCanvas *c5 = new TCanvas("c5","Imp/channel",250,80,800,600);		
	FillHist E("calibr10mV.txt","calibr10mV.root");
	E.ReadFit("calibr10mV.root",301,345,750,820);	
	
	const Int_t m=5;//число пиков
	 Double_t ch[m]={201.54,350.55,496.27,594.58,786.87};//второй пик
	 //Double_t ch[m]={80.38,137.96,196.44,237.18,321.91};//первый пик
	 Double_t U[m]={2,4,6,8,10};//узнать
	 Double_t erch[m]={0.09,0.11,0.13,0.12,0.11};
	 Double_t erU[m]={1,1,1,1,1};
	 
	TCanvas *c6 = new TCanvas("c6","Calibr",300,150,800,600);
	c6->SetGrid();
	TGraph *calibr = new TGraphErrors(m,ch,U,erch,erU);
	calibr->Draw("A*");
	calibr->Fit("pol1");
	calibr->GetXaxis()->SetTitle("Channel, N of peak");
	calibr->GetXaxis()->CenterTitle();
	calibr->GetYaxis()->SetTitle("Q, e-15 Coul");
	calibr->GetYaxis()->CenterTitle();
	calibr->SetTitle("Calibration");
	/*TCanvas *c7 = new TCanvas("c7","Calibration",500,150,800,600);
	c7->Divide(3,3);
	c7->cd(1);
	TFile f1("calibr2mV.root");
	TH1D *h2 = (TH1D*)f1.Get("h1");
	h2->Draw();
*/

}// eof main
