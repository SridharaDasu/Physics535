// $Id: PhysicsList.cc 98 2010-01-26 15:59:09Z vnivanch $
/**
 * @file
 * @brief Implements mandatory user class PhysicsList.
 */

#include "globals.hh"
#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4LossTableManager.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

#include "G4DecayTable.hh"
#include "G4Decay.hh"
#include "G4DecayWithSpin.hh"
#include "G4MuonDecayChannelWithSpin.hh"
#include "G4MuonRadiativeDecayChannelWithSpin.hh"

#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"


#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"




PhysicsList::PhysicsList():  G4VUserPhysicsList()
{
  defaultCutValue = 1.0*mm;
  SetVerboseLevel(1);
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

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  

  // ********************************************************************************
  // Task 3.b - Exercise 3.4
  //   - add particle definitions for mu+ and mu- here
  // ********************************************************************************
  //G4MuonPlus::MuonPlusDefinition();
  //G4MuonMinus::MuonMinusDefinition();

  /*
    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
  */
  // gamma
  G4Gamma::Gamma();

  // mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();

}

void PhysicsList::ConstructProcess()
{
  AddTransportation();

  ConstructEM();
  ConstructDecay();
}

void PhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    // ********************************************************************************
    // Task 3.b - Exercise 5 
    //  - Add the following discrete processes to the gamma:
    //    G4ComptonScattering, G4GammaConversion  
    // ********************************************************************************
    

    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      //..................................
      // .................................
      
    } 
     
    
    
  }
}

void PhysicsList::ConstructDecay()
{;}
  
void PhysicsList::SetCuts()
{
  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  //
  SetCutsWithDefault();
     
  if (verboseLevel>0) DumpCutValuesTable();
}

