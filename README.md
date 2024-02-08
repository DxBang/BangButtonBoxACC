# BangButtonACC
 Bang Buttons for ACC


## Input and modes
```text
Bang Button
	- Single Press: Bang, Timed or Toggled
	- Single Press while Banged: Debang
	- Hold: System Settings

System Settings
	- Engine Button: Change Profile
	- Ignition Button: Toggle Bang Mode
	- encoderMiddle Up/Dn: Change Brightness
	- encoderMiddle Push: Encoder Multiplier x10

Assetto Corsa Competizione Profile
	Default Functional Buttons 
		ignition: Ignition
		engine: Engine
		pit: Pit Limiter
		light: Lights
		rain: Rain Light
		flash: Flash
		wiper: Wiper
		position: MFD Position
		standing: MFD Standing
		pitstop: MFD Pitstop
		electronics: MFD Electronics
		select: Nav Select
		up: Nav Up
		down: Nav Down
		left: Nav Left
		right: Nav Right
	Default Functional Encoders
		encoderLeft Up/Dn: Brake Bias
		encoderRight Up/Dn: Traction Control
		encoderMiddle Up/Dn: Engine Map
		encoderLeft Push: Encoder Multiplier
		encoderRight Push: Encoder Multiplier
		encoderMiddle Push: Encoder Multiplier
	Banged Functional Buttons:
		ignition: Ignition
		engine: Engine 1 sec.
		pit: Time Table
		light: HUD
		rain: Map
		flash: Add highlight
		wiper: Names
		position: Dashboard up
		standing: Dashboard down
		pitstop: Race Logic
		electronics: Indicator Right
		select: Indicator Left
		up: Camera Bonnet
		down: Cycle Camera
		left: Camera Cockpit
		right: Camera Chase
	Banged Functional Encoders:
		encoderLeft Up/Dn: Anti-Brake System
		encoderRight Up/Dn: Traction Control Cut
		encoderMiddle Up/Dn: FOV
		encoderLeft Push: Encoder Multiplier
		encoderRight Push: Encoder Multiplier
		encoderMiddle Push: Encoder Multiplier
```

## Pinout
```text
D0	Rotary Encoder Left CLK
D1	Rotary Encoder Left DT
D2	Rotary Encoder Right DT
D3	Lights
D4	Matrix Sender 1
D5	Matrix Sender 2
D6	Matrix Sender 3
D7	Rotary Encoder Right CLK
D8	Rotary Encoder Middle CLK
D9	RGB LED R
D10	RGB LED G
D11	RGB LED B
D12	Rotary Encoder Middle SWT
D13	Bang LED
D14	Rotary Encoder Left SWT
D15	Rotary Encoder Right SWT
D16	Rotary Encoder Middle DT
D17	Can't use for output
A0	Matrix Sender 1
A1	Matrix Receiver 1
A2	Matrix Receiver 2
A3	Matrix Receiver 3
A4	Matrix Receiver 4
A5	Matrix Receiver 5

~ = PWM
^ = INT
/ = PCINT

              Board: Arduino Micro
                 ------USB------
        Bang LED | ~D13    D12 | RE Middle SWT
                 | 3V3   ~/D11 | RGB LED B
                 | AREF  ~/D10 | RGB LED G
    Matrix Sen 4 | A0     ~/D9 | RGB LED R
    Matrix Rec 1 | A1      /D8 | RE Middle CLK
    Matrix Rec 2 | A2      ^D7 | RE Right CLK
    Matrix Rec 3 | A3      ~D6 | Matrix Sen 3
    Matrix Rec 4 | A4      ~D5 | Matrix Sen 2
    Matrix Rec 5 | A5       D4 | Matrix Sen 1
                 |         ~D3 | Lights
                 |        ~^D2 | RE Right DT
       5V for RE | 5V      GND | GND
                 | RST     RST |
             GND | GND     ^D0 | RE Left CLK
                 | VIN     ^D1 | RE Left DT
    RE Left SWT  | D14    /D17 | 
   RE Right SWT  | D15    /D16 | RE Middle DT
                 ---------------

```