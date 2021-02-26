#!/bin/bash
{
//создание канвы
	TCanvas *c1 = new TCanvas("c1","Gauss",10,10,1200,800);
//разделение на 6 палетов
	c1.Divide(3,2);
//заполнение первых трех палетов случайным распр Гаусса	
	c1.cd(1);
	TH1D *h1 = new TH1D("h1","RNGauss 1",150,-7,7);
	char *axis_title = "x, cm";
	h1.GetXaxis().SetTitle(axis_title);
	h1.FillRandom("gaus",500);
	h1.SetLineColor(kRed +3);
	h1.SetFillColor(kRed -3);
	h1.Draw();
	
	c1.cd(2);
	TH1D *h2 = new TH1D("h2","RNGauss 2",150,-7,7);
	char *axis_title = "x, cm";
	h2.GetXaxis().SetTitle(axis_title);
	h2.FillRandom("gaus",500);
	h2.SetLineColor(kGreen +3);
	h2.SetFillColor(kGreen -3);	
	h2.Draw("C");
	
	c1.cd(3);
	TH1D *h3 = new TH1D("h3","RNGauss 3",150,-7,7);
	char *axis_title = "x, cm";
	h3.GetXaxis().SetTitle(axis_title);
	h3.FillRandom("gaus",500);
	h3.SetLineColor(kBlue +3);
	h3.SetFillColor(kBlue -3);
	h3.Draw();
//зарисовка двух распределений на одном палете
	c1.cd(4);
	TH1D *h4 = new TH1D("h4","RNGauss 3&4",150,-7,7);
	h4.FillRandom("gaus",800);
	h4.SetFillColor(kOrange +7);
	h4.SetLineColor(kOrange +4);
	char *axis_title = "x, cm";
	h4.GetXaxis().SetTitle(axis_title);
	h4.Draw();
	h2.Draw("same");
//создание 2х-мерной гистограммы
	c1.cd(5);
//	TH2D *h5 = new TH2D("h5","2D",150,-7,7,150,-7,7);
//	for( int i=0; i<1000; i++ ) {
//	double x = ;
//	double y = gRandom->Gaus(0.5,0.2);
//	h5.Fill(x,y);  
//	}
//	h5.Draw();
}
