# Setup CMSSW environment for a newer software release
# This should give access to most HEP software needed

source /afs/hep.wisc.edu/cms/setup/bashrc

pushd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw-patch/CMSSW_8_0_26_patch2
cmsenv
popd

source /afs/hep.wisc.edu/cms/dasu/Geant4/geant4.10.00.p01-install/bin/geant4.sh
