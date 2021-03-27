#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_EXCEPTIONS_HPP
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_EXCEPTIONS_HPP

#include <exception>

namespace libraries::exceptions {

	class mission_name_not_found_in_analyzer_exception : public std::exception {
	public:
		mission_name_not_found_in_analyzer_exception(std::string &&mission_name) :
				msg("Mission name \"" + mission_name + "\" not found in json_parser analyzer.") {}

		[[nodiscard]] const char *what() const noexcept override {
			return msg.c_str();
		}

	private:
		std::string msg;
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_EXCEPTIONS_HPP