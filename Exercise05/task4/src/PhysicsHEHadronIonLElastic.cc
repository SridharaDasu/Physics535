/**
 * @file
 * @brief Implements physics builder PhysicsHEHadronIonLElastic
 */

#include "PhysicsHEHadronIonLElastic.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4LElastic.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4HadronElasticProcess.hh"

/*!
\brief 

 PhysicsHEHadronIonElastic.cc
      protons, neutrons, pions (plus and minus),
      deuterons, tritons, alpha particles, He3 and generic ions
 
 Assembling elastic hadronic physics processes for:
 
 The considered process is G4HadronElasticProcess (for all above mentioned
 particles), and the applied model is G4LElastic, for all particles except 
 neutrons. For neutrons, two models are defined: the HP model (G4NeutronHPElastic) 
 from 0 to 20 MeV, and the G4LElastic for higher energies. A specific cross section model 
 is added for neutron elastic interactions (G4NeutronHPElasticData), which is read 
 from the G4NDL database. 
*/

PhysicsHEHadronIonLElastic::PhysicsHEHadronIonLElastic(const G4String& name): 
  G4VPhysicsConstructor(name) {

  G4cout<< "HADRONIC ELASTIC PROCESS(ES): G4HadronElasticProcess (all considered hadrons and ions)" 
        << G4endl
        << "APPLIED MODEL(S): G4LElastic" 
        << G4endl  
	<< "	       G4NeutronHPElastic (for neutrons below 20 MeV)" 
	<< G4endl;
}


PhysicsHEHadronIonLElastic::~PhysicsHEHadronIonLElastic() {

}


void PhysicsHEHadronIonLElastic::ConstructProcess() {

  G4ParticleDefinition* particle = 0;
  G4ProcessManager* processManager = 0;


  // ***************************************************
  // *** Proton, Neutron, Pion plus, Pion minus      ***
  // *** Deuteron, Triton, Alpha, He3, Generic Ion   ***
  // ***************************************************
 
  //This is the elastic process to be used for all particles but hadrons. We'll 
  //register the G4LElastic model in the full energy range. 
  G4HadronElasticProcess* hadronIonElasticProcess = 
                           new G4HadronElasticProcess("elastic-ionhadron");

  //This is the elastic process to be used for neutrons. We will register two models 
  //(G4LElastic and G4NeutronHPElastic) in two different energy ranges. A dedicated 
  //cross section model can be attached to this process, as well. Models available for 
  //a given process and a given particle can be seen at 
  //http://geant4.cern.ch/support/proc_mod_catalog/models/
  G4HadronElasticProcess* neutronElasticProcess = 
                           new G4HadronElasticProcess("elastic-neutron");

  //Define G4LElastic model for all hadrons. It is applied to the full energy range
  // (0 - 100 TeV), by default
  G4LElastic* hadronIonLElasticModel = new G4LElastic();
  
  //Define G4LElastic model for neutrons. It must be applied for energies above 20 MeV
  //Notice: it is good that the energy ranges of different models within the same process
  //slightly overlap, to allow a "smooth" matching between the two models, rather than a 
  //"step". In this case, the G4LElastic model is used from 19.8 MeV on.
  G4LElastic* neutronLElasticModel = new G4LElastic();
  neutronLElasticModel -> SetMinEnergy(19.8 * MeV);
  //Here define the G4NeutronHPElastic model (alternative). By default it is from 0 to 20 MeV,
  //because this is the coverage of the G4NDL database.
  G4NeutronHPElastic* neutronHPElasticModel = new G4NeutronHPElastic();

  //For neutrons, one can also define dedicated (and more precise) cross section data for the 
  //energy range between 0 and 20 MeV.
  G4NeutronHPElasticData* neutronHPCrossSection = new G4NeutronHPElasticData();

  //Register the LElastic model to the process for all hadrons but neutrons
  hadronIonElasticProcess -> RegisterMe(hadronIonLElasticModel); 

  //Register the two models (G4LElastic and G4NeutronHPElastic) to the neutron elastic process.
  neutronElasticProcess -> RegisterMe(neutronLElasticModel); 
  neutronElasticProcess -> RegisterMe(neutronHPElasticModel); 
  //Register also the specific cross section data set to the neutron elastic process.
  neutronElasticProcess -> AddDataSet(neutronHPCrossSection); 

  //Now we have to register the process to the process manager of particles. For each particle 
  //of interest, we retrieve the process manager, and we register the elastic process to it.
  particle = G4Proton::Proton();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess); 

  particle = G4Neutron::Neutron();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(neutronElasticProcess);
 
  particle = G4PionPlus::PionPlus(); 
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess);

  particle = G4PionMinus::PionMinus();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess); 

  particle = G4Deuteron::Deuteron();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess); 

  particle = G4Triton::Triton();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess);

  particle = G4Alpha::Alpha();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess); 

  particle = G4He3::He3();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess); 

  particle = G4GenericIon::GenericIon();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(hadronIonElasticProcess); 
}



