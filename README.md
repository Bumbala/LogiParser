# LogiParser
This is an application written by Tolga Akyay for a Logitech interview. It extracts the messages from a .bin file in PAYLOAD_HEADER (4 BYTES LE) SEQUENCE_NUMBER (4 BYTES LE) MESSAGE (STRING) format.

## Usage
Pass the file name to be parsed as a command line argument.

eg. LogiParser logi.bin

The program will just output the message as standard output.