/**
 * @file
 * @brief Implements physics builder PhysicsHIProtonNeutron
 */

#include "PhysicsHIProtonNeutron.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4BinaryCascade.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4NeutronHPFission.hh"
#include "G4NeutronHPFissionData.hh"
#include "G4LFission.hh"
#include "G4LCapture.hh"

/*!
\brief
 PhysicsHIProtonNeutron.cc
 
 Assembling inelastic hadronic physics processes for protons and neutrons.
 
 The considered processes G4ProtonInelasticProcess/G4NeutronInelasticProcess.
 for protons, the G4BinaryCascade model is used. For neutrons, two models are 
 defined: a HP model (G4NeutronHPInelastic) from 0 to 20 MeV, and the 
 G4BinaryCascade at higher energy. 
 Additionally, for neutrons the G4HadronCaptureProcess (using the G4LCapture and 
 G4NeutronHPCapture models) and the G4HadronFissionProcess (using the G4LFission and 
 G4NeutronHPFission) are applied (the processes represent neutron capture neutron 
 induced fission).
 The high-precision (HP) data-driven neutron processes are used from 0 to 20 MeV.

 In addition, specific cross section models (HP) are used for the inelastic, 
 capture and fission processes between 0 and 20 MeV.
*/

PhysicsHIProtonNeutron::PhysicsHIProtonNeutron(const G4String& name): 
  G4VPhysicsConstructor(name) {

  G4cout<< "HADRONIC INELASTIC PROCESS(ES): G4XXXInelasticProcess (protons, neutrons)" 
        << G4endl
        << "APPLIED MODEL(S): G4BinaryCascade" 
        << G4endl
	<< "                and G4NeutronHPInelastic (for neutrons below 20 MeV)" 
	<< G4endl;
}


PhysicsHIProtonNeutron::~PhysicsHIProtonNeutron() {

}


void PhysicsHIProtonNeutron::ConstructProcess() {

  G4ParticleDefinition* particle = 0;
  G4ProcessManager* processManager = 0;

  // **************
  // *** Proton ***
  // **************

  //For proton inelastic process, we use only one model, G4BinaryCascade, between 0 and 10 GeV.
  //We instantiate this model here, and then we'll register to the process.
  G4double protonBinaryMinEnergy = 0. * MeV;
  G4double protonBinaryMaxEnergy = 10. * GeV;
  G4BinaryCascade* protonBinaryCascadeModel = new G4BinaryCascade();
  protonBinaryCascadeModel -> SetMinEnergy(protonBinaryMinEnergy);
  protonBinaryCascadeModel -> SetMaxEnergy(protonBinaryMaxEnergy);
  
  //This is the process handling proton inelastic interactions. It is a specific process called 
  // G4ProtonInelasticProcess. See list at:
  // http://geant4.cern.ch/support/proc_mod_catalog/processes/
  G4ProtonInelasticProcess* protonInelasticProcess = 
                           new G4ProtonInelasticProcess("inelastic-proton");

  //Register the model to the proton process
  protonInelasticProcess -> RegisterMe(protonBinaryCascadeModel);
   
  //Retrieve the proton process manager, and register the inelastic process to it.
  particle = G4Proton::Proton();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(protonInelasticProcess);


  // ***************
  // *** Neutron ***
  // ***************
  //For neutron inelastic scattering, we will register two models (G4BinaryCascade and G4NeutronHPInelastic)
  //in different energy range. The G4NeutronHPInelastic models applies from 0 to 20 MeV. As for NeutronElastic,
  //we allow for a slight overlap between the two energy ranges.
  G4double neutronBinaryMinEnergy = 19.80 * MeV;
  G4double neutronBinaryMaxEnergy = 10. * GeV;

  //Instantiate the two models here. By default, the energy range of the HP processes is 0-20 MeV, 
  //since this is the coverage of the G4NDL database
  G4NeutronHPInelastic* theHPInelasticModel = new G4NeutronHPInelastic();
  G4BinaryCascade* neutronBinaryCascadeModel = new G4BinaryCascade();
  neutronBinaryCascadeModel -> SetMinEnergy(neutronBinaryMinEnergy);
  neutronBinaryCascadeModel -> SetMaxEnergy(neutronBinaryMaxEnergy);

  // This is the process handling neutron inelastic interactions. It is a specific process called 
  // G4NeutronInelasticProcess. See list at:
  // http://geant4.cern.ch/support/proc_mod_catalog/processes/
  G4NeutronInelasticProcess* neutronInelasticProcess = 
                           new G4NeutronInelasticProcess("inelastic-neutron");
			   
  // For neutron inelastic it is also available a specialized HP cross section model (database
  // driven, from 0 to 20 MeV), that we are going to register to the process.   
  G4NeutronHPInelasticData* neutronHPInelasticCrossSection =
                                            new G4NeutronHPInelasticData();

  // Register the two models (G4NeutronHPInelastic+G4BinaryCascade) and the specialized cross 
  // section model to the neutron inelastic process
  neutronInelasticProcess -> RegisterMe(neutronBinaryCascadeModel);
  neutronInelasticProcess -> RegisterMe(theHPInelasticModel);
  neutronInelasticProcess -> AddDataSet(neutronHPInelasticCrossSection);


  //Ok, now we can do the same for processes describing capture and fission of neutrons.
  //There are not specialized processes, so we use the generic G4HadronCaptureProcess and 
  //G4HadronFissionProcess (see http://geant4.cern.ch/support/proc_mod_catalog/processes/)
  G4HadronCaptureProcess* neutronCaptureProcess = 
                           new G4HadronCaptureProcess("capture-neutron");
  G4HadronFissionProcess* neutronFissionProcess = 
                           new G4HadronFissionProcess("fission-neutron");
			   
  //As for inelastic, we'll use a dedicated HP model (G4NeutronHPCapture and 
  //G4NeutronHPFission) between 0 and 20 MeV, and a generic model (G4LCapture and 
  //G4LFission) at higher energy. As before, we allow for a slight overlap of the two 
  //energy ranges.
  //Specialezed neutron cross section data (from G4NDL) are available, and we'll register 
  //them to the process (G4NeutronHPFissionData and G4NeutronHPCaptureData)
  G4double neutronCaptureFissionMinEnergy = 19.8 * MeV;
  G4double neutronCaptureFissionMaxEnergy = 100. * TeV;

  G4LCapture* neutronLCaptureModel = new G4LCapture();
  neutronLCaptureModel -> SetMinEnergy(neutronCaptureFissionMinEnergy);
  neutronLCaptureModel -> SetMaxEnergy(neutronCaptureFissionMaxEnergy);

  G4LFission* neutronLFissionModel = new G4LFission();
  neutronLFissionModel -> SetMinEnergy(neutronCaptureFissionMinEnergy);
  neutronLFissionModel -> SetMaxEnergy(neutronCaptureFissionMaxEnergy);

  G4NeutronHPFission* neutronHPFissionModel = new G4NeutronHPFission();
  G4NeutronHPCapture* neutronHPCaptureModel = new G4NeutronHPCapture();

  //Here are the dedicated cross section models
  G4NeutronHPCaptureData* neutronHPCaptureCrossSection = 
                                               new G4NeutronHPCaptureData();
  G4NeutronHPFissionData* neutronHPFissionCrossSection = 
                                               new G4NeutronHPFissionData();

  //Models and cross sections are registered to the corresponding process
  neutronCaptureProcess -> RegisterMe(neutronLCaptureModel);
  neutronCaptureProcess -> RegisterMe(neutronHPCaptureModel);
  neutronCaptureProcess -> AddDataSet(neutronHPCaptureCrossSection);
  neutronFissionProcess -> RegisterMe(neutronLFissionModel); 
  neutronFissionProcess -> RegisterMe(neutronHPFissionModel); 
  neutronFissionProcess -> AddDataSet(neutronHPFissionCrossSection);

  //Finally, retrieve the process manager for the neutron, and register the three 
  //processes that we have just defined, namely inelastic scattering, capture and 
  //fission.
  particle = G4Neutron::Neutron();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(neutronInelasticProcess);
  processManager -> AddDiscreteProcess(neutronCaptureProcess); 
  processManager -> AddDiscreteProcess(neutronFissionProcess);   

  //Done!
}



