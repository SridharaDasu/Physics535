// $Id: PhysicsList.cc 98 2010-01-26 15:59:09Z vnivanch $
/**
 * @file
 * @brief Implements mandatory user class PhysicsList.
 */

#include "PhysicsList.hh"
#include "Particles.hh"

#include "PhysicsHEHadronIonLElastic.hh"
#include "PhysicsHIPionBertini.hh"
#include "PhysicsHIIonBinary.hh"
#include "PhysicsHIProtonNeutron.hh"

#include "G4EmStandardPhysics.hh"
#include "G4LossTableManager.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

PhysicsList::PhysicsList():  G4VUserPhysicsList()
{

  defaultCutValue = 1.0*mm;
  SetVerboseLevel(1);
  //Here the EM physics comes from Geant4 (G4xxx)
  emPhysicsList = new G4EmStandardPhysics();
  
  //Other physics builders are produced by the user
  //(of course, one could have used something from 
  // G4).

  //Elastic scattering of hadrons
  heHadronIon = new PhysicsHEHadronIonLElastic();

  //Inelastic scattering of pions
  hiPion = new PhysicsHIPionBertini();

  //Inelastic scattering of ions
  hiIon = new PhysicsHIIonBinary();

  //Inelastic scattering of nucleons
  hiProtonNeutron = new PhysicsHIProtonNeutron();

  //Particle definition
  particles = new Particles();
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // define all particles in one shot
  particles->ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();

  //Em physics
  emPhysicsList->ConstructProcess();

  //Elastic scattering of hadrons
  heHadronIon->ConstructProcess();

  //Inelastic scattering of pions
  hiPion->ConstructProcess();

  //Inelastic scattering of ions
  hiIon->ConstructProcess();

  //Inelastic scattering of nucleons
  hiProtonNeutron->ConstructProcess();

}

void PhysicsList::SetCuts()
{
  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  //
  SetCutsWithDefault();

     
  if (verboseLevel>0) DumpCutValuesTable();
}

