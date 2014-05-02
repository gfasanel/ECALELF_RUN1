#!/usr/bin/env python

from optparse import OptionParser, make_option
from ROOT import *
import subprocess
import multiprocessing
import os

treeName="finalTree"
data = TChain(treeName)
mc = TChain(treeName)

#Global text print on top of the plots
text="CMS Preliminary #sqrt{s}=8 TeV"

# associate name of the variable to the expression to print it. This list should contain all the variables to plot
variables={}
variables['ptPhot']='ptPhot'
variables['etaPhot']='etaPhot'
variables['mvaIdPhot']='mvaIdPhot'
variables['nvtx']='nvtx'
variables['combinedPfIso03Phot']='combinedPfIso03Phot'
variables['rho']='rho'

#characteristics of the plot of a given variable
plotPars={}
plotPars['ptPhot']=dict( name='ptPhot', nBins=60, xMin=0., xMax=300., xaxisLabel="#gamma p_{T} (GeV)")
plotPars['etaPhot']=dict( name='etaPhot', nBins=60, xMin=-3., xMax=3., xaxisLabel="#gamma #eta")
plotPars['mvaIdPhot']=dict( name='mvaIdPhot', nBins=100, xMin=0., xMax=1., xaxisLabel="#gamma MVA output")
plotPars['nvtx']=dict( name='nvtx', nBins=41, xMin=-0.5, xMax=40.5, xaxisLabel="nvtx")
plotPars['combinedPfIso03Phot']=dict( name='combinedPfIso03Phot', nBins=200, xMin=-5, xMax=15, xaxisLabel="combined PfIso #DeltaR=0.3 (GeV)")
plotPars['rho']=dict( name='rho', nBins=100, xMin=0, xMax=40, xaxisLabel="#rho (GeV)")

#possible selections for the plots
cuts={}
cuts['All']='1' #just to avoid error
cuts['EB']='abs(etaPhot)<1.4442'
cuts['EE']='abs(etaPhot)>1.566 && abs(etaPhot)<2.5'

#different types of MC (and corresponding selection to differentiate them using ntuple variables"
mc_types={}
mc_types['Signal']="isMatchedPhot==1"
mc_types['Bkg']="isMatchedPhot==0"

#name of the variable to use as weight in MC
weight_var="weight"

#options to draw data and MC plots
draw_opts={}
draw_opts['data']=dict( SetMarkerSize=0.7,SetMarkerStyle=20,SetLineColor=1 )
draw_opts['mc_Bkg']=dict( SetLineColor=kMagenta,SetLineWidth=2,SetFillColor=kMagenta,SetFillStyle=1001 )
draw_opts['mc_Signal']=dict( SetLineColor=kCyan,SetLineWidth=2,SetFillColor=kCyan,SetFillStyle=1001 )

histos={}

ROOT.gROOT.SetBatch()
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)

def customizeCanvas(c):
    c.Range(0,0,1,1)
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetBorderSize(2)
    c.SetTickx(1)
    c.SetLeftMargin(0.13)
    c.SetRightMargin(0.07)
    c.SetTopMargin(0.09)
    c.SetBottomMargin(0.1)
    c.SetFrameFillStyle(0)
    c.SetFrameBorderMode(0)

def splitCanvas(c):
    pads=[]
    pads.append(TPad("pad1","pad1",0,0.3,1.,1.))
    pads.append(TPad("pad2","pad2",0,0.,1.,0.3))
    for pad in pads:
        pad.Draw()
    return pads

def drawText(additional_text):
    tex_m=TLatex()
    tex_m.SetNDC()
    tex_m.SetTextAlign(12)
    tex_m.SetTextSize(0.037)
    tex_m.SetLineWidth(2)
    tex_m.DrawLatex(0.25,0.94,text)
    
    if (additional_text != ""):
        tex_m.SetTextSize(0.045)
        tex_m.DrawLatex(0.63,0.63,additional_text)
        
#def plot(variable,plotsDir,additional_cuts="1",pars['additional_text']="",savefmts=[".C",".png",".pdf"]):
def plot(pars,savefmts=[".C",".png",".pdf",".root"]):
    c = TCanvas(pars['variable'],pars['variable'],1000,900)
    customizeCanvas(c)
    
    for cut in cuts.keys():
        histos[str(pars['variable'])+'_data_'+str(cut)]=TH1F(str(plotPars[str(pars['variable'])]['name'])+"_data_"+str(cut),str(plotPars[str(pars['variable'])]['name'])+"_data_"+str(cut),int(plotPars[str(pars['variable'])]['nBins']),float(plotPars[str(pars['variable'])]['xMin']),float(plotPars[str(pars['variable'])]['xMax']))
        histos[str(pars['variable'])+'_data_'+str(cut)].Sumw2()
        for type in mc_types.keys():
            histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)]=TH1F(str(plotPars[str(pars['variable'])]['name'])+"_mc_"+type+"_"+str(cut),str(plotPars[str(pars['variable'])]['name'])+"_mc_"+type+"_"+str(cut),plotPars[str(pars['variable'])]['nBins'],plotPars[str(pars['variable'])]['xMin'],plotPars[str(pars['variable'])]['xMax'])
            histos[str(pars['variable'])+'_mc_'+type+"_"+str(cut)].Sumw2()
        #Filling histos
        data.Project( histos[str(pars['variable'])+'_data_'+str(cut)].GetName(), str(variables[str(pars['variable'])]), str(cuts[cut])+"&&"+pars['additional_cuts'])
        histos[str(pars['variable'])+'_data_'+str(cut)].Print()
        #Now set drawing options
        for aopt in draw_opts['data'].keys():
            a=histos[str(pars['variable'])+'_data_'+str(cut)]
            eval('a.'+str(aopt)+'('+str(draw_opts['data'][aopt])+')')
            
        for mc_type in mc_types.keys():
            mc.Project( histos[str(pars['variable'])+'_mc_'+mc_type+"_"+str(cut)].GetName(), str(variables[str(pars['variable'])]), "("+str(cuts[cut])+"&&"+pars['additional_cuts']+"&&"+str(mc_types[mc_type])+")*"+weight_var )
            histos[str(pars['variable'])+'_mc_'+mc_type+"_"+str(cut)].Print()
            for aopt in draw_opts['mc_'+mc_type].keys():
                a=histos[str(pars['variable'])+'_mc_'+mc_type+"_"+str(cut)]
                eval('a.'+str(aopt)+'('+str(draw_opts['mc_'+mc_type][aopt])+')')

        #Stacked MC Histogram
        stack=THStack()
        mc_types_keys=mc_types.keys()
        mc_types_keys.sort()
        for mc_type in range(len(mc_types_keys)):
            stack.Add(histos[str(pars['variable'])+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)])
            
        histos[str(pars['variable'])+'_data_'+str(cut)].Draw("PE")
        histos[str(pars['variable'])+'_data_'+str(cut)].SetMaximum(histos[str(pars['variable'])+'_data_'+str(cut)].GetMaximum()*1.4)
        histos[str(pars['variable'])+'_data_'+str(cut)].SetMinimum(0)
        histos[str(pars['variable'])+'_data_'+str(cut)].GetXaxis().SetTitle(str(plotPars[str(pars['variable'])]['xaxisLabel']))
        histos[str(pars['variable'])+'_data_'+str(cut)].GetYaxis().SetTitle('Entries/'+str(histos[str(pars['variable'])+'_data_'+str(cut)].GetBinWidth(1)))
        histos[str(pars['variable'])+'_data_'+str(cut)].GetYaxis().SetTitleOffset(1.5)
        stack.Draw("HSAME")
        histos[str(pars['variable'])+'_data_'+str(cut)].Draw("PESAME")

        #Legend
        a=TLegend(0.63,0.68,0.88,0.88)
        a.SetBorderSize(0)
        a.SetFillColor(0)
        a.SetTextSize(0.038)
        a.SetHeader(str(cut))
        a.AddEntry( histos[str(pars['variable'])+'_data_'+str(cut)],"Data","PL" )
        for mc_type in range(len(mc_types_keys)):
             a.AddEntry( histos[str(pars['variable'])+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)], mc_types_keys[mc_type], "F" )
        a.Draw()

        #Additional text
        drawText(pars['additional_text'])

        #Save plots
        c.SetLogy(0)
        for format in savefmts:
            c.SaveAs(pars['plotsDir']+"/"+str(pars['variable'])+str(cut)+format)

        # now log and ratio plots in a splitted canvas
        c.Clear()
        pads=splitCanvas(c)

        #First pad
        pads[0].cd()
        gPad.SetLogy(1)
        histos[str(pars['variable'])+'_data_'+str(cut)].SetMaximum(histos[str(pars['variable'])+'_data_'+str(cut)].GetMaximum()*4.)
        histos[str(pars['variable'])+'_data_'+str(cut)].SetMinimum(0.1)
        histos[str(pars['variable'])+'_data_'+str(cut)].GetYaxis().SetTitleOffset(0.9)
        histos[str(pars['variable'])+'_data_'+str(cut)].Draw("PE")
        stack.Draw("HSAME")
        histos[str(pars['variable'])+'_data_'+str(cut)].Draw("PESAME")
        
        a=TLegend(0.63,0.68,0.88,0.88)
        a.SetBorderSize(0)
        a.SetFillColor(0)
        a.SetTextSize(0.038)
        a.SetHeader(str(cut))
        a.AddEntry( histos[str(pars['variable'])+'_data_'+str(cut)],"Data","PL" )
        for mc_type in range(len(mc_types_keys)):
             a.AddEntry( histos[str(pars['variable'])+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)], mc_types_keys[mc_type], "F" )
        a.Draw()

        drawText(pars['additional_text'])

        #Second pad (bottom)
        pads[1].cd()
        pads[1].SetBottomMargin(0.2)
        pads[1].SetGridy(1)

        #prepare ratio histogram
        ratio=histos[str(pars['variable'])+'_data_'+str(cut)].Clone("ratio")
        for mc_type in range(len(mc_types_keys)):
            if (mc_type==0):
                sum=histos[str(pars['variable'])+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)].Clone("sum")
            else:
                sum.Add(histos[str(pars['variable'])+'_mc_'+mc_types_keys[mc_type]+"_"+str(cut)])
        ratio.Divide(sum)
        ratio.SetMaximum(3)
        ratio.SetMinimum(0.2)

        ratio.GetYaxis().SetTitle("Data/MC")
        ratio.GetYaxis().SetLabelSize(0.07)
        ratio.GetXaxis().SetLabelSize(0.07)
        ratio.GetXaxis().SetTitleSize(0.08)
        ratio.GetYaxis().SetTitleSize(0.08)
        ratio.GetXaxis().SetTitleOffset(1.)
        ratio.GetYaxis().SetTitleOffset(0.35)
        ratio.Draw("PE")

        #Draw a line @1
        aL=TLine(float(plotPars[str(pars['variable'])]['xMin']),1,float(plotPars[str(pars['variable'])]['xMax']),1)
        aL.SetLineColor(4)
        aL.SetLineWidth(2)
        aL.Draw()
        
        ratio.Draw("PESAME")
        for format in savefmts:
            c.SaveAs(pars['plotsDir']+"/"+str(pars['variable'])+str(cut)+"_log"+format)

def main(options,args):

    print "+++++++++++++++++++++++++++++++++++++++++++"
    print "Processing with options: "
    print options
    print "+++++++++++++++++++++++++++++++++++++++++++"

    plotsDir=options.plotsDir
    additionalText=options.additionalText
    additionalCuts=options.additionalCuts

    #Creating output dir
    try:
        os.mkdir(plotsDir)
    except:
        pass

    #Reading data files list
    lines = [line.strip() for line in open(options.dataFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        data.Add(line)

    #Reading mc files list
    lines = [line.strip() for line in open(options.mcFiles)]
    for line in lines:
        if line.startswith('#'):
            continue
        mc.Add(line)
    #Setting up parallel processing
    ncpu=multiprocessing.cpu_count()

    if (options.numberOfCPU>0):
        ncpu=options.numberOfCPU
        
    pool = multiprocessing.Pool(processes=ncpu)

    #run all the samples in parallel 
    pars=[ dict(variable=x,plotsDir=plotsDir,additional_cuts=additionalCuts,additional_text=additionalText) for x in variables.keys() ]
    #      print pars
    pool.map(plot, pars)

    #for variable in variables.keys():
    #    plot(variable,plotsDir,additionalCuts,additionalText)

    
if __name__ == "__main__":
    parser = OptionParser(option_list=[
        make_option("--dataFiles",
                    action="store", type="string", dest="dataFiles",
                    default="data.txt",
                    help="", metavar=""
                    ),
        make_option("--mcFiles",
                    action="store", type="string", dest="mcFiles",
                    default="mc.txt",
                    help="", metavar=""
                    ),
        make_option("--plotsDir",
                    action="store", type="string", dest="plotsDir",
                    default="plots/",
                    help="", metavar=""
                    ),
        make_option("--additionalText",
                    action="store", type="string", dest="additionalText",
                    default="",
                    help="", metavar=""
                    ),
        make_option("--additionalCuts",
                    action="store", type="string", dest="additionalCuts",
                    default="1",
                    help="", metavar=""
                    ),
        make_option("--numberOfCPU",
                    action="store", type="int", dest="numberOfCPU",
                    default=-1,
                    help="", metavar=""
                    )
        ])
    
    (options, args) = parser.parse_args()
    
    main( options, args) 
