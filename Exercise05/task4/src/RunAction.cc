// $Id: RunAction.cc 102 2010-01-26 16:45:56Z adotti $
/**
 * @file   RunAction.cc
 *
 * @date   17 Dec 2009
 * @author adotti
 *
 * @brief  Implements user class RunAction.
 * Defining actions performed at the beginning and/or the end of each run
 */

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"


RunAction::RunAction()
{;}

void RunAction::BeginOfRunAction(const G4Run* aRun )
{
  // The run ID is printed at the beginning of each run
  G4cout<<"Starting Run: "<<aRun->GetRunID()<<G4endl;
  // Invoke the appropriate functionality of the Analysis
  // at the beginning of each run
  Analysis::GetInstance()->PrepareNewRun(aRun);
}

void RunAction::EndOfRunAction( const G4Run* aRun )
{
  // Invoke the appropriate functionality of the Analysis
  // at the end of each run
  Analysis::GetInstance()->EndOfRun(aRun);
}
