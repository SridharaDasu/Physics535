/**
 * @file SteppingAction.cc
 *
 * @brief Implements optional user action SteppingAction
 * Defines user actions to be performed at each tracking step
 */

#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"
#include "Analysis.hh"

SteppingAction::SteppingAction()
{;}

SteppingAction::~SteppingAction()
{;}

void SteppingAction::UserSteppingAction( const G4Step * theStep ) 
{  
  //We need to know if this step is done inside the EM calo or not.
  //We ask the PreStepPoint the volume copy number.
  //Remember: EM calo has copy num >9 and <100
  //We could have asked the volume name, but string comparison is not efficient
  const G4VTouchable* touchable = theStep->GetPreStepPoint()->GetTouchable();
  G4int volCopyNum = touchable->GetVolume()->GetCopyNo();
  //If we are in the EM calo, call the appropriate functionality in 
  //the analysis code, passing to it the actual energy deposited in 
  //the current step
  if ( volCopyNum > 9 && volCopyNum  < 100 ) //EM calo step    
    Analysis::GetInstance()->AddEDepEM( theStep->GetTotalEnergyDeposit() );    
}

