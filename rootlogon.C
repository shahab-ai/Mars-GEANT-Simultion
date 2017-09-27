{cout<<"to >> rootlogon.C"<<endl;
gROOT->GetApplication()->ProcessLine("#include <iomanip>");
gStyle->SetCanvasPreferGL(kTRUE);
gStyle->SetPalette(1);
gStyle->SetLabelOffset(0.01,"X");
gStyle->SetLabelOffset(0.01,"Y");
gStyle->SetLabelSize(0.045,"X");
gStyle->SetLabelSize(0.045,"Y");
gStyle->SetLabelSize(0.04,"Z");
gStyle->SetTitleSize(0.05,"X");
gStyle->SetTitleSize(0.05,"Z");
gStyle->SetTitleSize(0.05,"Y");
gStyle->SetMarkerStyle(20);
gStyle->SetMarkerColor(1);
gStyle->SetMarkerSize(0.5);
gStyle->SetOptStat(1111111);
gStyle->SetOptFit(1111);
gStyle->SetStatY(0.99);
gStyle->SetStatX(0.99);
gStyle->SetStatW(0.25);
gStyle->SetStatH(0.10);
gStyle->SetLineWidth(1);
gStyle->SetLineColor(1);     // errbars
gStyle->SetHistLineWidth(2);
gStyle->SetHistLineColor(1); // frames
gStyle->SetHistFillColor(0); // ?
gStyle->SetFillStyle(0);
gStyle->SetFillColor(1);    // ?
gStyle->SetFuncWidth(2);   // fitline
gStyle->SetFuncColor(2);   // fitline
gStyle->SetFuncStyle(7);   // fitline
gStyle->SetTitleXOffset(1);
gStyle->SetTitleYOffset(1.39);
gStyle->SetTitleColor(1);
gStyle->SetTitleFillColor(0);
gStyle->SetStatColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetCanvasDefX(0);
gStyle->SetCanvasDefY(0);
gStyle->SetCanvasDefW(600);
gStyle->SetCanvasDefH(500);
gStyle->SetPadLeftMargin(0.14);
gStyle->SetPadRightMargin(0.05);
gStyle->SetPadTopMargin(0.06);
gStyle->SetPadBottomMargin(0.11);
gStyle->SetCanvasBorderMode(0);
gStyle->SetCanvasBorderSize(0);
gStyle->SetTitleBorderSize(1);
gStyle->SetTitleX(0.43);
gStyle->SetTitleW(0.35);
gStyle->SetTitleH(0.05);
gStyle->SetNdivisions(510,"Y");
gStyle->SetNdivisions(510,"X");
gStyle->SetDrawBorder(0);
gStyle->SetPadBorderSize(0);
gStyle->SetPadGridX(1);
gStyle->SetPadGridY(1);
gStyle->SetOptLogx(0);
gStyle->SetOptLogy(0);
gROOT->ForceStyle();
cout<<"rootlogon.C >> end"<<endl;
}
// vim: set ai sw=4 ts=4:
