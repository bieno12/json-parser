#include <myjson/reader/Parser.hpp>
#include <iostream>
using namespace myjson::reader;
using myjson::Value;
Parser::Parser(std::string filename) : m_scanner(filename)
{
}

bool Parser::match_token(TokenType type)
{
	return  (curr_token.type() == type);
}
Token Parser::consume_token(TokenType type)
{
	Token temp = curr_token;
	std::cout << "consuming token: " << curr_token.to_string() << std::endl;
	if(match_token(type))
		curr_token = m_scanner.next_token();
	else
		throw ParseException(curr_token, "UnexpectedToken", "expected: " + Token(type).to_string() + " but found " + curr_token.to_string());
	return temp;
}

Value Parser::parse_json()
{
	curr_token = m_scanner.next_token();
	if(curr_token.type() == TokenType::Eof)
		return Value();
	m_json = parse_value();
	return m_json;
}


Value Parser::parse_value()
{
	if(match_token(TokenType::True))
	{
		consume_token(TokenType::True);
		return Value(true);
	}
	else if (match_token(TokenType::False))
	{
		consume_token(TokenType::False);
		return Value(false);
	}
	else if (match_token(TokenType::Null))
	{
		consume_token(TokenType::Null);
		return Value();
	}
	else if (match_token(TokenType::Number))
	{
		Value num(curr_token.double_value);
		consume_token(TokenType::Number);
		return num;
	}
	else if (match_token(TokenType::String))
	{
		Value str(curr_token.string_value);
		consume_token(TokenType::String);
		return str;
	}
	else if (match_token(TokenType::ArrayStart))
	{
		return parse_array();
	}
	else if (match_token(TokenType::ObjectStart))
	{
		return parse_object();
	}

	throw ParseException(curr_token, "UnexpectedToken", "Expected a value but found " + curr_token.to_string());
}


std::vector<Value> Parser::parse_array()
{
	std::vector<Value> array;
	consume_token(TokenType::ArrayStart);
	if (match_token(TokenType::ArrayEnd))
	{
		consume_token(TokenType::ArrayEnd);
		return array;
	}
	//parse_element
	Value element = parse_value();
	array.push_back(element);

	while(match_token(TokenType::CommaSep))
	{
		consume_token(TokenType::CommaSep);
		Value element = parse_value();
		array.push_back(element);
	}
	consume_token(TokenType::ArrayEnd);
	return array;
}

std::map<std::string, Value> Parser::parse_object()
{
	std::map<std::string, Value> object;
	consume_token(TokenType::ObjectStart);

	if(match_token(TokenType::ArrayEnd))
	{
		consume_token(TokenType::ArrayEnd);
		return object;
	}
	object.insert(parse_member());
	while(match_token(TokenType::CommaSep))
	{
		consume_token(TokenType::CommaSep);
		object.insert(parse_member());
	}
	consume_token(TokenType::ObjectEnd);
	return object;
}

std::pair<std::string, Value> Parser::parse_member()
{
	std::string name;
	name = consume_token(TokenType::String).string_value;
	consume_token(TokenType::ColonSep);
	return std::make_pair(name, parse_value());
}