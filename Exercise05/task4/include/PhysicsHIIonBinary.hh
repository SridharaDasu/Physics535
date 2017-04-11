#ifndef PHYSICSHIIONBINARY_HH
#define PHYSICSHIIONBINARY_HH 1

/**
 * @file
 * @brief Defines physics constructor to be used in the PhysicsList.
*/

#include "G4VPhysicsConstructor.hh"

/*!
\brief 

 PhysicsHIIonBinary.hh
 
 Assembling hadronic inelastic physics processes for:
      deuterons, tritons, alpha particles
 
 The considered process is G4XXXInelasticProcess (XXX to be replaced by 
 the particular ion name), and the applied model is G4BinaryLightIonReaction

 G4VPhysicsConstructor is the abstract base class for physics constructors:
*/

class PhysicsHIIonBinary : public G4VPhysicsConstructor {

 public:
  //! Constructor
  PhysicsHIIonBinary(const G4String& name = "Ion-Binary");
  //! Destructor
  virtual ~PhysicsHIIonBinary();

 
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








