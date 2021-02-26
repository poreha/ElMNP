//#include <sstream>
//#include <iostream.h>
//#include <fstream>
//#include <cstring>
#include <TCanvas.h>
#include <TGraph.h>
#include <math.h>

using namespace std;

void countspeed(){
	
const Int_t m=9;	
Double_t N1[m],N2[m],N3[m],erN1[m],erN2[m],erN3[m];
Double_t c1[m]={0,0,72.03,79.6,81.76,82.86,90.8,102.06,108.93};
Double_t c2[m]={0,0,68.83,81.2,82.9,81.9,90.6,103.3,111.9};
Double_t c3[m]={0,60.6,70.6,70.93,70.76,71.23,74.46,76.56,77.2};
Double_t erc1[m],erc2[m],erc3[m];
Double_t U1[m]={810,814,815,840,865,890,915,940,950};
Double_t U2[m]={810,808,810,835,860,885,910,935,950};
Double_t U3[m]={788,790,815,840,865,890,915,940,950};
Double_t erU[m]={1,1,1,1,1,1,1,1,1};


for(Int_t i=0;i<m;i++){
	N1[i]=30*c1[i]; N2[i]=30*c2[i]; N3[i]=30*c3[i];
	erN1[i]=sqrt(N1[i])/N1[i]; erN2[i]=sqrt(N2[i])/N2[i]; erN3[i]=sqrt(N3[i])/N3[i];
	erc1[i]=c1[i]*erN1[i];
	erc2[i]=c2[i]*erN2[i];
	erc3[i]=c3[i]*erN3[i]; 
	
	cout<<erc1[i]<<" "<<erc2[i]<<" "<<erc3[i]<<endl;
	 }	
//erc3[m+1]=sqrt(c3[m+1]);
	/* TCanvas *ca1 = new TCanvas("c1","Graph n/U",60,40,1200,800);
	ca1->SetGrid();
	TGraph *gr1 = new TGraphErrors(m,U1,c1,erU,erc1);
	TGraph *gr2 = new TGraphErrors(m,U1,c2,erU,erc2);
	TGraph *gr3 = new TGraphErrors(m,U1,c3,erU,erc3);
	gr2->Draw();
	gr1->Draw("same");
	gr3->Draw("same");*/
}
