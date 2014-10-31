{
  //La macro che disegna e' in ZFitter/macro/PlotDataMC.C

  TString outputPath="tmp/Plots/";

  std::vector<TString> mcLabel_vec;

  //mcLabel_vec.push_back("Madgraph");
  mcLabel_vec.push_back("Powheg");
  //mcLabel_vec.push_back("Sherpa");

  //dopo "eleID_loose-trigger-noPF-EB" ,"qui puoi mettere i tagli aggiuntivi a mano tu brutali proprio"
  
  //PLOT 1D
  
  string a="1D";

  
  c = PlotDataMCs(data, MakeChainVector(/*signalA,*/signalB/*,signalC*/), "energySCEle[0]", "(100,100,150)", "eleID_loose-trigger-noPF-EB", "", "DATA", mcLabel_vec, "E SC Ele [GeV]", "", false, true); 
  c->SaveAs(outputPath+"EneBarrel.png");

  //c = PlotDataMCs(data, MakeChainVector(/*signalA,*/signalB/*,signalC*/), "energySCEle[0]", "(100,100,150)", "eleID_loose-trigger-noPF-EE", "", "DATA", mcLabel_vec, "E SC Ele [GeV]", "", false, true); 
  //c->SaveAs(outputPath+"EneEndcap.png");

  //c = PlotDataMCs(data, MakeChainVector(/*signalA,*/signalB/*,signalC*/), "pModeGsfEle[0]", "(100,100,150)", "eleID_loose-trigger-noPF-EB", "", "DATA", mcLabel_vec, "Momentum Ele [GeV]", "", false, true); 
  //c->SaveAs(outputPath+"PBarrel.png");

  //c = PlotDataMCs(data, MakeChainVector(/*signalA,*/signalB/*,signalC*/), "pModeGsfEle[0]", "(100,100,150)", "eleID_loose-trigger-noPF-EE", "", "DATA", mcLabel_vec, "Momentum Ele [GeV]", "", false, true); 
  //c->SaveAs(outputPath+"PEndcap.png");

  //EB richiede entrambi gli elettroni nel barrel
  //signalC e' commentato perche' rallenta troppo nel disegno

  
  //PLOT 2D
  if(a=="2D"){
  gStyle->SetPalette(1);  

  // Da mandare in profile e cambiare il nome della canva
  //c = Plot2D_profileX_my(data,"energySCEle[0]:etaSCEle[0]","(10,-2,2,70,130,200)","","colz","eta SC Ele [0]","energy SC Ele [0]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 

  //Mapping
  //Barrel
  //c = Plot2D_new(data,MakeChainVector(signalB),"map","inside macro","eleID_loose-trigger-noPF-EB","","unused data label",mcLabel_vec,"iEta","iPhi","Map_barrel",false, true);
  //cambiare dentro la macro
   c = Plot2D_new(data,MakeChainVector(signalB),"map","inside macro","eleID_loose-trigger-noPF-EE","","unused data label",mcLabel_vec,"iEta","iPhi","Map_endcap",false, true);
  //logy-> false, PU->true (as default)

  /*c = Plot2D_new(data,MakeChainVector(signalB),"energySCEle[0]:etaSCEle[0]","(10,-1.5,1.5,20,100,250)","eleID_loose-trigger-noPF-EB","","unused data label",mcLabel_vec,"#eta SC Ele Leading","E SC Ele Leading [GeV]","EneVsEta_barrel",false, true);

  c = Plot2D_new(data,MakeChainVector(signalB),"energySCEle[0]:etaSCEle[0]","(40,-4,4,20,100,250)","eleID_loose-trigger-noPF-EE","","unused data label",mcLabel_vec,"#eta SC Ele Leading","E SC Ele Leading [GeV]","EneVsEta_endcap",false, true);

  c = Plot2D_new(data,MakeChainVector(signalB),"pModeGsfEle[0]:etaSCEle[0]","(10,-1.5,1.5,20,100,250)","eleID_loose-trigger-noPF-EB","","unused data label",mcLabel_vec,"#eta SC Ele Leading","Momentum SC Ele Leading [GeV]","PVsEta_barrel",false, true);

  c = Plot2D_new(data,MakeChainVector(signalB),"pModeGsfEle[0]:etaSCEle[0]","(40,-4,4,20,100,250)","eleID_loose-trigger-noPF-EE","","unused data label",mcLabel_vec,"#eta SC Ele Leading","Momentum SC Ele Leading [GeV]","PVsEta_endcap",false, true);*/

  /*  c = Plot2D_new(data,MakeChainVector(signalB),"energySCEle[0]:R9Ele[0]","(10,0,2,20,100,250)","eleID_loose-trigger-noPF-EB","","unused data label",mcLabel_vec,"R_{9}","E SC Ele Leading [GeV]","EneVsR9_barrel",false, true);

  c = Plot2D_new(data,MakeChainVector(signalB),"energySCEle[0]:R9Ele[0]","(10,0,2,20,100,250)","eleID_loose-trigger-noPF-EE","","unused data label",mcLabel_vec,"R_{9}","E SC Ele Leading [GeV]","EneVsR9_endcap",false, true);

  c = Plot2D_new(data,MakeChainVector(signalB),"pModeGsfEle[0]:R9Ele[0]","(10,0,2,20,100,250)","eleID_loose-trigger-noPF-EB","","unused data label",mcLabel_vec,"R_{9}","Momentum SC Ele Leading [GeV]","PVsR9_barrel",false, true);

  c = Plot2D_new(data,MakeChainVector(signalB),"pModeGsfEle[0]:etaSCEle[0]","(10,0,2,20,100,250)","eleID_loose-trigger-noPF-EE","","unused data label",mcLabel_vec,"R_{9}","Momentum SC Ele Leading [GeV]","PVsR9_endcap",false, true);*/




  }

}
