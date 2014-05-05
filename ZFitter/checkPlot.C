checkPlot(){
  gROOT->ProcessLine(".L DataMC.C++");

  //DataMC("variable",2,"ECAL_region","xlabel","ylabel","zlabel",yvalue for profile,rebin,nxbins,nybins);
  DataMC("InvMass",1,"endcap","m_{ee} [GeV]","Events","",50,0,2,2);
  DataMC("InvMass",1,"barrel","m_{ee} [GeV]","Events","",50,0,2,2);

  DataMC("EneSCEleLead",1,"endcap","E_{SC Lead} [GeV]","Events","",50,0,10,10);
  DataMC("EneSCEleLead",1,"barrel","E_{SC Lead} [GeV]","Events","",50,0,2,2);

  DataMC("EneSCEleSubLead",1,"endcap","E_{SC SubLead} [GeV]","Events","",50,0,10,10);
  DataMC("EneSCEleSubLead",1,"barrel","E_{SC SubLead} [GeV]","Events","",50,0,2,2);

  DataMC("MomentumLead",1,"endcap","p_{SC Lead} [GeV]","Events","",50,0,10,10);
  DataMC("MomentumLead",1,"barrel","p_{SC Lead} [GeV]","Events","",50,0,2,2);

  DataMC("MomentumSubLead",1,"endcap","p_{SC SubLead} [GeV]","Events","",50,0,10,10);
  DataMC("MomentumSubLead",1,"barrel","p_{SC SubLead} [GeV]","Events","",50,0,2,2);

  DataMC("EoverPLead",1,"endcap","(E/p)_{SC Lead}","Events","",50,0,10,10);
  DataMC("EoverPLead",1,"barrel","(E/p)_{SC Lead}","Events","",50,0,2,2);

  DataMC("EoverPSubLead",1,"endcap","(E/p)_{SC SubLead}","Events","",50,0,10,10);
  DataMC("EoverPSubLead",1,"barrel","(E/p)_{SC SubLead}","Events","",50,0,2,2);

  ////2D
  DataMC("MapEELead",2,"endcap","iX","iY","Events",50,0,10,10);
  DataMC("MapEBLead",2,"barrel","i#phi","i#eta","Events",50,0,2,2);
  DataMC("EneEleLeadvsEtaEleLead",2,"endcap","#eta_{SC Lead}","E_{SC Lead}","Events",50,0,10,10);
  DataMC("EneEleLeadvsEtaEleLead",2,"barrel","#eta_{SC Lead}","E_{SC Lead}","Events",50,0,10,10);
  DataMC("MapEEPLead",2,"endcap","iX","iY","p [GeV]",50,0,10,10);
  DataMC("MapEBPLead",2,"barrel","i#phi","i#eta","p [GeV]",50,0,2,2);




  gROOT->ProcessLine(".q");
  
}


