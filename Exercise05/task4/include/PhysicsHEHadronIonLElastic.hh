#ifndef PHYSICSHEHADRONIONLELASTIC_HH
#define PHYSICSHEHADRONIONLELASTIC_HH 1

/**
 * @file
 * @brief Defines physics constructor to be used in the PhysicsList.
*/

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

/*! 
\brief

 PhysicsHEHadronIonElastic.hh
      protons, neutrons, pions (plus and minus),
      deuterons, tritons, alpha particles, He3 and generic ions
 
 Assembling elastic hadronic physics processes for:
 
 The considered process is G4HadronElasticProcess (for all above mentioned
 particles), and the applied model is G4LElastic (for all particles).

G4VPhysicsConstructor is the abstract base class for physics constructors:
*/

class PhysicsHEHadronIonLElastic : public G4VPhysicsConstructor {

 public:
  //! Constructor
   PhysicsHEHadronIonLElastic(const G4String& name = "HadronIon-LElastic");
  //! Destructor
  virtual ~PhysicsHEHadronIonLElastic();

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








