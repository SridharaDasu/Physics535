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


void EventAction::BeginOfEventAction(const G4Event* anEvent )
{
  // The event ID is printed at the beginning of each event
  G4cout<<"Starting Event: "<<anEvent->GetEventID()<<G4endl;
  // Invoke the appropriate functionality of the Analysis
  // at the beginning of each event
  Analysis::GetInstance()->PrepareNewEvent(anEvent);
}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
  // Invoke the appropriate functionality of the Analysis
  // at the end of each event
  Analysis::GetInstance()->EndOfEvent(anEvent);
}

