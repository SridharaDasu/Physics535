// $Id: RunAction.cc 102 2010-01-26 16:45:56Z adotti $
/**
 * @file   RunAction.cc
 *
 * @date   17 Dec 2009
 * @author adotti
 *
 * @brief  Implements user class RunAction.
 */

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"

RunAction::RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* aRun )
{
  G4cout<<"Starting Run: "<<aRun->GetRunID()<<G4endl;
  //Invoke the appropriate begin-of-run analysis 
  //procedure
  Analysis::GetInstance()->PrepareNewRun(aRun);
}

void RunAction::EndOfRunAction( const G4Run* aRun )
{
  //Invoke the appropriate end-of-run analysis 
  //procedure
  Analysis::GetInstance()->EndOfRun(aRun);
}
