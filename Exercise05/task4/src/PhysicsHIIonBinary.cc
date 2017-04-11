/**
 * @file
 * @brief Implements physics builder PhysicsHIIonBinary
 */

#include "PhysicsHIIonBinary.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4TripathiCrossSection.hh"
#include "G4IonsShenCrossSection.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4LEDeuteronInelastic.hh"
#include "G4LETritonInelastic.hh"
#include "G4LEAlphaInelastic.hh"

/*!
\brief
 
 PhysicsHIIonBinary.cc
 
 Assembling hadronic inelastic physics processes for:
      deuterons, tritons, alpha particles
 
 The considered process is G4XXXInelasticProcess (XXX to be replaced by 
 the particular ion name), and the applied model is G4BinaryLightIonReaction
*/

PhysicsHIIonBinary::PhysicsHIIonBinary(const G4String& name): 
  G4VPhysicsConstructor(name) {

  G4cout<< "HADRONIC INELASTIC PROCESS(ES): G4XXXInelasticProcess (all ions)" 
        << G4endl
        << "APPLIED MODEL(S): G4BinaryLightIonReaction" 
        << G4endl;
}


PhysicsHIIonBinary::~PhysicsHIIonBinary() { 

}


void PhysicsHIIonBinary::ConstructProcess() {

  G4ParticleDefinition* particle = 0;
  G4ProcessManager* processManager = 0;

   
  // ***************************************************
  // *** Deuteron, Triton, Alpha: Common Definitions ***
  // ***************************************************

  G4double ionLEPMaxEnergy = 100. * MeV;
  G4double ionBinaryMinEnergy = 99. * MeV;
  G4double ionBinaryMaxEnergy = 10. * GeV;
 
  G4BinaryLightIonReaction* ionBinaryModel = new G4BinaryLightIonReaction;
  ionBinaryModel -> SetMinEnergy(ionBinaryMinEnergy);
  ionBinaryModel -> SetMaxEnergy(ionBinaryMaxEnergy);

  G4TripathiCrossSection* ionTripathiCrossSection = new G4TripathiCrossSection;
  G4IonsShenCrossSection* ionShenCrossSection = new G4IonsShenCrossSection;

  // ****************
  // *** Deuteron ***
  // ****************

  G4DeuteronInelasticProcess* deuteronInelasticProcess = 
                       new G4DeuteronInelasticProcess("inelastic-deuteron");

  G4LEDeuteronInelastic* deuteronLEPModel = new G4LEDeuteronInelastic;
  deuteronLEPModel -> SetMaxEnergy(ionLEPMaxEnergy);

  deuteronInelasticProcess -> AddDataSet(ionTripathiCrossSection);
  deuteronInelasticProcess -> AddDataSet(ionShenCrossSection);
  deuteronInelasticProcess -> RegisterMe(deuteronLEPModel);
  deuteronInelasticProcess -> RegisterMe(ionBinaryModel);

  particle = G4Deuteron::Deuteron();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(deuteronInelasticProcess);


  // **************
  // *** Triton ***
  // **************

  G4TritonInelasticProcess* tritonInelasticProcess = 
                              new G4TritonInelasticProcess("inelastic-triton");
  
  G4LETritonInelastic* tritonLEPModel = new G4LETritonInelastic;
  tritonLEPModel -> SetMaxEnergy(ionLEPMaxEnergy);

  tritonInelasticProcess -> AddDataSet(ionTripathiCrossSection);
  tritonInelasticProcess -> AddDataSet(ionShenCrossSection);
  tritonInelasticProcess -> RegisterMe(tritonLEPModel);
  tritonInelasticProcess -> RegisterMe(ionBinaryModel);

  particle = G4Triton::Triton();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(tritonInelasticProcess);
 

  // *************
  // *** Alpha ***
  // *************

  G4AlphaInelasticProcess* alphaInelasticProcess = 
                              new G4AlphaInelasticProcess("inelastic-alpha");

  G4LEAlphaInelastic* alphaLEPModel = new G4LEAlphaInelastic;
  alphaLEPModel -> SetMaxEnergy(ionLEPMaxEnergy);
 
  alphaInelasticProcess -> AddDataSet(ionTripathiCrossSection);
  alphaInelasticProcess -> AddDataSet(ionShenCrossSection);
  alphaInelasticProcess -> RegisterMe(alphaLEPModel);
  alphaInelasticProcess -> RegisterMe(ionBinaryModel);

  particle = G4Alpha::Alpha();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(alphaInelasticProcess); 
}



