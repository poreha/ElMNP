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

//defining function for fit
Double_t fitf(Double_t *x,Double_t *par)
{
Double_t arg = 0;
if (par[2] != 0) arg = (x[0] - par[1])/par[2];
Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);	

	return fitval;
}

Double_t fitf1(Double_t *x,Double_t *par)
{
//if (par1[2] != 0) 
//Double_t fitval1 = par[0]/(1-x[0]/2*par[0]);
Double_t fitval1 = -par[1]*x[0]+par[0];
 	return fitval1;
}
Double_t background(Double_t *x, Double_t *par) {
return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par) {
return background(x,par) + fitf(x,&par[3]);//lorentzianPeak(x,&par[3]);
}

Double_t fitFunction2(Double_t *x, Double_t *par) {
Double_t arg = 0;
if (par[4] != 0) arg = (x[0] - par[3])/par[4];
	return -par[1]*x[0]+par[0] + par[2]*TMath::Exp(-0.5*arg*arg);
}

void scincillation(){
	
	const Int_t n=1024,m=5;
	Int_t j=1,k=0,l,i,o;
	Double_t all[2*n][m],y[n][m],x[n][m];
	Double_t sumNaI30=0,sumNaI10=0,sumAntr=0;
	//РАБОТА С УКАЗАТЕЛЯМИ 
	ifstream fin1("SpektrCsNaI3.txt");
	ifstream fin2("SpektrCsNaI10.txt");
	ifstream fin3("SpektrCsAntr.txt");
	ifstream fin4("SpektrCsNaI40.txt");
	ifstream fin5("SpektrCoNaI40.txt");
if((!fin1)||(!fin2)||(!fin3)){cout<<"error"<<endl;}
for(i=0;i<2*n;i++)
{	fin1>>all[i][0];
	fin2>>all[i][1];
	fin3>>all[i][2];
	fin4>>all[i][3];
	fin5>>all[i][4];
		}//заполнение буферного массива

TCanvas *c1 = new TCanvas("c1","Hist E/channel",60,40,1200,800);
TH1D *h1 = new TH1D("h1","hist1",512,0,512);
TH1D *h2 = new TH1D("h2","hist2",512,0,512);
TH1D *h3 = new TH1D("h3","Cs NaI30/10/Antr",512,0,512);
TH1D *h4 = new TH1D("h4","Co/Cs NaI40",1024,0,1024);
TH1D *h5 = new TH1D("h5","Co/Cs NaI40",1024,0,1024);
//заполнение массивов
	for(o=0;o<m;o++)
	{ j=1;k=0;
	for(i=0;i<n;i++){	
		
		x[i][o]=all[k][o];
		y[i][o]=all[j][o];
		
					//ery[i]=sqrt(y[i]);
					//erx[i]=1.5;//ошибки в каждой точке
				if(o==0) {h1->Fill(x[i][o],y[i][o]); sumNaI30=sumNaI30+y[i][o];};
				if(o==1) {h2->Fill(x[i][o],y[i][o]); sumNaI10=sumNaI10+y[i][o];};
				if(o==2) {h3->Fill(x[i][o],y[i][o]); sumAntr=sumAntr+y[i][o];};
					if(o==3) h4->Fill(x[i][o],y[i][o]);
					if(o==4) h5->Fill(x[i][o],y[i][o]);
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
printf("Integrals: NaI30=%f NaI10=%f Antr=%f\n",sumNaI30,sumNaI10,sumAntr);
					h1->SetLineColor(3);
					h2->SetLineColor(2);
					//gStyle->SetOptStat(001001111);
					
					h1->Draw();
					h2->Draw("SAME");
					h3->Draw("SAME");
					

/*
// create a TF1 with the range from 0 to 3 and 6 parameters
TF1 *fitFcn = new TF1("fitFcn",fitFunction,0,512,6);
// first try without starting values for the parameters
// this defaults to 1 for each param.
//h1->Fit("fitFcn");
// this results in an ok fit for the polynomial function however
// the non-linear part (Lorentzian) does not respond well
// second try: set start values for some parameters
fitFcn->SetParameter(0,0);
fitFcn->SetParameter(1,4);
fitFcn->SetParameter(2,-0.01);
fitFcn->SetParameter(3,200);//fitf: амплитуда
fitFcn->SetParameter(4,110);//fitf: смещение
// width
fitFcn->SetParameter(5,20);//fitf: сигма квадрат
// peak
h1->Fit("fitFcn","V+");
// improve the picture:
TF1 *backFcn = new TF1("backFcn",background,0,512,3);
backFcn->SetLineColor(3);
TF1 *signalFcn = new TF1("signalFcn",fitf,0,512,3);
signalFcn->SetLineColor(4);
Double_t par[6];
// writes the fit results into the par array
fitFcn->GetParameters(par);
backFcn->SetParameters(par);
backFcn->Draw("same");
signalFcn->SetParameters(&par[3]);
signalFcn->Draw("same");
//
*/

TCanvas *c2 = new TCanvas("c2","Hist E/channel",10,200,1200,800);
h4->SetLineColor(2);
h4->Draw("e");
h5->Draw("eSAME");

//фит из примера  переделать под свою функцию подложки
TF1 *g1 = new TF1("m1","gaus",500,567);
TF1 *g2 = new TF1("m2","gaus",567,650);
//g3 = new TF1("m3","gaus",0,1024);

//Double_t par[9];//ряд параметров
TF1 *func = new TF1("fit",fitf,400,1024,3);
func->SetParameters(400,350,100);//h5->GetMean(),h5->GetRMS());
//total = new TF1("mstotal","gaus(0)+gaus(3)",500,650);
//g1->GetParameters(&par1[0]);
//g2->GetParameters(&par1[3]);
//g3->GetParameters(&par[6]);
h5->Fit(g1,"R");
h5->Fit(g2,"R+");
func->Draw("same");
//h5->Fit(func,"R+");
//h5->Fit(g3,"R+");
//total->SetParameters(par);
//h5->Fit(total,"R+");
	// eof fit 3gaus

TCanvas *c11 = new TCanvas("c11","NaI(30x30) E/channel",60,40,1200,800);
h1->Draw("e");
h1->SetLineColor(1);
TF1 *fitFcn1 = new TF1("fitFcn1",fitFunction2,60,180,5);
fitFcn1->SetParameter(0,750);//смещение по у
fitFcn1->SetParameter(1,0.9);//угол наклона
fitFcn1->SetParameter(2,300);//ампл
fitFcn1->SetParameter(3,120);//смещение
fitFcn1->SetParameter(4,15);//сигма 
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
printf("backwards1 %g\n",signalFcn1->Integral(0,512));

TCanvas *c12 = new TCanvas("c12","NaI(30x10) E/channel",60,40,1200,800);
h2->Draw("e");
h2->SetLineColor(1);
TF1* fitFcn2 = new TF1("fitFcn2",fitFunction2,60,180,5);
fitFcn2->SetParameter(0,620);//смещение по у
fitFcn2->SetParameter(1,1);//угол наклона
fitFcn2->SetParameter(2,280);//ампл
fitFcn2->SetParameter(3,130);//смещение
fitFcn2->SetParameter(4,15);//сигма 
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
printf("backwards2 %g\n",signalFcn2->Integral(0,512));

TCanvas *c13 = new TCanvas("c13","Antr E/channel",60,40,1200,800);
h3->Draw("e");
h3->SetLineColor(1);
/*TF1* fitFcn2 = new TF1("fitFcn2",fitFunction2,60,180,5);
fitFcn2->SetParameter(0,750);//смещение по у
fitFcn2->SetParameter(1,0.6);//угол наклона
fitFcn2->SetParameter(2,280);//ампл
fitFcn2->SetParameter(3,110);//смещение
fitFcn2->SetParameter(4,8);//сигма 
//fitFcn2->Draw("same");
TF1 *g3 = new TF1("m3","gaus",100,140);
h3->Fit(g3,"R+");
TF1 *backFcn = new TF1("backFcn",fitf1,70,150,2);
backFcn->SetLineColor(2);
TF1 *signalFcn = new TF1("signalFcn",fitf,60,180,3);
signalFcn->SetLineColor(2);

Double_t parm[5];
// writes the fit results into the par array
fitFcn2->GetParameters(parm);
backFcn->SetParameters(parm);
backFcn->Draw("same");
signalFcn->SetParameters(&parm[2]);
signalFcn->Draw("same");
*/
//printf("backwards3 %g\n",signalFcn->Integral(0,512));

Double_t n21=sumNaI10/sumNaI30;
Double_t n31=sumAntr/sumNaI30;
printf("Effective registration: %f %f\n",n21,n31);

printf("int NaI30 %g\n",h1->Integral());
printf("int NaI10 %g\n",h2->Integral());
printf("int Antr %g\n",h3->Integral());
//почему отличаются от простого суммирования событий по каналам?
//потому что без учета не попавших на гистограмму
//интеграл в пересчете на бины
printf("int NaI30 Compton %g\n",h1->Integral(2*85,2*165));
printf("int NaI30 Photo %g\n",h1->Integral(170*2,256*2));
printf("int NaI10 Compton %g\n",h2->Integral(90*2,175*2));
printf("int NaI10 Photo %g\n",h2->Integral(180*2,256*2));

					
/*TCanvas *c6 = new TCanvas("c6","Graph E/channel",60,40,1200,800);
	c6->SetGrid();
	TGraph *gr1 = new TGraph(n,x,y);
	gr1->SetTitle("Number of events on channel");
	gr1->SetLineColor(kBlue -2);
	gr1->GetXaxis()->SetTitle("Channel");
	gr1->GetXaxis()->CenterTitle();
	gr1->Draw("AC");
	*/
	//return 0;
	}
	// end of main
