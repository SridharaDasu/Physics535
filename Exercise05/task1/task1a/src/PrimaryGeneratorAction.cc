// $Id: PrimaryGeneratorAction.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file
 * @brief implements mandatory user class PrimaryGeneratorAction


 Definition of primary particles and their properties (spectrum
 of energies, initial vertices, ...)
*/

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

using namespace CLHEP;

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : outfile(0)
{
  //Instantiation of the General Particle Source provided 
  //by Geant4 and definition of the defaults (particle type,
  //particle energy spectrum, position distribution, 
  //angular distribution).
  gun = InitializeGPS();
  
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
  // Creating the primary vertex: The current event must be passed as argument.
  gun->GeneratePrimaryVertex(anEvent);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  // The instance of the GPS is deleted
  delete gun;
}

G4VPrimaryGenerator* PrimaryGeneratorAction::InitializeGPS()
{
  G4GeneralParticleSource * gps = new G4GeneralParticleSource();
  
  // setup details easier via UI commands see gps.mac

  // particle type
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* pion = particleTable->FindParticle("pi+");  
  gps->GetCurrentSource()->SetParticleDefinition(pion);

  // set energy distribution
  G4SPSEneDistribution *eneDist = gps->GetCurrentSource()->GetEneDist() ;
  eneDist->SetEnergyDisType("Mono"); // or gauss
  eneDist->SetMonoEnergy(2.0*GeV);

  // set position distribution
  G4SPSPosDistribution *posDist = gps->GetCurrentSource()->GetPosDist();
  posDist->SetPosDisType("Beam");  // or Point,Plane,Volume,Beam
  posDist->SetCentreCoords(G4ThreeVector(0.0*cm,0.0*cm,-80.0*cm));
  posDist->SetBeamSigmaInX(0.1*mm);
  posDist->SetBeamSigmaInY(0.1*mm);

  // set angular distribution
  G4SPSAngDistribution *angDist = gps->GetCurrentSource()->GetAngDist();
  angDist->SetParticleMomentumDirection( G4ThreeVector(0., 0., 1.) );
  //valid options are:
  // iso, cos, user, planar, beam2d, beam1d
  angDist->SetAngDistType("beam2d");
  angDist->SetBeamSigmaInAngX(0.1*mrad);
  angDist->SetBeamSigmaInAngY(0.1*mrad);
  angDist->DefineAngRefAxes("angref1",G4ThreeVector(-1.,0.,0.));

  return gps;
}

