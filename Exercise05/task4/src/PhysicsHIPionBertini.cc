/**
 * @file
 * @brief Implements physics builder PhysicsHIPionBertini
 */

#include "PhysicsHIPionBertini.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PionPlusInelasticProcess.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4CascadeInterface.hh"
#include "G4PiMinusAbsorptionAtRest.hh"
#include "G4PiNuclearCrossSection.hh" 

/*!
\brief

 PhysicsHIPionBertini.cc
 
 Assembling hadronic inelastic physics processes for pions (plus and minus).
 
 The considered process is G4PionXXXInelasticProcess (XXX to be replaced
 by Plus or Minus), and the applied model is G4CascadeInterface 
 (namely, Bertini cascade). For pion
 minus particles absorption at rest is also activated 
 (G4PiMinusAbsorptionAtRest process).
*/


PhysicsHIPionBertini::PhysicsHIPionBertini(const G4String& name): 
  G4VPhysicsConstructor(name) {

  G4cout<< "HADRONIC INELASTIC PROCESS(ES): G4PionXXXInelasticProcess (pions+/-)" 
        << G4endl
        << "APPLIED MODEL(S): Bertini Cascade" 
        << G4endl;
}


PhysicsHIPionBertini::~PhysicsHIPionBertini() {

}


void PhysicsHIPionBertini::ConstructProcess() {

  G4ParticleDefinition* particle = 0;
  G4ProcessManager* processManager = 0;


  // ***********************************
  // *** Pion+/-: Common Definitions ***
  // ***********************************

  G4double pionBertiniMinEnergy = 0. * MeV;
  G4double pionBertiniMaxEnergy = 10. * GeV;

  G4CascadeInterface* pionBertiniCascadeModel = new G4CascadeInterface();
  pionBertiniCascadeModel -> SetMinEnergy(pionBertiniMinEnergy);
  pionBertiniCascadeModel -> SetMaxEnergy(pionBertiniMaxEnergy);

  G4PiNuclearCrossSection* pionNuclearCrossSection = 
                  new G4PiNuclearCrossSection();

  // *************
  // *** Pion+ ***
  // *************

  G4PionPlusInelasticProcess* pionPlusInelasticProcess = 
                  new G4PionPlusInelasticProcess("inelastic-pionplus");

  pionPlusInelasticProcess -> AddDataSet(pionNuclearCrossSection);
  pionPlusInelasticProcess -> RegisterMe(pionBertiniCascadeModel);
 
  particle = G4PionPlus::PionPlus(); 
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(pionPlusInelasticProcess);
 
 
  // **************
  // *** Pion-  ***
  // **************

  G4PionMinusInelasticProcess* pionMinusInelasticProcess = 
                     new G4PionMinusInelasticProcess("inelastic-pionminus");
  G4PiMinusAbsorptionAtRest* pionMinusAbsAtRestProcess = 
                     new G4PiMinusAbsorptionAtRest();

  pionMinusInelasticProcess -> AddDataSet(pionNuclearCrossSection);
  pionMinusInelasticProcess -> RegisterMe(pionBertiniCascadeModel);

  particle = G4PionMinus::PionMinus();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(pionMinusInelasticProcess);
  processManager -> AddRestProcess(pionMinusAbsAtRestProcess);
}



