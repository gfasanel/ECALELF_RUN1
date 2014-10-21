./script/GenRootChain.sh -f data/validation/22Jan2012-runDepMCAll_v5.dat --corrEleType=HggRunEtaR9Et --smearEleType=stochastic
root -l initial_plotter.C
cp -r initial_plots/*.png ~/scratch1/www/validation_GS