#include "MiniCalculator_ver.C.h"

int main()
{
	while (true)
	{
		Input();
		token = NextToken();
		if (token.tokenKind == TokenKind::EndOfToken)
		{
			break;
		}
		Statement();
	}
}