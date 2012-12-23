/**
 * Donut
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <getopt.h>
#include <libgen.h>
#include <iomanip>
#include <cstdlib>
#include <exception>
#include <sstream>
#include <tarte/Logger.h>
#include <tarte/Exception.h>
#include "../../donut/Donut.h"

namespace donut {
using namespace tarte;

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
	std::cout << "chisa::donut" << ": " <<" (build at " << __DATE__ << " " << __TIME__ << " )" << std::endl;
	exit(0);
}

const struct option ARG_OPTIONS[] = {
		{"trace", no_argument, 0, 1},
		{"verbose", no_argument, 0, 2},
		{"debug", no_argument, 0, 3},
		{"warning", no_argument, 0, 4},
		{"info", no_argument, 0, 5},
		{"error", no_argument, 0, 6},
		{"help", no_argument, 0, 7},
		{"version", no_argument, 0, 8},
		{0,0,0,0}
};

std::string readAll(std::istream& stream) {
	std::stringstream source_;
	std::string buf;
	while(std::cin && std::getline(stream, buf)){
		while(buf.size() > 0 && (buf.at(buf.size()-1)=='\r' || buf.at(buf.size()-1)=='\n')){
			buf=buf.substr(0, buf.size()-1);
		}
		while(buf.size() > 0 && (buf.at(0)=='\r' || buf.at(0)=='\n')){
			buf=buf.substr(1);
		}
		source_ << buf << std::endl;
	}
	return source_.str();
}

int main(int argc, char* argv[]){

	int indexptr=0;
	Logger::Level level = Logger::Level::WARN_;
	while(1){
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
			break;
		case 8:
			version(argc, argv);
			break;
		case '?':
			exit(0);
			break;
		}
	}

	Logger log(std::cout, level);
	log.t(TAG, "Logger created. Level: %d", level);

	std::string source;
	if(optind == argc){
		log.t(TAG, "Read from std::cin");
		source = readAll(std::cin);
	}else{
		log.t(TAG, "Read from file: %s", argv[optind]);
		std::ifstream in(argv[optind]);
		source = readAll(in);
	}
	log.t(TAG, "Source: \n%s", source.c_str());
	log.t(TAG, "Start executing...");

	{ //実行
		Handler<Donut> donut(new Donut(log));
		donut->bootstrap();
		Handler<Machine> machine = donut->queryMachine();
		Handler<Source> src = donut->parse( source, "<CIN>" );
		Handler<Object> obj = machine->start( src );

		std::cout << obj->toString( donut->heap() ) << std::endl;
	}

	return 0;
}

}

int main(int argc, char* argv[]){
	try{
		const int resultCode = donut::main(argc, argv);
		return resultCode;
	} catch (donut::DonutException& e){
		std::cout << "Donut Exception catch: " << e.what() << std::endl;
		return -1;
	} catch (tarte::Exception& e){
		std::cout << "Tarte Exception catch: " << e.what() << std::endl;
		return -1;
	} catch (std::exception& ex){
		std::cout << "Default Exception catch: " << ex.what() << std::endl;
		return -2;
	} catch(...){
		std::cout << "[FIXME] Unkown exception caught..." << std::endl;
		return -3;
	}
}
