#include <myjson/json.hpp>
using myjson::reader::Scanner; 

myjson::Value myjson::from_file(std::string filename)
{
	Scanner scanner(filename);
	(void) scanner;
	return myjson::Value();
}

// myjson::Value myjson::from_str(std::string json_string)
// {

// }