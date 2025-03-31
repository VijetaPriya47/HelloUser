/**
 * @file main.cpp
 * @author Vijeta Priya (priyavijeta4@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <memory>
#include "User.hpp"

int main()
{
	User user = User();

	user.Start();

	user.display_mean_latencies();

	std::cout << "Exiting...\n";
}