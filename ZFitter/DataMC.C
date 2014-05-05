#include "TFile.h"
#include "TLatex.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"
#include "TStyle.h"
#include "TPad.h"
#include "TBenchmark.h"
#include "TGraph.h"
#include "TMath.h"
#include "Math/DistFunc.h"
#include "Math/GoFTest.h"
#include "Math/Functor.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Rtypes.h"
#include "Fit/Fitter.h"
#include "TObject.h"
#include "TLegend.h"
#include "THStack.h"
#include <vector>
#include "TLine.h"
#include "TFile.h"
#include "TProfile.h"
using namespace std;

void DataMC(string histo_name,int option_dim,string ECAL_region, string xaxis, string yaxis, string zaxis, double y, int rebin,int nxbins,int nybins){

  gStyle->SetOptStat(0);
  string Datafile="tmp/histograms_data_"+ECAL_region+".root";
  string MCfile="tmp/histograms_mc_"+ECAL_region+".root";

  TFile *_file0 = TFile::Open(Datafile.c_str());
  TFile *_file1 = TFile::Open(MCfile.c_str());

  if(option_dim==2){
  TH2D *data = (TH2D*)_file0->Get(histo_name.c_str());
  TH2D *mc = (TH2D*)_file1->Get(histo_name.c_str());
    if(rebin==1){
      data->Rebin2D(nxbins,nybins);
    }

  TCanvas *c1=new TCanvas();
  c1->SetRightMargin(0.2);
  c1->SetBottomMargin(0.12);
  c1->SetLeftMargin(0.12);
  TH2D *data_copy = (TH2D*)data->Clone("data_copy");
  data->GetXaxis()->SetTitle(xaxis.c_str());
  data->GetXaxis()->SetTitleSize(0.06);
  data->GetYaxis()->SetTitle(yaxis.c_str());
  data->GetYaxis()->SetTitleSize(0.06);
  data->GetZaxis()->SetTitle(zaxis.c_str());
  data->GetZaxis()->SetTitleSize(0.06);
  data->Draw("colz");
  c1->SaveAs(("check_Plots/2D/"+histo_name+"_data"+ECAL_region+".png").c_str());
  c1->SaveAs(("check_Plots/2D/"+histo_name+"_data"+ECAL_region+".pdf").c_str());
  c1->SaveAs(("check_Plots/2D/"+histo_name+"_data"+ECAL_region+".eps").c_str());
  c1->SaveAs(("check_Plots/2D/"+histo_name+"_data"+ECAL_region+".C").c_str());

  TCanvas *c2=new TCanvas();
  c2->SetRightMargin(0.2);
  c2->SetBottomMargin(0.12);
  c2->SetLeftMargin(0.12);
  mc->GetXaxis()->SetTitle(xaxis.c_str());
  mc->GetXaxis()->SetTitleSize(0.06);
  mc->GetYaxis()->SetTitle(yaxis.c_str());
  mc->GetYaxis()->SetTitleSize(0.06);
  mc->GetZaxis()->SetTitle(zaxis.c_str());
  mc->GetZaxis()->SetTitleSize(0.06);
  mc->Draw("colz");
  c2->SaveAs(("check_Plots/2D/"+histo_name+"_mc"+ECAL_region+".png").c_str());
  c2->SaveAs(("check_Plots/2D/"+histo_name+"_mc"+ECAL_region+".pdf").c_str());
  c2->SaveAs(("check_Plots/2D/"+histo_name+"_mc"+ECAL_region+".eps").c_str());
  c2->SaveAs(("check_Plots/2D/"+histo_name+"_mc"+ECAL_region+".C").c_str());

  TCanvas *c3=new TCanvas();
  c3->SetRightMargin(0.2);
  c3->SetBottomMargin(0.12);
  c3->SetLeftMargin(0.12);
  data_copy->GetXaxis()->SetTitle(xaxis.c_str());
  data_copy->GetXaxis()->SetTitleSize(0.06);
  data_copy->GetYaxis()->SetTitle(yaxis.c_str());
  data_copy->GetYaxis()->SetTitleSize(0.06);
  data_copy->GetZaxis()->SetTitle("Ratio Data/MC");
  data_copy->GetZaxis()->SetTitleSize(0.06);
  data_copy->Divide(mc);
  data_copy->Draw("colz");
  c3->SaveAs(("check_Plots/2D/"+histo_name+"_ratio"+ECAL_region+".png").c_str());
  c3->SaveAs(("check_Plots/2D/"+histo_name+"_ratio"+ECAL_region+".pdf").c_str());
  c3->SaveAs(("check_Plots/2D/"+histo_name+"_ratio"+ECAL_region+".eps").c_str());
  c3->SaveAs(("check_Plots/2D/"+histo_name+"_ratio"+ECAL_region+".C").c_str());

  //Profile
  //makes the average along y -> Useless
  //TCanvas *c4=new TCanvas();
  //TProfile *prof = data_copy->ProfileX();
  //c4->SetRightMargin(0.2);
  //c4->SetBottomMargin(0.12);
  //c4->SetLeftMargin(0.12);
  //prof->GetXaxis()->SetTitle(xaxis.c_str());
  //prof->GetXaxis()->SetTitleSize(0.06);
  //prof->GetYaxis()->SetTitle(yaxis.c_str());
  //prof->GetYaxis()->SetTitleSize(0.06);
  //prof->GetZaxis()->SetTitle("Ratio Data/MC");
  //prof->GetZaxis()->SetTitleSize(0.06);
  //prof->Draw();

  //data->ProjectionX(" ",firstybin,lastybin,"[cutg]");
  TCanvas *c4=new TCanvas();
  c4->SetRightMargin(0.2);
  c4->SetBottomMargin(0.12);
  c4->SetLeftMargin(0.12);

  int ybin;
  ybin=data_copy->GetYaxis()->FindBin(y);

  std::ostringstream os;
  os << y;
  string ystr = os.str();
  TH1D* projection= data_copy->ProjectionX("projection",ybin,ybin);//Scan along x axis looking at the 5th y 
  projection->GetXaxis()->SetTitle(xaxis.c_str());
  projection->GetXaxis()->SetTitleSize(0.06);
  projection->GetYaxis()->SetTitle(("Ratio Data/MC @ "+yaxis+"= "+ystr).c_str());
  projection->GetYaxis()->SetTitleSize(0.06);
  projection->Draw("ep");
  c4->SaveAs(("check_Plots/2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".png").c_str());
  c4->SaveAs(("check_Plots/2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".pdf").c_str());
  c4->SaveAs(("check_Plots/2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".eps").c_str());
  c4->SaveAs(("check_Plots/2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".C").c_str());
  } //End 2D histos

  if(option_dim==1){//1D histo
  TH1D *data = (TH1D*)_file0->Get(histo_name.c_str());
  TH1D *mc = (TH1D*)_file1->Get(histo_name.c_str());
    if(rebin==1){
      data->Rebin(nxbins);
    }
  data->SetLineColor(kBlack);
  mc->SetLineColor(kRed);

  TCanvas *c1=new TCanvas();
  c1->Divide(1,2);
  //gStyle->SetOptTitle(0);//The title is not shown
  gStyle->SetOptStat(0);//Statistics not shown
  c1->cd(1)->SetPad(.005,.305,.995,.995);//xlow,ylow, xup,yup
  TH1D *data_copy = (TH1D*)data->Clone("data_copy");
  data->GetYaxis()->SetTitle(yaxis.c_str());
  data->GetYaxis()->SetTitleSize(0.06);

  vector<double> max;
  double MAX;
  max.push_back(data->GetMaximum());
  max.push_back(mc->GetMaximum());
  MAX = *max_element(max.begin(), max.end());
  mc->SetMaximum(MAX+0.2*MAX);
  mc->SetFillColor(kRed);
  mc->SetFillStyle(3001);
  mc->Draw("hist");
  data->SetMarkerStyle(20);
  data->Draw("epsame");  
  TLegend *leg;
  leg= new TLegend(0.6,0.7,0.9,0.9);//x1,y1,x2,y2
  leg->SetFillStyle(0);//the legend is trasparent
  leg->SetBorderSize(0);//The legend is without contour
  leg->AddEntry(data,"Data");
  leg->AddEntry(mc,"Powheg");
  leg->Draw("same");

  //Plotting Ratio
  c1->cd(2)->SetPad(.005,.025,.995,.305);
  c1->cd(2)->SetGridy(1);
  gStyle->SetOptTitle(0);//The title is not shown
  //gPad->SetBottomMargin(0.25);                 
  gPad->SetBottomMargin(0.35);
  data_copy->Divide(mc);
  data_copy->SetMarkerStyle(20);
  data_copy->SetMarkerSize(0.6);
  data_copy->GetYaxis()->SetRangeUser(0.5,2);
  data_copy->GetYaxis()->SetTitle("Ratio Data/MC");
  data_copy->GetYaxis()->SetTitleOffset(0.35);//set distance between axis and axis title          
  data_copy->GetYaxis()->SetLabelSize(0.1);//Label e' la dimensione dei numeretti sugli assi      
  data_copy->GetYaxis()->SetTitleSize(0.11);//Questa invece e' la dimensione del titolo dell'asse 
  data_copy->GetXaxis()->SetLabelSize(0.1); //aumento pure la dimensione dei numeretti sull'asse x
  data_copy->GetXaxis()->SetTitleSize(0.15);//Questa invece e' la dimensione del titolo dell'asse 
  data_copy->GetXaxis()->SetTitle(xaxis.c_str());
  data_copy->Draw();

  //Draw line at 1
  TLine *line = new TLine(data_copy->GetXaxis()->GetXmin(),1,data_copy->GetXaxis()->GetXmax(),1);
  line->Draw("same");

  c1->SaveAs(("check_Plots/1D/"+histo_name+ECAL_region+".png").c_str());
  c1->SaveAs(("check_Plots/1D/"+histo_name+ECAL_region+".pdf").c_str());
  c1->SaveAs(("check_Plots/1D/"+histo_name+ECAL_region+".eps").c_str());
  c1->SaveAs(("check_Plots/1D/"+histo_name+ECAL_region+".C").c_str());

  }

}
