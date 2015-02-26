import FWCore.ParameterSet.Config as cms

process = cms.Process("ntuple")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('LNuAA_LM3_Reweight_Tree.root')
                                   )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:LNuAA_LM3_Reweight_step0.root'
    )
)

process.ntuple = cms.EDAnalyzer('Reweight_EDMtoRootTree',
                              lheEventSrc=cms.InputTag("source")
                              )

process.ntuple_step = cms.Path(process.ntuple)
process.schedule = cms.Schedule(process.ntuple_step)

#process.p = cms.Path(process.Reweight_EDMtoRootTree)
