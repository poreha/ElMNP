/*Берёт текстовый файл со двумя столбцами n-координат: x y переводит их
 * в два массива, может составить гистограмму, полный график,
 * поставить погрешности в пиках (количество пиков задается m), приблизить
 * часть графика с погрешностями точек
 * Нужно задавать: Название тхт файла, вершины пиков, погрешности пиков
 * ширину и высоту проведения половины пика
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <TCanvas.h>
#include <TGraph.h>
using namespace std;

//class histo()

void streamgraph()
{

const Int_t n=4096,m=3,p=2;//m-для пиков p-для прямых половины
Double_t peak[m]={955,1001,1672};
Double_t l1x[p]={2000,2200};//заменить массивом х+-100
Double_t l2x[p]={2100,2300};
Double_t l3x[p]={2300,2500};
Double_t l1y[p],l2y[p],l3y[p];
Double_t all[2*n],y[n],x[n],erx[n],ery[n];
Double_t x1[m]={2063,2210,2355};
Double_t ey[m];
Double_t ener[m]={0.01,0.001,0.01};//погрешность энергии указать
Double_t ex[m]={2,2,2};
Double_t energy[m]={4.8,5.15,5.5};
double sumx=0,sumy=0,sumx2=0,sumxy=0,alpha=0,b=0;
Int_t i=0,j=1,k=0,l=0;

//добавить возможность ввода названия файла
//FILE *inputf = fopen("Vvodnoe.txt","r");

ifstream fin("Vvodnoe.txt");
if(!fin){
	cout<<"error"<<endl;
	 //return 1;//остаток с int нужен ли? выведет ли прогр ошибку?
		}
for(i=0;i<2*n;i++){fin>>all[i];	}//заполнение буферного массива
	//создание канвы
	/*TCanvas *c5 = new TCanvas("c5","hist1",800,600);
	//c5->Divide(2,1); делаю две канвы
	//c5->cd(1);
	TH1D *h1 = new TH1D("Title","h1",500,0,4000);
	h1->GetXaxis()->SetTitle("E, eV");
	*/
	for(l=0;l<p;l++){
		l1y[l]=peak[0]/2;
		l2y[l]=peak[1]/2;
		l3y[l]=peak[2]/2;}
					 l=0;
	for(l=0;l<m;l++){ey[l]=sqrt(peak[l]);
		 printf("deltaN= %f\n",ey[l]);
		 };
	l=0;
	//заполнение массивов
	i=0;
	while(j<2*n){	
					y[i]=all[j];
					x[i]=all[k];
					ery[i]=sqrt(y[i]);
					erx[i]=1.5;//ошибки в каждой точке
		
//					h1->Fill(x[i],y[i]);
					j+=2;
					k+=2;
					i++;
					};
					fin.close();
	//h1->Draw();				
	for(l=0;l<m;l++){
		sumx=sumx+x1[l];
		sumy=sumy+energy[l];
		sumx2=sumx2+sumx*sumx;
		sumxy=sumxy+x1[l]*energy[l];
		};
		alpha=((m*sumxy-sumx*sumy)/(m*sumx2-sumx*sumx));
		b=((sumy-alpha*sumx)/m);
		printf("a= %f ",alpha);
		printf("b= %f\n",b);
			
	//c5->cd(2);
	TCanvas *c6 = new TCanvas("c6","Graph E/channel",60,40,1200,800);
	c6->SetGrid();
	TGraph *gr2 = new TGraphErrors(m,x1,peak,ex,ey);
	TGraph *gr1 = new TGraph(n,x,y);
	TGraph *gr3 = new TGraphErrors(n,x,y,erx,ery);
	TGraph *calibr = new TGraphErrors(m,x1,energy,ex,ener);
	gr3->SetName("GraphEr");//чтобы drawtext видел
	gr1->SetTitle("Number of events on channel");
	gr1->SetLineColor(kBlue -2);
	//gr1->GetYaxis()->SetTitle("Number");
	gr1->GetXaxis()->SetTitle("Channel");
	gr1->GetXaxis()->CenterTitle();
	//gr1->GetYaxis()->CenterTitle();
	gr1->Draw("AP");
	
	//подпись координат точек gr2 смотри Имя
	TExec *exo = new TExec("exo","drawtext();");
    gr2->GetListOfFunctions()->Add(exo);
    for(Int_t a=0;a<m;a++){gr2->SetPoint(a,x1[a],peak[a]);}
	gr3->GetListOfFunctions()->Add(exo);
    for(i=0;i<n;i++){gr3->SetPoint(i,x[i],y[i]);}
	//
	gStyle->SetEndErrorSize(3);
	gr2->SetName("GraphEr");
	//gr2->SetLineColor(2);
	gr2->SetMarkerColor(2);
	gr2->SetMarkerStyle(24);
	gr2->Draw("P");
	
	TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);//легенда
	legend->AddEntry(gr2,"1st Peak (2063;955)");
	legend->AddEntry(gr2,"2nd Peak (2210;1001)");
	legend->AddEntry(gr2,"3rd Peak (2355;1672)");
	legend->SetEntryOption("lp"); // добавляем график в легенду
	legend->Draw("lp"); // тут тоже могут быть разные опции
//построение калибровочного графика погрешности какие-то маленькие
	TCanvas *c10 = new TCanvas("c10","Calibration",800,600);
	calibr->GetXaxis()->SetTitle("Channel, N of peak");
	calibr->GetXaxis()->CenterTitle();
	calibr->GetYaxis()->SetTitle("Energy, MeV");
	calibr->SetTitle("Calibration");
	calibr->SetMarkerColor(2);
	calibr->Draw();

	
	//зумирование графика через гист
	//середина первого пика
c7 = new TCanvas("c7","Middle of the 1st Peak",200,10,800,600);
hpx1 = new TH2F("hpx1","Middle = 477.5",70,2010,2110,100,450,500); // axis range
hpx1->SetStats(kFALSE); // no statistics
hpx1->Draw();
TGraph *line1 = new TGraph(p,l1x,l1y);
gr3->SetMarkerColor(2);
gr3->SetMarkerStyle(24);
gr3->Draw("lp");
TLegend *legend1 = new TLegend(0.55,0.65,0.76,0.82);//легенда
legend1->InsertEntry("Desp","Despersion = 2.5ch");
legend1->SetEntryOption("lp");
legend1->InsertEntry("width","Width = 69.5ch");
legend1->InsertEntry("middle","Middle = 477.5 events");
legend1->Draw("p");
legend1->SetEntryOption("lp");	

line1->SetLineStyle(2);
line1->Draw("cp");
	
	//середина второго пика
c8 = new TCanvas("c8","Middle of the 2nd Peak",250,30,800,600);
hpx2 = new TH2F("hpx2","Middle = 500.5",70,2160,2250,100,470,520); // axis range
hpx2->SetStats(kFALSE); // no statistics
hpx2->Draw();
gr3->Draw("lp");
TGraph *line2 = new TGraph(p,l2x,l2y);
line2->SetLineStyle(2);
line2->Draw("cp");	
TLegend *legend2 = new TLegend(0.55,0.65,0.76,0.82);//легенда
legend2->InsertEntry("Desp","Despersion = 1.1ch");
legend2->InsertEntry("width","Width = 67.5ch");
legend2->InsertEntry("middle","Middle = 500.5 events");
legend2->Draw("p");	
legend2->SetEntryOption("p");


	//середина третьего пика
c9 = new TCanvas("c9","Middle of the 3rd Peak",260,50,800,600);
hpx3 = new TH2F("hpx3","Middle = 836",70,2310,2400,100,800,860); // axis range
hpx3->SetStats(kFALSE); // no statistics
hpx3->Draw();
gr3->Draw("lp");
TGraph *line3 = new TGraph(p,l3x,l3y);
line3->SetLineStyle(2);
line3->Draw("cp");
TLegend *legend3 = new TLegend(0.55,0.65,0.76,0.82);//легенда
legend3->InsertEntry("Desp","Despersion = 1.1ch");
legend3->InsertEntry("width","Width = 67.5ch");
legend3->InsertEntry("middle","Middle = 836 events");
legend3->Draw("p");	
legend3->SetEntryOption("p");

	
}

//подписывает все координаты, перед этим граф переименовать в GraphEr
void drawtext()
{
   Int_t i,n;
   Double_t x,y;
   TLatex l;

   l.SetTextSize(0.02);
   l.SetTextFont(41);
   l.SetTextAlign(33);
   l.SetTextColor(kBlack);

   TGraph *g = (TGraph*)gPad->GetListOfPrimitives()->FindObject("GraphEr");
   n = g->GetN();

   for (i=0; i<n; i++) {
      g->GetPoint(i,x,y);
      l.PaintText(x-2,y,Form("(%4.0f,%4.0f)	",x,y));
   }
}


/*class histo{
	public:
	Int_t mas1;
	Int_t mas2;
	histo(int mas1,int mas2);
	
	TCanvas *c1 = new TCanvas("c1","hist1",800,600);
	
}*/
//проблема - построение всего графика gr3 с подписями дает большую нагрузку
//end of file
