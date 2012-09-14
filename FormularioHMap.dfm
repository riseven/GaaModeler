object FormParamHMap: TFormParamHMap
  Left = 359
  Top = 417
  Width = 401
  Height = 260
  Caption = 'Crear Mapa de alturas'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 32
    Width = 7
    Height = 13
    Caption = 'X'
  end
  object Label2: TLabel
    Left = 24
    Top = 64
    Width = 7
    Height = 13
    Caption = 'Y'
  end
  object Label3: TLabel
    Left = 24
    Top = 96
    Width = 7
    Height = 13
    Caption = 'Z'
  end
  object Label4: TLabel
    Left = 80
    Top = 8
    Width = 31
    Height = 13
    Caption = 'Centro'
  end
  object Label5: TLabel
    Left = 200
    Top = 32
    Width = 32
    Height = 13
    Caption = 'Escala'
  end
  object Label6: TLabel
    Left = 208
    Top = 64
    Width = 27
    Height = 13
    Caption = 'Altura'
  end
  object Label7: TLabel
    Left = 8
    Top = 152
    Width = 81
    Height = 13
    Caption = 'Bitmap de alturas'
  end
  object BotonOK: TBitBtn
    Left = 120
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Aceptar'
    TabOrder = 0
    OnClick = BotonOKClick
  end
  object BotonCancelar: TBitBtn
    Left = 200
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 1
    OnClick = BotonCancelarClick
  end
  object EditX: TEdit
    Left = 40
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object EditY: TEdit
    Left = 40
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 3
    Text = '0'
  end
  object EditZ: TEdit
    Left = 40
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '0'
  end
  object EditEscala: TEdit
    Left = 240
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 5
    Text = '0'
  end
  object BotonColor: TButton
    Left = 216
    Top = 128
    Width = 41
    Height = 25
    Caption = 'Color'
    TabOrder = 6
    OnClick = BotonColorClick
  end
  object EditColor: TEdit
    Left = 136
    Top = 128
    Width = 73
    Height = 21
    Enabled = False
    TabOrder = 7
  end
  object EditAltura: TEdit
    Left = 240
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 8
    Text = '0'
  end
  object EditFichero: TEdit
    Left = 16
    Top = 168
    Width = 193
    Height = 21
    Enabled = False
    TabOrder = 9
  end
  object BotonFichero: TButton
    Left = 216
    Top = 168
    Width = 41
    Height = 25
    Caption = 'Buscar'
    TabOrder = 10
    OnClick = BotonFicheroClick
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 304
    Top = 128
  end
  object OpenDialog1: TOpenDialog
    Filter = 'BMP|*.bmp'
    Left = 304
    Top = 168
  end
end
