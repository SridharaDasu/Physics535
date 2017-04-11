/**
 * @file   StackingAction.cc
 *
 * @date   17 Dec 2009
 * @author adotti
 *
 * @brief  Implements user class StackingAction.
 */

#include "StackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "Analysis.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"


StackingAction::StackingAction()
{;}


StackingAction::~StackingAction() 
{;}


G4ClassificationOfNewTrack 
StackingAction::ClassifyNewTrack( const G4Track * aTrack ) {
  Analysis* analysis = Analysis::GetInstance();
  if ( aTrack->GetParentID() > 0 )//This is a secondary  
    analysis->AddSecondary(1);
  
  return G4UserStackingAction::ClassifyNewTrack(aTrack);

}


