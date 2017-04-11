#ifndef PHYSICSHIPIONBERTINI_HH
#define PHYSICSHIPIONBERTINI_HH 1

/**
 * @file
 * @brief Defines physics constructor to be used in the PhysicsList.
*/

#include "G4VPhysicsConstructor.hh"

/*!
\brief
 PhysicsHIPionBertini.hh
 
 Assembling hadronic inelastic physics processes for pions (plus and minus).
 
 The considered process is G4PionXXXInelasticProcess (XXX to be replaced
 by Plus or Minus), and the applied model is the Bertini cascade. For pion
 minus particles absorption at rest is also activated 
 (G4PiMinusAbsorptionAtRest process).

 G4VPhysicsConstructor is the abstract base class for physics constructors:
*/

class PhysicsHIPionBertini : public G4VPhysicsConstructor {

 public:
  //! Constructor
   PhysicsHIPionBertini(const G4String& name = "Pion-Bertini");
  //! Destructor
   virtual ~PhysicsHIPionBertini();

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








