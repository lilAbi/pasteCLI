
#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int argc, char **argv) {
    //add command line instructions
    description.add_options()("help", "See available commands");
    description.add_options()("key", boost::program_options::value<std::string>(), "Developer Key\n");
    description.add_options()("title",boost::program_options::value< std::vector<std::string> >()->multitoken(), "Title\n");
    description.add_options()("text", boost::program_options::value< std::vector<std::string> >()->multitoken(), "Text Body\n");
    description.add_options()("mode", boost::program_options::value<std::string>()->default_value("0"), "0 = public\n1 = unlisted\n2 = private\n");
    description.add_options()("format",boost::program_options::value<std::string>(), "Ending File Type\n");
    description.add_options()("expire",boost::program_options::value<std::string>()->default_value("N"), "Set the expiration date:\n"
                                                                                                         "N = Never\n"
                                                                                                         "10M = 10 Minutes\n"
                                                                                                         "1H = 1 Hour\n"
                                                                                                         "1D = 1 Day\n"
                                                                                                         "1W = 1 Week\n"
                                                                                                         "2W = 2 Weeks\n"
                                                                                                         "1M = 1 Month\n"
                                                                                                         "6M = 6 Months\n"
                                                                                                         "1Y = 1 Year  \n");

    //parse argv and store arguments into container
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), variablesMap);
    boost::program_options::notify(variablesMap);
}