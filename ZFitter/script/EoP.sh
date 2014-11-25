#!/bin/bash
source script/functions.sh
commonCut=Et_25-trigger-noPF
outDirData=test/dato
extension=Double_Ele_scaleStep4_smearing_0a
region=scaleStep4smearing_0a

#Be careful with onlyScale: you must use a NON ZERO SIGMA!

# you should run this script using screen 
# it creates a single job of 50 subjobs (array of jobs)
# Directory organization: 

############################My EoP case####################################

 if [ ! -e "${outDirData}/${extension}/fitres" ];then mkdir ${outDirData}/${extension}/fitres -p; fi
 if [ ! -e "${outDirData}/table" ];then mkdir ${outDirData}/table -p; fi
 if [ ! -e "${outDirData}/${extension}/img" ];then mkdir ${outDirData}/${extension}/img -p; fi

############# SUBMITTING JOBS ###########################################

        for index in `seq 1 50`
        do
            mkdir ${outDirData}/${extension}/${index}/fitres/ -p
            mkdir ${outDirData}/${extension}/${index}/img -p
        done

	bsub -q 2nd\
            -oo ${outDirData}/${extension}/%I/fitres/`basename ${outFile} .dat`-${region}-stdout.log\
            -eo ${outDirData}/${extension}/%I/fitres/`basename ${outFile} .dat`-${region}-stderr.log\
            -J "${region} ${extension}[1-50]"\
            "cd $PWD; eval \`scramv1 runtime -sh\`; uname -a; echo \$CMSSW_VERSION;

./bin/ZFitter.exe -f data/validation/22Jan2012-runDepMCAll_v5.dat --corrEleType=HggRunEtaR9Et --smearEleType=stochastic --regionsFile=data/regions/${region}.dat --EoP=true --invMass_var=invMass_SC_regrCorrSemiParV5_ele --autoBin --outDirImgData=${outDirData}/${extension}/\$LSB_JOBINDEX/img/ --outDirFitResData=${outDirData}/${extension}/\$LSB_JOBINDEX/fitres --smearerFit --initFile=init_eop_scaleStep4smearing_0a.txt || exit 1";

exit 0
#Qui aspetta che i job siano completati
	while [ "`bjobs -J \"${region} ${extension}\" | grep -v JOBID | grep -v found | wc -l`" != "0" ]; do /bin/sleep 2m; done

    ./script/haddTGraph.sh -o ${outDirData}/${extension}/fitres/outProfile-eop-$region-${commonCut}.root ${outDirData}/${extension}/*/fitres/outProfile-eop-$region-${commonCut}.root



	###########################Make Plots###########################33
    echo "{" > tmp/fitProfiles.C
    echo "gROOT->ProcessLine(\".include $ROOFITSYS/include\");" >> tmp/fitProfiles.C
    echo "gROOT->ProcessLine(\".L macro/macro_fit.C+\");" >> tmp/fitProfiles.C
    echo "gROOT->ProcessLine(\".L macro/plot_data_mc.C+\");" >> tmp/fitProfiles.C
    echo "FitProfile2(\"${outDirData}/${extension}/fitres/outProfile-eop-$region-${commonCut}.root\",\"\",\"\",true,true,true);" >> tmp/fitProfiles.C
    echo "}" >> tmp/fitProfiles.C
    root -l -b -q tmp/fitProfiles.C

#    cat "`echo $initFile | sed 's|.*=||'`" |grep "C L" >>  ${outFile}
#    if [ ! -e "${outFile}" ];then
#	touch ${outFile}
#    fi

#    cat ${outDirData}/${extension}/img/outProfile-eop-${region}-${commonCut}-FitResult.config > ${outFile}
    
    
#    cat "`echo $initFile | sed 's|.*=||'`" |grep "C L" >>  ${outFile}
    
    echo "[STATUS] Making data/MC plots"

#CAMBIARE Questo serve solo ad avere i plot carini
#     ./bin/ZFitter.exe -f $outDirData/${extension}/`basename $configFile` --regionsFile ${regionFileEB} $isOdd $updateOnly --selection=${newSelection}  --invMass_var ${invMass_var} --commonCut ${commonCut} --outDirFitResMC=${outDirMC}/${extension}/fitres --outDirImgMC=${outDirMC}/${extension}/img --outDirImgData=${outDirData}/${extension}/img/ --outDirFitResData=${outDirData}/${extension}/fitres --constTermFix  --smearerFit  --smearingEt --autoNsmear --autoBin --initFile=${outFile} --corrEleType=HggRunEtaR9Et --plotOnly >debug_plot_only.txt || exit 1
    