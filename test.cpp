#include <iostream>
#include <cmath>
#include <vector>

int main() {
	std::vector<int> xPos;
	std::vector<int> yPos;
	for (int i = 0; i < 400; ++i) {
		// std::cout << i << "\t" << i * 2.5 << "\t" << static_cast<int>(200 * exp(-0.025 * i * 2.5)) << "\t" << 20 * exp(-0.025 * i * 2.5)  << std::endl;
		xPos.push_back(i);
		yPos.push_back(static_cast<int>(200 * exp(-0.025 * i * 2.5)));
	}
	for (int i = 0; i < xPos.size(); ++i) {
		std::cout << xPos[i] << "\t" << yPos[i] << std::endl;
	}
	return 0;
}
