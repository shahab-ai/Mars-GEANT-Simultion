//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm4/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
//
//
// $Id: PrimaryGeneratorAction.cc 67268 2013-02-13 11:38:40Z ihrivnac $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic

  G4ParticleDefinition* particle
    //    = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));

  fParticleGun->SetParticleEnergy(1*GeV);
  //fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));

  InitFunction();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event
  //
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  //const G4double twopi = 360.*degree; //3.14159265358979;
  //const G4double pi = 180.*degree; //1.5707963267949;

  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("WorldLV");
  G4Box* worldBox = 0;
  if ( worldLV) worldBox = dynamic_cast< G4Box*>(worldLV->GetSolid());
  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("GMBPrimaryGeneratorAction::GeneratePrimaries()","MyCode0002",JustWarning,msg);
  }

  //fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., worldZHalfLength));

  G4double posphi = twopi*G4UniformRand();
  G4double postheta = pi*G4UniformRand()/8.;
  fParticleGun->SetParticlePosition(G4ThreeVector(worldZHalfLength*std::sin(postheta)*std::cos(posphi), worldZHalfLength*std::sin(postheta)*std::sin(posphi), worldZHalfLength*std::cos(postheta)));


  //
  //distribution uniform in solid angle
  //
  //G4double cosTheta = 2*G4UniformRand() - 1.; // isotrope
  G4double cosTheta = -G4UniformRand();  // forward hemisphere
  //G4double cosTheta = -1.;                 // forward
  //G4double cosTheta = 1. - 2*G4UniformRand(); // isotrope
  G4double  phi = twopi*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
           uy = sinTheta*std::sin(phi),
           uz = cosTheta;

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));


  G4double energy = InverseCumul();
  fParticleGun->SetParticleEnergy(energy);



  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::InitFunction()
{
  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("WorldLV");
  G4Box* worldBox = 0;
  if ( worldLV) worldBox = dynamic_cast< G4Box*>(worldLV->GetSolid());
  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("GMBPrimaryGeneratorAction::GeneratePrimaries()","MyCode0002",JustWarning,msg);
  }

  // tabulated function
  // f is assumed positive, linear per segment, continuous
  //
  nPoints = 46;
  const G4double xx[] =
        { 10*MeV, 20*MeV, 30*MeV, 40*MeV, 50*MeV, 60*MeV, 70*MeV, 80*MeV, 90*MeV,
          100*MeV, 200*MeV, 300*MeV, 400*MeV, 500*MeV, 600*MeV, 700*MeV, 800*MeV,
          900*MeV,
          1*GeV, 2*GeV, 3*GeV, 4*GeV, 5*GeV, 6*GeV, 7*GeV, 8*GeV, 9*GeV,
          10*GeV, 20*GeV, 30*GeV, 40*GeV, 50*GeV, 60*GeV, 70*GeV, 80*GeV, 90*GeV,
          100*GeV, 200*GeV, 300*GeV, 400*GeV, 500*GeV, 600*GeV, 700*GeV, 800*GeV,
          900*GeV,
          1*TeV};/*, 2*TeV, 3*TeV, 4*TeV, 5*TeV, 6*TeV, 7*TeV, 8*TeV, 9*TeV,
          10*TeV, 20*TeV, 30*TeV, 40*TeV, 50*TeV, 60*TeV, 70*TeV, 80*TeV, 90*TeV,
          100*TeV };*/


  //copy arrays in std::vector and compute fMax
  //
  x.resize(nPoints); f.resize(nPoints);

  for (G4int j=0; j<nPoints; j++) {
    x[j] = xx[j];
    f[j] = x[j]*1.8e4*std::pow((x[j]/(1*GeV)), -2.70)*(2*pi*(1-std::cos(pi)))*(2*pi*(1-std::cos(pi)))*worldZHalfLength*worldZHalfLength;
    };

  //compute slopes
  //
  a.resize(nPoints);
  for (G4int j=0; j<nPoints-1; j++) {
    a[j] = (f[j+1] - f[j])/(x[j+1] - x[j]);
  };

  //compute cumulative function
  //
  Fc.resize(nPoints);
  Fc[0] = 0.;
  for (G4int j=1; j<nPoints; j++) {
    Fc[j] = Fc[j-1] + 0.5*(f[j] + f[j-1])*(x[j] - x[j-1]);
  };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double PrimaryGeneratorAction::InverseCumul()
{
  // tabulated function
  // f is assumed positive, linear per segment, continuous
  // --> cumulative function is second order polynomial

  //choose y randomly
  G4double y_rndm = G4UniformRand()*Fc[nPoints-1];
  //find bin
  G4int j = nPoints-2;
  while ((Fc[j] > y_rndm) && (j > 0)) j--;
  //y_rndm --> x_rndm :  Fc(x) is second order polynomial
  G4double x_rndm = x[j];
  G4double aa = a[j];
  if (aa != 0.) {
    G4double b = f[j]/aa, c = 2*(y_rndm - Fc[j])/aa;
    G4double delta = b*b + c;
    G4int sign = 1; if (aa < 0.) sign = -1;
    x_rndm += sign*std::sqrt(delta) - b;
  } else if (f[j] > 0.) {
    x_rndm += (y_rndm - Fc[j])/f[j];
  };
  return x_rndm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
