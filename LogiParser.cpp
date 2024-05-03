
// LogiParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned char Byte;
typedef int Int32;

/// <summary>
/// A structure which represents a message.
/// </summary>
struct LogiMessage
{
    LogiMessage() : sequenceNumber(0), length(0), message(NULL) {}

    Int32 sequenceNumber;
    Int32 length;
    char* message;
};

/// <summary>
/// Checks the endianness of the system.
/// </summary>
/// <returns>true if the system is little-endian.</returns>
bool isLittleEndian()
{
    const int value = 0x01;
    const void* address = static_cast<const void*>(&value);
    const unsigned char* leastSignificantAddress = static_cast<const unsigned char*>(address);
    return *leastSignificantAddress == 0x01;
}

/// <summary>
/// Helper function for endianness conversion.
/// </summary>
/// <typeparam name="T">The type of the argument.</typeparam>
/// <param name="pObj">The pointer to the object.</param>
template <typename T>
void endSwap(T* pObj)
{
    Byte* pMem = reinterpret_cast<Byte*>(pObj);
    reverse(pMem, pMem + sizeof(T));
}

int main(int argc, char* argv[])
{
    // Check whether the file name is supplied.
    if (argc < 2)
    {
        cout << "Please specify a file name.\n";
        return 1;
    }

    // Open the file.
    ifstream stream(argv[1], ios::binary);

    // Check whether the file is good.
    if (!stream.good())
    {
        cout << "Could not read the file.\n";
        return 1;
    }

    // Read the file into LogiMessage items.
    vector<LogiMessage> messages;
    while (!stream.eof())
    {
        LogiMessage msg;

        // Read the length.
        stream.read((char*)&msg.length, sizeof(Int32));

        // If there is no message, skip.
        if (!msg.length)
            continue;

        // Read the sequence number.
        stream.read((char*)&msg.sequenceNumber, sizeof(Int32));

        // If the system is not little-endian, swap the bytes.
        if (!isLittleEndian())
        {
            endSwap(&msg.sequenceNumber);
            endSwap(&msg.length);
        }

        // Read the actual message content.
        msg.message = (char*)malloc(msg.length + 1);
        stream.read(msg.message, msg.length);
        msg.message[msg.length] = '\0';

        messages.push_back(msg);
    }

    // Close the file resource.
    stream.close();

    // Output the messages, or they can be utilised in another way.
    for (LogiMessage msg : messages)
    {
        printf("%d| %s\n", msg.sequenceNumber, msg.message);
    }

    return 0;
}
