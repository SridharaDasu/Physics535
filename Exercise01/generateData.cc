// This simple program generates events for various physics processes.

using namespace std;
#include <math.h>

#include "Pythia.h"
using namespace Pythia8; 

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

  // Begin event loop
  for (int iEvent = 0; iEvent < nEvents; ) {

    // Generate event. Skip if error. List first ten.
    if (!pythia.next()) continue;

    // List first few events, both hard process and complete events.
    if (iEvent < nList) { 
      pythia.info.list();
      pythia.process.list();
      event.list();
    }

    if(!(iEvent % 100)) cout << "Processed event " << iEvent << endl;
    iEvent++;
    
  }

  // Save output

  pythia.statistics();

  return 0;

}
