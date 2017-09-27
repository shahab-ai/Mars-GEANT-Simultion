#include <TFile.h>
#include <TNtuple.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TFrame.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TRandom3.h>
#include <TBenchmark.h>
#include <TInterpreter.h>

void plotHisto(Int_t getFile=0)
{
  gROOT->Reset();

  // Draw histos filled by Geant4 simulation
  //
  TFile *f = TFile::Open("Hadr06_build/runx.root");
  TCanvas* c1 = new TCanvas("c1", "  ");

  c1->cd();
  c1->Update();

  const char separator = ',';

  //TH1D* energy = (TH1D*)f->Get("12");
  //TH1D* theta = (TH1D*)f->Get("14");
  //TH1D* time = (TH1D*)f->Get("6");
  //hist6->Draw("HIST");


  TH1D* hist12 = (TH1D*)f->Get("12");
  hist12->Draw("HIST");
/*
  ofstream file_out("hist11.dat");
  file_out << "# Output " << hist11->ClassName() << ": " << hist11->GetName() << " (" << hist11->GetTitle() << ")\n";
  file_out << "# BinCenter" << separator << "Content" << separator << "BinHalfWidth" << separator << "Error\n";
  for (int i=1; i<=hist11->GetNbinsX(); i++)
    file_out << hist11->GetBinCenter(i) << separator << hist11->GetBinContent(i) << separator << hist11->GetBinWidth(i)/2 << separator << hist11->GetBinError(i) << endl;
  file_out.close();
*/

/*
  TH1D* hist12 = (TH1D*)f->Get("12");
  hist12->Draw("HIST");

  ofstream file_out("hist12.dat");
  file_out << "# Output " << hist12->ClassName() << ": " << hist12->GetName() << " (" << hist12->GetTitle() << ")\n";
  file_out << "# BinCenter" << separator << "Content" << separator << "BinHalfWidth" << separator << "Error\n";
  for (int i=1; i<=hist12->GetNbinsX(); i++)
    file_out << hist12->GetBinCenter(i) << separator << hist12->GetBinContent(i) << separator << hist12->GetBinWidth(i)/2 << separator << hist12->GetBinError(i) << endl;
  file_out.close();
*/

/*
  TH1D* hist13 = (TH1D*)f->Get("13");
  hist13->Draw("HIST");

  ofstream file_out("hist13.dat");
  file_out << "# Output " << hist13->ClassName() << ": " << hist13->GetName() << " (" << hist13->GetTitle() << ")\n";
  file_out << "# BinCenter" << separator << "Content" << separator << "BinHalfWidth" << separator << "Error\n";
  for (int i=1; i<=hist13->GetNbinsX(); i++)
    file_out << hist13->GetBinCenter(i) << separator << hist13->GetBinContent(i) << separator << hist13->GetBinWidth(i)/2 << separator << hist13->GetBinError(i) << endl;
  file_out.close();
*/

/*
  TH1D* hist12 = (TH1D*)f->Get("12");
  hist12->Draw("HIST");

  ofstream file_out("hist12.dat");
  file_out << "# Output " << hist12->ClassName() << ": " << hist12->GetName() << " (" << hist12->GetTitle() << ")\n";
  file_out << "# BinCenter" << separator << "Content" << separator << "BinHalfWidth" << separator << "Error\n";
  for (int i=1; i<=hist12->GetNbinsX(); i++)
    file_out << hist12->GetBinCenter(i) << separator << hist12->GetBinContent(i) << separator << hist12->GetBinWidth(i)/2 << separator << hist12->GetBinError(i) << endl;
  file_out.close();
*/

  TH2D* hist3 = (TH2D*)f->Get("3");
  hist3->DrawClone("lego2");

  //TH2D* hist2 = (TH2D*)f->Get("2");
  //hist2->DrawClone("lego2");

  //TH1D* hist11 = (TH1D*)f->Get("11");
  //hist11->Draw("HIST");


}
