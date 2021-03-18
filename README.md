# lpt-typewriter

Convert your printer into a type writer! print as you write.<br>
Theoritically should support all printers that have a LPT port.

Tested on Epson dot matrix printer LQ-300+

Connect stobe pin of parallel port to Arduino pin 11.<br>
Connect data pins 0 to 7 to Arduino pins 3 to 10.<br>
Look at the Parallel_port reference (link below) to find pin numbers
on a LPT connector.

- https://en.wikipedia.org/wiki/Parallel_port
- https://en.wikipedia.org/wiki/ESC/P
- https://files.support.epson.com/pdf/general/escp2ref.pdf

Ideas to extend: 
- Extend and inherit from the Arduino's Print class.
- Support full set of ESC/P codes.
- Draw mode to draw ASCII chars above 127 (table chars) easily.
- Move head/paper commands.
- Configure on-the-fly by reading pin numbers from Serial port.

