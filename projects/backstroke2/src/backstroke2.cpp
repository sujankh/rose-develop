// Author: Markus Schordan, 2013, 2014.

#include "rose.h"

#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <cmath>

#include "SgNodeHelper.h"

#include "Timer.h"

#include "limits.h"
#include "assert.h"

#include "CommandLineOptions.h"
#include "CodeGenerator.h"
#include "Utility.h"

using namespace std;
using namespace Backstroke;

int main(int argc, char* argv[]) {
  try {
    CommandLineOptions clo;
    clo.process(argc,argv);
    if(clo.isFinished()) {
      return 0;
    } else {
      cout << "STATUS: Parsing and creating AST."<<endl;
      SgProject* root = frontend(argc,argv);
      if(clo.optionRoseAstCheck()) {
        AstTests::runAllTests(root);
      }
      if(clo.optionShowRoseFileNodeInfo()) {
        Utility::printRoseInfo(root);
      }
      cout << "STATUS: Generating reverse code."<<endl;
      Backstroke::CodeGenerator g(&clo);
      g.generateCode(root);
      cout << "STATUS: finished."<<endl;
    }
  } catch(char* str) {
    cerr << "Exception raised: " << str << endl;
    return 1;
  } catch(const char* str) {
    cerr << "Exception raised: " << str << endl;
    return 1;
  } catch(...) {
    cerr << "Unknown exception raised. Bailing out. " <<endl;
    return 1;
  }
  return 0;
}
