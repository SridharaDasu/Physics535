// $Id: HadCaloHit.cc 100 2010-01-26 16:12:59Z adotti $
/**
 * @file
 * @brief Implementation of user class HadCaloHit.
*/

#include "HadCaloHit.hh"
#include "G4UnitsTable.hh"
// -- one more nasty trick for new and delete operator overloading:
G4Allocator<HadCaloHit> HadCaloHitAllocator;

//Does just initialization of the two members: layerID and energy
HadCaloHit::HadCaloHit(const G4int layer) :
  layerNumber(layer),
  eDep(0)
{;}

HadCaloHit::~HadCaloHit()
{;}

void HadCaloHit::Print()
{
  //---------------------
  // Exercise 2 of task 5b
  //---------------------
  //Add some print out on screen: layer number and energy deposited
}
