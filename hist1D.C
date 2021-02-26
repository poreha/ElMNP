#/!bin/bash
void getrandomh(){
//создание гистограммы
TH1D *h1 = new TH1D("h1","Test1",100,-7,7);
//заполнение гистограммы
h1.FillRandom("gaus",500);
TH1D *h2 = new TH1D("h2","Test2",100,-10,10);
for(int_t i=0;i<1000;i++){
	h2.Fill(h1.GetRandom());
	}
//отрисовка
TCanvas *c2 = new TCanvas("c2","Testing",1200,800);
c2.Divide(1,2);
c2.cd(1);
c2.SetFillColor(kRed);
h1.Draw();
c2.cd(2);
h2.Draw();
}
