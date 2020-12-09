#include "ReversePolish.h"

int main()
{
	char expression[80];
	

	std::cout << "입력: ";
	std::cin.getline(expression, 80);

	Polish(expression);
	// 유효하지 않은 식인 경우
	if (polish_result[0] == '\0')
	{
		exit(1);
	}

	int result{ Execute() };
	std::cout << "변환: " << polish_result << '\n';
	std::cout << "결과: " << result << '\n';
}
