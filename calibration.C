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

void calibration(){
	//добавить координаты х и ошибки
	
	const Int_t m=8;
	/*
	Double_t x[m]={0.1,0.2,0.4,0.6,0.8,1,1.2,1.4};
	Double_t ex[m]={0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};
	Double_t e[m]={5,5,5,4,7,15,40,150};
	Double_t er[m]={0.1,0.1,0.1,0.1,0.1,0.1,0.2,0.5};
	
	TCanvas *c62 = new TCanvas("c2","Graph Q/channel",60,40,1200,800);
	c62->SetGrid();
	TGraph *calibr = new TGraphErrors(m,x,e,ex,er);
	calibr->Draw("A*");
	//calibr->Fit("pol1");
	calibr->GetXaxis()->SetTitle("U, kV");
	calibr->GetXaxis()->CenterTitle();
	calibr->GetYaxis()->SetTitle("Q, e-15 Coul");
	calibr->GetYaxis()->CenterTitle();
	*/
	
	Double_t x[m]={0.1,0.2,0.4,0.6,0.8,1,1.2,1.4};
	Double_t ex[m]={0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};
	Double_t e[m]={1.04,1.04,1.04,0.83,1.46,3.1,8.3,31};
	Double_t er[m]={0.07,0.07,0.07,0.06,0.09,0.2,0.5,2};
	 
	TCanvas *c62 = new TCanvas("c2","Graph Mexp/channel",60,40,1200,800);
	c62->SetGrid();
	TGraph *calibr = new TGraphErrors(m,x,e,ex,er);
	calibr->Draw("A*");
	//calibr->Fit("pol1");
	calibr->GetXaxis()->SetTitle("U, kV");
	calibr->GetXaxis()->CenterTitle();
	calibr->GetYaxis()->SetTitle("Mexp");
	calibr->GetYaxis()->CenterTitle();
	TF1 *g0 = new TF1("m0","pol0",0.1,0.8);
	TF1 *g1 = new TF1("m1","pol1",0.8,1);
	TF1 *g2 = new TF1("m2","expo",1,1.5);
	calibr->Fit(g0,"R");
	calibr->Fit(g1,"R+");
	calibr->Fit(g2,"R+");
	}

