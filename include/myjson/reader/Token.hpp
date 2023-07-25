#ifndef MYJSON_READER_TOKEN_HPP
#define MYJSON_READER_TOKEN_HPP
#include <string>
namespace myjson::reader
{
	enum class TokenType
	{
		True,
		False,
		Null,
		ObjectStart,
		ObjectEnd,
		CommaSep,
		ArrayStart,
		ArrayEnd,
		String,
		Number,
		ColonSep,
		UnkownKeyword,
		Error,
		Eof
	};
	class Token
	{
	private:
		TokenType m_type;
	public:
		Token();
		Token(TokenType);
		Token(TokenType, std::string);
		Token(TokenType, double);

		std::string error_type;
		std::string string_value;
		double double_value;
		TokenType type();
		std::string to_string();
	};

} // namespace myjson::reader


#endif