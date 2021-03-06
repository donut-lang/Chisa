/* coding: utf-8 */
/**
 * Donut
 *
 * Copyright 2012-2013, PSI
 */

#include <iostream>
#include <fstream>
#include <getopt.h>
#include <libgen.h>
#include <iomanip>
#include <cstdlib>
#include <exception>
#include <sstream>

#include <config.h>
#include <gperftools/profiler.h>

#include <cinamo/FileSystem.h>
#include <donut/Donut.hpp>
#include "SystemProvider.hpp"
#include "SystemObject.hpp"
#include "SystemPatron.hpp"

namespace donut_cli {
using namespace cinamo;
using namespace donut;

static const std::string TAG("Donut");

void usage(int argc, char* argv[]){
	static const std::string USAGE_TAB="    ";
	std::cout << "Usage: " << basename(argv[0]) << " [switches] [--] [programfile] [arguments]" << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--trace" << "set log level." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--verbose" << "set log level." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--debug"<<"set log level." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--warning"<<"set log level." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--info"<<"set log level." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--error"<<"set log level." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "--version"<<"output the version, then exit." << std::endl;
	std::cout << USAGE_TAB << std::left << std::setw(15) << "-h, --help"<<"output the help, then exit." << std::endl;
	exit(0);
}

void version(int argc, char* argv[]){
	std::cout << "donut - a programming language for time leapers!" << ": " <<" (build at " << __DATE__ << " " << __TIME__ << " )" << std::endl;
	exit(0);
}

const struct option ARG_OPTIONS[] = {
		{"trace", no_argument, nullptr, 1},
		{"verbose", no_argument, nullptr, 2},
		{"debug", no_argument, nullptr, 3},
		{"warning", no_argument, nullptr, 4},
		{"info", no_argument, nullptr, 5},
		{"error", no_argument, nullptr, 6},
		{"help", no_argument, nullptr, 7},
		{"version", no_argument, nullptr, 8},
		{nullptr,0, nullptr,0}
};

int runDonut(Logger& log, int argc, char** argv)
{
	std::string source;
	std::string filename;
	if(0 == argc){
		log.t(TAG, "Read from std::cin");
		source = ::cinamo::file::readAsString(std::cin);
		filename = "<CIN>";
	}else{
		log.t(TAG, "Read from file: %s", argv[0]);
		std::ifstream in(argv[0]);
		source = ::cinamo::file::readAsString(in);
		filename = argv[0];
	}
	log.t(TAG, "Source: \n%s", source.c_str());
	log.t(TAG, "Start executing...");

	{ //実行
		Handler<Donut> donut(new Donut(log, Handler<Patron>(new SystemPatron(argc, argv))));
		donut->bootstrap();
		Handler<Machine> machine = donut->queryMachine();
		Handler<Source> src = donut->parse( source, filename );
		Handler<Object> obj = machine->start( src );
	}
	return 0;
}

int main(int argc, char* argv[]){
	int indexptr=0;
	Logger::Level level = Logger::Level::WARN_;
	while(true) {
		int opt = getopt_long(argc, argv, "h", ARG_OPTIONS, &indexptr);
		if(opt < 0){
			break;
		}
		switch(opt)
		{
		case 1:
			level = Logger::TRACE_;
			break;
		case 2:
			level = Logger::VERBOSE_;
			break;
		case 3:
			level = Logger::DEBUG_;
			break;
		case 4:
			level = Logger::INFO_;
			break;
		case 5:
			level = Logger::WARN_;
			break;
		case 6:
			level = Logger::ERROR_;
			break;
		case 7:
		case 'h':
			usage(argc, argv);
            return 0;
		case 8:
			version(argc, argv);
            return 0;
        default:
            usage(argc, argv);
            return 0;
		}
	}

	Logger log(std::cout, level);
	log.t(TAG, "Logger created. Level: %d", level);

	return runDonut(log, argc-optind, &argv[optind]);
}

}

int main(int argc, char* argv[]){
#ifdef PROF
    ProfilerStart("prof.out");
#endif
    try{
		const int resultCode = donut_cli::main(argc, argv);
		return resultCode;
	} catch (donut::DonutException& e){
		std::cout << "Donut Exception catch: " << e.what() << std::endl;
		return -1;
	} catch (cinamo::Exception& e){
		std::cout << "Tarte Exception catch: " << e.what() << std::endl;
		return -1;
	} catch (std::exception& ex){
		std::cout << "Default Exception catch: " << ex.what() << std::endl;
		return -2;
	} catch(...){
		std::cout << "[FIXME] Unkown exception caught..." << std::endl;
		return -3;
	}
#ifdef PROF
    ProfilerStop();
#endif
}
