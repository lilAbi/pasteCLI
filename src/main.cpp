#include "core/App.h"
#include "core/CommandLineParser.h"

//developer key dIrhAc_e1amQpJ6xtgzr1ugG38AEDty3

int main(int argc, char* argv[]) {
    CommandLineParser parser(argc, argv);

    App app(parser.getVarMap(), parser.getOptionDescription());

    app.Execute();

    return 0;
}
