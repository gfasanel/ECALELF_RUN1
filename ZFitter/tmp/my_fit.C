fitter(){

  TFile *_file0 = TFile::Open("tmp/g_sumGraph-scale_EB-Et_25-trigger-noPF.root");
  
  //First I fit with a standard pol2, 
  //then I use the fitted parameter as initialization parameters of the second fit (asym Parabola)

  TF1* f=new TF1("f","pol2",0.98,1.02);
  Graph->Fit(f,"OFR+","",0.98,1.02);

  TF1* f2=new TF1("f2",asymmetricParabola,0.98,1.02,4);
  f2->SetParameter(0,0);
  double minX=f->GetMinimumX();
  f2->SetParameter(1,minX);
  double sigma=1./sqrt(2* f->GetParameter(2)); 
  f2->SetParameter(2,1/(2*sigma*sigma));                                                                                                                
  f2->SetParameter(3,1/(2*sigma*sigma));

  Graph->Fit(f2,"OFR+","",0.98,1.02);
  Graph->Draw("AP*");
  f2->Draw("same");
  cout<<"minimum "<<f2->GetMinimumX()<<endl; 
  cout<<"chi2/ndof "<<f2->GetChisquare()/f2->GetNDF();
}

Double_t asymmetricParabola(Double_t* x,Double_t* par)
{
  // qualche commento non farebbe male                                                                                                                  
    Double_t value=0.;
    if (x[0]<=par[1])
      value=par[2]*(x[0]-par[1])*(x[0]-par[1]);
    else
      value=par[3]*(x[0]-par[1])*(x[0]-par[1]);
    return value+par[0];
}
