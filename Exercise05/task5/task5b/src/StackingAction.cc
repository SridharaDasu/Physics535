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


StackingAction::StackingAction()
{;}


StackingAction::~StackingAction() {
}


G4ClassificationOfNewTrack 
StackingAction::ClassifyNewTrack( const G4Track * aTrack ) 
{
  if ( aTrack->GetParentID() > 0 )//This is a secondary
    Analysis::GetInstance()->AddSecondary(1);
  

  return G4UserStackingAction::ClassifyNewTrack(aTrack);
}


