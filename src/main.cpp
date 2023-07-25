#include <iostream>
#include <myjson/json.hpp>
#include <myjson/reader/Scanner.hpp>
#include <myjson/reader/Parser.hpp>
#include <iostream>
using namespace std;
using namespace myjson::reader;

using myjson::Value;
int main()
{
	// Scanner scanner("test.json");
	// Token token;
	// while(token.type() != TokenType::Eof)
	// {
	// 	token = scanner.next_token();
	// 	cout << token.to_string() << endl;
	// }

	myjson::reader::Parser parser("test.json");
	try
	{
		auto value= parser.parse_json();
		cout <<  value.to_string() << endl;
	
	}
	catch( myjson::reader::Parser::ParseException &e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}