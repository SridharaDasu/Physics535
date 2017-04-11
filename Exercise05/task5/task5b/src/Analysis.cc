/**
 * @file   Analysis.cc
 *
 * @date   17 Dec 2009
 * @author adotti
 *
 * @brief  Implements user class Analysis (singleton)
 */

#include "Analysis.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"
#include "HadCaloHit.hh"


Analysis* Analysis::singleton = 0;

//Constructor: it initializes parameters
Analysis::Analysis() :
	thisEventTotEM(0),
	thisEventSecondaries(0),
	thisRunTotEM(0),
	thisRunTotSecondaries(0)
{;}

//---------------------------------------------------------------

void Analysis::PrepareNewEvent(const G4Event* /*anEvent*/)
{
  //This method is called via 
  // EventAction::BeginOfEventAction()
  //at each new event
  //Reset variables relative to this event
  thisEventSecondaries = 0;
  thisEventTotEM = 0;
  //set to zero the event energy deposit in each layer of the hCAL
  for ( int i = 0; i<NUMLAYERS ; ++i ) 
    thisEventTotHad[i]=0;
}

//---------------------------------------------------------------

void Analysis::PrepareNewRun(const G4Run* /*aRun*/ )
{
  //This method is called via 
  // RunAction::BeginOfRunAction()
  //at each new event
  //Reset variables relative to the run
  thisRunTotEM = 0;
  thisRunTotSecondaries = 0;
  //set to zero the run (total) energy deposit in each layer of the hCAL
  for ( int i = 0; i<NUMLAYERS ; ++i ) 
    thisRunTotHad[i]=0;
}

//---------------------------------------------------------------

void Analysis::EndOfEvent(const G4Event* anEvent)
{
  //This method is called via 
  // EventAction::EndOfEventAction()
  //at the end of each new event

  //Accumulate over the run
  thisRunTotEM += thisEventTotEM;
  thisRunTotSecondaries += thisEventSecondaries;

  //We want now to retrieve the collection of hits created by the HadCalo SD
  //We need to know the collection ID associated with the collection name,
  //for this purpose we can ask the Sensitive
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  //retrieve the ID of the proper hit collection --> association done 
  //via its name
  G4int hitCollID = SDman->GetCollectionID("HadCaloHitCollection");

  //retrieve the full hit-collection of the current event
  G4HCofThisEvent* hitsCollections = anEvent->GetHCofThisEvent();
  
  //Among all the HCs defined for the events, retrieve the one having 
  //ID=hitCollID. Incidentally, this is the only hit collection
  //defined, but in principle they could be more. All of them can be 
  //retrieved in the same way.
  HadCaloHitCollection* hits = 0;
  if ( hitsCollections )    
    hits = static_cast<HadCaloHitCollection*>(hitsCollections->GetHC(hitCollID));
    
  //Ok, now we have the hit collection at hand. If it is not a NULL pointer,
  //we can have a look at it, and read the information we need.
  if ( hits ) //hits container found we can proceed
    {
      //read the number of hits contained in the collection
      G4int numberHits = hits->entries();
      //Loop on all hits
      //we can loop and get each single hit
      for(G4int i = 0; i < numberHits ; i++) {
	//retrieve the i-th hit from the collection
	HadCaloHit* hit = (*hits)[i];
	
	//Now read the content and add the energy to our conters
	G4int layer = hit->GetLayerNumber();
	G4double edep = hit->GetEdep();
	if ( layer >= 0 && layer < NUMLAYERS )
	  {
	    thisEventTotHad[layer] += edep;
	  }
	//else something else very strange happened
	//In this exercise we use simple arrays, this is not the best C++ way to do 
	//things, but it's quite simple!
	}
    }
  for ( int i = 0; i<NUMLAYERS ; ++i ) 
    thisRunTotHad[i] += thisEventTotHad[i];
}

//---------------------------------------------------------------


void Analysis::EndOfRun(const G4Run* aRun)
{
  //Some print outs
  G4int numEvents = aRun->GetNumberOfEvent();
  
  G4double totHadCalo = 0;
  for ( int i = 0 ; i < NUMLAYERS ; ++i) totHadCalo += thisRunTotHad[i];
  
  G4cout<<"================="<<G4endl;
  G4cout<<"Summary for run: "<<aRun->GetRunID()<<G4endl;
  G4cout<<"\t Event processed: "<<numEvents<<G4endl;
  G4cout<<"\t Average number of secondaries: "<<thisRunTotSecondaries/numEvents<<G4endl;
  G4cout<<"\t Average energy in EM calo: "<<G4BestUnit(thisRunTotEM/numEvents,"Energy")<<G4endl;
  G4cout<<"\t Average energy in Had calo: "<<G4BestUnit(totHadCalo/numEvents,"Energy")<<G4endl;
  for ( int layer = 0 ; layer < NUMLAYERS ; ++layer)
    {
      G4cout<<"\t\t Average energy in Layer "<<layer<<": "<<G4BestUnit(thisRunTotHad[layer],"Energy")<<G4endl;
    }
}
