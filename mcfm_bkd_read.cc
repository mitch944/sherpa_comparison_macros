//#include "TFile.h"
//#include "TTree.h"
//#include "TH1F.h"
//#include "TLorentzVector.h"

//#include <iostream>
//#include <math.h>

// C++ standard library headers
#include <iostream>
#include <vector>

// ROOT headers
#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>
#include <TH1D.h>

// our own headers
// these files are located in the include directory
// #include "tcnt.hh" // tcnt prints the incremented counter value every second


using namespace std;

void mcfm_bkd_read()
{
  //TChain* fin = new TChain("ntuple");
  //fin->Add("./*.root");
    TFile *f = new TFile("../data/mcfm_data.root");
    TTree *ntuple = (TTree*)f->Get("ntuple");



// This works as .x read.cc or .x read.cc+
// adapted from routine  for WW fusion

  double wt_ALL,wt_gq,wt_gg,wt_qq,wt_qqb;

  double px31,px4,px5; //py6,py7;
  double py3,py4,py5;
  double pz3,pz4,pz5; //,pz6,pz7;
  double E_3,E_4,E_5; //,E_6,E_7;
    
 
double y_j3, pt_j3, phi_j3, phi_h_j3;

  ntuple->SetBranchAddress("px3",&px31);
  ntuple->SetBranchAddress("px4",&px4);
  ntuple->SetBranchAddress("px5",&px5);
//  h10->SetBranchAddress("px6",&px6);
//  h10->SetBranchAddress("px7",&px7);
  ntuple->SetBranchAddress("py3",&py3);
  ntuple->SetBranchAddress("py4",&py4);
  ntuple->SetBranchAddress("py5",&py5);
// h10->SetBranchAddress("py6",&py6);
//  h10->SetBranchAddress("py7",&py7);
  ntuple->SetBranchAddress("pz3",&pz3);
  ntuple->SetBranchAddress("pz4",&pz4);
  ntuple->SetBranchAddress("pz5",&pz5);
//  h10->SetBranchAddress("pz6",&pz6);
//  h10->SetBranchAddress("pz7",&pz7);
  ntuple->SetBranchAddress("E_3",&E_3);
  ntuple->SetBranchAddress("E_4",&E_4);
  ntuple->SetBranchAddress("E_5",&E_5);
// h10->SetBranchAddress("E_6",&E_6);
//  h10->SetBranchAddress("E_7",&E_7);
  ntuple->SetBranchAddress("wt_ALL",&wt_ALL);
  ntuple->SetBranchAddress("wt_gg",&wt_gg);
  ntuple->SetBranchAddress("wt_gq",&wt_gq);
  ntuple->SetBranchAddress("wt_qq",&wt_qq);
  ntuple->SetBranchAddress("wt_qqb",&wt_qqb);

  TFile* fout = new TFile("half_mcfm_bkd_hists.root","recreate");
    
    TH1D* pho_ratio_5 = new TH1D("pho_rato_5","pho1/pho2 ratio 0-5", 18,1,10);
    TH1D* pho_ratio_10 = new TH1D("pho_rato_10","pho1/pho2 ratio 5-10", 18,1,10);
    TH1D* pho_ratio_15 = new TH1D("pho_rato_15","pho1/pho2 ratio 10-15", 18,1,10);
    TH1D* pho_ratio_20 = new TH1D("pho_rato_20","pho1/pho2 ratio 15-20", 18,1,10);
    TH1D* pho_ratio_25 = new TH1D("pho_rato_25","pho1/pho2 ratio 20-25", 18,1,10);
    TH1D* pho_ratio_30 = new TH1D("pho_rato_30","pho1/pho2 ratio 25-30", 18,1,10);
    TH1D* pho_ratio_35 = new TH1D("pho_rato_35","pho1/pho2 ratio 30-35", 18,1,10);
    TH1D* pho_ratio_45 = new TH1D("pho_rato_45","pho1/pho2 ratio 35-45", 18,1,10);
    TH1D* pho_ratio_60 = new TH1D("pho_rato_60","pho1/pho2 ratio 45-60", 18,1,10);
    TH1D* pho_ratio_80 = new TH1D("pho_rato_80","pho1/pho2 ratio 60-80", 18,1,10);
    TH1D* pho_ratio_100 = new TH1D("pho_rato_100","pho1/pho2 ratio 80-100", 18,1,10);
    TH1D* pho_ratio_120 = new TH1D("pho_rato_120","pho1/pho2 ratio 100-120", 18,1,10);
    TH1D* pho_ratio_140 = new TH1D("pho_rato_140","pho1/pho2 ratio 120-140", 18,1,10);
    TH1D* pho_ratio_170 = new TH1D("pho_rato_170","pho1/pho2 ratio 140-170", 18,1,10);
    TH1D* pho_ratio_200 = new TH1D("pho_rato_200","pho1/pho2 ratio 170-200", 18,1,10);
    TH1D* pho_ratio_250 = new TH1D("pho_rato_250","pho1/pho2 ratio 200-250", 18,1,10);
    TH1D* pho_ratio_300 = new TH1D("pho_rato_300","pho1/pho2 ratio 250-300", 18,1,10);
    TH1D* pho_ratio_350 = new TH1D("pho_rato_350","pho1/pho2 ratio 300-350", 28,1,15);
    TH1D* pho_ratio_450 = new TH1D("pho_rato_450","pho1/pho2 ratio 350-450", 28,1,15);
    TH1D* pho_ratio_550 = new TH1D("pho_rato_550","pho1/pho2 ratio 450-550", 28,1,15);
    TH1D* pho_ratio_650 = new TH1D("pho_rato_650","pho1/pho2 ratio 550-650", 28,1,15);


  int nEntries = (int)ntuple->GetEntries();
  cout << "nEntries = " << nEntries << endl;

  for(int iEntry = 0; iEntry < nEntries; iEntry++){

    if(!(iEntry%50000))
      cout << "... reading event " << iEntry << endl;
    ntuple->GetEntry(iEntry);

    TLorentzVector vgam1(px31,py3,pz3,E_3);   // photon 1 4-vector
    TLorentzVector vgam2(px4,py4,pz4,E_4);  // photon 2 4-vector
    TLorentzVector vj1(px5,py5,pz5,E_5);  // 1st jet

    TLorentzVector vh = vgam1 + vgam2;      // higgs 4-vector
    
    double m_yy = (vgam1 + vgam2).M();      // higgs  mass
  
    double y_gam1 = vgam1.Rapidity();
    double pt_gam1 = vgam1.Perp();

    double y_gam2 = vgam2.Rapidity();
    double pt_gam2 = vgam2.Perp();

  
    double pho_ratio = pt_gam1/pt_gam2;

    double pt_h = vh.Perp();            // Higgs pT
   
      if ((m_yy<121 && m_yy>110) || (m_yy<160 && m_yy>129)) {
          if (pt_gam1>43.75) {
              if (pt_gam2>31.25) {
                  if (fabs(y_gam1)<2.4 && fabs(y_gam2)<2.4) {

                      if (pt_h<5) {
                          pho_ratio_5->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>5 && pt_h<10) {
                          pho_ratio_10->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>10 && pt_h<15) {
                          pho_ratio_15->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>15 && pt_h<20) {
                          pho_ratio_20->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>20 && pt_h<25) {
                          pho_ratio_25->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>25 && pt_h<30) {
                          pho_ratio_30->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>30 && pt_h<35) {
                          pho_ratio_35->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>35 && pt_h<45) {
                          pho_ratio_45->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>45 && pt_h<60) {
                          pho_ratio_60->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>60 && pt_h<80) {
                          pho_ratio_80->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>80 && pt_h<100) {
                          pho_ratio_100->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>100 && pt_h<120) {
                          pho_ratio_120->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>120 && pt_h<140) {
                          pho_ratio_140->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>140 && pt_h<170) {
                          pho_ratio_170->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>170 && pt_h<200) {
                          pho_ratio_200->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>200 && pt_h<250) {
                          pho_ratio_250->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>250 && pt_h<300) {
                      pho_ratio_300->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>300 && pt_h<350) {
                          pho_ratio_350->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>350 && pt_h<450) {
                          pho_ratio_450->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>450 && pt_h<550) {
                          pho_ratio_550->Fill(pho_ratio,wt_ALL);
                      }
                      if (pt_h>550 && pt_h<650) {
                          pho_ratio_650->Fill(pho_ratio,wt_ALL);
                      }
                  }
              }
          }
      }
  }
                              
   // hs->Draw();
    fout->Write();
  fout->Close();
    
}
