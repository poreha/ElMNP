#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <TCanvas.h>
#include <TGraph.h>
using namespace std;

/*class Fill
{ int n=1024;
public: all[2*n];
void getname(char *c){
	ifstream fin(c); 
	if(!fin){cout<<"error"<<endl}
	for(int i=0;i<2*n;i++){fin>>all[i];}
	}	
	
};
*/
void ionisation(){
	
	const Int_t n=1024,m=7;
	Int_t j=1,k=0,l,i,o;
	Double_t all[2*n][m],y[n][m],x[n][m];
	ifstream fin1("calibr2mV.txt");
	ifstream fin2("calibr4mV.txt");
	ifstream fin3("calibr6mV.txt");
	ifstream fin4("calibr8mV.txt");
	ifstream fin5("calibr10mV.txt");
	ifstream fin6("Speksetk1.txt");
	ifstream fin7("Spectr2nonet.txt");
if((!fin1)||(!fin2)||(!fin3)||(!fin4)||(!fin5)||(!fin6)||(!fin7))
	{cout<<"error"<<endl;}
for(i=0;i<2*n;i++)
{	fin1>>all[i][0];
	fin2>>all[i][1];
	fin3>>all[i][2];
	fin4>>all[i][3];
	fin5>>all[i][4];
	fin6>>all[i][5];
	fin7>>all[i][6];
		}
TH1D *h1 = new TH1D("h1","hist1",512,0,1024);
TH1D *h2 = new TH1D("h2","hist2",512,0,1024);
TH1D *h3 = new TH1D("h3","hist3",512,0,1024);
TH1D *h4 = new TH1D("h4","hist4",512,0,1024);
TH1D *h5 = new TH1D("h5","hist5",1024,0,1024);
TH1D *h6 = new TH1D("h6","hist6",1024,0,1024);
TH1D *h7 = new TH1D("h7","hist7",1024,0,1024);
		
		for(o=0;o<m;o++)
	{ j=1;k=0;
	for(i=0;i<n;i++){	
		
		x[i][o]=all[k][o];
		y[i][o]=all[j][o];
		
					//ery[i]=sqrt(y[i]);
					//erx[i]=1.5;//ошибки в каждой точке
				if(o==0) h1->Fill(x[i][o],y[i][o]); 
				if(o==1) h2->Fill(x[i][o],y[i][o]); 
				if(o==2) h3->Fill(x[i][o],y[i][o]); 
					if(o==3) h4->Fill(x[i][o],y[i][o]);
					if(o==4) h5->Fill(x[i][o],y[i][o]);
					if(o==5) h6->Fill(x[i][o],y[i][o]);
					if(o==6) h7->Fill(x[i][o],y[i][o]);
					j+=2;k+=2;
					x[i][o]=0;//против наложения
					y[i][o]=0;					
					}
	}
					fin1.close();
					fin2.close();
					fin3.close();
					fin4.close();
					fin5.close();
					fin6.close();
					fin7.close();
	
	TCanvas *c1 = new TCanvas("c1","To-Be-Calibrated",60,40,1200,800);
	c1->Divide(3,3);
	c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->cd(3);
	h3->Draw();
	c1->cd(4);
	h4->Draw();
	
	
	}
