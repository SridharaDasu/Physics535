/**
 * @file StackingAction.cc
 * @brief Implements optional user action StackingAction
 */

#include "StackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Neutron.hh"

/*!
 stackingAction.cc

 The action is used here to kill all low-energy secondary 
 neutrons (below 1 MeV). Neutrons are killed without being 
 tracked at all. This allows to save computing time.
*/

StackingAction::StackingAction()
{;}


StackingAction::~StackingAction() {;}


G4ClassificationOfNewTrack 
StackingAction::ClassifyNewTrack( const G4Track * aTrack ) {

  G4ClassificationOfNewTrack result( fUrgent );
 
  //This method returns the definition of the partycle type
  G4ParticleDefinition * particleType = aTrack->GetDefinition();

  //Check for particles above threshold.
  G4double thresh = 1*MeV;

  //Kill low-energy neutrons
  if (particleType == G4Neutron::Neutron() 
       && aTrack->GetKineticEnergy() < thresh) 
     result = fKill;

  //For other particles/energy, the result is "fUrgent", namely 
  //the track is registered to the stack and tracked.
  return result;
}


