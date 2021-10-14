/*
 purpose :
 inputs :
 outputs :
 */

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

#include "tcnt.hh"

using std::cout;
using std::cerr;
using std::endl;
using ivanp::tcnt;

int main(int argc, char* argv[]) {
    
    // make sure you have all necessary arguments
    if (argc != 3) {
      cout << "usage: " << argv[0] << " data.root histograms.root\n";
        return 1;
    }

    // this is the file that will contain the histograms
    TFile fout(argv[2],"recreate");
    if (fout.IsZombie()) {
        cerr << "\033[31m" "cannot open output ROOT file" "\033[0m\n";
        return 1;
    }

    // here are all the histograms
    TH1D* pho_ratio_5 = new TH1D("pho_rato_5","pho1/pho2 ratio 0-5", 2,1,2);
    TH1D* pho_ratio_10 = new TH1D("pho_rato_10","pho1/pho2 ratio 5-10", 2,1,2);
    TH1D* pho_ratio_15 = new TH1D("pho_rato_15","pho1/pho2 ratio 10-15", 2,1,2);
    TH1D* pho_ratio_20 = new TH1D("pho_rato_20","pho1/pho2 ratio 15-20", 2,1,2);
    TH1D* pho_ratio_25 = new TH1D("pho_rato_25","pho1/pho2 ratio 20-25", 4,1,3);
    TH1D* pho_ratio_30 = new TH1D("pho_rato_30","pho1/pho2 ratio 25-30", 4,1,3);
    TH1D* pho_ratio_35 = new TH1D("pho_rato_35","pho1/pho2 ratio 30-35", 4,1,3);
    TH1D* pho_ratio_45 = new TH1D("pho_rato_45","pho1/pho2 ratio 35-45", 4,1,3);
    TH1D* pho_ratio_60 = new TH1D("pho_rato_60","pho1/pho2 ratio 45-60", 6,1,4);
    TH1D* pho_ratio_80 = new TH1D("pho_rato_80","pho1/pho2 ratio 60-80", 6,1,4);
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

  // get the data file
    cout << "reading input ROOT file \"" << argv[1] <<'\"'<< endl;
    TFile fin(argv[1]);
    if (fin.IsZombie()) {
        cerr << "\033[31m" "cannot open input ROOT file" "\033[0m\n";
        return 1;
    }

  // get the data tree
    TTree* tree = fin.Get<TTree>("HGamData");
    if (!tree) {
        cerr << "\033[31m" "cannot get TTree \"HGamData\"" "\033[0m\n";
        return 1;
    }
    cout << '\n';

  // create the TTreeReader
    TTreeReader reader(tree);
    TTreeReaderValue<UInt_t> b_njets(reader,"njets");
    TTreeReaderArray<Float_t>
        b_photon_pt      (reader,   "photon_pt" ),
        b_photon_eta     (reader,   "photon_eta"),
        b_photon_phi     (reader,   "photon_phi"),
        b_photon_m       (reader,   "photon_m"  ),
        b_jet_pt         (reader,   "jet_pt" ),
        b_jet_eta        (reader,   "jet_eta"),
        b_jet_phi        (reader,   "jet_phi"),
        b_jet_m          (reader,   "jet_m"  );

  // set un lorentz vectors
  std::vector<TLorentzVector>
    photons(2),
    jets;

  // loop over all events
    for (tcnt cnt(reader.GetEntries()); reader.Next(); ++cnt) {

    // get the lorentz vectors of the photons
        for (unsigned i=0; i<2; ++i) {
            photons[i].SetPtEtaPhiM(
                                    b_photon_pt [i],
                                    b_photon_eta[i],
                                    b_photon_phi[i],
                                    b_photon_m  [i]
                                    );
        }
    

    // get lorentz vectors of the jets
        const unsigned njets = *b_njets;
        jets.resize( *b_njets);
        
        for (unsigned i=0; i< *b_njets; ++i) {
            jets[i].SetPtEtaPhiM(
                                b_jet_pt [i],
                                b_jet_eta[i],
                                b_jet_phi[i],
                                b_jet_m  [i]
                                );
        }
        
        // get the diphoton lorentz vector and create necessary variables
        const TLorentzVector diphoton = photons[0] + photons[1];

        double pt_gam1 = photons[0].Pt();
        double pt_gam2 = photons[1].Pt();
        double y_gam1 = photons[0].Rapidity();
        double y_gam2 = photons[1].Rapidity();
        double pho_ratio = pt_gam1/pt_gam2;
        double pt_h = diphoton.Pt();
        double m_yy = diphoton.M();
            
            // use if statements to add each event to the correct histogram
        if ((m_yy<121 && m_yy>110) || (m_yy<160 && m_yy>129)) {
            if (pt_gam1>43.75) {
                if (pt_gam2>31.25) {
                    if (fabs(y_gam1)<2.4 && fabs(y_gam2)<2.4) {
                        if (pt_h<5) {
                            pho_ratio_5->Fill(pho_ratio);
                        }
                        if (pt_h>5 && pt_h<10) {
                            pho_ratio_10->Fill(pho_ratio);
                        }
                        if (pt_h>10 && pt_h<15) {
                            pho_ratio_15->Fill(pho_ratio);
                        }
                        if (pt_h>15 && pt_h<20) {
                            pho_ratio_20->Fill(pho_ratio);
                        }
                        if (pt_h>20 && pt_h<25) {
                            pho_ratio_25->Fill(pho_ratio);
                        }
                        if (pt_h>25 && pt_h<30) {
                            pho_ratio_30->Fill(pho_ratio);
                        }
                        if (pt_h>30 && pt_h<35) {
                            pho_ratio_35->Fill(pho_ratio);
                        }
                        if (pt_h>35 && pt_h<45) {
                            pho_ratio_45->Fill(pho_ratio);
                        }
                        if (pt_h>45 && pt_h<60) {
                            pho_ratio_60->Fill(pho_ratio);
                        }
                        if (pt_h>60 && pt_h<80) {
                            pho_ratio_80->Fill(pho_ratio);
                        }
                        if (pt_h>80 && pt_h<100) {
                            pho_ratio_100->Fill(pho_ratio);
                        }
                        if (pt_h>100 && pt_h<120) {
                            pho_ratio_120->Fill(pho_ratio);
                        }
                        if (pt_h>120 && pt_h<140) {
                            pho_ratio_140->Fill(pho_ratio);
                        }
                        if (pt_h>140 && pt_h<170) {
                            pho_ratio_170->Fill(pho_ratio);
                        }
                        if (pt_h>170 && pt_h<200) {
                            pho_ratio_200->Fill(pho_ratio);
                        }
                        if (pt_h>200 && pt_h<250) {
                            pho_ratio_250->Fill(pho_ratio);
                        }
                        if (pt_h>250 && pt_h<300) {
                            pho_ratio_300->Fill(pho_ratio);
                        }
                        if (pt_h>300 && pt_h<350) {
                            pho_ratio_350->Fill(pho_ratio);
                        }
                        if (pt_h>350 && pt_h<450) {
                            pho_ratio_450->Fill(pho_ratio);
                        }
                        if (pt_h>450 && pt_h<550) {
                            pho_ratio_550->Fill(pho_ratio);
                        }
                        if (pt_h>550 && pt_h<650) {
                            pho_ratio_650->Fill(pho_ratio);
                        }
                    }
                }
            }
        }
    } // end event loop
    fout.Write(); // write changes to the output file
} // end main



