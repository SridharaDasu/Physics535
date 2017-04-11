// This simple program generates events for various physics processes.

using namespace std;
#include <math.h>

#include "Pythia.h"
using namespace Pythia8; 

#include "UltraFastSim.h"

#include "EventAnalysis.h"

int main(int argc, char **argv) {
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
  Event& event = pythia.event;

  if(argc >= 2) pythia.readFile(argv[1]);
  else {
    cerr << "Command syntax: " 
	 << argv[0] 
	 << " <command file name> [<runNumber>]" 
	 << endl;
    exit(1);
  }

  int runNumber = 0;
  if(argc == 3) runNumber = atoi(argv[2]);

  int nEvents = pythia.mode("Main:numberOfEvents");
  int    nList     = pythia.mode("Main:numberToList");
  int    nShow     = pythia.mode("Main:timesToShow");
  int    nAbort    = pythia.mode("Main:timesAllowErrors");
  bool   showCS    = pythia.flag("Main:showChangedSettings");
  bool   showAS    = pythia.flag("Main:showAllSettings");
  bool   showCPD   = pythia.flag("Main:showChangedParticleData");
  bool   showAPD   = pythia.flag("Main:showAllParticleData");

  // Initialize pythia

  pythia.init();

  // List settings.
  if (showCS) pythia.settings.listChanged();
  if (showAS) pythia.settings.listAll();

  // List particle data.  
  if (showCPD) pythia.particleData.listChanged();
  if (showAPD) pythia.particleData.listAll();

  Rndm * rndmPtr = &pythia.rndm;
  rndmPtr->init(runNumber);

  // Setup analysis class
  string hFileName(argv[1]);
  hFileName.erase(hFileName.rfind("."));  
  hFileName += ".root";
  EventAnalysis eventAnalysis(hFileName);

  // Ultra Fast Simulator

  UltraFastSim ufs;

  // Begin event loop
  for (int iEvent = 0, iAbort = 0; iEvent < nEvents; ) {

    // Generate event. Skip if error. Unless, errors are too many.
    if (!pythia.next()) {
      iAbort++;
      if(iAbort > nAbort) {
	cerr << "Too many aborted events = " << nAbort << endl;
	exit(1);
      }
      continue;
    }

    // List first few events, both hard process and complete events.
    if (iEvent < nList) { 
      pythia.info.list();
      pythia.process.list();
      event.list();
    }

    // Ultra fast simulation of detector effects
    if(!ufs.run(pythia.event, rndmPtr))
      {
	cerr << "Ultra fast simulation failed - aborting" << endl;
	exit(2);
      }

    // Event Analysis
    eventAnalysis.processEvent(event, ufs);

    // Heartbeat
    if(!(iEvent % nShow)) cout << "Processed event " << iEvent << endl;
    iEvent++;
    
  }

  // Save output

  pythia.statistics();
  eventAnalysis.finalize();

  return 0;

}
