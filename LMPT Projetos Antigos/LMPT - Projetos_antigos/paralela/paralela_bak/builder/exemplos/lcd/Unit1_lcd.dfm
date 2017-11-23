object Form1: TForm1
  Left = 519
  Top = 331
  Width = 330
  Height = 384
  Hint = 'Endereço da paralela'
  Caption = 'LCD'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  ShowHint = True
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 191
    Height = 25
    Caption = 'Endereço da paralela:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 153
    Width = 157
    Height = 25
    Caption = 'Mensagem inicial:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 265
    Width = 128
    Height = 25
    Caption = 'Tecla digitada:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 16
    Top = 57
    Width = 185
    Height = 25
    Caption = 'Endereço do teclado:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 16
    Top = 96
    Width = 162
    Height = 25
    Caption = 'Endereço do LCD:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Campo_endereco_paralela: TEdit
    Left = 217
    Top = 16
    Width = 50
    Height = 24
    MaxLength = 5
    TabOrder = 1
    Text = '0x278'
  end
  object Texto_inicial_LCD_1: TEdit
    Left = 16
    Top = 185
    Width = 273
    Height = 24
    MaxLength = 40
    TabOrder = 2
    Text = '  Sistema de Aquisicao CLIMUS / SENSU'
  end
  object Texto_inicial_LCD_2: TEdit
    Left = 16
    Top = 208
    Width = 273
    Height = 24
    MaxLength = 40
    TabOrder = 3
    Text = ' *: Mostra as teclas digitadas'
  end
  object Campo_tecla_digitada: TEdit
    Left = 160
    Top = 265
    Width = 33
    Height = 24
    Enabled = False
    TabOrder = 4
  end
  object Campo_endereco_teclado: TEdit
    Left = 217
    Top = 57
    Width = 24
    Height = 24
    MaxLength = 1
    TabOrder = 5
    Text = '3'
  end
  object Botao_inicia_aquisicao: TButton
    Left = 58
    Top = 313
    Width = 75
    Height = 24
    Caption = '&Inicia'
    TabOrder = 0
    OnClick = Botao_inicia_aquisicaoClick
  end
  object Botao_sair: TButton
    Left = 214
    Top = 313
    Width = 74
    Height = 24
    Caption = '&Sair'
    TabOrder = 6
    OnClick = Botao_sairClick
  end
  object Campo_endereco_LCD: TEdit
    Left = 216
    Top = 96
    Width = 25
    Height = 24
    TabOrder = 7
    Text = '0'
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 240
    Top = 136
  end
end
