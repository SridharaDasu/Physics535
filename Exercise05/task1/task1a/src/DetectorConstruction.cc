// G.A.P.Cirrone, May 2012

/**
 * @file
 * @brief Implements mandatory user class DetectorConstruction.
 */

#include "DetectorConstruction.hh"
//#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Isotope.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4NistManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"

using namespace CLHEP;

DetectorConstruction::DetectorConstruction() : 
  pbwo4(0)
{
  //--------- Material definition ---------
  DefineMaterials();
  
  //--------- Sizes of the principal geometrical components (solids)  ---------
  ComputeParameters();
}
 
DetectorConstruction::~DetectorConstruction()
{;}
 
void DetectorConstruction::DefineMaterials() 
{
  //Get Materials from NIST database
  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(0);

  // define NIST materials
  vacuum  = man->FindOrBuildMaterial("G4_Galactic");

  // These are the materials used for the tracker. 
  // "air" and "silicon" are G4Material* and defined as 
  // private members of the class.
  air     = man->FindOrBuildMaterial("G4_AIR");
  silicon = man->FindOrBuildMaterial("G4_Si");
  
  //---------------------------------------------------------------------
  // Exercise 1a.1: create a custom material
  // Em calo
  // Oxygen element is added for you
  G4double a; //mass of a mole
  a=16*g/mole;
  G4Element* elO = new G4Element("Oxygen",//Oxygen
				 "O",//Symbol
				 8,  // Z
				 a ); //mass of a mole

  //Add Pb and W and create the material

  a=183.84*g/mole;
  G4Element* elW = new G4Element("Tungsten","W",74,a);
   
  a=207.20*g/mole;
  G4Element* elPb = new G4Element("Lead","Pb",82,a);
  
  G4double density = 8.280*g/cm3;
  G4Material* myPbwo4 = new G4Material("PbWO4",//name
			 density,//density
			 3);//number of elements
  myPbwo4->AddElement(elPb,1);
  myPbwo4->AddElement(elW,1);
  myPbwo4->AddElement(elO,4);

//---------------------------------------------------------------------
  // Exercise 1a.2: use NIST manager
  //Hint: the NIST name is G4_PbWO4
  //To use the NIST manager see examples from Tracker materials

  pbwo4 = man->FindOrBuildMaterial("G4_PbWO4");

  //---------------------------------------------------------------------
  //  Exercise 1a.3 : Create a material starting from isotopes
  // 
  // Here is the first isotope
  //define others by yourself!
  G4String name,symbol;
  G4double abundance;
  G4int nIsotopes,natoms;
   
  //Define isotopes
  G4Isotope* Ge72 = new G4Isotope(name="Ge72",  32, 72, 71.92*g/mole);
  G4Isotope* Ge73 = new G4Isotope(name="Ge73",  32, 73, 73.0*g/mole);
  G4Isotope* Ge74 = new G4Isotope(name="Ge74",  32, 74, 74.0*g/mole);
  G4Isotope* Ge76 = new G4Isotope(name="Ge76",  32, 76, 76.0*g/mole);
   
  //Define element from isotopes
  G4Element* elGeEnr = new G4Element(name="enrichedGermanium",
                                     symbol="GeEnr",nIsotopes=4);
  elGeEnr->AddIsotope(Ge72,abundance= 0.1*perCent);
  elGeEnr->AddIsotope(Ge73,abundance= 0.2*perCent);
  elGeEnr->AddIsotope(Ge74,abundance= 13.1*perCent);
  elGeEnr->AddIsotope(Ge76,abundance= 86.6*perCent);
   
  //Print the material table
  G4cout<<*(G4Material::GetMaterialTable()) <<G4endl;
}
 
void DetectorConstruction::ComputeParameters() 
{
  //This function defines the defaults
  //of the geometry construction

  // ** world **
  halfWorldLength = 5* m;

  // ** em calo **
  emCaloCentralCrystalWidth = 22*mm;
  emCaloWidth               = 110*mm;
  emCaloLength              = 230*mm;
  posEmCalo = -G4ThreeVector(0,0,emCaloLength/2);

  // ** Si tracker **
  noOfSensorStrips = 600;//48;
  sensorStripLength = 10.*mm;
  sensorThickness = 300.*um;
  teleStripPitch  = 80*um;//20. * um;
  posFirstSensor  = G4ThreeVector(0., 0., -190*mm - emCaloLength);
  posSecondSensor = G4ThreeVector(0., 0., -100*mm - emCaloLength);
  posThirdSensor  = G4ThreeVector(0., 0., -10.*mm - emCaloLength);

}
 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //This function is called by G4 when the detector has to be created
  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  
  // The geometry of this exercise is the following: 
  // --> A World volume containing the whole geometry
  // --> Three Silicum planes (strip detector acting as tracker)
  // --> An electromagnetic calorimeter

  //---------------------------------------------------------------------
  //First construct the world volume
  //---------------------------------------------------------------------

  //------------------------------
  // World
  //------------------------------
 
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(2.*halfWorldLength);
  G4cout << "Computed tolerance = "
	 << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
	 << " mm" << G4endl;


  G4Box * solidWorld= new G4Box("world",halfWorldLength,halfWorldLength,halfWorldLength);
  logicWorld= new G4LogicalVolume( solidWorld, air, "World", 0, 0, 0);
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  //
  G4VPhysicalVolume * physiWorld = new G4PVPlacement(0,               // no rotation
						     G4ThreeVector(), // at (0,0,0)
						     logicWorld,      // its logical volume
						     "World",         // its name
						     0,               // its mother  volume
						     false,           // no boolean operations
						     0);              // copy number
				 


  //Construction of the three si plane is actually done here
  ConstructTelescope();

  //Construction of the EM calorimeter
  ConstructEMCalo();

  //--------- Visualization attributes -------------------------------
  G4Color
    green(0.0,1.0,0.0),
    blue(0.0,0.0,1.0),
    brown(0.4,0.4,0.1),
    white(1.0,1.0,1.0);

  //world volume is invisible
  logicWorld -> SetVisAttributes(G4VisAttributes::Invisible);
    
  //always return the physical World
  //
  return physiWorld;
}

G4VPhysicalVolume* DetectorConstruction::ConstructTelescope()
{
  //This is an "helper" method to construct the 3 silicon planes. The method 
  //is called by Construct(), which is the mandatory member of the 
  //user detector construction.

  
  //
  // 1st Plane of Si tracker
  //
  // one: define solid
  G4double halfSensorSizeX = noOfSensorStrips*teleStripPitch/2.;
  G4double halfSensorSizeY = sensorStripLength/2.;
  G4double halfSensorSizeZ = sensorThickness/2.;

  G4Box * solidSensor = new G4Box("Sensor",
				  halfSensorSizeX,halfSensorSizeY,halfSensorSizeZ);
  //two: define logical volume
  G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor, // its solid
							   silicon,	//its material
							   "SensorPlane");	//its name
  //three: define the physical volume (= placed logical volume)
  physiFirstSensor = new G4PVPlacement(0,	//no rotation
				       posFirstSensor,
				       logicSensorPlane,		//its logical volume
				       "FirstSensor",		//its name
				       logicWorld,		//its mother  volume
				       false,			//no boolean operation
				       0);			//copy number


  //Now it comes the fun: the three planes are identical, differing only for 
  //the position: you can place three times the same logical volume, just 
  //changing the position (and the copy number)

  // 2nd Plane of Si tracker
  physiSecondSensor = new G4PVPlacement(0,//rm,
					posSecondSensor,
					logicSensorPlane,
					"SecondSensor",
					logicWorld,
					false,
					1);			//copy number

  // 3rd Plane of Si tracker
  physiThirdSensor = new G4PVPlacement(0,
				       posThirdSensor,
				       logicSensorPlane,
				       "ThirdSensor",
				       logicWorld,
				       false,
				       2);			//copy number

  //
  // Strips
  //
  //Note that we use G4VReplica giving as logical volume
  //the logicSensorPlane as mother. This ensures that three
  //replicas will exists, one for each physical volume where
  //logicSensorPlane is used: the Si planes
  G4double halfSensorStripSizeX = teleStripPitch/2.;
  G4double halfSensorStripSizeY = sensorStripLength/2.;
  G4double halfSensorStripSizeZ = sensorThickness/2.;

  G4Box * solidSensorStrip =
    new G4Box("SensorStrip",
	      halfSensorStripSizeX,halfSensorStripSizeY,halfSensorStripSizeZ);

  G4LogicalVolume * logicSensorStrip =
    new G4LogicalVolume(solidSensorStrip,silicon,"SensorStrip");

  physiSensorStrip = new G4PVReplica("SensorStrip",		//its name
				     logicSensorStrip,		//its logical volume
				     logicSensorPlane,		//its mother
				     kXAxis,		        //axis of replication
				     noOfSensorStrips,		//number of replica
				     teleStripPitch);	        //witdth of replica

  G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0);
  //the plane is yellow, the strips are red
  logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
  logicSensorStrip -> SetVisAttributes(new G4VisAttributes(red));

  return physiSecondSensor;
}


G4VPhysicalVolume* DetectorConstruction::ConstructEMCalo()
{
  //This is an "helper" method to construct the EM calorimeter. The method 
  //is called by Construct(), which is the mandatory member of the 
  //user detector construction.

  //dimensions are originally defined in ComputeParameters()

  //First the main body 
  G4double halfEmCaloSizeX = emCaloWidth/2;
  G4double halfEmCaloSizeY = emCaloWidth/2;
  G4double halfEmCaloSizeZ = emCaloLength/2;
  G4double halfEmCentralSizeX = emCaloCentralCrystalWidth/2;
  G4double halfEmCentralSizeY = emCaloCentralCrystalWidth/2;

  //1) solid
  G4Box* emSolid = new G4Box("emCaloSolid",halfEmCaloSizeX,halfEmCaloSizeY,halfEmCaloSizeZ);
  //2) logical volume
  if (!pbwo4)
    {
      G4cout << "Material PbWO4 is not defined. Please define it!" << G4endl;
      G4Exception("DetectorConstruction::ConstructEMCalo()", "task1a01", FatalException, "Run abort");
    }

  G4LogicalVolume* emLogic = new G4LogicalVolume( emSolid,//its solid
						  pbwo4, //its material
						  "emCaloLogic");//its name
  //3) physical volume
  emCalo = new G4PVPlacement(0, //no rotation
			     posEmCalo,//translation
			     emLogic, //its logical volume
			     "EmCalo",//its name
			     logicWorld,//its mother volume
			     false, //no boolean operation
			     10); //copy number

  //Define here the central part: notice this is a dauthgter volume of
  //emLogic
  G4Box* emCentralSolid=new G4Box("emCentralSolid",halfEmCentralSizeX,halfEmCentralSizeY,halfEmCaloSizeZ);
  G4LogicalVolume* emCentralLogic = new G4LogicalVolume( emCentralSolid,pbwo4,"emCentralLogic");
  emCaloCentralCrystal = new G4PVPlacement( 0 ,//no rotation
					    G4ThreeVector(0,0,0), //translation
					    emCentralLogic , // its logical volume
					    "EmCentral", //its name
					    emLogic , //mother logical volume
					    false, //no boolean operation 
					    11); //copy number

  //central body is red, the rest is yellow
  G4Color yellow(1,1,0);
  emLogic->SetVisAttributes(new G4VisAttributes(yellow)); 
  G4Color red(1,0,0);
  emCentralLogic->SetVisAttributes(new G4VisAttributes(red));
  return emCalo;
}

