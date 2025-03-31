#include "Spdlog.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int User::display_response(const std::string &resp)
{
    try
    {
        // Parse the JSON response
        auto json_obj = nlohmann::json::parse(resp);


        spdlog::info("New Operation logging");
        spdlog::default_logger()->flush(); 

        // Check for errors in the response
        if (json_obj.find("error") != json_obj.end())
        {
            spdlog::error("Error detected: {}", json_obj.at("error").dump(4));
            std::cerr << "Error detected:\n"
                      << json_obj.at("error").dump(4) << '\n';
            return EXIT_FAILURE;
        }


        
        // Check if "result" exists in the JSON
        if (json_obj.find("result") != json_obj.end())
        {
            // Print the result if it exists
            spdlog::info("Result: {}", json_obj.at("result").dump(4));
            std::cout << "Response:\n"
                    << json_obj.at("result").dump(4) << '\n';
        }
        else
        {
            // Print the entire JSON if "result" is not found
            spdlog::warn("Result not found. Printing entire JSON: {}", json_obj.dump(4));
            std::cout << "Response (entire JSON):\n"
                    << json_obj.dump(4) << '\n';
        }



        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        // Log the exception
        spdlog::error("Failed to parse JSON: {}", e.what());
        std::cerr << "Failed to parse JSON: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
