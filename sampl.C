

#include <TH1.h>
#include <TCanvas.h>
#include <TRandom.h>
void redG();
void cicleG(int col, int cfill, int cline);

void sampl(){
	int col,cline,cfill;
//char *axis_title = "x, cm";
TCanvas *c1 = new TCanvas("c1","Sample",10,10,800,600);
c1->Divide(2,2);
	c1->cd(1);
	cout<<"Enter color code: ";
	cin>>col;
	cout<<"Fill color: ";
	cin>>cfill;
	cout<<"Line color: ";
	cin>>cline;
	//color
	cicleG(col,cfill,cline);
	
//c1->cd(1);
//redG();
//col=0; cline=0; cfill=0;
}
// redG - скорее функция, чем класс
void redG(){
//TCanvas *c1 = new TCanvas("c1","Sample",10,10,800,600);
//c1->Divide(2,2);
//c1->cd(1);
//h1->GetXaxis()->SetTitle(axis_title);
TH1D *h1 = new TH1D("h1","redGauss",50,-10,10);
h1->FillRandom("gaus",2000);
h1->SetLineColor(kRed +3);
h1->SetFillColor(kRed -3);
h1->Draw();
}

void cicleG(int col, int cfill, int cline){
	TH1D *h1 = new TH1D("h1","ColorGauss",40,-10,10);
h1->FillRandom("gaus",2000);

if(col==1){
h1->SetLineColor(kRed +cline);
h1->SetFillColor(kRed -cfill);
};

if(col==2){
h1->SetLineColor(kBlue +cline);
h1->SetFillColor(kBlue -cfill);
};

if(col==3){
h1->SetLineColor(kGreen +cline);
h1->SetFillColor(kGreen -cfill);
};

else{cout<<"widen color pallete"<<endl;};
h1->Draw();
col==0; cline==0; cfill==0;
	}

//void axis(){
//	char *axis_title = "x, cm";
//	GetXaxis()->SetTitle(axis_title);
//	}

//end
