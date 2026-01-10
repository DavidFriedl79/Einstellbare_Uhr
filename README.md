Projektziel:
Anzeige einer Uhrzeit (hh:mm) auf einem 4-stelligen 7-Segment-Display (5461AS, Common Anode)
Einstellen der Zeit über einen Joystick (HW-504)
Die Uhr tickt jede Minute automatisch weiter
Anzeige aller Ziffern über Multiplexing
Common-Anode-Logik:
LOW = EIN, HIGH = AUS

Hardware:
Arduino (Uno / Nano)
4-stelliges 7-Segment-Display (5461AS)
Joystick HW-504
Vorwiderstände
Steckbrett & Jumper-Kabel

Funktionsweise:
Anzeige von Stunden und Minuten
Zeit läuft unabhängig vom Einstellen weiter
Joystick - Links/Rechts → Stunden oder Minuten auswählen
Hoch/Runter → Wert ändern
Taster → Einstellmodus

Technische Grundlagen:
Segmentsteuerung
Common-Anode-Display
Segmente werden mit LOW eingeschaltet
Segmentmuster für Ziffern 0–9

Multiplexing:
7 gemeinsame Segmentleitungen
4 separate Anoden
Ziffern werden schnell nacheinander aktiviert

Joystick:
X- & Y-Achse analog (analogRead())
Taster digital (digitalRead())

Zeitsteuerung:
Verwendung von millis() statt delay()
Jede vergangene Minute erhöht die Uhrzeit

Quellen:
Grundlagen aus der offiziellen Dokumentation von
Arduino





