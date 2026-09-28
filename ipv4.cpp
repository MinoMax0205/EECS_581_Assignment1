#include <iostream>
#include <string>

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort)
{
    // Default values for failure
    outAddress = 0;
    outPort = -1;

    unsigned long candidateAddress = 0;
    int candidatePort = -1;

    // Scan through the entire string one character at a time
    for (size_t i = 0; i < str.length(); )
    {
        char c = str[i];

        // Skip garbage characters
        if (!((c >= '0' && c <= '9') || c == '.' || c == ':'))
        {
            i++;
            continue;
        }

        // Beginning of a candidate token
        size_t start = i;

        // Find the end of this continuous sequence of digits, periods, and colons
        while (i < str.length())
        {
            char ch = str[i];

            if ((ch >= '0' && ch <= '9') || ch == '.' || ch == ':')
                i++;
            else
                break;
        }

        size_t end = i;

        // Try to parse the ENTIRE candidate
        size_t pos = start;

        unsigned long address = 0;
        bool valid = true;

        // Parse exactly four octets
        for (int octetNumber = 0; octetNumber < 4 && valid; octetNumber++)
        {
            // Octet must begin with a digit
            if (pos >= end || str[pos] < '0' || str[pos] > '9')
            {
                valid = false;
                break;
            }

            size_t digitStart = pos;
            int value = 0;
            int digitCount = 0;

            // Read the digits of this octet
            while (pos < end &&
                   str[pos] >= '0' &&
                   str[pos] <= '9')
            {
                digitCount++;

                // More than 3 digits is invalid
                if (digitCount > 3)
                {
                    valid = false;
                    break;
                }

                value = value * 10 + (str[pos] - '0');
                pos++;
            }

            if (!valid)
                break;

            // Check leading zero
            if (digitCount > 1 && str[digitStart] == '0')
            {
                valid = false;
                break;
            }

            // Check octet range
            if (value > 255)
            {
                valid = false;
                break;
            }

            // Add octet to the 32-bit address
            address = (address << 8) | value;

            // First three octets must be followed by a period
            if (octetNumber < 3)
            {
                if (pos >= end || str[pos] != '.')
                {
                    valid = false;
                    break;
                }

                pos++;
            }
        }

        if (!valid)
            continue;

        int port = -1;

        // After the fourth octet, either:
        // 1. candidate ends, or
        // 2. there is exactly one valid :port
        if (pos < end)
        {
            // Anything other than ':' is invalid
            if (str[pos] != ':')
                continue;

            pos++;

            // Port must contain at least one digit
            if (pos >= end || str[pos] < '0' || str[pos] > '9')
                continue;

            size_t portStart = pos;
            int portValue = 0;
            int digitCount = 0;
            bool validPort = true;

            while (pos < end &&
                   str[pos] >= '0' &&
                   str[pos] <= '9')
            {
                digitCount++;

                // Port may contain at most 5 digits
                if (digitCount > 5)
                {
                    validPort = false;
                    break;
                }

                portValue = portValue * 10 + (str[pos] - '0');
                pos++;
            }

            if (!validPort)
                continue;

            // No leading zero unless port is exactly 0
            if (digitCount > 1 && str[portStart] == '0')
                continue;

            // Port range
            if (portValue > 65535)
                continue;

            // Nothing may remain in the candidate
            if (pos != end)
                continue;

            port = portValue;
        }

        // If there was no port, make sure nothing remained
        else
        {
            port = -1;
        }

        // Entire candidate successfully parsed
        if (pos == end)
        {
            candidateAddress = address;
            candidatePort = port;

            outAddress = candidateAddress;
            outPort = candidatePort;

            return true;
        }
    }

    // No valid address found
    outAddress = 0;
    outPort = -1;
    return false;
}

int main()
{
    std::string input;

    while (true)
    {
        std::cout << "Enter a string (or 'END' to quit):" << std::endl;
        std::getline(std::cin, input);

        if (input == "END")
        {
            std::cout << "Program terminated." << std::endl;
            break;
        }

        unsigned long address;
        int port;

        if (extractIPv4(input, address, port))
        {
            // Recover each octet from the 32-bit numeric address
            unsigned long a = (address >> 24) & 255;
            unsigned long b = (address >> 16) & 255;
            unsigned long c = (address >> 8) & 255;
            unsigned long d = address & 255;

            std::cout << "Extracted IPv4 address: "
                      << a << "."
                      << b << "."
                      << c << "."
                      << d
                      << " (decimal value: "
                      << address
                      << ", port: ";

            if (port == -1)
                std::cout << "none";
            else
                std::cout << port;

            std::cout << ")" << std::endl << std::endl;
        }
        else
        {
            std::cout << "Invalid input: no valid IPv4 address found"
                      << std::endl << std::endl;
        }
    }

    return 0;
}