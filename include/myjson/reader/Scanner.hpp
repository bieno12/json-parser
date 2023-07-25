#ifndef MYJSON_READER_SCANNER_HPP
# define MYJSON_READER_SCANNER_HPP
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <myjson/reader/Token.hpp>
#include <stdexcept>
namespace myjson::reader
{
	// enum class TokenType
	// {
	// 	True,
	// 	False,
	// 	Null,
	// 	ObjectStart,
	// 	ObjectEnd,
	// 	CommaSep,
	// 	ArrayStart,
	// 	ArrayEnd,
	// 	String,
	// 	Number,
	// 	UnkownKeyword,
	// 	Error,
	// 	Eof
	// };

	class Scanner
	{
		enum State
		{
			ENTRY_STATE,
			KEYWORD_STATE,
			OBJECT_START_STATE,
			OBJECT_END_STATE,
			COMMA_SEP_SATE,
			COLON_SEP_STATE,
			ARRAY_START_STATE,
			ARRAY_END_STATE,
			STRING_LETIRAL_STATE,
			ESCAPE_STATE,
			INTEGER_STATE,
			FRACTION_STATE,
			EXPONENT_STATE,
			KEYWORD_TRUE_STATE,
			KEYWORD_FALSE_STATE,
			KEYWORD_NULL_STATE,
			UNKOWN_KEYWORD_STATE,
			ERROR_STATE,
			EMMIT_TOKEN_STATE
		};
	public:
		Scanner(std::string filename);
		Scanner();
		Token next_token();
		static Scanner from_json_string(std::string json_string);
	private:
		std::ifstream ss;
		Token current_token;
	
		void entry_state(char &ch, int &state, std::string &buffer, Token &token);
		void keyword_state(char &ch, int &state, std::string &buffer, Token &token);
		void integer_state(char &ch, int &state, std::string &buffer, Token &token);
		void exponent_state(char &ch, int &state, std::string &buffer, Token &token);
		void fraction_state(char &ch, int &state, std::string &buffer, Token &token);
		void string_letiral_state(char &ch, int &state, std::string &buffer, Token &token);
		void escape_state(char &ch, int &state, std::string &buffer, Token &token);

	};
} // namespace myjson::reader::Scanner


#endif