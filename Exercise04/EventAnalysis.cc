#include "EventAnalysis.h"

using namespace std;
#include <math.h>
#include <string>
#include <map>

#include "Pythia8/Pythia.h"
using namespace Pythia8; 

#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TMath.h"

#include "UltraFastSim.h"

EventAnalysis::EventAnalysis(string histFileName) {
  file = new TFile(histFileName.c_str(), "recreate");
  // Define histograms
  histograms["NStableParticles"] = new TH1F("NStableParticles", "Number of Stable Particles", 50, 0., 10000.);
  histograms["NVisibleParticles"] = new TH1F("NVisibleParticles", "Number of Visible Particles", 50, 0., 10000.);
  histograms["NInvisibleParticles"] = new TH1F("NInvisibleParticles", "Number of Invisible Particles", 10, 0., 10.);
  histograms["RecoPhotonET"] = new TH1F("RecoPhotonET", "Transverse energy of reconstructed photons (GeV)", 100, 0., 100.);
}

void EventAnalysis::processEvent(Event& event, UltraFastSim &ufs) {
  
  // Process the generator level event

  int nStableParticles = 0;
  int nVisibleParticles = 0;
  int nInvisibleParticles = 0;
  for(int i = 0; i < event.size(); ++i) {
    Particle& particle = event[i];
    // Consider only particles with good status
    if(particle.status() > 0) {   // If status is less than zero, the particle decayed
      nStableParticles++;
      // Consider only visible particles -- ignores neutrinos
      if(particle.isVisible()) {
	nVisibleParticles++;
	// hNVisibleParticles->Fill(nVisibleParticles);
      }
      else {
	nInvisibleParticles++;
      }
    }
  }
  histograms["NStableParticles"]->Fill(nStableParticles);
  histograms["NVisibleParticles"]->Fill(nVisibleParticles);
  histograms["NInvisibleParticles"]->Fill(nInvisibleParticles);

  // Process the reconstructed event
  for(unsigned int i = 0; i < ufs.photonList().size(); i++) {
    double recoPhotonET = ufs.photonList()[i].Pt();
    histograms["RecoPhotonET"]->Fill(recoPhotonET);
  }

}

void EventAnalysis::finalize() {
  file->cd();
  file->Write();
  file->Close();
}
