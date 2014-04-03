{
  //La macro che disegna e' in ZFitter/macro/PlotDataMC.C

  TString outputPath="tmp/Plots/";

  std::vector<TString> mcLabel_vec;

  mcLabel_vec.push_back("Madgraph");
  mcLabel_vec.push_back("Powheg");
  mcLabel_vec.push_back("Sherpa");

  //dopo "eleID_loose-trigger-noPF-EB" ,"qui puoi mettere i tagli aggiuntivi a mano tu brutali proprio"
  
  //PLOT 1D
  
  string a="2D";
  a="check";
  a="2D";

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "invMass", "(100,0,150)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "M_{ee} [GeV]", "", false, true); 
  c->SaveAs(outputPath+"invMass.eps");
  c->SaveAs(outputPath+"invMass.png");

  //EB richiede entrambi gli elettroni nel barrel
  //signalC e' commentato perche' rallenta troppo nel disegno
  if(a=="1D"){
  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "energySCEle[0]", "(100,200,300)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "energy SC ele leading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"energySCEleLeading.eps");
  c->SaveAs(outputPath+"energySCEleLeading.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "energySCEle[0]", "(70,130,200)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "energy SC ele leading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"energySCEleLeading_1.eps");
  c->SaveAs(outputPath+"energySCEleLeading_1.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "energySCEle[1]", "(100,200,300)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "energy SC ele subleading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"energySCEleSubLeading.eps");
  c->SaveAs(outputPath+"energySCEleSubLeading.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "energySCEle[1]", "(70,130,200)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "energy SC ele Subleading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"energySCEleSubLeading_1.eps");
  c->SaveAs(outputPath+"energySCEleSubLeading_1.png");

  //MOMENTUM
  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "pModeGsfEle[0]", "(100,200,300)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "Momentum ele leading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"pModeGsfEleLeading.eps");
  c->SaveAs(outputPath+"pModeGsfEleLeading.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "pModeGsfEle[0]", "(70,130,200)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "Momentum ele leading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"pModeGsfEleLeading_1.eps");
  c->SaveAs(outputPath+"pModeGsfEleLeading_1.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "pModeGsfEle[1]", "(100,200,300)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "Momentum ele subleading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"pModeGsfEleSubLeading.eps");
  c->SaveAs(outputPath+"pModeGsfEleSubLeading.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "pModeGsfEle[1]", "(70,130,200)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "Momentum ele Subleading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"pModeGsfEleSubLeading_1.eps");
  c->SaveAs(outputPath+"pModeGsfEleSubLeading_1.png");

  //E/p
  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "energySCEle[0]/pModeGsfEle[0]", "(100,0,1.5)", "eleID_loose-trigger-noPF", "", "DATA", mcLabel_vec, "E/p ele leading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"EoverPEleLeading.eps");
  c->SaveAs(outputPath+"EoverPEleLeading.png");

  c = PlotDataMCs(data, MakeChainVector(signalA,signalB/*,signalC*/), "energySCEle[0]/pModeGsfEle[0]", "(100,0,1.5)", "eleID_loose-trigger-noPF", "energySCEle[0]>200 && energySCEle[0]<300", "DATA", mcLabel_vec, "E/p ele leading [GeV]", "", false, true); 
  c->SaveAs(outputPath+"EoverPEleLeading_Eg200.eps");
  c->SaveAs(outputPath+"EoverPEleLeading_Eg200.png");

  }
  
  //PLOT 2D
  if(a=="2D"){
  gStyle->SetPalette(1);
  
  // Da mandare in profile e cambiare il nome della canva
  c = Plot2D_profileX_my(data,"energySCEle[0]:etaSCEle[0]","(10,-2,2,70,130,200)","","colz","eta SC Ele [0]","energy SC Ele [0]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 
  c->SaveAs(outputPath+"energyLeadvsEta_profileX.eps");
  c->SaveAs(outputPath+"energyLeadvsEta_profileX.png");

  /*
  c = Plot2D_profileX_my(data,"energySCEle[1]:etaSCEle[1]","(10,-2,2,70,130,200)","","colz","eta SC Ele [1]","energy SC Ele [1]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 
  c->SaveAs(outputPath+"energySubLeadvsEta_profileX.eps");
  c->SaveAs(outputPath+"energySubLeadvsEta_profileX.png");

  c = Plot2D_my(data,"energySCEle[0]:etaSCEle[0]","(10,-1.5,1.5,35,130,200)","","colz","eta SC Ele [0]","energy SC Ele [0]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 
  c->SaveAs(outputPath+"energyLeadvsEta_2D_1.eps");
  c->SaveAs(outputPath+"energyLeadvsEta_2D_1.png");

  c = Plot2D_my(data,"energySCEle[1]:etaSCEle[1]","(10,-1.5,1.5,35,130,200)","","colz","eta SC Ele [1]","energy SC Ele [1]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 
  c->SaveAs(outputPath+"energySubLeadvsEta_2D_1.eps");
  c->SaveAs(outputPath+"energySubLeadvsEta_2D_1.png");

  c = Plot2D_my(data,"energySCEle[0]:etaSCEle[0]","(10,-1.5,1.5,50,200,300)","","colz","eta SC Ele [0]","energy SC Ele [0]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 
  c->SaveAs(outputPath+"energyLeadvsEta_2D.eps");
  c->SaveAs(outputPath+"energyLeadvsEta_2D.png");
  */
  c = Plot2D_my(data,"energySCEle[1]:etaSCEle[1]","(10,-1.5,1.5,50,200,300)","","colz","eta SC Ele [1]","energy SC Ele [1]"); //che deficiente il tizio di root => y:x e poi x,xmin,xmax, y, ymin,ymax 
  c->SaveAs(outputPath+"energySubLeadvsEta_2D.eps");
  c->SaveAs(outputPath+"energySubLeadvsEta_2D.png");
  

  delete c;
  }

}
