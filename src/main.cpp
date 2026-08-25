#include <iostream>
#include <optional>
#include <pjh_json/json.hpp>
#include <pjh_platform.hpp>
#include <pjh_result.hpp>
#include <string>

#include "pjh_platform/file_watcher.hpp"

int main()
{
    auto pesult = pjh::result::Result<std::string, std::nullopt_t>::Ok(
        "Hello World from PJH_RESULT!");
    std::cout << pesult.unwrap() << std::endl;

    pjh::json::Json pson("Hello World from PJH_JSON!");
    std::cout << pson.as_string() << std::endl;

    pjh::platform::FileEventKind::Created;
    std::cout << "Hello World!" << std::endl;
}