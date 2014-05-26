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

void DataMC(string dir,string histo_name, int logy_y,int option_dim,string ECAL_region, string xaxis, string yaxis, string zaxis, double y, int rebin,int nxbins,int nybins, int limit_axis=0,double xmin=0, double xmax=0, int limit_yaxis=0,double ymin=0,double ymax=0){

  gStyle->SetOptStat(0);
  string Datafile="tmp/"+dir+"/histograms_data_"+ECAL_region+".root";
  string Powhegfile="tmp/"+dir+"/histograms_Powheg_"+ECAL_region+".root";
  string MadGraphfile="tmp/"+dir+"/histograms_MadGraph_"+ECAL_region+".root";
  string Sherpafile="tmp/"+dir+"/histograms_Sherpa_"+ECAL_region+".root";

  TFile *_file0 = TFile::Open(Datafile.c_str());
  TFile *_file1 = TFile::Open(Powhegfile.c_str());
  TFile *_file2 = TFile::Open(MadGraphfile.c_str());
  TFile *_file3 = TFile::Open(Sherpafile.c_str());

  if(option_dim==2){
  TH2D *data = (TH2D*)_file0->Get(histo_name.c_str());
  TH2D *powheg = (TH2D*)_file1->Get(histo_name.c_str());
  TH2D *madgraph = (TH2D*)_file1->Get(histo_name.c_str());
  TH2D *sherpa = (TH2D*)_file1->Get(histo_name.c_str());

  if(histo_name=="MapEBP"){
  TH2D *MapEB_data = (TH2D*)_file0->Get("MapEB");
  TH2D *MapEB_powheg = (TH2D*)_file1->Get("MapEB");
    data->Divide(MapEB_data);
    powheg->Divide(MapEB_powheg);
  }else if(histo_name=="MapEEP"){
  TH2D *MapEE_data = (TH2D*)_file0->Get("MapEE");
  TH2D *MapEE_powheg = (TH2D*)_file1->Get("MapEE");
    data->Divide(MapEE_data);
    powheg->Divide(MapEE_powheg);
  }


    if(rebin==1){
      data->Rebin2D(nxbins,nybins);
      powheg->Rebin2D(nxbins,nybins);
    }
    if(limit_axis==1){      
      data->GetXaxis()->SetRange(data->GetXaxis()->FindBin(xmin),data->GetXaxis()->FindBin(xmax));
      powheg->GetXaxis()->SetRange(powheg->GetXaxis()->FindBin(xmin),powheg->GetXaxis()->FindBin(xmax));
    }
    if(limit_yaxis==1){      
      data->GetYaxis()->SetRange(data->GetYaxis()->FindBin(ymin),data->GetYaxis()->FindBin(ymax));
      powheg->GetYaxis()->SetRange(powheg->GetYaxis()->FindBin(ymin),powheg->GetYaxis()->FindBin(ymax));
    }

    powheg->Scale(data->Integral()/powheg->Integral());

    TCanvas *c1=new TCanvas();
  c1->SetRightMargin(0.2);
  c1->SetBottomMargin(0.12);
  c1->SetLeftMargin(0.12);
  TH2D *data_copy = (TH2D*)data->Clone("data_copy");
  TH2D *data_copy_2 = (TH2D*)data->Clone("data_copy_2");
  TH2D *data_copy_3 = (TH2D*)data->Clone("data_copy_3");

  data->GetXaxis()->SetTitle(xaxis.c_str());
  data->GetXaxis()->SetTitleSize(0.06);
  data->GetYaxis()->SetTitle(yaxis.c_str());
  data->GetYaxis()->SetTitleSize(0.06);
  data->GetZaxis()->SetTitle(zaxis.c_str());
  data->GetZaxis()->SetTitleSize(0.06);
  data->Draw("colz");
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_data"+ECAL_region+".png").c_str());
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_data"+ECAL_region+".pdf").c_str());
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_data"+ECAL_region+".eps").c_str());
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_data"+ECAL_region+".C").c_str());

  TCanvas *c2=new TCanvas();
  c2->SetRightMargin(0.2);
  c2->SetBottomMargin(0.12);
  c2->SetLeftMargin(0.12);
  powheg->GetXaxis()->SetTitle(xaxis.c_str());
  powheg->GetXaxis()->SetTitleSize(0.06);
  powheg->GetYaxis()->SetTitle(yaxis.c_str());
  powheg->GetYaxis()->SetTitleSize(0.06);
  powheg->GetZaxis()->SetTitle(zaxis.c_str());
  powheg->GetZaxis()->SetTitleSize(0.06);
  powheg->Draw("colz");
  c2->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_mc"+ECAL_region+".png").c_str());
  c2->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_mc"+ECAL_region+".pdf").c_str());
  c2->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_mc"+ECAL_region+".eps").c_str());
  c2->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_mc"+ECAL_region+".C").c_str());

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
  data_copy->Divide(powheg);
  data_copy->Draw("colz");
  c3->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio"+ECAL_region+".png").c_str());
  c3->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio"+ECAL_region+".pdf").c_str());
  c3->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio"+ECAL_region+".eps").c_str());
  c3->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio"+ECAL_region+".C").c_str());

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
  c4->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".png").c_str());
  c4->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".pdf").c_str());
  c4->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".eps").c_str());
  c4->SaveAs(("check_Plots_DataMC/"+dir+"/"+"2D/"+histo_name+"_ratio_y"+ystr+ECAL_region+".C").c_str());
  } //End 2D histos

  if(option_dim==1){//1D histo
  TH1D *data = (TH1D*)_file0->Get(histo_name.c_str());
  TH1D *powheg = (TH1D*)_file1->Get(histo_name.c_str());
  TH1D *madgraph = (TH1D*)_file2->Get(histo_name.c_str());
  TH1D *sherpa = (TH1D*)_file3->Get(histo_name.c_str());

    if(rebin==1){
      data->Rebin(nxbins);
      powheg->Rebin(nxbins);
      madgraph->Rebin(nxbins);
      sherpa->Rebin(nxbins);
    }
    powheg->Scale(data->Integral()/powheg->Integral());
    madgraph->Scale(data->Integral()/madgraph->Integral());
    sherpa->Scale(data->Integral()/sherpa->Integral());

    if(limit_axis==1){
      data->GetXaxis()->SetRange(data->GetXaxis()->FindBin(xmin),data->GetXaxis()->FindBin(xmax));
      powheg->GetXaxis()->SetRange(powheg->GetXaxis()->FindBin(xmin),powheg->GetXaxis()->FindBin(xmax));
      madgraph->GetXaxis()->SetRange(madgraph->GetXaxis()->FindBin(xmin),madgraph->GetXaxis()->FindBin(xmax));
      sherpa->GetXaxis()->SetRange(sherpa->GetXaxis()->FindBin(xmin),sherpa->GetXaxis()->FindBin(xmax));
    }
  data->SetLineColor(kBlack);
  powheg->SetLineColor(kRed);
  madgraph->SetLineColor(kBlue);
  sherpa->SetLineColor(kGreen);

  powheg->SetLineWidth(2.5);
  madgraph->SetLineWidth(2.5);
  sherpa->SetLineWidth(2.5);



  TCanvas *c1=new TCanvas();
  c1->Divide(1,2);
  //gStyle->SetOptTitle(0);//The title is not shown
  gStyle->SetOptStat(0);//Statistics not shown
  c1->cd(1)->SetPad(.005,.305,.995,.995);//xlow,ylow, xup,yup
  if(logy_y==1){
    data->SetMinimum(0.001);//I want to set Log Scale
    c1->cd(1)->SetLogy();
  }
  TH1D *data_copy = (TH1D*)data->Clone("data_copy");
  TH1D *data_copy_2 = (TH1D*)data->Clone("data_copy_2");
  TH1D *data_copy_3 = (TH1D*)data->Clone("data_copy_3");
  data->GetYaxis()->SetTitle(yaxis.c_str());
  data->GetYaxis()->SetTitleSize(0.06);

  vector<double> max;
  double MAX;
  max.push_back(data->GetMaximum());
  max.push_back(powheg->GetMaximum());
  max.push_back(madgraph->GetMaximum());
  max.push_back(sherpa->GetMaximum());

  MAX = *max_element(max.begin(), max.end());
  powheg->SetMaximum(MAX+0.2*MAX);
  powheg->SetFillColor(kRed);
  powheg->SetFillStyle(3001);

  madgraph->SetFillColor(kBlue);
  madgraph->SetFillStyle(3017);

  sherpa->SetFillColor(kGreen);
  sherpa->SetFillStyle(3018);
  powheg->Draw("hist");
  madgraph->Draw("histsame");
  sherpa->Draw("histsame");

  data->SetMarkerStyle(20);
  data->Draw("epsame");  
  TLegend *leg;
  leg= new TLegend(0.6,0.7,0.9,0.9);//x1,y1,x2,y2
  leg->SetFillStyle(0);//the legend is trasparent
  leg->SetBorderSize(0);//The legend is without contour
  leg->AddEntry(data,"Data");
  leg->AddEntry(powheg,"Powheg");
  leg->AddEntry(madgraph,"MadGraph");
  leg->AddEntry(sherpa,"Sherpa");
  leg->Draw("same");

  //Plotting Ratio
  c1->cd(2)->SetPad(.005,.025,.995,.305);
  c1->cd(2)->SetGridy(1);
  gStyle->SetOptTitle(0);//The title is not shown
  //gPad->SetBottomMargin(0.25);                 
  gPad->SetBottomMargin(0.35);
  data_copy->Divide(powheg);
  data_copy->SetLineColor(kRed);
  data_copy->SetMarkerColor(kRed);
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
  data_copy_2->Divide(madgraph);
  data_copy_2->SetLineColor(kBlue);
  data_copy_2->SetMarkerColor(kBlue);
  data_copy_2->Draw("same");
  data_copy_3->Divide(sherpa);
  data_copy_3->SetLineColor(kGreen);
  data_copy_3->SetMarkerColor(kGreen);
  data_copy_3->Draw("same");


  //Draw line at 1
  if(limit_axis==0){
    TLine *line = new TLine(data_copy->GetXaxis()->GetXmin(),1,data_copy->GetXaxis()->GetXmax(),1);
    line->Draw("same");
  }else{
    TLine *line = new TLine(xmin,1,xmax,1);
    line->Draw("same");
  }


  string log="";
  if(logy_y==1){
  log="_logy";
  }
  if(histo_name=="InvMass"){
    histo_name=Form("InvMass_%.0lf",xmin);//no decimal point
  }
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"1D/"+histo_name+ECAL_region+log+".png").c_str());
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"1D/"+histo_name+ECAL_region+log+".pdf").c_str());
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"1D/"+histo_name+ECAL_region+log+".eps").c_str());
  c1->SaveAs(("check_Plots_DataMC/"+dir+"/"+"1D/"+histo_name+ECAL_region+log+".C").c_str());

  }

}
