#ifndef PHYSICSHIPROTONNEUTRON_HH
#define PHYSICSHIPROTONNEUTRON_HH 1

/**
 * @file
 * @brief Defines physics constructor to be used in the PhysicsList.
*/

#include "G4VPhysicsConstructor.hh"

/*! 
\brief
PhysicsHIProtonNeutron.hh
 
Assembling inelastic hadronic physics processes for protons and neutrons.
 
The considered processes G4ProtonInelasticProcess/G4NeutronInelasticProcess
where the G4BinaryCascade model is used. Additionally, for neutrons the
G4HadronCaptureProcess (using the G4LCapture model) and the 
G4HadronFissionProcess (using the G4LFission model) are applied (the 
processes represent neutron capture neutron induced fission).

G4VPhysicsConstructor is the abstract base class for physics constructors:
*/

class PhysicsHIProtonNeutron : public G4VPhysicsConstructor {

 public:
  //! Constructor
  PhysicsHIProtonNeutron(const G4String& name = "ProtonNeutron-inelastic");
  //! Destructor
  virtual ~PhysicsHIProtonNeutron();

  //! G4VPhysicsConstructor has two pure virtual methods which must be 
  //! implemented by the user: ConstructParticle and ConstructProcess.
  //! Since only physics processes are dealt with here, ConstructParticle
  //! is irrelevant and performs no action. ConstructProcess is used to
  //! instantiate all physics processes relevant for the considered particle
  //! and type of interaction.

  //@{
  //! Constructs particles (empty)
   void ConstructParticle() { };
  //!Construct physics processes
   void ConstructProcess();
  //@}

};

#endif








