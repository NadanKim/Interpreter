#include "Tokenizer.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		exit(1);
	}

	ifs.open(argv[1]);
	if (!ifs.is_open())
	{
		exit(1);
	}

	InitializeCharTypeTable();

	std::cout << std::setw(5) << "text" << std::setw(17) << "kind" << std::setw(7) << "intVal" << '\n';

	Token token = NextToken();
	while (token.tokenKind != TokenKind::EndOfToken)
	{
		std::cout << std::setw(5) << token.text <<
			std::setw(17) << TokenKindToString(token.tokenKind) <<
			std::setw(7) << token.intValue << '\n';

		token = NextToken();
	}
}