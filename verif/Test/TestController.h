/*
###############################################################################
#   Licensing information found at: 
#     https://github.com/matthamptonasic/Hardware/
#   In file LICENSING.md
###############################################################################
#
#   File          :   TestController.h 
#   Creator       :   Matt Hampton (matthamptonasic@gmail.com)
#   Owner         :   Matt Hampton (matthamptonasic@gmail.com)
#   Creation Date :   09/15/16
#   Description   :   Controls the flow of the test.
#                     This includes which test is run.
#
###############################################################################
*/
#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <map>
#include <string>
#include <vector>

#include "Common.h"

using namespace std;

class TestController
{
  // Enums
  public:

  // Constants
  private:
    const string c_cArgsPrefix = "+c_args=";

  // Nested Classes
  public:

  // Private Members
  private:
    vector<string> *      m_commandLineArgs;
    string                m_cArgs;
    map<string, Int32> *  m_nameToInt32Map;
    map<string, Int64> *  m_nameToInt64Map;
    map<string, string> * m_nameToStringMap;

  // Public Properties
  public:
    vector<string> & CommandLineArgs_get();

  // Singleton Pattern
  public:
    static TestController & Access()
    {
      static TestController ls_inst; // Guaranteed to be destroyed.
      return ls_inst;                // Instantiated on 1st use.
    }
  private:
    TestController();
  public:
    TestController(TestController const &) = delete; // These are public for clarity of debug.
    void operator=(TestController const &) = delete; // Can be made private if intellisense is used.

  // Inits
  private:
    void init();

  // Public Methods
  public:
    void PrintCommandLineArgs();

  // Private Methods
  private:
    void commandLineArgs_set();
    void findCArgs();
    void parseCArgs();

};

#endif /* TESTCONTROLLER_H */
