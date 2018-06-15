#include "CMTScanPrimaryGeneratorMessenger.hh"
#include "CMTScanPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CMTScanPrimaryGeneratorMessenger::CMTScanPrimaryGeneratorMessenger(CMTScanPrimaryGeneratorAction* Gun) : Action(Gun)
{
  	CRYDir = new G4UIdirectory("/CRY/");
  	CRYDir->SetGuidance("CRY initialization");
   
  	FileCmd = new G4UIcmdWithAString("/CRY/file",this);
  	FileCmd->SetGuidance("This reads the CRY definition from a file");
  	FileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
   
  	InputCmd = new G4UIcmdWithAString("/CRY/input",this);
  	InputCmd->SetGuidance("CRY input lines");
  	InputCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  	UpdateCmd = new G4UIcmdWithoutParameter("/CRY/update",this);
  	UpdateCmd->SetGuidance("Update CRY definition.");
  	UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  	UpdateCmd->SetGuidance("if you changed the CRY definition.");
  	UpdateCmd->AvailableForStates(G4State_Idle);

  	MessInput = new std::string;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CMTScanPrimaryGeneratorMessenger::~CMTScanPrimaryGeneratorMessenger()
{
  	delete CRYDir;
  	delete InputCmd;
  	delete UpdateCmd;
  	delete FileCmd;
  	delete MessInput;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CMTScanPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  	if( command == InputCmd )
   	{ 
    	Action->InputCRY();
    	(*MessInput).append(newValue);
     	(*MessInput).append(" ");
   	}

  	if( command == UpdateCmd )
   	{ 
   	  	Action->UpdateCRY(MessInput); 
   	  	*MessInput = "";
   	}

  	if( command == FileCmd )
   	{ 
		Action->CRYFromFile(newValue); 
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
