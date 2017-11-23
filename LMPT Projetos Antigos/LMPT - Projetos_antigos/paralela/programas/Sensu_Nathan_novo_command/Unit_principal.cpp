//---------------------------------------------------------------------------

#pragma hdrstop

#include "TuSen.h"

#define KeyboardReadInterval 1 // Interval between keyboard reads, in seconds
#define AcquisitionInterval 1 // Interval between acquisitions, in seconds

#pragma argsused

//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  time_t UserInteractionInitialTime, UserInteractionFinalTime;
  time_t AcquisitionInitialTime, AcquisitionFinalTime;
  time_t HDWriteInitialTime, HDWriteFinalTime;

  SENSU.Initialize();

  UserInteractionInitialTime = time(NULL);
  AcquisitionInitialTime = time(NULL);
  HDWriteInitialTime = time(NULL);

  while(1)
  {
    UserInteractionFinalTime = time(NULL);
    AcquisitionFinalTime = time(NULL);
    HDWriteFinalTime = time(NULL);

    // Verify if the SENSU must be interact with user
    if ((difftime(UserInteractionFinalTime, UserInteractionInitialTime)) >= KeyboardReadInterval)
    {
      SENSU.UserInteraction();
      UserInteractionInitialTime = time(NULL);

      cout << "Interacao com usuario efetuada" << endl;
    }

    // Verify if the acquisition must be done
    if ((difftime(AcquisitionFinalTime, AcquisitionInitialTime)) >= AcquisitionInterval)
    {
      SENSU.ReadChannels();
      AcquisitionInitialTime = time(NULL);
      cout << "Aquisicao efetuada" << endl;
    }

    // Verify if the data must be saved in HD
    if (SENSU.WriteInDisc == true)
    {
      if ((difftime(HDWriteFinalTime, HDWriteInitialTime)) >= (SENSU.HDWriteBetweenTime*60))
      {
        HDWriteInitialTime = time(NULL);
        SENSU.HDWriteOutArq();
        cout << "Dados gravados no HD" << endl;
        SENSU.ClearTractedSignalAcumulator();
      }
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
