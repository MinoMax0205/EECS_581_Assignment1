GAI Tool Used: 
I used ChatGPT (GPT-5.6 Sol) to assist with this assignment.

Date consulted: September 27, 2026

AI-Generated vs. Student-Written Work

ChatGPT generated the initial C++ implementation of the extractIPv4 function and the main input loop based on the constraints in my prompt.

I personally:

compiled and ran the program in WSL

manually tested valid and invalid IPv4 addresses

tested valid and invalid ports

tested leading-zero cases

tested octet and port boundary values

tested malformed candidates containing extra periods and colons

tested incorrect octet counts

tested multiple candidates in one input line

verified that an invalid candidate is rejected and that scanning continues for a later valid candidate

added an extra blank line between inputs to make the console output easier to read

reviewed the final code and test results before submission

Modifications Made

I made a small formatting change to the AI-generated program by adding an additional std::endl after each result so that there is a blank line between input attempts.

I also created and ran my own edge-case tests to verify that the parser followed the assignment requirements instead of only checking the example inputs.

No major parsing logic changes were required after testing.

Verification Statement

I reviewed the submitted code and understand how the parsing process works, including candidate detection, manual digit accumulation, octet validation, port validation, address construction, and rejection of malformed complete tokens.

I tested the program with normal valid IPv4 addresses, addresses with ports, minimum and maximum boundary values, out-of-range values, leading zeros, malformed separators, missing and extra octets, invalid ports, garbage surrounding valid addresses, and multiple candidates in one input line.

Based on these tests, the program works as intended.

Known Bugs or Limitations:

I am not aware of any unresolved bugs or unexpected behavior in the submitted version.
