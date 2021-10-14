
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
#include "tcnt.hh" // tcnt prints the incremented counter value every second

using std::cout;
using std::cerr;
using std::endl;
using ivanp::tcnt;

int main(int argc, char* argv[]) {
    if (argc != 3) { // require two command line arguments
      cout << "usage: " << argv[0] << " data.root histograms.root\n";
        return 1;
    }

  // open ROOT file for writing
  // this is the file that will contain our histograms
    TFile fout(argv[2],"recreate");
    if (fout.IsZombie()) {
        cerr << "\033[31m" "cannot open output ROOT file" "\033[0m\n";
        return 1;
    }

  // create histograms with the desired binning
  // TH1D constructor arguments: name, title, nbins, xmin, xmax
    
    
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
    TH1D* pho_ratio_350 = new TH1D("pho_rato_350","pho1/pho2 ratio 300-350", 38,1,20);
    TH1D* pho_ratio_450 = new TH1D("pho_rato_450","pho1/pho2 ratio 350-450", 38,1,20);
    TH1D* pho_ratio_550 = new TH1D("pho_rato_550","pho1/pho2 ratio 450-550", 38,1,20);
    TH1D* pho_ratio_650 = new TH1D("pho_rato_650","pho1/pho2 ratio 550-650", 38,1,20);

  // open input ROOT file for reading
    cout << "reading input ROOT file \"" << argv[1] <<'\"'<< endl;
    TFile fin(argv[1]);
    if (fin.IsZombie()) {
        cerr << "\033[31m" "cannot open input ROOT file" "\033[0m\n";
        return 1;
    }

  // get the tree called "HGamData" and make sure it exists
    TTree* tree = fin.Get<TTree>("CollectionTree");
    if (!tree) {
        cerr << "\033[31m" "cannot get TTree \"CollectionTree\"" "\033[0m\n";
        return 1;
    }
    cout << '\n';

  // setup readers for the branches of the input TTree
    TTreeReader reader(tree);

    TTreeReaderValue<Float_t>
        b_m_yy           (reader,   "m_yy"  ),
        b_pT_yy          (reader,   "pT_yy" ),
        b_pT_y1          (reader,   "pT_y1" ),
        b_pT_y2          (reader,   "pT_y2" ),
        b_eta_y1         (reader,   "eta_y1"),
        b_eta_y2         (reader,   "eta_y2");
	
  // loop over all events in the data tree
    for (tcnt cnt(reader.GetEntries()); reader.Next(); ++cnt) {
        
        auto pho_ratio = *b_pT_y1/(*b_pT_y2);
    
        if ((*b_m_yy>(129*1000) && *b_m_yy<(160*1000)) || (*b_m_yy>(110*1000) && *b_m_yy<(121*1000))) {
            if (*b_pT_y1>(43.75*1000)) {
                if (*b_pT_y2>(31.25*1000)) {
                    if (fabs(*b_eta_y1)<(2.4*1000) && fabs(*b_eta_y2)<(2.4*1000)) {
                        if (*b_pT_yy<(5*1000)){
                            pho_ratio_5->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(5*1000) && *b_pT_yy<(10*1000)) {
                            pho_ratio_10->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(10*1000) && *b_pT_yy<(15*1000)) {
                            pho_ratio_15->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(15*1000) && *b_pT_yy<(20*1000)) {
                            pho_ratio_20->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(20*1000) && *b_pT_yy<(25*1000)) {
                            pho_ratio_25->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(25*1000) && *b_pT_yy<(30*1000)) {
                            pho_ratio_30->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(30*1000) && *b_pT_yy<(35*1000)) {
                            pho_ratio_35->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(35*1000) && *b_pT_yy<(45*1000)) {
                            pho_ratio_45->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(45*1000) && *b_pT_yy<(60*1000)) {
                            pho_ratio_60->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(60*1000) && *b_pT_yy<(80*1000)) {
                            pho_ratio_80->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(80*1000) && *b_pT_yy<(100*1000)) {
                            pho_ratio_100->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(100*1000) && *b_pT_yy<(120*1000)) {
                            pho_ratio_120->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(120*1000) && *b_pT_yy<(140*1000)) {
                            pho_ratio_140->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(140*1000) && *b_pT_yy<(170*1000)) {
                            pho_ratio_170->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(170*1000) && *b_pT_yy<(200*1000)) {
                            pho_ratio_200->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(200*1000) && *b_pT_yy<(250*1000)) {
                            pho_ratio_250->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(250*1000) && *b_pT_yy<(300*1000)) {
                            pho_ratio_300->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(300*1000) && *b_pT_yy<(350*1000)) {
                            pho_ratio_350->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(350*1000) && *b_pT_yy<(450*1000)) {
                            pho_ratio_450->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(450*1000) && *b_pT_yy<(550*1000)) {
                            pho_ratio_550->Fill(pho_ratio );
                        }
                        if (*b_pT_yy>(550*1000) && *b_pT_yy<(650*1000)) {
                            pho_ratio_650->Fill(pho_ratio );
                        }
                    }
                }
            }
        }
    
    } // end event loop
    
    
    fout.Write(); // write changes to the output file

  // NOTE:
  // Even though the histograms were dynamically allocated
  // using the `new` operator, they don't need to be explicitly deleted.
  // The distructor of the TFile they belong to will deallocate them.

} // end main



