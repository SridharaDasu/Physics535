// $Id: StackingAction.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file
 * @brief implements user class StackingAction
 */

#include "StackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "Analysis.hh"

StackingAction::StackingAction()
{;}

StackingAction::~StackingAction() 
{;}

G4ClassificationOfNewTrack 
StackingAction::ClassifyNewTrack( const G4Track * aTrack ) 
{ 
  if ( aTrack->GetParentID() > 0 )//This is a secondary
    {
      //aTrack->GetDefinition() returns the particle definition 
      //(= which particle it is) of the current track
      Analysis::GetInstance()->AddSecondary(aTrack->GetDefinition());
    }
  else // This is primary
    {
      //aTrack->GetDefinition() returns the particle definition 
      //(= which particle it is) of the current track.
      //GetKineticEnergy() returns the kinetic energy 
      Analysis::GetInstance()->SetBeam(aTrack->GetDefinition(),
				       aTrack->GetKineticEnergy());
    }

  // return the classification (= fUrgent) which would have 
  // been given by the parent class G4UserStackingAction
  return G4UserStackingAction::ClassifyNewTrack(aTrack);
}


