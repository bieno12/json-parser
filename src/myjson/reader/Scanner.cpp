#include <myjson/reader/Scanner.hpp>
#include <sstream>

using myjson::reader::Scanner;
using myjson::reader::Token;
using myjson::reader::TokenType;

Scanner::Scanner(std::string filename)
{
	ss = std::ifstream(filename);
	if (!ss.is_open())
		throw std::runtime_error("Couldn't open file :" + filename);

}
// Scanner Scanner::from_json_string(std::string json_string)
// {
	
// 	return scanner;
// }


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
// 	ColonSep,
// 	UnkownKeyword,
// 	Error,
// 	Eof
// };
#include <iostream>
using namespace std;

Token Scanner::next_token()
{

	int state = ENTRY_STATE;
	std::string buffer;
	char ch = ss.get();
	Token token;

	while (state != ENTRY_STATE || !(ch == EOF))
	{
		switch (state)
		{
		case ENTRY_STATE:
		{
			token = Token(TokenType::String);
			entry_state(ch, state, buffer, token);
		}
		break;
		case OBJECT_START_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::ObjectStart, "{");
		}
		break;
		case OBJECT_END_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::ObjectEnd, "}");
		}
		break;
		case COMMA_SEP_SATE:
		{
			state = EMMIT_TOKEN_STATE;

			token = Token(TokenType::CommaSep, ",");
		}
		break;
		case ARRAY_START_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::ArrayStart, "[");
		}
		break;
		case ARRAY_END_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::ArrayEnd, "]");
		}
		break;
		case COLON_SEP_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::ColonSep, ":");
		}
		break;
		case STRING_LETIRAL_STATE:
		{
			string_letiral_state(ch, state, buffer, token);
		}
		break;
		case ESCAPE_STATE:
		{
			escape_state(ch, state, buffer, token);
			state = STRING_LETIRAL_STATE;
		}
		break;
		case INTEGER_STATE:
		{
			token = Token(TokenType::Number);
			integer_state(ch, state, buffer, token);
		}
		break;
		case FRACTION_STATE:
		{
			token = Token(TokenType::Number);
			fraction_state(ch, state, buffer, token);
		}
		break;
		case EXPONENT_STATE:
		{
			token = Token(TokenType::Number);
			exponent_state(ch, state, buffer, token);
		}
		break;
		case KEYWORD_STATE:
		{
			keyword_state(ch, state, buffer, token);
		}
		break;
		case KEYWORD_TRUE_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::True, buffer);
		}
		break;
		case KEYWORD_FALSE_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::False, buffer);
		}
		break;
		case KEYWORD_NULL_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::Null, buffer);
		}
		break;
		case UNKOWN_KEYWORD_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::UnkownKeyword, buffer);
		}
		break;
		case ERROR_STATE:
		{
			state = EMMIT_TOKEN_STATE;
			token = Token(TokenType::Error, buffer);
		}
		break;
		case EMMIT_TOKEN_STATE:
		{
			return token;
		}
		break;
		default:
			break;
		}
	}
	return Token(TokenType::Eof);
}
void Scanner::entry_state(char &ch, int &state, std::string &buffer, Token &token)
{

	(void)token;
	(void)buffer;
	if (ch == '{')
	{
		state = OBJECT_START_STATE;
	}
	else if (ch == '}')
	{
		state = OBJECT_END_STATE;
	}
	else if (ch == ',')
	{
		state = COMMA_SEP_SATE;
	}
	else if (ch == '[')
	{
		state = ARRAY_START_STATE;
	}
	else if (ch == ']')
	{
		state = ARRAY_END_STATE;
	}
	else if (ch == '"')
	{
		state = STRING_LETIRAL_STATE;
	}
	else if (ch == ':')
	{
		state = COLON_SEP_STATE;
	}
	else if (isdigit(ch) || ch == '-')
	{
		state = INTEGER_STATE;
	}
	else if (ch == '_' || isalpha(ch))
	{
		state = KEYWORD_STATE;
	}
	else if (isspace(ch))
	{
		ch = ss.get();
		state = ENTRY_STATE;
	}
	else
	{
		state = EMMIT_TOKEN_STATE;
		token = Token(TokenType::Error, std::string(1, ch));
		token.error_type = "UnkownCharacter";
	}
}

void Scanner::keyword_state(char &ch, int &state, std::string &buffer, Token &token)
{

	(void)token;
	buffer.push_back(ch);
	while (!(ch == EOF))
	{
		ch = ss.get();
		if (ch == '_' || isalnum(ch))
			buffer.push_back(ch);
		else
		{
			ss.putback(ch);
			break;
		}
	}
	if (buffer == "true")
		state = KEYWORD_TRUE_STATE;
	else if (buffer == "false")
		state = KEYWORD_FALSE_STATE;
	else if (buffer == "null")
		state = KEYWORD_NULL_STATE;
	else
		state = UNKOWN_KEYWORD_STATE;
}

void Scanner::string_letiral_state(char &ch, int &state, std::string &buffer, Token &token)
{

	ch = ss.get();
	while (!(ch == EOF))
	{
		if (ch == '"')
		{
			state = EMMIT_TOKEN_STATE;
			token.string_value = buffer;
			return;
		}
		else if (ch == '\\')
		{
			state = ESCAPE_STATE;
			return;
		}
		else
			buffer.push_back(ch);
		ch = ss.get();
	}
	state = EMMIT_TOKEN_STATE;
	token = Token(TokenType::Error, buffer);
	token.error_type = "UnterminatedStringLetiral";
}

void Scanner::escape_state(char &ch, int &state, std::string &buffer, Token &token)
{

	(void)token;
	state = STRING_LETIRAL_STATE;
	ch = ss.get();
	if (ch == '"' || (ch == '\\'))
	{
		buffer.push_back(ch);
		return;
	}
	if (ch == '/')
	{
		buffer.push_back('/');
		return;
	}
	if (ch == 'b')
	{
		buffer.push_back('\b');
		return;
	}
	if (ch == 'f')
	{
		buffer.push_back('\f');
		return;
	}
	if (ch == 'n')
	{
		buffer.push_back('\n');
		return;
	}
	if (ch == 'r')
	{
		buffer.push_back('\r');
		return;
	}
	if (ch == 't')
	{
		buffer.push_back('\t');
		return;
	}
	if (ch == 'u')
	{
		std::string digits;
		int i = 0;
		while (i++ < 4)
		{
			ch = ss.get();
			if (isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))
				digits.push_back(ch);
			else
			{
				ss.putback(ch);
				while (!digits.empty())
				{
					ss.putback(digits.back());
					digits.pop_back();
				}
				buffer += "\\u";

				token = Token(TokenType::Error);
				token.error_type = "InvalidUnicodeEscape";
				return;
			}
		}
		buffer.push_back('@');
	}
	buffer += std::string("\\") + ch;
	token = Token(TokenType::Error);
	token.error_type = "UnknownEscapeCharacter";
	return;
}

void Scanner::integer_state(char &ch, int &state, std::string &buffer, Token &token)
{

	buffer.push_back(ch);
	ch = ss.get();
	while (!(ch == EOF))
	{
		if (isdigit(ch))
			buffer.push_back(ch);
		else
		{
			ss.putback(ch);
			break;
		}
		ch = ss.get();
	}
	// check if it has leading zero
	if (buffer.size() == 1)
	{
		if (buffer.front() == '-')
		{
			token = Token(TokenType::Error);
			token.error_type = "InvalidNumber";
		}
	}
	else
	{

		std::string digits = buffer.substr(buffer.front() == '-');
		if (digits.size() > 1 && digits.front() == '0')
		{
			token = Token(TokenType::Error);
			token.error_type = "InvalidNumber";
		}
	}

	// fraction dot
	ch = ss.get();
	if (ch == '.')
	{
		state = FRACTION_STATE;
	}
	else if (ch == 'e' || ch == 'E')
	{
		state = EXPONENT_STATE;
	}
	else
	{
		ss.putback(ch);
		state = EMMIT_TOKEN_STATE;
		token.string_value = buffer;
		if (token.type() == TokenType::Number)
			token.double_value = std::stod(buffer);
	}

	// // check if is notvalid
	// if (buffer.back() == '.')
	// 	is_valid = false;

	// parse exponent
	// if (!(ch == EOF))
	// {
	// 	ch = ss.get();
	// 	if (ch == 'E' || ch == 'e')
	// 		parse_exponent(ch, state, buffer, token);
	// 	else
	// 		ss.putback(ch);
	// }

	// return error token in case number is invalid
}

void Scanner::fraction_state(char &ch, int &state, std::string &buffer, Token &token)
{

	// fraction digits
	buffer.push_back(ch);
	ch = ss.get();
	while (!(ch == EOF))
	{
		if (isdigit(ch))
			buffer.push_back(ch);
		else
		{
			ss.putback(ch);
			break;
		}
		ch = ss.get();
	}
	// check if valid fraction
	if (buffer.back() == '.')
	{
		token = Token(TokenType::Error, buffer);
		token.error_type = "InvalidNumber";
	}

	// change state
	ch = ss.get();
	if (ch == 'e' || ch == 'E')
	{
		state = EXPONENT_STATE;
	}
	else
	{
		ss.putback(ch);
		state = EMMIT_TOKEN_STATE;
		if (token.type() == TokenType::Number)
			token.double_value = std::stod(buffer);
		token.string_value = buffer;
	}
}

void Scanner::exponent_state(char &ch, int &state, std::string &buffer, Token &token)
{

	buffer.push_back(ch);
	ch = ss.get();
	if (ch == '-' || ch == '+')
		buffer.push_back(ch);
	else
		ss.putback(ch);
	// extract at least one digit
	ch = ss.get();
	while (!(ch == EOF))
	{
		if (isdigit(ch))
			buffer.push_back(ch);
		else
		{
			ss.putback(ch);
			break;
		}
		ch = ss.get();
	}
	if (!isdigit(buffer.back()))
	{
		token = Token(TokenType::Error, buffer);
		token.error_type = "InvalidNumber";
	}
	// emit token
	state = EMMIT_TOKEN_STATE;
	if (token.type() == TokenType::Number)
		token.double_value = std::stod(buffer);
	token.string_value = buffer;
}
