#ifndef PARTICLES_HH
#define PARTICLES_HH 1

/**
 * @file
 * @brief Defines physics constructor to be used in the PhysicsList.
*/

#include "G4VPhysicsConstructor.hh"

/*!
\brief
Particles.hh
 
Constructing particles used in the simulation.
G4VPhysicsConstructor is the abstract base class for physics constructors:
*/

class Particles : public G4VPhysicsConstructor {

 public: 
  //! Constructor
  Particles(const G4String& name = "Particles");
  //! Destructor
  virtual ~Particles();
 
  //! G4VPhysicsConstructor has two pure virtual methods which must be 
  //! implemented by the user: ConstructParticle and ConstructProcess.
  //! Since only physics processes are dealt with here, ConstructParticle
  //! is irrelevant and performs no action. ConstructProcess is used to
  //! instantiate all physics processes relevant for the considered particle
  //! and type of interaction.
  //@{
  //! Constructs particles 
  void ConstructParticle();
  //! Construct physics processes (empty)
  void ConstructProcess() { }; 
  //@}
};

#endif // PARTICLES_HH








