{
gROOT->ProcessLine(".include /cvmfs/cms.cern.ch/slc5_amd64_gcc462/lcg/roofit/5.32.03-cms16//include");
gROOT->ProcessLine(".L macro/macro_fit.C+");
gROOT->ProcessLine(".L macro/plot_data_mc.C+");
 FitProfile2("test/dato/Mee/fitres/outProfile-basic_2-Et_25-trigger-noPF.root","","",true,true,true);//using Mee
 FitProfile2("test/dato/GS/fitres/outProfile-eop-basic_pt-Et_25-trigger-noPF.root","","",true,true,true);//using EoP
}
