


//чтение рут файла и заполнение гист
{
TFile *f = new TFile("tree1.root");
TTree *t1 = (TTree*)f->Get("t1");
Float_t px, py, pz;
Int_t ev;
t1->SetBranchAddress("px",&px);
t1->SetBranchAddress("py",&py);
t1->SetBranchAddress("pz",&pz);
t1->SetBranchAddress("ev",&ev);
  
TH2F *hpxpy = new TH2F("hpxpy","py vs px",30,-3,3,30,-3,3);
Int_t nentries = (Int_t)t1->GetEntries();
for (Int_t i=0; i<nentries; i++) {
  t1->GetEntry(i);
  hpxpy->Fill(px,py);
}
hpxpy->Draw();
} 
