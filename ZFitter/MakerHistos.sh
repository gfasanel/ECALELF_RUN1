cmsenv
make
#This works
#you should put the MC corrections trees in data/other

invMass_var=invMass_SC_regrCorrSemiParV5_ele
#invMass_var=invMass_SC

mkdir tmp/$invMass_var
#./bin/ZFitter.exe --doHistos -f data/validation/22Jan2012-runDepMCAll_v3.dat -m data_only --invMass_var=$invMass_var --corrEleType=HggRunEtaR9Et --smearEleType=stochastic --regionsFile=data/regions/scaleStep2smearing_8.dat 

#./bin/ZFitter.exe --doHistos -f data/validation/22Jan2012-runDepMCAll_v3.dat -m Powheg --invMass_var=$invMass_var --corrEleType=HggRunEtaR9Et --smearEleType=stochastic --regionsFile=data/regions/scaleStep2smearing_8.dat 

#./bin/ZFitter.exe --doHistos -f data/validation/22Jan2012-runDepMCAll_v3.dat -m MadGraph --invMass_var=$invMass_var --corrEleType=HggRunEtaR9Et --smearEleType=stochastic --regionsFile=data/regions/scaleStep2smearing_8.dat 

./bin/ZFitter.exe --doHistos -f data/validation/22Jan2012-runDepMCAll_v3.dat -m Sherpa --invMass_var=$invMass_var --corrEleType=HggRunEtaR9Et --smearEleType=stochastic --regionsFile=data/regions/scaleStep2smearing_8.dat 



#