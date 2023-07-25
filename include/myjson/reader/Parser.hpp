#ifndef MYJSON_READER_PARSER_HPP
# define MYJSON_READER_PARSER_HPP

#include <string>
#include <myjson/Value.hpp>
#include <myjson/reader/Scanner.hpp>
#include <exception>
#include <vector>
#include <map>
namespace myjson::reader
{
	class Parser
	{
		
	private:
		Scanner m_scanner;
		Token curr_token;
		Value m_json;

	bool match_token(TokenType);
	Token consume_token(TokenType);

	Value parse_value();
	std::vector<Value> parse_array();
	std::map<std::string, Value> parse_object();
	std::pair<std::string, Value> parse_member();

	public:
		Parser(std::string filename);
		Value parse_json();

		class ParseException : std::exception
		{
		private:
			std::string message;
			std::string error_type;
			Token 		token;
			void construct_message()
			{
				message = error_type;

			}
		public:
			ParseException(Token token, std::string error_type, std::string detail)
			{
				this->token = token;
				this->error_type = error_type;
				message = error_type + ": " + detail;
			}
			const char* what() const noexcept
			{
				return message.c_str();
			}
		};
	};
	

	
} // namespace myjson::reader::Parser

#endif