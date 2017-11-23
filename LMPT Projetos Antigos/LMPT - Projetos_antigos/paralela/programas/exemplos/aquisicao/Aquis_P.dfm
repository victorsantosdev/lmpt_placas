object Form1: TForm1
  Left = 910
  Top = 329
  Width = 325
  Height = 194
  Caption = 'Aquis_P'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 80
    Top = 9
    Width = 112
    Height = 16
    Caption = 'Endere'#231'o da porta'
  end
  object Label2: TLabel
    Left = 160
    Top = 80
    Width = 102
    Height = 16
    Caption = 'Tens'#227'o em Volts'
  end
  object Label3: TLabel
    Left = 57
    Top = 41
    Width = 35
    Height = 16
    Caption = 'Canal'
  end
  object Label4: TLabel
    Left = 144
    Top = 41
    Width = 12
    Height = 16
    Caption = 'CI'
  end
  object Label5: TLabel
    Left = 8
    Top = 112
    Width = 182
    Height = 16
    Caption = 'Aquisi'#231#245'es por segundo [S/s]:'
  end
  object Button1: TButton
    Left = 208
    Top = 9
    Width = 105
    Height = 24
    Caption = 'Iniciar Leitura'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 25
    Top = 9
    Width = 45
    Height = 24
    TabOrder = 1
    Text = '0x378'
  end
  object Edit2: TEdit
    Left = 25
    Top = 80
    Width = 120
    Height = 24
    ReadOnly = True
    TabOrder = 2
  end
  object Edit3: TEdit
    Left = 25
    Top = 41
    Width = 24
    Height = 24
    MaxLength = 2
    TabOrder = 3
    Text = '0'
  end
  object Edit4: TEdit
    Left = 112
    Top = 41
    Width = 25
    Height = 24
    MaxLength = 1
    TabOrder = 4
    Text = '1'
  end
  object Botao_Parar_aquisicao: TButton
    Left = 208
    Top = 41
    Width = 105
    Height = 24
    Caption = 'Parar Leitura'
    Enabled = False
    TabOrder = 5
    OnClick = Botao_Parar_aquisicaoClick
  end
  object Edit5: TEdit
    Left = 200
    Top = 112
    Width = 73
    Height = 24
    TabOrder = 6
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 168
    Top = 40
  end
end
