// $Id: EventAction.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file   EventAction.cc
 *
 * @date   17 Dec 2009
 * @author adotti
 * 
 * @brief  Implements user class EventAction.
 */

#include "EventAction.hh"
#include "G4Event.hh"
#include "Analysis.hh"

EventAction::EventAction()
{;}

//---------------------------------------------------------------

void EventAction::BeginOfEventAction(const G4Event* anEvent )
{  
  G4cout<<"Starting Event: "<<anEvent->GetEventID()<<G4endl;
  //Invoke the appropriate begin-of-event analysis 
  //procedure
  Analysis::GetInstance()->PrepareNewEvent(anEvent);
}

//---------------------------------------------------------------

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
  //Invoke the appropriate end-of-event analysis 
  //procedure
  Analysis::GetInstance()->EndOfEvent(anEvent);
}

