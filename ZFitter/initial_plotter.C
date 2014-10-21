{
  TFile *_file0 = TFile::Open("tmp/d_chain.root");
  TFile *_file0 = TFile::Open("tmp/s1_chain.root");
  TFile *_file1 = TFile::Open("tmp/s1_chain.root");
  TFile *_file2 = TFile::Open("tmp/s1_chain.root");
    gROOT->ProcessLine(".x tmp/load.C");
  gROOT->ProcessLine(".L macro/PlotDataMC.C+");
  data->Draw("energySCEle_regrCorrSemiParV5_ele[0]/cosh(etaEle[0])>>barrel_12",GetCut("EB-Et_25-trigger-noPF-gainEle_12",1));
  data->Draw("energySCEle_regrCorrSemiParV5_ele[0]/cosh(etaEle[0])>>barrel_6",GetCut("EB-Et_25-trigger-noPF-gainEle_6",1));
  data->Draw("energySCEle_regrCorrSemiParV5_ele[0]/cosh(etaEle[0])>>barrel_1",GetCut("EB-Et_25-trigger-noPF-gainEle_1",1));

  TCanvas=new TCanvas("myCanvas","myCanvas");
  barrel_12->SetLineWidth(2);
  barrel_6->SetLineWidth(2);
  barrel_1->SetLineWidth(2);
  barrel_12->Draw("");
  barrel_6->SetLineColor(kCyan);
  barrel_6->Draw("same");
  barrel_1->SetLineColor(kMagenta);
  barrel_1->Draw("same");
  myCanvas->SetLogy();
  barrel_12->GetXaxis()->SetTitle("p_{T} [GeV]");
  barrel_12->GetYaxis()->SetTitle("Events");
  TLegend* leg=new TLegend(0.5,0.5,0.9,0.9);
  leg->AddEntry(barrel_12,"Events with G12; EB");
  leg->AddEntry(barrel_6,"Events with G6; EB");
  leg->AddEntry(barrel_1,"Events with G1; EB");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw("same");
  myCanvas->SaveAs("initial_plots/Pt_distribution_barrel.png");
    gROOT->ProcessLine(".q");
}
