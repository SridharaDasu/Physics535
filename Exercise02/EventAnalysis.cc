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

EventAnalysis::EventAnalysis(string histFileName) {
  file = new TFile(histFileName.c_str(), "recreate");
  // Define histograms
  histograms["NStableParticles"] = new TH1F("NStableParticles", "Number of Stable Particles", 50, 0., 1000.);
  histograms["NVisibleParticles"] = new TH1F("NVisibleParticles", "Number of Visible Particles", 50, 0., 1000.);
  histograms["NInvisibleParticles"] = new TH1F("NInvisibleParticles", "Number of Invisible Particles", 10, 0., 10.);
}

void EventAnalysis::processEvent(Event& event) {
  
  // Process the event

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
}

void EventAnalysis::finalize() {
  file->cd();
  file->Write();
  file->Close();
}
