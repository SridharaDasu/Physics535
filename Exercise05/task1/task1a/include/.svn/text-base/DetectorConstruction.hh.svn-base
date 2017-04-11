// $Id: DetectorConstruction.hh 33 2010-01-14 17:08:18Z adotti $
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

/**
 * @file
 * @brief Defines mandatory user class DetectorConstruction.

 Setup of the detector geometry, definition of dectector properties

 This class is mandatory for setting up Geant4 simulations.

 */

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
//class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*!
\brief This mandatory user class defines the geometry.

It is responsible for
 - Definition of material, and
 - Construction of geometry

\sa Construct()
 */

//! G4VUserDetectorConstruction is the abstract base class for constructing
//! the detector:
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  //! Constructor
  DetectorConstruction();
  //! Destructor
  ~DetectorConstruction();
public:
  /** G4VUserDetectorConstruction has one pure virtual method which must be
  implemented in derived classes: Construct()
  This function is called by G4RunManager during the initialization.
  The user must implement the detector and world geometry in the overloaded
  Construct() function. The function must return the pointer to the
  physical volume of the world. 
  */

  //! Construct geometry of the setup
  G4VPhysicalVolume* Construct();

  //! \name some simple set & get functions
  //@{
  G4ThreeVector FirstSensorPosition() const  { return posFirstSensor; }
  G4ThreeVector SecondSensorPosition() const { return posSecondSensor; }
  G4ThreeVector ThirdSensorPosition() const { return posThirdSensor; }

  G4ThreeVector SetFirstSensorPosition(const G4ThreeVector & pos) { return posFirstSensor=pos; }
  G4ThreeVector SetSecondSensorPosition(const G4ThreeVector & pos) { return posSecondSensor=pos; }
  G4ThreeVector SetThirdSensorPosition(const G4ThreeVector & pos) { return posThirdSensor=pos; } 
  //@}
private:
  //! define needed materials
  void DefineMaterials();
  //! initialize geometry parameters
  void ComputeParameters();
  //! Construct geometry of the Beam Telescope
  G4VPhysicalVolume* ConstructTelescope();
  //! Construct geometry of the Electromagnetic Calorimeter
  G4VPhysicalVolume* ConstructEMCalo();
private:

  //! \name Materials
  //@{
  G4Material* air;
  G4Material* silicon;
  G4Material* vacuum;
  G4Material* pbwo4;
  //@}

  //! \name global mother volume
  //@{
  G4LogicalVolume * logicWorld;
  G4double halfWorldLength;
  //@}

  //! \name Geometry tracker
  //@{
  //! 1st telescope plane
  G4VPhysicalVolume* physiFirstSensor;
  //! 2nd telescope plane
  G4VPhysicalVolume* physiSecondSensor;
  //! 3rd telescope plane
  G4VPhysicalVolume* physiThirdSensor;
  //! subdivisions of a plane in sensor strips
  G4VPhysicalVolume * physiSensorStrip; 
  //@}

  //! \name Parameters for tracker
  //@{
  G4int noOfSensorStrips;
  G4double sensorStripLength;
  G4double sensorThickness;
  G4double teleStripPitch;
  G4ThreeVector posFirstSensor;
  G4ThreeVector posSecondSensor;
  G4ThreeVector posThirdSensor;
  //@}

  //! \name Geometry em calo
  //@{
  G4VPhysicalVolume* emCaloCentralCrystal;
  G4VPhysicalVolume* emCalo;
  //@}
  //! \name Parameters for em calo
  //@{
  G4double emCaloLength;
  G4double emCaloWidth;
  G4double emCaloCentralCrystalWidth;
  G4ThreeVector posEmCalo;
  //@}

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
