//test macro

#include <TCanvas.h>
#include <TRandom.h>
#include <TH1.h>
#include <TGraph.h>

// fit library
// TFit
// 

void testmacro(){
	test();}

void test(){
cout<<"test output<<"<<endl;

//gStyle->("r");

TCanvas *c1=new TCanvas("c2","Title",1200,800);
c1->Divide(2,2);

	c1->cd(1);
	TH1D *h1 = new TH1D("h1","RNGauss 1",140,-7,7);

	h1->FillRandom("gaus",50000);
	h1->SetLineColor(kRed +3);
	h1->SetFillColor(kRed -3);
	h1->Draw();
	
	
	c1->cd(2);
	TH1D *h2 = new TH1D("h2","RNGauss 2",140,-7,7);

	h2->FillRandom("landau",50000);
	h2->SetLineColor(kBlue +3);
	h2->SetFillColor(kBlue -3);
	h2->Draw();
	
	c1->cd(3);
	h1->Draw(); h2->Draw("same");
	
	c1->cd(4);
	TH2D *h3=new TH2D("h3","",100,0,100,100,0,100);

	
	

}
