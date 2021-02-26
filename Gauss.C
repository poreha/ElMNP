#!/bin/bash
void Gauss(){
//создание канвы
	TCanvas *c1 = new TCanvas("c1","Gauss",10,10,1200,800);
//разделение на 6 палетов
	c1.Divide(3,2);
//заполнение первых трех палетов случайным распр Гаусса	
	c1.cd(1);
	TH1D *h1 = new TH1D("h1","RNGauss 1",500,-7,7);
	char *axis_title = "x, cm";
	h1.GetXaxis().SetTitle(axis_title);
	h1.FillRandom("gaus",500);
	h1.SetLineColor(kRed +3);
	h1.SetFillColor(kRed -3);
	h1.Draw();
	
	c1.cd(2);
	TH1D *h2 = new TH1D("h2","RNGauss 2",500,-7,7);
	char *axis_title = "x, cm";
	h2.GetXaxis().SetTitle(axis_title);
	h2.FillRandom("gaus",500);
	h2.SetLineColor(kGreen +3);
	h2.SetFillColor(kGreen -3);	
	h2.Draw();
	
	c1.cd(3);
	TH1D *h3 = new TH1D("h3","RNGauss 3",500,-7,7);
	char *axis_title = "x, cm";
	h3.GetXaxis().SetTitle(axis_title);
	h3.FillRandom("gaus",500);
	h3.SetLineColor(kBlue +3);
	h3.SetFillColor(kBlue -3);
	h3.Draw();
	//подпись оси координат
	char *axis_title = "x, cm";
	c1.GetXaxis().SetTitle(axis_title);
	//зарисовка двух распределений на одном палете
	c1.cd(4);
	TH1D *h4 = new TH1D("h4","RNGauss 3&4",500,-7,7);
	h4.FillRandom("gaus",100);
	h4.Draw();
	h3.Draw("same");
}
