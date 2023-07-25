#include <myjson/reader/Token.hpp>
#include <sstream>
using Token = myjson::reader::Token;
using TokenType = myjson::reader::TokenType;

Token::Token()
{
	m_type = TokenType::Error;
}

Token::Token(TokenType type)
{
	if (type == TokenType::Error)
		error_type = "Error";
	m_type = type;
}
Token::Token(TokenType type, std::string str)
{
	if (type == TokenType::Error)
		error_type = "Error";
	m_type = type;
	string_value = str;
}

Token::Token(TokenType type, double num)
{
	if (type == TokenType::Error)
		error_type = "Error";
	m_type = type;
	double_value = num;
}

myjson::reader::TokenType Token::type()
{
	return m_type;
}

// String,
// Number,
// ColonSep,

std::string Token::to_string()
{
	std::stringstream ss;
	switch (m_type)
	{
	case TokenType::True:
		ss << "TokenType<True>";
		break;
	case TokenType::False:
		ss << "TokenType<False>";

		break;
	case TokenType::Null:
		ss << "TokenType<Null>";

		break;
	case TokenType::ObjectStart:
		ss << "TokenType<ObjectStart>";

		break;
	case TokenType::ObjectEnd:
		ss << "TokenType<ObjectEnd>";

		break;
	case TokenType::ArrayStart:
		ss << "TokenType<ArrayStart>";

		break;
	case TokenType::ArrayEnd:
		ss << "TokenType<ArrayEnd>";

		break;
	case TokenType::CommaSep:
		ss << "TokenType<CommaSep>";

		break;
	case TokenType::ColonSep:
		ss << "TokenType<ColonSep>";

		break;
	case TokenType::String:
		ss << "TokenType<String>(\"" << string_value << "\")";

		break;
	case TokenType::Number:
		ss << "TokenType<Number>(" << double_value << ")";

		break;
	case TokenType::UnkownKeyword:
		ss << "TokenType<UnkownKeyword>(" << string_value << ")";

		break;
	case TokenType::Error:
		ss << "TokenType<" << error_type << ">(\"" << string_value << "\")";

		break;
	case TokenType::Eof:
		ss << "TokenType<Eof>";

		break;
	default:
		break;
	}
	return ss.str();
}