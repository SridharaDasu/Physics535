// $Id: PhysicsList.hh 22 2009-12-22 12:36:46Z schaelic $

#ifndef PhysicsList_h
#define PhysicsList_h 1

/**
 * @file
 * @brief Defines mandatory user class PhysicsList.
*/

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4VPhysicsConstructor;

/*!
\brief This mandatory user class provides the physics

It is responsible for
 - Definition of particles
 - Construction of physics processes
 - setting of user cuts

Here a modular physics list is used. Modules can be either 
taken from Geant4 (ready-for-the-use) or written by 
the user.

\sa ConstructParticle(), ConstructProcess(), SetCuts()
*/
class PhysicsList: public G4VUserPhysicsList
{
public:
  //! Constructor
  PhysicsList();
  //! Destructor
  ~PhysicsList();

protected:
  //! Construct particle and physics (mandatory)
  //@{
  //! Construct particles
  void ConstructParticle();
  //! Construct physics processes
  void ConstructProcess();
  //! Define user cuts
  void SetCuts();
  //@}
private:
 
  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor* heHadronIon;
  G4VPhysicsConstructor* hiPion;
  G4VPhysicsConstructor* hiIon;
  G4VPhysicsConstructor* hiProtonNeutron;
  G4VPhysicsConstructor* particles;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

 
