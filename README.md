# LogiParser
This is an application written by Tolga Akyay for a Logitech interview. It extracts the messages from a .bin file in PAYLOAD_HEADER (4 BYTES LE) SEQUENCE_NUMBER (4 BYTES LE) MESSAGE (STRING) format.

## Installation
The program is written originally by Visual Studio 2019. You can open the solution in Visual Studio and compile it, or you can use your favourite C++ compiler to build LogiParser.cpp.

## Usage
Pass the file name to be parsed as a command line argument.

eg. LogiParser logi.bin

The program will just output the message as standard output.