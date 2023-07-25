#ifndef MYJSON_H
#define MYJSON_H
#include <myjson/Value.hpp>
#include <myjson/reader/Parser.hpp>
#include <string>

namespace myjson
{
	Value from_file(std::string filename);

	Value from_str(std::string json_string);
} // namespace myjson

#endif