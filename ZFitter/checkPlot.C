checkPlot(){
  gROOT->ProcessLine(".L DataMC.C++");
  //invMass_var="invMass_SC";
  invMass_var="invMass_SC_regrCorrSemiParV5_ele";
  string Ecal_region_description="";//just barrel and endcap
  //Ecal_region_description="_goodR9";
  //Ecal_region_description="_badR9";
  
  //DataMC(invMass_var,"variable",logscale y,2 boh,"Ecal_region","xlabel","ylabel","zlabel",yvalue for profile,rebin,nxbins,nybins,limit_axis,xmin.xmax,ymin,ymax);
  DataMC(invMass_var,"InvMass",0,1,"endcap"+Ecal_region_description,"m_{ee} [GeV]","Events","",50,0,2,2,1,60,120);
  DataMC(invMass_var,"InvMass",0,1,"barrel"+Ecal_region_description,"m_{ee} [GeV]","Events","",50,0,2,2,1,60,120);
  DataMC(invMass_var,"InvMass",0,1,"endcap"+Ecal_region_description,"m_{ee} [GeV]","Events","",50,0,2,2,1,80,100);
  DataMC(invMass_var,"InvMass",0,1,"barrel"+Ecal_region_description,"m_{ee} [GeV]","Events","",50,0,2,2,1,80,100);


  DataMC(invMass_var,"EneSeed",0,1,"endcap"+Ecal_region_description,"E_{SC seed} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"EneSeed",0,1,"barrel"+Ecal_region_description,"E_{SC seed} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"EneSeed",1,1,"endcap"+Ecal_region_description,"E_{SC seed} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"EneSeed",1,1,"barrel"+Ecal_region_description,"E_{SC seed} [GeV]","Events","",50,1,10,4,1,0,500);

  DataMC(invMass_var,"EneSCEle",0,1,"endcap"+Ecal_region_description,"E_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"EneSCEle",0,1,"barrel"+Ecal_region_description,"E_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"EneSCEle",1,1,"endcap"+Ecal_region_description,"E_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"EneSCEle",1,1,"barrel"+Ecal_region_description,"E_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  //DataMC(invMass_var,"EneSCEleLead",0,1,"endcap"+Ecal_region_description,"E_{SC Lead} [GeV]","Events","",50,1,10,4,1,0,500);
  //DataMC(invMass_var,"EneSCEleLead",0,1,"barrel"+Ecal_region_description,"E_{SC Lead} [GeV]","Events","",50,1,10,4,1,0,500);

  //DataMC(invMass_var,"EneSCEleSubLead",0,1,"endcap"+Ecal_region_description,"E_{SC SubLead} [GeV]","Events","",50,1,10,4,1,0,500);
  //DataMC(invMass_var,"EneSCEleSubLead",0,1,"barrel"+Ecal_region_description,"E_{SC SubLead} [GeV]","Events","",50,1,10,4,1,0,500);

  DataMC(invMass_var,"Momentum",0,1,"endcap"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum",0,1,"barrel"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum",1,1,"endcap"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum",1,1,"barrel"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum_Vertex",0,1,"endcap"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum_Vertex",0,1,"barrel"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum_Vertex",1,1,"endcap"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  DataMC(invMass_var,"Momentum_Vertex",1,1,"barrel"+Ecal_region_description,"p_{SC} [GeV]","Events","",50,1,10,4,1,0,500);
  //DataMC(invMass_var,"MomentumLead",0,1,"endcap"+Ecal_region_description,"p_{SC Lead} [GeV]","Events","",50,1,10,4,1,0,500);
  //DataMC(invMass_var,"MomentumLead",0,1,"barrel"+Ecal_region_description,"p_{SC Lead} [GeV]","Events","",50,1,10,4,1,0,500);

  //DataMC(invMass_var,"MomentumSubLead",0,1,"endcap"+Ecal_region_description,"p_{SC SubLead} [GeV]","Events","",50,1,10,4,1,0,500);
  //DataMC(invMass_var,"MomentumSubLead",0,1,"barrel"+Ecal_region_description,"p_{SC SubLead} [GeV]","Events","",50,1,10,4,1,0,500);

  DataMC(invMass_var,"EoverP",0,1,"endcap"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP",0,1,"barrel"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP",1,1,"endcap"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP",1,1,"barrel"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP_Vertex",0,1,"endcap"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP_Vertex",0,1,"barrel"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP_Vertex",1,1,"endcap"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  DataMC(invMass_var,"EoverP_Vertex",1,1,"barrel"+Ecal_region_description,"(E/p)_{SC}","Events","",50,1,5,2,1,0,3);
  //DataMC(invMass_var,"EoverPLead",0,1,"endcap"+Ecal_region_description,"(E/p)_{SC Lead}","Events","",50,1,10,2);
  //DataMC(invMass_var,"EoverPLead",0,1,"barrel"+Ecal_region_description,"(E/p)_{SC Lead}","Events","",50,1,10,2);

  //DataMC(invMass_var,"EoverPSubLead",0,1,"endcap"+Ecal_region_description,"(E/p)_{SC SubLead}","Events","",50,1,10,2);
  //DataMC(invMass_var,"EoverPSubLead",0,1,"barrel"+Ecal_region_description,"(E/p)_{SC SubLead}","Events","",50,1,10,2);

  ////2D
  /*
  DataMC(invMass_var,"MapEE",0,2,"endcap"+Ecal_region_description,"iX","iY","Events",50,0,2,2);
  DataMC(invMass_var,"MapEB",0,2,"barrel"+Ecal_region_description,"i#phi","i#eta","Events",50,0,2,2);
  //DataMC(invMass_var,"MapEELead",0,2,"endcap"+Ecal_region_description,"iX","iY","Events",50,0,2,2);
  //DataMC(invMass_var,"MapEBLead",0,2,"barrel"+Ecal_region_description,"i#phi","i#eta","Events",50,0,2,2);
  //DataMC(invMass_var,"EneEleLeadvsEtaEleLead",0,2,"endcap"+Ecal_region_description,"#eta_{SC Lead}","E_{SC Lead}","Events",50,0,2,2,1,-2.7,2.7);
  //DataMC(invMass_var,"EneEleLeadvsEtaEleLead",0,2,"barrel"+Ecal_region_description,"#eta_{SC Lead}","E_{SC Lead}","Events",50,0,2,2,1,-1.6,1.6);
  DataMC(invMass_var,"EneElevsEtaEle",0,2,"endcap"+Ecal_region_description,"#eta_{SC}","E_{SC}","Events",50,0,2,2,1,-2.7,2.7);
  DataMC(invMass_var,"EneElevsEtaEle",0,2,"barrel"+Ecal_region_description,"#eta_{SC}","E_{SC}","Events",50,0,2,2,1,-1.6,1.6);
  //DataMC(invMass_var,"MapEEPLead",0,2,"endcap"+Ecal_region_description,"iX","iY","p [GeV]",50,0,2,2);
  //DataMC(invMass_var,"MapEBPLead",0,2,"barrel"+Ecal_region_description,"i#phi","i#eta","p [GeV]",50,0,2,2);
  DataMC(invMass_var,"MapEEP",0,2,"endcap"+Ecal_region_description,"iX","iY","p [GeV]",50,0,2,2);
  DataMC(invMass_var,"MapEBP",0,2,"barrel"+Ecal_region_description,"i#phi","i#eta","p [GeV]",50,0,2,2);
  */



  gROOT->ProcessLine(".q");
  
}


