#include <iostream.h>
#include <fstream.h>
#include <sstream.h>
#include <iomanip.h>
#include <dirent.h>
#include <math.h>
#include "..\bibliotecas\include\tlc1543.h"
#include "..\bibliotecas\include\keyboard4x3.h"
#include "..\bibliotecas\include\lcd2x40.h"
#include "..\bibliotecas\include\Dlportio.h"

#define MAX_NUM_LPT 2

class TSensu
{
  public:
  TSensu();       // Constructor
  void Initialize();
  void ReadChannels();
  void UserInteraction();
  void HDWriteOutArq();
  void ClearTractedSignalAcumulator();

  bool WriteInDisc;
  unsigned int HDWriteBetweenTime;

  private:
  void InitialMenu();
  void VerifyMenu();
  void SuperiorAcquisitionScreen();
  void ShowChannelsMenu();
  void ChannelInformationSelection();
  void ShowSelectedInformation(char *, unsigned int);
  void AcquisitionMenu();
  void HDWriteIntervalMenu();
  void DigitizeHDWriteIntervalMenu();
  void CreateOutputArq();
  void SuperiorFDMenu();
  void FDCopyMenu();
  void SelectFile();
  void CopySelectedFile();
  void SuperiorShutdownMenu();
  void ShutdownMenu();
  double BodyThermicLoadCalc();
  
  int key, ShowChannelNum, ShowLPTNum, ShowConverterNum, DoneAcquisitionsNum;
  int readed_value[11][4][MAX_NUM_LPT];
  unsigned int num_lpt, addr_conv, channel, HorMenuNum, VerMenuNum, KeyReadedNum;
  unsigned int DigitatedAcquisitionInterval, CharCounter;
  unsigned int TractedSignalAcumulatorCounter, unit, Activity, VestmentIndice;
  double TractedSignalAcumulator[11][4][MAX_NUM_LPT];
  bool ConverterFound[2][4];
  bool ConvertersNotFound;
  char month[10],year[10], hour[10], minutes[10], day[10];
  string TextLCD, DataFileName, FDDataFileName, DigitatedTime, SelectedFile;
  string GeneratedFiles, DataDirectory;
  fstream Write, Read;
  ostringstream header;
  struct tm *datehour;
  time_t date;
};