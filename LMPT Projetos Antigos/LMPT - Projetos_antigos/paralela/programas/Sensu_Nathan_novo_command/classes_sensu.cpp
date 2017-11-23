#include "classes_sensu.h"
//---------------------------------------------------------------------------

// Global variables
const int AddressLPT = 0x378;
const int AddressKeyboard = 3;
const int AddressLCD = 0;
//---------------------------------------------------------------------------

// Constructor
TSensu::TSensu()
{
  DataDirectory = "../dados/";
  ConvertersNotFound = true;
  WriteInDisc = false;

  /* Initialize the storage variables for converters readed values, tracted
  signal acumulator and founded converters flags. */
  for (num_lpt = 0; num_lpt <= (MAX_NUM_LPT - 1); num_lpt++)
  {
    for (addr_conv = 0; addr_conv <= 3; addr_conv++)
    {
      ConverterFound[num_lpt][addr_conv] = false;
      for (channel = 0; channel <= 10; channel++)
      {
        readed_value[channel][addr_conv][num_lpt] = -1;
        TractedSignalAcumulator[channel][addr_conv][num_lpt] = 0;
      }
    }
  }
  TractedSignalAcumulatorCounter = 0;
}
//---------------------------------------------------------------------------

void TSensu::Initialize()
{
  int test;

  // Due problems with Windows initialization, which sets some
  // bits of the LPT's to 1, the following lines are needed.
  // They sets the bits of LPT´s to 0, to avoid problems during
  // the converters detection.

  DlPortWritePortUchar(0x378, 0x00);
  DlPortWritePortUchar(0x278, 0x00);

  // Converters search
  for (num_lpt = 0; num_lpt <= (MAX_NUM_LPT - 1); num_lpt++)
  {
    for (addr_conv = 0; addr_conv <= 3; addr_conv++)
    {
      switch (num_lpt)
      {
        case 0:
          test = le_canal(11, addr_conv, 0x378);
        break;

        default:
          test = le_canal(11, addr_conv, 0x278);
      }
      if((test >= 510)&(test <= 514))
      {
        ConverterFound[num_lpt][addr_conv] = true;
        ConvertersNotFound = false;
      }
    }
  }

  // Write the converters configuration file, for depuration purposes
  Write.open("cnfconv.txt",ios::out);

  for (num_lpt = 0; num_lpt <= (MAX_NUM_LPT - 1); num_lpt++)
  {
    switch (num_lpt)
    {
      case 0:
        Write << "888;";
      break;

      default:
        Write << "632;";
    }

    for (addr_conv = 0; addr_conv <= 3; addr_conv++)
    {
      Write << ConverterFound[num_lpt][addr_conv] << ";";
    }

    Write << endl;
  }

  Write.close();

  // If converter is not found, exit program
  if (ConvertersNotFound == true)
  {
    exit(1);
  }

  Read.open("SensuConf.txt",ios::in);
  if (Read)
  {
    Read >> HDWriteBetweenTime;
    Read.close();
  }
  else
  {
    HDWriteBetweenTime = 1;
    cout << "Impossivel abrir o arquivo de configuracao do SENSU" << endl;
    cout << "Tentando criar um arquivo padrao" << endl;
    Write.open("SensuConf.txt",ios::out);
    if (Write)
    {
      Write << HDWriteBetweenTime;
      Write.close();
      cout << "Arquivo criado com sucesso" << endl;
    }
    else
    {
      cout << "Impossivel criar o arquivo de configuracao do SENSU" << endl;
      cout << "Verifique se o disco está cheio" << endl;
      cout << "Execucao do programa terminada" << endl;
      exit(1);
    }
  }

  InitializeLCD(AddressLCD, AddressLPT);
  InitialMenu();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

// Converters functions

void TSensu::ReadChannels()
{
  for (num_lpt = 0; num_lpt <= (MAX_NUM_LPT - 1); num_lpt++)
  {
    for (addr_conv = 0; addr_conv <= 3; addr_conv++)
    {
      if (ConverterFound[num_lpt][addr_conv] == true)
      {
        for (channel = 0; channel <= 10; channel++)
        {
          switch (num_lpt)
          {
            case 0:
              readed_value[channel][addr_conv][num_lpt] = le_canal(channel, addr_conv, 0x378);
            break;

            default:
              readed_value[channel][addr_conv][num_lpt] = le_canal(channel, addr_conv, 0x278);
          }

          if (WriteInDisc == true)
          {
            TractedSignalAcumulator[channel][addr_conv][num_lpt] = TractedSignalAcumulator[channel][addr_conv][num_lpt] + readed_value[channel][addr_conv][num_lpt];
          }
        }
        if (WriteInDisc == true)
        {
          TractedSignalAcumulatorCounter++;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void TSensu::UserInteraction()
{
  key = ReadKeyboard(AddressKeyboard, AddressLPT);
  VerifyMenu();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

// Display functions

void TSensu::InitialMenu()
{
  HorMenuNum = 1;
  VerMenuNum = 1;
  ShowChannelNum = -1;

  ClearLCD(AddressLCD, AddressLPT);
  TextLCD = " Visualizar canais";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  LineLCD(2, AddressLCD, AddressLPT);
  TextLCD = "0:Todos 1:Seleciona";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//---------------------------------------------------------------------------

void TSensu::VerifyMenu() // Current column verify
{
  switch (HorMenuNum)
  {
    case 1: ShowChannelsMenu();
    break;

    case 2: AcquisitionMenu();
    break;

    case 3: FDCopyMenu();
    break;

    default: ShutdownMenu();
  }
}
//---------------------------------------------------------------------------

void TSensu::ShowChannelsMenu()
{
  switch (VerMenuNum)               // Current line verify
  {
    case 1:                         // Superior menu
      if (key == 0)
      {
        VerMenuNum = 3;
        ShowChannelNum = -1;
        ShowConverterNum = 0;
        num_lpt = 0;
        ChannelInformationSelection();
      }
      else
      {
        if (key == 9)
        {
          SuperiorAcquisitionScreen();
        }
        else
        {
          if (key == 1)
          {
            VerMenuNum = 2;         // Select channel option
            ShowChannelNum = -1;
            ShowConverterNum = 0;
            num_lpt = 0;
            ChannelInformationSelection();
          }
        }
      }
    break;

    case 2:                         // Show selected channel

      if (key == 9)                 // Show next channel
      {
        ChannelInformationSelection();
      }
      else
      {
        if (key == 11)              // Return to initial menu
        {
          InitialMenu();
        }
        else
        {
          // Decreases the ShowChannelNum counter for fix
          // the showed channel
          ShowChannelNum--;
          
          ChannelInformationSelection();
        }
      }
    break;

    default:                        // Channel parade

      if (key == 11)
      {
        InitialMenu();
      }
      else
      {
        ChannelInformationSelection();
      }
    break;
  }
}
//------------------------------------------------------------------------------

void TSensu::ChannelInformationSelection()
{
  ClearLCD(AddressLCD, AddressLPT);

  // Select the next converter if channel > 10
  // If the converter selected is > 3, select the next lpt port
  // If the lpt > (MAX_NUM_LPT - 1), select the first lpt
  if (ShowChannelNum < 10)
  {
    ShowChannelNum++;
  }
  else
  {
    ShowChannelNum = 0;
    if (ShowConverterNum <= 3)
    {
      ShowConverterNum++;
    }
    else
    {
      ShowConverterNum = 0;
      if (num_lpt <= (MAX_NUM_LPT - 1))
      {
        num_lpt++;
      }
      else
      {
        num_lpt = 0;
      }
    }
  }

  // Verify if selected converter and lpt are valid
  // If not, select a valid converter and lpt
  while (ConverterFound[num_lpt][ShowConverterNum] != true)
  {
    if (ShowConverterNum <= 3)
    {
      ShowConverterNum++;
    }
    else
    {
      ShowConverterNum = 0;
      num_lpt++;

      if (num_lpt > (MAX_NUM_LPT - 1))
      {
        num_lpt = 0;
      }
    }
  }

  switch (ShowConverterNum)
  {
    case 1:
      switch(ShowChannelNum)
      {
        case 0:
          TextLCD = "Canal 1: Temp. do ar";
          unit = 1;
        break;

        case 1:
          TextLCD = "Canal 2: Vel. do ar";
          unit = 3;
        break;

        case 2:
          TextLCD = "Canal 3: Temp. Globo";
          unit = 1;
        break;

        case 3:
          TextLCD = "Canal 4: Umid. do ar";
          unit = 2;
        break;

        case 4:
          TextLCD = "Canal 5: Amp. 1";
          unit = 4;
        break;

        case 5:
          TextLCD = "Canal 6: Amp. 2";
          unit = 1;
        break;

        case 6:
          TextLCD = "Canal 7: Amp. 3";
          unit = 4;
        break;

        case 7:
          TextLCD = "Canal 8: Amp. 4";
          unit = 4;
        break;

        case 8:
          TextLCD = "Canal 9: Temp. Ref.";
          unit = 1;
        break;

         case 9:
          TextLCD = "Canal 10:  Sinal 1";
          unit = 4;
        break;

        default:
          TextLCD = "Canal 11:  Sinal 2";
          unit = 4;
        break;
      }
    break;

    default:
    break;
  }

  ShowSelectedInformation(&TextLCD[0], unit);
}
//------------------------------------------------------------------------------

void TSensu::ShowSelectedInformation(char *pTextLCD, unsigned int unit)
{
  ostringstream bufferstream;

  LineLCD(1, AddressLCD, AddressLPT);
  WriteTextInLCD(pTextLCD, AddressLCD, AddressLPT);

  LineLCD(2, AddressLCD, AddressLPT);
  TextLCD = "                    ";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  LineLCD(2, AddressLCD, AddressLPT);
  
  bufferstream.setf(ios::left);
  bufferstream << setw(6) << setprecision(4) << readed_value[ShowChannelNum][ShowConverterNum][num_lpt];

  switch (unit)
  {
    case 1:
      TextLCD = bufferstream.str() + "  [C]";
    break;

    case 2:
      TextLCD = bufferstream.str() + "  [%]";
    break;

    case 3:
      TextLCD = bufferstream.str() + "  [m/s]";
    break;

    default:
      TextLCD = bufferstream.str() + "  [V]";
  }

  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void TSensu::SuperiorAcquisitionScreen()
{
  HorMenuNum = 2;
  VerMenuNum = 1;

  ClearLCD(AddressLCD, AddressLPT);

  TextLCD = "Gravacao em disco";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  LineLCD(2, AddressLCD, AddressLPT);

  if (WriteInDisc == false)
  {
    DoneAcquisitionsNum = 0;

    ClearTractedSignalAcumulator();

    TextLCD = "0:Iniciar 1:Interv.";
    WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  }
  else
  {
    TextLCD = "0:Parar   1:Interv.";
    WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  }
}
//---------------------------------------------------------------------------

void TSensu::AcquisitionMenu()
{
  char character;

  switch (VerMenuNum) // Current line verify
  {
    case 1:  // Superior Menu

      if (key == 0)                 // If press '0'
      {
        if (WriteInDisc == true)
        {
          WriteInDisc = false;
          SuperiorAcquisitionScreen();
        }
        else
        {
          WriteInDisc = true;
          CreateOutputArq();
          SuperiorAcquisitionScreen();
        }
      }
      else
      {
        if (key == 1) // If press '1'
        {
          HDWriteIntervalMenu();
        }
        else
        {
          if (key == 9)  // If press '9'
          {
            SuperiorFDMenu();
          }
        }
      }
    break;


    case 2:  // HD write interval adjust menu

      if (key == 11) // Cancel HD write timer adjust
      {
        SuperiorAcquisitionScreen();
        DigitatedTime = "";
      }
      else
      {
        if (key == 0)
        {
          DigitizeHDWriteIntervalMenu();
          KeyReadedNum = 0;
        }
      }
    break;


    default:  // Enter HD write interval menu

      if (key == 10) // Apply HD write timer adjust
      {
        Write.open("SensuConf.txt",ios::out);
        if (Write)
        {
          Write << DigitatedAcquisitionInterval;
          Write.close();
        }

        HDWriteBetweenTime = DigitatedAcquisitionInterval;

        HDWriteIntervalMenu();
      }
      else
      {
        if (key == 11)
        {
          HDWriteIntervalMenu();
        }
        else
        {
          if (key != -1)
          {
            KeyReadedNum++;

            if (KeyReadedNum <= 2)  // If was digitaded less then two characters
            {
              if (KeyReadedNum == 1)
              {
                DigitatedAcquisitionInterval =  key;
                character = key + 0x30;
                DigitatedTime = character;
              }
              else
              {
                DigitatedAcquisitionInterval =  DigitatedAcquisitionInterval*10 + key;
                character = key + 0x30;
                DigitatedTime = DigitatedTime + character;
              }

              TextLCD = "Novo Intervalo: " + DigitatedTime + "  ";

              LineLCD(1, AddressLCD, AddressLPT);

              WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
            }
          }
        }
      }
    break;
  }
}

//------------------------------------------------------------------------------

void TSensu::HDWriteIntervalMenu()
{
  ostringstream bufferstream;

  KeyReadedNum = 0;

  VerMenuNum = 2;

  ClearLCD(AddressLCD, AddressLPT);

  TextLCD = "Intervalo [min]:";
  bufferstream << (HDWriteBetweenTime);
  TextLCD = TextLCD + bufferstream.str();
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);

  LineLCD(2, AddressLCD, AddressLPT);

  TextLCD = "0: Novo intervalo";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//------------------------------------------------------------------------------

void TSensu::DigitizeHDWriteIntervalMenu()
{
  VerMenuNum = 3;

  ClearLCD(AddressLCD, AddressLPT);

  LineLCD(2, AddressLCD, AddressLPT);

  TextLCD = "Em minutos          ";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);

  LineLCD(1, AddressLCD, AddressLPT);

  TextLCD = "Novo Intervalo:     ";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//------------------------------------------------------------------------------

void TSensu::CreateOutputArq()
{
  time(&date);
  datehour = localtime(&date);
  strftime(month,10,"%B",datehour);
  strftime(year,10,"%Y",datehour);
  strftime(day,10,"%d",datehour);
  strftime(hour,10,"%H",datehour);
  strftime(minutes,10,"%M",datehour);

  DataFileName = DataDirectory;
  FDDataFileName = "";
  DataFileName = DataFileName + day + "_" + month + "_" + year + "_" + hour + "h" + minutes + "m" + ".txt";
  FDDataFileName = FDDataFileName + day + "_" + month + "_" + year + "_" + hour + "h" + minutes + "m" + ".txt";

  // Create the header for the data file
  header << "Horário;Segundos desde 01/01/1900;Temperatura_do_ar_[C];Velocidade_do_ar_[m/s];";
  header << "Temperatura_de_globo_[C];Umidade_do_ar_[%];Amplificador_1_[V];";
  header << "Amplificador_2_[V];Amplificador_3_[V];Amplificador_4_[V];";
  header << "Temperatura_de_referência_[C];Sinal_1_[V];Sinal_2_[V]" << endl;

  Write.open(DataFileName.c_str(),ios::out);
  Write << header.str();
  Write.close();
}
//------------------------------------------------------------------------------

void TSensu::HDWriteOutArq()
{
  /* gets time of day */
  time(&date);
  datehour = localtime(&date);
  strftime(month,10,"%B",datehour);
  strftime(year,10,"%Y",datehour);
  strftime(day,10,"%d",datehour);
  strftime(hour,10,"%H",datehour);
  strftime(minutes,10,"%M",datehour);

  if (TractedSignalAcumulatorCounter != 0)
  {
    Write.open(DataFileName.c_str(),ios::out|ios::app);

    Write << year <<"/"<< month << "/" << day << "," << hour;
    Write << "h" << minutes << "m" << ";" << date << ";";

    for (num_lpt = 0; num_lpt <= (MAX_NUM_LPT - 1); num_lpt++)
    {
      for (addr_conv = 0; addr_conv <= 3; addr_conv++)
      {
        if (ConverterFound[num_lpt][addr_conv] == true)
        {
          for (channel = 0; channel <= 10; channel++)
          {
            Write << TractedSignalAcumulator[channel][addr_conv][num_lpt]/TractedSignalAcumulatorCounter << ";";
          }
        }
      }
    }

    Write << endl;
    Write.close();
    TractedSignalAcumulatorCounter = 0;
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void TSensu::SuperiorFDMenu()
{
  HorMenuNum = 3;
  VerMenuNum = 1;

  LineLCD(1, AddressLCD, AddressLPT);

  TextLCD = " Copia em disquete  ";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);

  LineLCD(2, AddressLCD, AddressLPT);

  TextLCD = "0:Atual 1:Seleciona ";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//------------------------------------------------------------------------------

void TSensu::FDCopyMenu()
{
  DIR           *dir_p;
  struct dirent *dir_entry_p;

  switch (VerMenuNum) // Verify current line
  {
    case 1:  // Superior Menu

      if (key == 0)
      {
        if (DataFileName == "")
        {
          VerMenuNum = 3;
          ClearLCD(AddressLCD, AddressLPT);
          TextLCD = "Nenhum arquivo sele-cionado. Tecle #";
          WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
        }
        else
        {
          SelectedFile = DataFileName;
          CopySelectedFile();
        }
      }
      else
      {
        if (key == 1)
        {
          // List the generated files
          GeneratedFiles.clear();

          if ((dir_p = opendir(&DataDirectory[0])) != NULL) // Open the data directory
          {
            while(NULL != (dir_entry_p = readdir(dir_p)))
            {
              GeneratedFiles = GeneratedFiles + dir_entry_p->d_name + ";";

              // Erase strings [.;] and [.;] from the list
              if ((GeneratedFiles == ".;")|(GeneratedFiles == "..;"))
              {
                GeneratedFiles.clear();
              }
            }

            closedir(dir_p);
          }
          else
          {
           // Colocar aqui o código para tratar o caso de impossibilidade
           // de abrir o diretório de dados
          }

          if (GeneratedFiles == "")
          {
            VerMenuNum = 3;
            ClearLCD(AddressLCD, AddressLPT);
            TextLCD = "Nenhum arq. gerado. Tecle #";
            WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
          }
          else
          {
            VerMenuNum = 2;
            CharCounter = 0;
            SelectFile();
          }
        }
        else
        {
          if (key ==9)
          {
            SuperiorShutdownMenu();
          }
        }
      }
    break;


    case 2:  // Select file menu

      if (key == 9) // Show next file
      {
        SelectFile();
      }
      else
      {
        if (key == 10)  // Write showed file in FD
        {
          SelectedFile = DataDirectory + SelectedFile;
          CopySelectedFile();
        }
        else
        {
          if (key == 11) 
          {
            SuperiorFDMenu();
          }
        }
      }
    break;

    case 3:

      if (key == 11)
      {
        SuperiorFDMenu();
      }
    break;


    default:

      if (key == 11)
      {
        SuperiorFDMenu();
      }
    break;
  }
}
//------------------------------------------------------------------------------

void TSensu::SelectFile()
{
  // Verify if achieve end of listing
  if (CharCounter == (GeneratedFiles.length() - 1))
  {
    // If achieve, start listing again
    CharCounter = 0;
  }
  else
  {
    // Erase string [.;] from the list
    if (CharCounter != 0)
    {
      CharCounter++;
    }
  }

  TextLCD = "";
  string Separator = ";";
  while (GeneratedFiles[CharCounter] != Separator[0])
  {
    TextLCD = TextLCD + GeneratedFiles[CharCounter];
    CharCounter++;
  }

  SelectedFile = TextLCD;
  FDDataFileName = TextLCD;

  ClearLCD(AddressLCD, AddressLPT);
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//------------------------------------------------------------------------------

void TSensu::CopySelectedFile()
{
  fstream Write, Read;
  string buffer;

  FDDataFileName = "a:" + FDDataFileName;

  Read.open(SelectedFile.c_str(),ios::in); // Tenta abrir o arquivo de dados
  if (Read.is_open())
  {
    Write.open(FDDataFileName.c_str(),ios::out); // Tenta abrir o arquivo no disquete

    if (Write.is_open())
    {
      TextLCD = "Copiando arquivo,   aguarde";
      ClearLCD(AddressLCD, AddressLPT);
      WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);

      while (Read >> buffer) // Carrega o conteúdo do arquivo no buffer;
      {
        Write << buffer << endl;
      }
      Write.close();
      TextLCD = " Arquivo   Copiado    #: Menu superior";
      ClearLCD(AddressLCD, AddressLPT);
      WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
    }
    else
    {
      TextLCD = "Disquete invalido oucheio. #: Menu sup.";
      ClearLCD(AddressLCD, AddressLPT);
      WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
    }
    Read.close();
  }
  else
  {
    TextLCD = "Erro ao ler o aquivode dados. #: Menu sup.";
    ClearLCD(AddressLCD, AddressLPT);
    WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  }
  VerMenuNum = 3;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void TSensu::SuperiorShutdownMenu()
{
  HorMenuNum = 4;

  ClearLCD(AddressLCD, AddressLPT);
  LineLCD(1, AddressLCD, AddressLPT);
  TextLCD = "      Desligar";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
  LineLCD(2, AddressLCD, AddressLPT);
  TextLCD = "*:Confirma #:Cancela";
  WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
}
//------------------------------------------------------------------------------

void TSensu::ShutdownMenu()
{
  if (key == 10)
  {
    ClearLCD(AddressLCD, AddressLPT);
    TextLCD = "Desligue o conforti-metro em 5 segundos";
    WriteTextInLCD(&TextLCD[0], AddressLCD, AddressLPT);
    ExitWindowsEx(1,0);
  }
  else
  {
    if ((key == 11)|(key == 9))
    {
      InitialMenu();
    }
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void TSensu::ClearTractedSignalAcumulator()
{
  for (num_lpt = 0; num_lpt <= (MAX_NUM_LPT - 1); num_lpt++)
  {
    for (addr_conv = 0; addr_conv <= 3; addr_conv++)
    {
      for (channel = 0; channel <= 10; channel++)
      {
        TractedSignalAcumulator[channel][addr_conv][num_lpt] = 0;
      }
    }
  }
  TractedSignalAcumulatorCounter = 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
double TSensu::BodyThermicLoadCalc()
{
  double BodyThermicLoad;
  double SaturationPressure;
  double SteamPressure;
  double ClothTemperature;
  double AbsRadiantTemperature, InitialClothTemperature;
  double fcl1, fcl2, fcl;


  // The use of casts grants the double format in results
  SaturationPressure = (double) 0.0047*(pow(readed_value[0][1][0],2))- (double) 0.043*readed_value[0][1][0]+1.3299;
  SteamPressure = (double) ((double) SaturationPressure*readed_value[3][1][0])/100.0;

  fcl1 = 1.0+ (double)0.2*VestmentIndice;
  fcl2 = 1.05+ (double)0.1*VestmentIndice;
  if (fcl1 > fcl2)
  {
    fcl = fcl1;
  }
  else
  {
    fcl = fcl2;
  }

  hc = 12.1*sqrt(readed_value[1][1][0]);

  AbsRadiantTemperature = readed_value[2][1][0] + 273.0;
  InitialClothTemperature = ( (double)35.7+readed_value[0][1][0])/2.0;

  // For code clarity, the evaluaton of ClothTemperature was divided into several lines
  ClothTemperature = 3.96*pow(10,-8)*pow((InitialClothTemperature+273.0),4)- pow(AbsRadiantTemperature,4);
  ClothTemperature = ClothTemperature - hc*(InitialClothTemperature - readed_value[0][1][0]);
  ClothTemperature = 35.7-0.028*Activity-0.155*VestmentIndice*fcl;

  while (fabs(ClothTemperature-InitialClothTemperature) > 0.1)
  {
    InitialClothTemperature = ClothTemperature;
    ClothTemperature = 3.96*pow(10,-8)*pow((InitialClothTemperature+273.0),4)- pow(AbsRadiantTemperature,4);
    ClothTemperature = ClothTemperature - hc*(InitialClothTemperature - readed_value[0][1][0]);
    ClothTemperature = 35.7-0.028*Activity-0.155*VestmentIndice*fcl;
  }


  // For code clarity, the evaluaton of BodyThermicLoad was divided into several lines
  BodyThermicLoad = (double)Activity- (double)3.05* (double)(5.073- (double)0.007*Activity - SteamPressure);
  BodyThermicLoad = BodyThermicLoad- (double)0.42* (double)(Activity-58.15)- (double)0.0173*Activity* (double)(5.87 - SteamPressure);
//  BodyThermicLoad = BodyThermicLoad- (double)0.0014*Activity* (double)(34.0-readed_value[0][1][0])
}

